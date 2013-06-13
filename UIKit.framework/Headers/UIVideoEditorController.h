//
//  UIVideoEditorController.h
//  UIKit
//
//  Copyright (c) 2009-2011, Apple Inc.. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UINavigationController.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIImagePickerController.h>

@protocol UIVideoEditorControllerDelegate;

UIKIT_CLASS_AVAILABLE(3_1) @interface UIVideoEditorController : UINavigationController {
  @private
    int                               _previousStatusBarStyle;
    NSMutableDictionary              *_properties;
    
    struct {
        unsigned int visible:1;
        unsigned int isCleaningUp:1;
        unsigned int didRevertStatusBar:1;
    } _flags;
}

+ (BOOL)canEditVideoAtPath:(NSString *)videoPath __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_1);

@property(nonatomic,assign)    id <UINavigationControllerDelegate, UIVideoEditorControllerDelegate> delegate;

@property(nonatomic, copy)     NSString                              *videoPath;
@property(nonatomic)           NSTimeInterval                        videoMaximumDuration; // default value is 10 minutes. set to 0 to specify no maximum duration.
@property(nonatomic)           UIImagePickerControllerQualityType    videoQuality;         // default value is UIImagePickerControllerQualityTypeMedium

@end

@protocol UIVideoEditorControllerDelegate<NSObject>
@optional
// The editor does not dismiss itself; the client dismisses it in these callbacks.
// The delegate will receive exactly one of the following callbacks, depending whether the user
// confirms or cancels or if the operation fails.
- (void)videoEditorController:(UIVideoEditorController *)editor didSaveEditedVideoToPath:(NSString *)editedVideoPath; // edited video is saved to a path in app's temporary directory
- (void)videoEditorController:(UIVideoEditorController *)editor didFailWithError:(NSError *)error;
- (void)videoEditorControllerDidCancel:(UIVideoEditorController *)editor;

@end
