//
//  UIImagePickerController.h
//  UIKit
//
//  Copyright (c) 2008-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UINavigationController.h>
#import <UIKit/UIKitDefines.h>

@class UIImage;
@protocol UIImagePickerControllerDelegate;

enum {
    UIImagePickerControllerSourceTypePhotoLibrary,
    UIImagePickerControllerSourceTypeCamera,
    UIImagePickerControllerSourceTypeSavedPhotosAlbum
};
typedef NSUInteger UIImagePickerControllerSourceType;

enum {
    UIImagePickerControllerQualityTypeHigh = 0,       // highest quality 
    UIImagePickerControllerQualityTypeMedium = 1,     // medium quality, suitable for transmission via Wi-Fi 
    UIImagePickerControllerQualityTypeLow = 2,         // lowest quality, suitable for tranmission via cellular network
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_4_0
    UIImagePickerControllerQualityType640x480 = 3,    // VGA quality
#endif
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_5_0
    UIImagePickerControllerQualityTypeIFrame1280x720 = 4,
    UIImagePickerControllerQualityTypeIFrame960x540 = 5
#endif
};
typedef NSUInteger UIImagePickerControllerQualityType;

enum {
    UIImagePickerControllerCameraCaptureModePhoto,
    UIImagePickerControllerCameraCaptureModeVideo
};
typedef NSUInteger UIImagePickerControllerCameraCaptureMode;

enum {
    UIImagePickerControllerCameraDeviceRear,
    UIImagePickerControllerCameraDeviceFront
};
typedef NSUInteger UIImagePickerControllerCameraDevice;

enum {
    UIImagePickerControllerCameraFlashModeOff  = -1,
    UIImagePickerControllerCameraFlashModeAuto = 0,
    UIImagePickerControllerCameraFlashModeOn   = 1
};
typedef NSInteger UIImagePickerControllerCameraFlashMode;

// info dictionary keys
UIKIT_EXTERN NSString *const UIImagePickerControllerMediaType;      // an NSString (UTI, i.e. kUTTypeImage)
UIKIT_EXTERN NSString *const UIImagePickerControllerOriginalImage;  // a UIImage
UIKIT_EXTERN NSString *const UIImagePickerControllerEditedImage;    // a UIImage
UIKIT_EXTERN NSString *const UIImagePickerControllerCropRect;       // an NSValue (CGRect)
UIKIT_EXTERN NSString *const UIImagePickerControllerMediaURL;       // an NSURL
UIKIT_EXTERN NSString *const UIImagePickerControllerReferenceURL        __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_1);  // an NSURL that references an asset in the AssetsLibrary framework
UIKIT_EXTERN NSString *const UIImagePickerControllerMediaMetadata       __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_1);  // an NSDictionary containing metadata from a captured photo

UIKIT_CLASS_AVAILABLE(2_0) @interface UIImagePickerController : UINavigationController <NSCoding> {
  @private
    UIImagePickerControllerSourceType _sourceType;
    id                                _image;
    CGRect                            _cropRect;
    NSArray                          *_mediaTypes;
    NSMutableDictionary              *_properties;
    int                               _previousStatusBarStyle;
    
    struct {
        unsigned int visible:1;
        unsigned int isCleaningUp:1;
        unsigned int savingOptions:3;
        unsigned int didRevertStatusBar:1;
    } _imagePickerFlags;
}

+ (BOOL)isSourceTypeAvailable:(UIImagePickerControllerSourceType)sourceType;                 // returns YES if source is available (i.e. camera present)
+ (NSArray *)availableMediaTypesForSourceType:(UIImagePickerControllerSourceType)sourceType; // returns array of available media types (i.e. kUTTypeImage)

+ (BOOL)isCameraDeviceAvailable:(UIImagePickerControllerCameraDevice)cameraDevice                   __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0); // returns YES if camera device is available 
+ (BOOL)isFlashAvailableForCameraDevice:(UIImagePickerControllerCameraDevice)cameraDevice           __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0); // returns YES if camera device supports flash and torch.
+ (NSArray *)availableCaptureModesForCameraDevice:(UIImagePickerControllerCameraDevice)cameraDevice __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0); // returns array of NSNumbers (UIImagePickerControllerCameraCaptureMode)

@property(nonatomic,assign)    id <UINavigationControllerDelegate, UIImagePickerControllerDelegate> delegate;

@property(nonatomic)           UIImagePickerControllerSourceType     sourceType;                                                        // default value is UIImagePickerControllerSourceTypePhotoLibrary.
@property(nonatomic,copy)      NSArray                              *mediaTypes;  
    // default value is an array containing kUTTypeImage.
@property(nonatomic)           BOOL                                  allowsEditing __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_1);     // replacement for -allowsImageEditing; default value is NO.
@property(nonatomic)           BOOL                                  allowsImageEditing __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_2_0,__IPHONE_3_1);

// video properties apply only if mediaTypes includes kUTTypeMovie
@property(nonatomic)           NSTimeInterval                        videoMaximumDuration __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_1); // default value is 10 minutes.
@property(nonatomic)           UIImagePickerControllerQualityType    videoQuality __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_1);         // default value is UIImagePickerControllerQualityTypeMedium. If the cameraDevice does not support the videoQuality, it will use the default value.

// camera additions available only if sourceType is UIImagePickerControllerSourceTypeCamera.
@property(nonatomic)           BOOL                                  showsCameraControls __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_1);   // set to NO to hide all standard camera UI. default is YES
@property(nonatomic,retain)    UIView                                *cameraOverlayView  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_1);   // set a view to overlay the preview view.
@property(nonatomic)           CGAffineTransform                     cameraViewTransform __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_1);   // set the transform of the preview view.

- (void)takePicture __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_1);                                                   
// programatically initiates still image capture. ignored if image capture is in-flight.
// clients can initiate additional captures after receiving -imagePickerController:didFinishPickingMediaWithInfo: delegate callback

- (BOOL)startVideoCapture __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
- (void)stopVideoCapture  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

@property(nonatomic) UIImagePickerControllerCameraCaptureMode cameraCaptureMode __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0); // default is UIImagePickerControllerCameraCaptureModePhoto
@property(nonatomic) UIImagePickerControllerCameraDevice      cameraDevice      __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0); // default is UIImagePickerControllerCameraDeviceRear
@property(nonatomic) UIImagePickerControllerCameraFlashMode   cameraFlashMode   __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0); // default is UIImagePickerControllerCameraFlashModeAuto. 
// cameraFlashMode controls the still-image flash when cameraCaptureMode is Photo. cameraFlashMode controls the video torch when cameraCaptureMode is Video.

@end

@protocol UIImagePickerControllerDelegate<NSObject>
@optional
// The picker does not dismiss itself; the client dismisses it in these callbacks.
// The delegate will receive one or the other, but not both, depending whether the user
// confirms or cancels.
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingImage:(UIImage *)image editingInfo:(NSDictionary *)editingInfo __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_2_0,__IPHONE_3_0);
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info;
- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker;

@end


// Adds a photo to the saved photos album.  The optional completionSelector should have the form:
//  - (void)image:(UIImage *)image didFinishSavingWithError:(NSError *)error contextInfo:(void *)contextInfo;
UIKIT_EXTERN void UIImageWriteToSavedPhotosAlbum(UIImage *image, id completionTarget, SEL completionSelector, void *contextInfo);

// Is a specific video eligible to be saved to the saved photos album? 
UIKIT_EXTERN BOOL UIVideoAtPathIsCompatibleWithSavedPhotosAlbum(NSString *videoPath) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_1);

// Adds a video to the saved photos album. The optional completionSelector should have the form:
//  - (void)video:(NSString *)videoPath didFinishSavingWithError:(NSError *)error contextInfo:(void *)contextInfo;
UIKIT_EXTERN void UISaveVideoAtPathToSavedPhotosAlbum(NSString *videoPath, id completionTarget, SEL completionSelector, void *contextInfo) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_1);


