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
    self.customLayer = nil;
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
    self.customLayer = nil;
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
            
            // crop the crop rect that the user selected  
            CGRect cropRect = self.stillImage.frame;//CGRectMake(0, 0, 320, 430);  
            
            NSLog(@"[INFO]: Still Image Frame Later = %@", NSStringFromCGRect(self.stillImage.frame));
            NSLog(@"[INFO]: IMAGE SIZE = %@", NSStringFromCGSize(image.size));
            
            // create a graphics context of the correct size      
            UIGraphicsBeginImageContext(cropRect.size);
            CGContextRef context = UIGraphicsGetCurrentContext();  
            
            // correct for image orientation      
            UIImageOrientation orientation = [image imageOrientation];  
            if(orientation == UIImageOrientationUp) {  
                NSLog(@"[INFO]: Image Orientation UP");
                CGContextTranslateCTM(context, 0, size.height);  
                CGContextScaleCTM(context, 1, -1);                  
//                cropRect = CGRectMake(cropRect.origin.x,   
//                                      -cropRect.origin.y,   
//                                      cropRect.size.width,   
//                                      cropRect.size.height);  
            } else if(orientation == UIImageOrientationRight) {  
                NSLog(@"[INFO]: Image Orientation RIGHT");
                CGContextScaleCTM(context, 1.0, -1.0);  
                CGContextRotateCTM(context, -M_PI/2);  
//                size = CGSizeMake(size.height, size.width);  
//                cropRect = CGRectMake(-10,   
//                                      -10,   
//                                      cropRect.size.height,   
//                                      cropRect.size.width);  
            } else if(orientation == UIImageOrientationDown) {  
                NSLog(@"[INFO]: Image Orientation DOWN");
                CGContextTranslateCTM(context, size.width, 0);  
                CGContextScaleCTM(context, -1, 1);          
//                cropRect = CGRectMake(-cropRect.origin.x,   
//                                      cropRect.origin.y,   
//                                      cropRect.size.width,   
//                                      cropRect.size.height);  
            } 
            
            CGContextDrawImage(context, CGRectMake(
                                                   -((((cropRect.size.width/size.width)*size.height)-cropRect.size.height)/2),
                                                   0,
                                                   ((cropRect.size.width/size.width)*size.height),
                                                   cropRect.size.width),
                               image.CGImage);
            
            NSLog(@"[INFO]: Image drawing = %@", NSStringFromCGRect(CGRectMake(
                                                                               -((((cropRect.size.width/size.width)*size.height)-cropRect.size.height)/2),
                                                                               0,
                                                                               ((cropRect.size.width/size.width)*size.height),
                                                                               cropRect.size.width)));
            
            UIImage *croppedImage = UIGraphicsGetImageFromCurrentImageContext();  
            UIGraphicsEndImageContext();
            
            
            self.stillImage.image = croppedImage;
            
            [image release];
            [croppedImage release];
            
            // [self.captureSession stopRunning];
     }];
}


     
//
//-(id)takePhoto:(id)args
//{
//    NSLog(@"[INFO] ---- TAKING PICTURE ----");
//    
////    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Do you want to say hello?" message:@"More info..." delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"Say Hello",nil];
////    [alert show];
////    [alert release];
////    
//    AVCaptureConnection *videoConnection = nil;
//    
//    NSLog(@"Getting connections ... : %@", self.stillImageOutput.connections);
//    
//	for (AVCaptureConnection *connection in self.stillImageOutput.connections)
//	{
//		for (AVCaptureInputPort *port in [connection inputPorts])
//		{
//			if ([[port mediaType] isEqual:AVMediaTypeVideo] )
//			{
//				videoConnection = connection;
//				break;
//			}
//		}
//		if (videoConnection) { break; }
//	}
//    
//    NSLog(@"Getting videoConnection ... : %@", videoConnection);
////	
//	NSLog(@"about to request a capture from: %@", self.stillImageOutput);
////	[self.stillImageOutput captureStillImageAsynchronouslyFromConnection:videoConnection completionHandler: ^(CMSampleBufferRef imageSampleBuffer, NSError *error)
////     { 
//////         CFDictionaryRef exifAttachments = CMGetAttachment(imageSampleBuffer, kCGImagePropertyExifDictionary, NULL);
//////         if (exifAttachments) {
//////             NSLog(@"attachments: %@", exifAttachments);
//////         } else { 
//////             NSLog(@"no attachments");
//////         }
//////         
//////         NSLog(@"--- Getting past attachments");
//////         
//////         NSData *imageData = [AVCaptureStillImageOutput jpegStillImageNSDataRepresentation:imageSampleBuffer];    
//////         UIImage *image = [[UIImage alloc] initWithData:imageData];
//////         
//////         NSLog(@"--- Getting past next couple of variables");
//////         
//////         self.stillImage.image = image;
//////         
//////         [image release];
//////         
//////         NSLog(@"--- Getting past next couple of variables");
//////         
//////         [self.captureSession stopRunning];
//////         
////////         [self.square removeFromSuperview];
//////         
//////         NSLog(@"--- Getting to end of taking photo");
////         
////     }];
//    return self.stillImage;
//}
//

#pragma mark -
#pragma mark AVCaptureSession delegate
//- (void)captureOutput:(AVCaptureOutput *)captureOutput
//didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer
//       fromConnection:(AVCaptureConnection *)connection
//{
//    /*We create an autorelease pool because as we are not in the main_queue our code is
//     not executed in the main thread. So we have to create an autorelease pool for the thread we are in*/
//    
//    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
//    
//    CVImageBufferRef imageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);
//    /*Lock the image buffer*/
//    CVPixelBufferLockBaseAddress(imageBuffer,0);
//    /*Get information about the image*/
//    uint8_t *baseAddress = (uint8_t *)CVPixelBufferGetBaseAddress(imageBuffer);
//    size_t bytesPerRow = CVPixelBufferGetBytesPerRow(imageBuffer);
//    size_t width = CVPixelBufferGetWidth(imageBuffer);
//    size_t height = CVPixelBufferGetHeight(imageBuffer);
//    
//    /*Create a CGImageRef from the CVImageBufferRef*/
//    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
//    CGContextRef newContext = CGBitmapContextCreate(baseAddress, width, height, 8, bytesPerRow, colorSpace, kCGBitmapByteOrder32Little | kCGImageAlphaPremultipliedFirst);
//    CGImageRef newImage = CGBitmapContextCreateImage(newContext);
//    
//    /*We release some components*/
//    CGContextRelease(newContext);
//    CGColorSpaceRelease(colorSpace);
//    
//    [self.customLayer performSelectorOnMainThread:@selector(setContents:) withObject: (id) newImage waitUntilDone:YES];
//    
//    UIImage *image= [UIImage imageWithCGImage:newImage scale:1.0 orientation:UIImageOrientationRight];
//    
//    /*We relase the CGImageRef*/
//    CGImageRelease(newImage);
//    
//    //[self.imageView performSelectorOnMainThread:@selector(setImage:) withObject:image waitUntilDone:YES];
//    
//    /*We unlock the  image buffer*/
//    CVPixelBufferUnlockBaseAddress(imageBuffer,0);
//    
//    [pool drain];
//}
- (void)captureOutput:(AVCaptureOutput *)captureOutput 
didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer 
	   fromConnection:(AVCaptureConnection *)connection 
{ 
    //NSLog(@"got frame");
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
//        
//        AVCaptureDeviceInput *captureInput = [AVCaptureDeviceInput
//                                              deviceInputWithDevice:[AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo]
//                                              error:nil];
//        
//        AVCaptureVideoDataOutput *captureOutput = [[AVCaptureVideoDataOutput alloc] init];
//        
//        captureOutput.alwaysDiscardsLateVideoFrames = YES;
//        
//        //captureOutput.minFrameDuration = CMTimeMake(1, 10);
//        
//        dispatch_queue_t queue;
//        queue = dispatch_queue_create("cameraQueue", NULL);
//        [captureOutput setSampleBufferDelegate:self queue:queue];
//        dispatch_release(queue);
//        
//        // Set the video output to store frame in BGRA (It is supposed to be faster)
//        NSString* key = (NSString*)kCVPixelBufferPixelFormatTypeKey;
//        NSNumber* value = [NSNumber numberWithUnsignedInt:kCVPixelFormatType_32BGRA];
//        NSDictionary* videoSettings = [NSDictionary dictionaryWithObject:value forKey:key];
//        [captureOutput setVideoSettings:videoSettings];
//        /*And we create a capture session*/
//        self.captureSession = [[AVCaptureSession alloc] init];
//        /*We add input and output*/
//        [self.captureSession addInput:captureInput];
//        [self.captureSession addOutput:captureOutput];
//        /*We use medium quality, ont the iPhone 4 this demo would be laging too much, the conversion in UIImage and CGImage demands too much ressources for a 720p resolution.*/
//        [self.captureSession setSessionPreset:AVCaptureSessionPresetMedium];
//        
//        /*We add the Custom Layer (We need to change the orientation of the layer so that the video is displayed correctly)*/
////        self.customLayer = [CALayer layer];
////        self.customLayer.frame = square.bounds;
////        self.customLayer.transform = CATransform3DRotate(CATransform3DIdentity, M_PI/2.0f, 0, 0, 1);
////        self.customLayer.contentsGravity = kCAGravityResizeAspectFill;
//        //[square.layer addSublayer:self.customLayer];
//        
//        /*We add the imageView*/
//        self.imageView = [[UIImageView alloc] init];
//        self.imageView.frame = [self bounds];
//        [square addSubview:self.imageView];
//        
//        /*We add the preview layer*/
//        self.prevLayer = [AVCaptureVideoPreviewLayer layerWithSession: self.captureSession];
//        self.prevLayer.frame = [self bounds];
//        self.prevLayer.videoGravity = AVLayerVideoGravityResizeAspectFill;
//        [square.layer addSublayer: self.prevLayer];
//        
//        self.stillImageOutput = [[AVCaptureStillImageOutput alloc] init];
//        NSDictionary *outputSettings = [[NSDictionary alloc] initWithObjectsAndKeys: AVVideoCodecJPEG, AVVideoCodecKey, nil];
//        [self.stillImageOutput setOutputSettings:outputSettings];
//        
//        [self.captureSession addOutput:self.stillImageOutput];
//        
//        /*We start the capture*/
//        [self.captureSession startRunning];
        
        /////////////////////////////////////////////////////////////////////////////
        // Create a preview layer that has a capture session attached to it.
        // Stick this preview layer into our UIView.
        /////////////////////////////////////////////////////////////////////////////
        self.captureSession = [[AVCaptureSession alloc] init];
        self.captureSession.sessionPreset = AVCaptureSessionPresetMedium;
        
//        self.customLayer = [CALayer layer];
//        self.customLayer.frame = square.bounds;
//        self.customLayer.transform = CATransform3DRotate(CATransform3DIdentity, M_PI/2.0f, 0, 0, 1);
//        self.customLayer.contentsGravity = kCAGravityResizeAspectFill;
//        [square.layer addSublayer:self.customLayer];
        
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
        //captureOutput.minFrameDuration = CMTimeMake(1, 3); // deprecated in IOS5
        
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