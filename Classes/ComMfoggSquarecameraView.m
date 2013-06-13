#import "ComMfoggSquarecameraView.h"
#import "ComMfoggSquarecameraViewProxy.h"
#import <AVFoundation/AVFoundation.h>
#import <ImageIO/ImageIO.h>
#import <CoreMedia/CoreMedia.h>

@implementation ComMfoggSquarecameraView

@synthesize captureSession = _captureSession;
@synthesize imageView = _imageView;
@synthesize customLayer = _customLayer;
@synthesize prevLayer = _prevLayer;
@synthesize stillImageOutput = _stillImageOutput;
@synthesize stillImage = _stillImage;

- (void) dealloc
{
    self.imageView = nil;
    self.prevLayer = nil;
    self.stillImage = nil;
    self.stillImageOutput = nil;
    RELEASE_TO_NIL(square);
    
    NSLog(@"[INFO] ---- DEALLOCATED ----");
    
    [super dealloc];
}

-(void)initializeState
{
    NSLog(@"[INFO] ---- INITIALIZED STATE ----");
    [super initializeState];
    
    self.imageView = nil;
    self.prevLayer = nil;
    self.stillImage = nil;
    self.stillImageOutput = nil;
}

-(void)frameSizeChanged:(CGRect)frame bounds:(CGRect)bounds
{
    NSLog(@"[INFO] ---- FRAME SIZE CHANGED ----");
    [TiUtils setView:self.square positionRect:bounds];
}

- (void)takePhoto:(id)args
{
    AVCaptureConnection *videoConnection = nil;
    
    NSLog(@"Getting connections ... : %@", self.stillImageOutput.connections);
    
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
    
    NSLog(@"about to request a capture from: %@", self.stillImageOutput);
    
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
            CGRect cropRect = self.stillImage.frame;//CGRectMake(0, 0, 320, 430);  
            CGRect customImageRect = CGRectMake(
                                                -((((cropRect.size.width/size.width)*size.height)-cropRect.size.height)/2),
                                                0,
                                                ((cropRect.size.width/size.width)*size.height),
                                                cropRect.size.width);
            
            UIGraphicsBeginImageContext(cropRect.size);
            CGContextRef context = UIGraphicsGetCurrentContext();  
            
            CGContextDrawImage(context, customImageRect,
                               image.CGImage);
            
            UIImage *croppedImage = UIGraphicsGetImageFromCurrentImageContext();  
            UIGraphicsEndImageContext();
            
            self.stillImage.image = croppedImage;
            
            [image release];
            [croppedImage release];
            
            // [self.captureSession stopRunning];
     }];
}

- (void)captureOutput:(AVCaptureOutput *)captureOutput 
didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer 
	   fromConnection:(AVCaptureConnection *)connection 
{ 
    
}

-(UIView*)square
{   
    if (square == nil) {
        NSLog(@"[INFO] ---- SQUARE LOADED ----");
        
        square = [[UIView alloc] initWithFrame:[self frame]];
        [self addSubview:square]; 
        
        self.stillImage = [[UIImageView alloc] init];
        self.stillImage.frame = [square bounds];
        [self addSubview:self.stillImage];
        
        NSLog(@"[INFO]: Still Image Frame = %@", NSStringFromCGRect(self.stillImage.frame));
        
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
        
        AVCaptureDevice *device = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];
        
        NSError *error = nil;
        AVCaptureDeviceInput *input = [AVCaptureDeviceInput deviceInputWithDevice:device error:&error];
        if (!input) {
            // Handle the error appropriately.
            NSLog(@"ERROR: trying to open camera: %@", error);
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
        
        /////////////////////////////////////////////////////////////////////////////
    }
    
    return square;
}

@end