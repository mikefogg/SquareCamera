//
//  UIScreen.h
//  UIKit
//
//  Copyright (c) 2007-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>

@class UIScreenMode, CADisplayLink;

// Object is the UIScreen that represents the new screen. Connection notifications are not sent for screens present when the application is first launched
UIKIT_EXTERN NSString *const UIScreenDidConnectNotification __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2);
// Object is the UIScreen that represented the disconnected screen.
UIKIT_EXTERN NSString *const UIScreenDidDisconnectNotification __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2);
// Object is the UIScreen which changed. [object currentMode] is the new UIScreenMode.
UIKIT_EXTERN NSString *const UIScreenModeDidChangeNotification __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2);
UIKIT_EXTERN NSString *const UIScreenBrightnessDidChangeNotification __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

// when the connected screen is overscanning, UIScreen can attempt to compensate for the overscan to avoid clipping
typedef enum {
    UIScreenOverscanCompensationScale,                 // the final composited framebuffer for the screen is scaled to avoid clipping
    UIScreenOverscanCompensationInsetBounds,           // the screen's bounds will be inset in the framebuffer to avoid clipping. no scaling will occur
    UIScreenOverscanCompensationInsetApplicationFrame, // the screen's applicationFrame will be inset in the bounds. content drawn in the bounds outside applicationFrame may be clipped
} UIScreenOverscanCompensation;

UIKIT_CLASS_AVAILABLE(2_0) @interface UIScreen : NSObject {
  @private
    id _display;
    CGRect _bounds;
    CGFloat _scale;
    CGFloat _horizontalScale;
    struct {
        unsigned int bitsPerComponent:4;
        unsigned int initialized:1;
        unsigned int connected:1;
        unsigned int overscanCompensation:2;
    } _screenFlags;
}

+ (NSArray *)screens __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2);          // all screens currently attached to the device
+ (UIScreen *)mainScreen;      // the device's internal screen

@property(nonatomic,readonly) CGRect  bounds;                // Bounds of entire screen in points
@property(nonatomic,readonly) CGRect  applicationFrame;      // Frame of application screen area in points (i.e. entire screen minus status bar if visible)
@property(nonatomic,readonly) CGFloat scale __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

@property(nonatomic,readonly,copy) NSArray *availableModes __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2);             // The list of modes that this screen supports
@property(nonatomic,readonly,retain) UIScreenMode *preferredMode __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_3);       // Preferred mode of this screen. Choosing this mode will likely produce the best results
@property(nonatomic,retain) UIScreenMode *currentMode __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2);                  // Current mode of this screen
@property(nonatomic) UIScreenOverscanCompensation overscanCompensation __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0); // Default is UIScreenOverscanCompensationScale. Determines how the screen behaves if the connected display is overscanning

@property(nonatomic,readonly,retain) UIScreen *mirroredScreen __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_3);          // The screen being mirrored by the receiver. nil if mirroring is disabled or unsupported. Moving a UIWindow to this screen will disable mirroring

@property(nonatomic) CGFloat brightness __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);        // 0 .. 1.0, where 1.0 is maximum brightness. Only supported by main screen.
@property(nonatomic) BOOL wantsSoftwareDimming __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0); // Default is NO. If YES, brightness levels lower than that of which the hardware is capable are emulated in software, if neccessary. Having enabled may entail performance cost.

- (CADisplayLink *)displayLinkWithTarget:(id)target selector:(SEL)sel __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

@end
