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

/*!
 @brief	The capture session takes the input from the camera and capture it
 */
@property (nonatomic, strong) AVCaptureSession *captureSession;

/*!
 @brief	The UIImageView we use to display the image generated from the imageBuffer
 */
@property (nonatomic, strong) UIImageView *imageView;

/*!
 @brief	The CALAyer customized by apple to display the video corresponding to a capture session
 */
@property (nonatomic, strong) AVCaptureVideoPreviewLayer *prevLayer;

/*!
 @brief	The capture session takes the input from the camera and capture it
 */
@property(nonatomic, retain) AVCaptureStillImageOutput *stillImageOutput;

/*!
 @brief	The capture session takes the input from the camera and capture it
 */
@property(nonatomic, retain) UIImageView *stillImage;

/*!
 @brief	This method initializes the capture session
 */
//- (void)setupCapture;

@end

