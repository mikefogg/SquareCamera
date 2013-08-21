#import "ComMfoggSquarecameraView.h"
#import "ComMfoggSquarecameraViewProxy.h"
#import <AVFoundation/AVFoundation.h>
#import <ImageIO/ImageIO.h>
#import <CoreMedia/CoreMedia.h>


@implementation ComMfoggSquarecameraView

// original via github.com/mikefogg/SquareCamera

// http://developer.appcelerator.com/question/154132/titanium-custom-camera-module-iphone#comment-185903


@synthesize captureSession = _captureSession;
@synthesize prevLayer = _prevLayer;
@synthesize stillImageOutput = _stillImageOutput;
@synthesize stillImage = _stillImage;
@synthesize captureDevice = _captureDevice;
@synthesize flashOn = _flashOn;
@synthesize isUsingFrontFacingCamera = _isUsingFrontFacingCamera;

  /// used for KVO observation of the @"capturingStillImage" property to perform flash bulb animation
static const NSString *AVCaptureStillImageIsCapturingStillImageContext = @"AVCaptureStillImageIsCapturingStillImageContext";


- (void) dealloc
{
    [self teardownAVCapture];

    self.prevLayer = nil;
    self.stillImage = nil;
    self.stillImageOutput = nil;
    self.captureDevice = nil;
    
    RELEASE_TO_NIL(square);
        
    [super dealloc];
}

-(void)initializeState
{
    [super initializeState];
    
    self.prevLayer = nil;
    self.stillImage = nil;
    self.stillImageOutput = nil;
    self.captureDevice = nil;
    self.isUsingFrontFacingCamera = NO;
}

-(void)frameSizeChanged:(CGRect)frame bounds:(CGRect)bounds
{
    // This is initializing the square view
    [TiUtils setView:self.square positionRect:bounds];
}

- (void)turnFlashOn:(id)args
{
    if([self.captureDevice lockForConfiguration:true]){
        [self.captureDevice setFlashMode:AVCaptureFlashModeOn];
        self.flashOn = YES;  
        [self.captureDevice lockForConfiguration:false];
        
        [self.proxy fireEvent:@"onFlashOn"];
    };
};

- (void)turnFlashOff:(id)args
{
    if([self.captureDevice lockForConfiguration:true]){
        [self.captureDevice setFlashMode:AVCaptureFlashModeOff];
        self.flashOn = NO;  
        [self.captureDevice lockForConfiguration:false];
        
        [self.proxy fireEvent:@"onFlashOff"];
    };
};

// utility routine to display error aleart if takePicture fails
- (void)displayErrorOnMainQueue:(NSError *)error withMessage:(NSString *)message
{
    dispatch_async(dispatch_get_main_queue(), ^(void) {
        UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:[NSString stringWithFormat:@"%@ (%d)", message, (int)[error code]]
                                                            message:[error localizedDescription]
                                                           delegate:nil 
                                                  cancelButtonTitle:@"Dismiss" 
                                                  otherButtonTitles:nil];
        [alertView show];
        [alertView release];
    });
}

- (void)takePhoto:(id)args
{

    NSLog(@"[INFO] takePhoto ... ");

    AVCaptureConnection *stillImageConnection = nil;
        
	for (AVCaptureConnection *connection in self.stillImageOutput.connections)
	{
		for (AVCaptureInputPort *port in [connection inputPorts])
		{
			if ([[port mediaType] isEqual:AVMediaTypeVideo] )
			{
				stillImageConnection = connection;
				break;
			}
		}
		if (stillImageConnection) { break; }
	}
    
    [self.stillImageOutput captureStillImageAsynchronouslyFromConnection:stillImageConnection completionHandler: ^(CMSampleBufferRef imageSampleBuffer, NSError *error)
        { 

            // Not using these yet, but interesting nonetheless.
            // Could send them back with the event, for extra pudding.

            CFDictionaryRef exifAttachments = CMGetAttachment(imageSampleBuffer, kCGImagePropertyExifDictionary, NULL);
            if (exifAttachments) {
                NSLog(@"[INFO] imageSampleBuffer Exif attachments: %@", exifAttachments);
            } else { 
                NSLog(@"[INFO] No imageSampleBuffer Exif attachments");
            }


            NSData *imageData = [AVCaptureStillImageOutput jpegStillImageNSDataRepresentation:imageSampleBuffer];    

            UIImage *image = [[UIImage alloc] initWithData:imageData];
            
            CGSize size = image.size;  
            CGRect cropRect = self.stillImage.frame;  
            CGRect customImageRect = CGRectMake(
                                                -((((cropRect.size.width/size.width)*size.height)-cropRect.size.height)/2),
                                                0,
                                                ((cropRect.size.width/size.width)*size.height),
                                                cropRect.size.width);
            
            UIGraphicsBeginImageContext(cropRect.size);
            CGContextRef context = UIGraphicsGetCurrentContext();  
            
            CGContextScaleCTM(context, 1.0, -1.0);  
            CGContextRotateCTM(context, -M_PI/2);  
            
            if(self.isUsingFrontFacingCamera){
                CGContextScaleCTM(context, 1.0, -1.0);
            }
            
            CGContextDrawImage(context, customImageRect,
                               image.CGImage);
            
            UIImage *croppedImage = UIGraphicsGetImageFromCurrentImageContext();  
            UIGraphicsEndImageContext();
            
            // don't set the viewer to the new photo! 
            //self.stillImage.image = croppedImage;
            
            
            TiBlob *imageBlob = [[TiBlob alloc] initWithImage:croppedImage]; // maybe try image here 
            NSDictionary *event = [NSDictionary dictionaryWithObject:imageBlob forKey:@"media"];
            
            // HURRAH! 
            [self.proxy fireEvent:@"success" withObject:event];


           // [imageBlob release];
           // [image release];
           // [croppedImage release];
            
            // keep it running for now - since we didn't replace it with an image
            // [self.captureSession stopRunning];
  
            // what are we doing with the potential error value? 
            // proably should be sending an event if it's not nil... or something. 


     }];
}

-(void)switchCamera:(id)args
{
    AVCaptureDevicePosition desiredPosition;
    if (self.isUsingFrontFacingCamera)
    desiredPosition = AVCaptureDevicePositionBack;
    else
    desiredPosition = AVCaptureDevicePositionFront;

    for (AVCaptureDevice *d in [AVCaptureDevice devicesWithMediaType:AVMediaTypeVideo]) {
        if ([d position] == desiredPosition) {
            [[self.prevLayer session] beginConfiguration];
            AVCaptureDeviceInput *input = [AVCaptureDeviceInput deviceInputWithDevice:d error:nil];
            for (AVCaptureInput *oldInput in [[self.prevLayer session] inputs]) {
                [[self.prevLayer session] removeInput:oldInput];
            }
            [[self.prevLayer session] addInput:input];
            [[self.prevLayer session] commitConfiguration];
            break;
        }
    }
    self.isUsingFrontFacingCamera = !self.isUsingFrontFacingCamera;
    
    [self.proxy fireEvent:@"onSwitchCamera"];
}

- (void)captureOutput:(AVCaptureOutput *)captureOutput 
didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer 
	   fromConnection:(AVCaptureConnection *)connection 
{ 
    /*
    // from https://developer.apple.com/library/ios/qa/qa1702/_index.html
    // Create a UIImage from the sample buffer data
    UIImage *image = [self imageFromSampleBuffer:sampleBuffer];

     < Add your code here that uses the image >

    // afaik this is not longer needed, nor the imageFromSampleBuffer method 
    */

}

-(UIView*)square
{   
    if (square == nil) {
        
        square = [[UIView alloc] initWithFrame:[self frame]];
        [self addSubview:square]; 
        


        self.stillImage = [[UIImageView alloc] init];
        self.stillImage.frame = [square bounds];
        [self addSubview:self.stillImage];


        
        if ([UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypeCamera]) {
            // If camera is avaialble
        
            
             
            // is this even needed? 
            //CALayer *viewLayer = self.square.layer;
            //NSLog(@"viewLayer = %@", viewLayer);
  

            self.captureSession = [[AVCaptureSession alloc] init];
            self.captureSession.sessionPreset = AVCaptureSessionPresetMedium;
 

            self.prevLayer = [[AVCaptureVideoPreviewLayer alloc] initWithSession:self.captureSession];
            self.prevLayer.frame = self.square.bounds;
            self.prevLayer.videoGravity = AVLayerVideoGravityResizeAspectFill;
            [self.square.layer addSublayer:self.prevLayer];
            

            self.captureDevice = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];
            
            NSError *error = nil;
            AVCaptureDeviceInput *input = [AVCaptureDeviceInput deviceInputWithDevice:self.captureDevice error:&error];
            if (!input) {
                // Handle the error appropriately.
                NSLog(@"ERROR: trying to open camera: %@", error);
            }

            AVCaptureVideoDataOutput *videoDataOutput = [[[AVCaptureVideoDataOutput alloc] init] autorelease];
            [videoDataOutput setAlwaysDiscardsLateVideoFrames:YES]; // discard if the data output queue is blocked (as we process the still image)


            videoDataOutputQueue = dispatch_queue_create("videoDataOutputQueue", DISPATCH_QUEUE_SERIAL);
            [videoDataOutput setSampleBufferDelegate:self queue:videoDataOutputQueue];
            // ??? dispatch_release(videoDataOutputQueue);

            /////////////////////////////////////////////////////////////
            // OUTPUT #1: Still Image
            /////////////////////////////////////////////////////////////
            // Add an output object to our session so we can get a still image
            // We retain a handle to the still image output and use this when we capture an image.
            self.stillImageOutput = [[AVCaptureStillImageOutput alloc] init];

// https://developer.apple.com/library/ios/samplecode/SquareCam/Listings/SquareCam_SquareCamViewController_m.html#//apple_ref/doc/uid/DTS40011190-SquareCam_SquareCamViewController_m-DontLinkElementID_7
            // see KVO note above
            [self.stillImageOutput addObserver:self forKeyPath:@"capturingStillImage" options:NSKeyValueObservingOptionNew context:AVCaptureStillImageIsCapturingStillImageContext];


          //  NSDictionary *outputSettings = [[NSDictionary alloc] initWithObjectsAndKeys: AVVideoCodecJPEG, AVVideoCodecKey, nil];
          //  [self.stillImageOutput setOutputSettings:outputSettings];

            [self.captureSession addInput:input];

            [self.captureSession addOutput:self.stillImageOutput];
            
            //[outputSettings release];



            // we want BGRA, both CoreGraphics and OpenGL work well with 'BGRA'
            NSDictionary *rgbOutputSettings = [NSDictionary dictionaryWithObject:
                                       [NSNumber numberWithInt:kCMPixelFormat_32BGRA] forKey:(id)kCVPixelBufferPixelFormatTypeKey];
    
            [videoDataOutput setVideoSettings:rgbOutputSettings];

           

            videoDataOutput.minFrameDuration = CMTimeMake(1, 10);

 
            [self.captureSession addOutput:videoDataOutput];

            [[videoDataOutput connectionWithMediaType:AVMediaTypeVideo] setEnabled:NO];



/*
 
    From : https://developer.apple.com/library/ios/samplecode/SquareCam/Listings/SquareCam_SquareCamViewController_m.html#//apple_ref/doc/uid/DTS40011190-SquareCam_SquareCamViewController_m-DontLinkElementID_7
 
    // create a serial dispatch queue used for the sample buffer delegate as well as when a still image is captured
    // a serial dispatch queue must be used to guarantee that video frames will be delivered in order
    // see the header doc for setSampleBufferDelegate:queue: for more information

    videoDataOutputQueue = dispatch_queue_create("VideoDataOutputQueue", DISPATCH_QUEUE_SERIAL);
    [videoDataOutput setSampleBufferDelegate:self queue:videoDataOutputQueue];
    
    if ( [session canAddOutput:videoDataOutput] )
        [session addOutput:videoDataOutput];
    [[videoDataOutput connectionWithMediaType:AVMediaTypeVideo] setEnabled:NO];
    
    effectiveScale = 1.0;
    previewLayer = [[AVCaptureVideoPreviewLayer alloc] initWithSession:session];
    [previewLayer setBackgroundColor:[[UIColor blackColor] CGColor]];
    [previewLayer setVideoGravity:AVLayerVideoGravityResizeAspect];
    CALayer *rootLayer = [previewView layer];
    [rootLayer setMasksToBounds:YES];
    [previewLayer setFrame:[rootLayer bounds]];
    [rootLayer addSublayer:previewLayer];
    [session startRunning]; 

*/




            [self.captureSession startRunning];

bail:
    [self.captureSession release];
    if (error) {
        UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:[NSString stringWithFormat:@"Failed with error %d", (int)[error code]]
                                                            message:[error localizedDescription]
                                                           delegate:nil 
                                                  cancelButtonTitle:@"Dismiss" 
                                                  otherButtonTitles:nil];
        [alertView show];
        [alertView release];
        [self teardownAVCapture];
    }


            /*
            /////////////////////////////////////////////////////////////////////////////
            // Create a preview layer that has a capture session attached to it.
            // Stick this preview layer into our UIView.
            /////////////////////////////////////////////////////////////////////////////
            self.captureSession = [[AVCaptureSession alloc] init];
            self.captureSession.sessionPreset = AVCaptureSessionPresetMedium;


                    
            self.prevLayer = [[AVCaptureVideoPreviewLayer alloc] initWithSession:self.captureSession];
            self.prevLayer.frame = square.bounds;
            //self.prevLayer.transform = CATransform3DRotate(CATransform3DIdentity, M_PI/2.0f, 0, 0, 1);
            self.prevLayer.videoGravity = AVLayerVideoGravityResizeAspectFill;
            [square.layer addSublayer:self.prevLayer];



            
            self.captureDevice = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];
            
            // set the flash off 
            // lock it 
            if([self.captureDevice lockForConfiguration:true]){
                // set it
                [self.captureDevice setFlashMode:AVCaptureFlashModeOff];
                self.flashOn = NO;  
                // unlock it 
                [self.captureDevice lockForConfiguration:false];
            };
            
            NSError *error = nil;
            AVCaptureDeviceInput *input = [AVCaptureDeviceInput deviceInputWithDevice:self.captureDevice error:&error];
            if (!input) {
                // Handle the error appropriately.
            }
            [self.captureSession addInput:input];

            
            /////////////////////////////////////////////////////////////
            // OUTPUT #1: Still Image
            /////////////////////////////////////////////////////////////
            // Add an output object to our session so we can get a still image
            // We retain a handle to the still image output and use this when we capture an image.
            self.stillImageOutput = [[AVCaptureStillImageOutput alloc] init];

            NSDictionary *outputSettings = [[NSDictionary alloc] initWithObjectsAndKeys: AVVideoCodecJPEG, AVVideoCodecKey, nil];
            [self.stillImageOutput setOutputSettings:outputSettings];
            [self.captureSession addOutput:self.stillImageOutput];
            
            
            /////////////////////////////////////////////////////////////
            // OUTPUT #2: Video Frames
            /////////////////////////////////////////////////////////////
            // Create Video Frame Outlet that will send each frame to our delegate
            AVCaptureVideoDataOutput *captureOutput = [[[AVCaptureVideoDataOutput alloc] init] autorelease];
            captureOutput.alwaysDiscardsLateVideoFrames = YES; 
            
            // We need to create a queue to funnel the frames to our delegate

            dispatch_queue_t queue = dispatch_queue_create("cameraQueue", NULL);
            dispatch_set_context(queue, self);

            // a warning is happening here for some reason...  
            [captureOutput setSampleBufferDelegate:self queue:queue];

            dispatch_release(queue);
            
            // Set the video output to store frame in BGRA (It is supposed to be faster)
            NSString* key = (NSString*)kCVPixelBufferPixelFormatTypeKey; 
            // let's try some different keys, 
            NSNumber* value = [NSNumber numberWithUnsignedInt:kCVPixelFormatType_32BGRA]; 
            
            NSDictionary* videoSettings = [NSDictionary dictionaryWithObject:value forKey:key]; 
            [captureOutput setVideoSettings:videoSettings];    
            
            [self.captureSession addOutput:captureOutput]; 
            /////////////////////////////////////////////////////////////
            
            
            // start the capture session
            [self.captureSession startRunning];


            */
            
        } else {
            // If camera is NOT avaialble
            [self.proxy fireEvent:@"noCamera"];
        }        
        /////////////////////////////////////////////////////////////////////////////
    }
    
    return square;
}


- (void)teardownAVCapture
{

    NSLog(@"[INFO] TEAR DOWN CAPTURE");

    [self.captureSession stopRunning];

    [_videoDataOutput release];
    if (videoDataOutputQueue)
        dispatch_release(videoDataOutputQueue);
    [self.stillImageOutput removeObserver:self forKeyPath:@"capturingStillImage"];
    [self.stillImageOutput release];
    [self.prevLayer removeFromSuperlayer];
    [self.prevLayer release];
}


// perform a flash bulb animation using KVO to monitor the value of the capturingStillImage property of the AVCaptureStillImageOutput class
- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context
{
    if ( context == AVCaptureStillImageIsCapturingStillImageContext ) {
        BOOL isCapturingStillImage = [[change objectForKey:NSKeyValueChangeNewKey] boolValue];
        if ( isCapturingStillImage ) {
            // do flash bulb like animation
            flashView = [[UIView alloc] initWithFrame:[self.stillImage frame]];
            [flashView setBackgroundColor:[UIColor whiteColor]];
            [flashView setAlpha:0.f];

            [self addSubview:flashView];
            // fade it in            
            [UIView animateWithDuration:.4f
                             animations:^{
                                 [flashView setAlpha:1.f];
                             }
             ];
        }
        else {
            // fade it out
            [UIView animateWithDuration:.4f
                            animations:^{
                                [flashView setAlpha:0.f];
                            }
                            completion:^(BOOL finished){
                                // get rid of it
                                [flashView removeFromSuperview];
                                [flashView release];
                                flashView = nil;
                            }
             ];
        }
    }
}


// utility routing used during image capture to set up capture orientation
- (AVCaptureVideoOrientation)avOrientationForDeviceOrientation:(UIDeviceOrientation)deviceOrientation
{
    AVCaptureVideoOrientation result = deviceOrientation;
    if ( deviceOrientation == UIDeviceOrientationLandscapeLeft )
        result = AVCaptureVideoOrientationLandscapeRight;
    else if ( deviceOrientation == UIDeviceOrientationLandscapeRight )
        result = AVCaptureVideoOrientationLandscapeLeft;
    return result;
}


@end