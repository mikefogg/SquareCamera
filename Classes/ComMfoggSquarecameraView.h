/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#import "TiUIView.h"
#import "TiBase.h"
#import "TiHost.h"
#import "TiUtils.h"
#import "TiBlob.h"


#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <CoreVideo/CoreVideo.h>
#import <CoreMedia/CoreMedia.h>
#import <CoreFoundation/CoreFoundation.h>
#import <CoreFoundation/CFData.h>
#import <CoreFoundation/CFSocket.h>
#import <ImageIO/ImageIO.h>
#import <ImageIO/CGImageProperties.h>

@interface ComMfoggSquarecameraView : TiUIView <AVCaptureVideoDataOutputSampleBufferDelegate>
{
    UIView *square;
    UIView *flashView;
    dispatch_queue_t videoDataOutputQueue;
}

<<<<<<< HEAD


=======
>>>>>>> 2c4df9552805c087595c2867f4194b5f6f31e2a5
@property (nonatomic, strong) AVCaptureSession *captureSession;

@property (nonatomic, strong) AVCaptureVideoPreviewLayer *prevLayer;

<<<<<<< HEAD
@property (nonatomic, assign) AVCaptureVideoOrientation *orientation;

@property (nonatomic,retain) AVCaptureDeviceInput *videoInput;
@property (nonatomic,retain) AVCaptureDeviceInput *audioInput;

@property(nonatomic, retain) AVCaptureStillImageOutput *stillImageOutput;

@property(nonatomic, retain) AVCaptureVideoDataOutput *videoDataOutput;




=======
@property(nonatomic, retain) AVCaptureStillImageOutput *stillImageOutput;

>>>>>>> 2c4df9552805c087595c2867f4194b5f6f31e2a5
@property(nonatomic, retain) UIImageView *stillImage;

@property(nonatomic, retain) AVCaptureDevice *captureDevice;

<<<<<<< HEAD

 


=======
>>>>>>> 2c4df9552805c087595c2867f4194b5f6f31e2a5
@property(nonatomic) Boolean flashOn;

@property(nonatomic) Boolean isUsingFrontFacingCamera;

@end

