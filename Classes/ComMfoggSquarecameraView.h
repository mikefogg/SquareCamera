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

@interface ComMfoggSquarecameraView : TiUIView
{
    UIView *square;
}

@property (nonatomic, strong) AVCaptureSession *captureSession;

@property (nonatomic, strong) AVCaptureVideoPreviewLayer *prevLayer;

@property(nonatomic, retain) AVCaptureStillImageOutput *stillImageOutput;

@property(nonatomic, retain) UIImageView *stillImage;

@property(nonatomic, retain) AVCaptureDevice *captureDevice;

@property(nonatomic) Boolean flashOn;

@property(nonatomic) Boolean isUsingFrontFacingCamera;

@end

