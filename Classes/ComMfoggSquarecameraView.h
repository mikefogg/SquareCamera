/**
 *  SquareCamera Titanium Module
 *
 *  learning/tests/dev/etc...
 *
 *  original author : Mike Fogg  : blirpit : 2013
 *
 *  modifications / attempts to fix / general fist thumping : Kosso : August 2013
 * .
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

@interface ComMfoggSquarecameraView : TiUIView <AVCaptureMetadataOutputObjectsDelegate, AVCaptureVideoDataOutputSampleBufferDelegate>
{
    UIView *square;
    UIView *flashView;
    dispatch_queue_t videoDataOutputQueue;
}

@property (nonatomic, strong) AVCaptureSession *captureSession;
@property (nonatomic, strong) AVCaptureVideoPreviewLayer *prevLayer;
@property (nonatomic, assign) AVCaptureVideoOrientation *orientation;
@property (nonatomic,retain) AVCaptureDeviceInput *videoInput;
@property (nonatomic,retain) AVCaptureDeviceInput *audioInput;
@property (nonatomic, retain) AVCaptureStillImageOutput *stillImageOutput;
@property (nonatomic, retain) AVCaptureVideoDataOutput *videoDataOutput;
@property (nonatomic, retain) UIImageView *stillImage;
@property (nonatomic, retain) AVCaptureDevice *captureDevice;
@property (nonatomic, retain) NSString *camera;
@property (nonatomic, retain) NSDictionary *barcodeDict;
@property (nonatomic, retain) NSArray *barcodeTypes;
@property (nonatomic) Boolean flashOn;
@property (nonatomic) BOOL adjustingExposure;
@property (nonatomic, assign) BOOL detectCodes;
@property (nonatomic, assign) BOOL forceHorizontal;
@property (nonatomic, retain) NSString *frontQuality;
@property (nonatomic, retain) NSString *backQuality;
@property (nonatomic, retain) NSDictionary *scanCrop;
@property (nonatomic) BOOL scanCropPreview;

@end
