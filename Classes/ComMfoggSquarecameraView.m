#import "ComMfoggSquarecameraView.h"
#import "ComMfoggSquarecameraViewProxy.h"
#import <AVFoundation/AVFoundation.h>
#import <ImageIO/ImageIO.h>
#import <CoreMedia/CoreMedia.h>

@implementation ComMfoggSquarecameraView

@synthesize captureSession = _captureSession;
@synthesize prevLayer = _prevLayer;
@synthesize stillImageOutput = _stillImageOutput;
@synthesize stillImage = _stillImage;
@synthesize captureDevice = _captureDevice;
@synthesize flashOn = _flashOn;
@synthesize isUsingFrontFacingCamera = _isUsingFrontFacingCamera;

- (void) dealloc
{
    [self.captureSession stopRunning];
    
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

- (void)takePhoto:(id)args
{
    AVCaptureConnection *videoConnection = nil;
        
	for (AVCaptureConnection *connection in self.stillImageOutput.connections)
	{
		for (AVCaptureInputPort *port in [connection inputPorts])
		{
			if ([[port mediaType] isEqual:AVMediaTypeVideo] )
			{
				videoConnection = connection;
				break;
			}
		}
		if (videoConnection) { break; }
	}
    
    [self.stillImageOutput captureStillImageAsynchronouslyFromConnection:videoConnection completionHandler: ^(CMSampleBufferRef imageSampleBuffer, NSError *error)
        { 
            CFDictionaryRef exifAttachments = CMGetAttachment(imageSampleBuffer, kCGImagePropertyExifDictionary, NULL);
            if (exifAttachments) {
                NSLog(@"attachments: %@", exifAttachments);
            } else { 
                NSLog(@"no attachments");
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
            
            self.stillImage.image = croppedImage;
            
            [self.proxy fireEvent:@"onTakePhoto"];
                        
            [image release];
            [croppedImage release];
            
            [self.captureSession stopRunning];
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
            
            if([self.captureDevice lockForConfiguration:true]){
                [self.captureDevice setFlashMode:AVCaptureFlashModeOff];
                self.flashOn = NO;  
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
            AVCaptureVideoDataOutput *captureOutput = [[AVCaptureVideoDataOutput alloc] init];
            captureOutput.alwaysDiscardsLateVideoFrames = YES; 
            
            // We need to create a queue to funnel the frames to our delegate
            dispatch_queue_t queue;
            queue = dispatch_queue_create("cameraQueue", NULL);
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
            
        } else {
            // If camera is NOT avaialble
            [self.proxy fireEvent:@"noCamera"];
        }        
        /////////////////////////////////////////////////////////////////////////////
    }
    
    return square;
}

@end