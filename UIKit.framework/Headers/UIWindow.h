//
//  UIWindow.h
//  UIKit
//
//  Copyright (c) 2005-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIView.h>
#import <UIKit/UIApplication.h>
#import <UIKit/UIKitDefines.h>

typedef CGFloat UIWindowLevel;

@class UIEvent, UIScreen, NSUndoManager, UIViewController;

UIKIT_CLASS_AVAILABLE(2_0) @interface UIWindow : UIView {
  @package
    id                       _delegate;
    CGFloat                  _windowLevel;
    CGFloat                  _windowSublevel;
    id                       _layerContext;
    UIView                  *_lastMouseDownView;
    UIView                  *_lastMouseEnteredView;
    UIResponder             *_firstResponder;
    id                       _fingerInfo;
    id                       _touchData;
    UIInterfaceOrientation   _viewOrientation;
    UIView                  *_exclusiveTouchView;
    NSUndoManager           *_undoManager;
    UIScreen                *_screen;
    CALayer                 *_transformLayer;
    NSMutableArray          *_rotationViewControllers;
    UIViewController        *_rootViewController;
    UIColor                 *_savedBackgroundColor;
    NSMutableSet            *_subtreeMonitoringViews;
    struct {
	unsigned int delegateWillRotate:1;
        unsigned int delegateDidRotate:1;
        unsigned int delegateWillAnimateFirstHalf:1;
        unsigned int delegateDidAnimationFirstHalf:1;
        unsigned int delegateWillAnimateSecondHalf:1;
        unsigned int autorotatesToPortrait:1;
        unsigned int autorotatesToPortraitUpsideDown:1;
        unsigned int autorotatesToLandscapeLeft:1;
        unsigned int autorotatesToLandscapeRight:1;
        unsigned int dontBecomeKeyOnOrderFront:1;
        unsigned int output:1;
        unsigned int inGesture:1;
        unsigned int cancelScroller:1;
        unsigned int bitsPerComponent:4;
        unsigned int autorotates:1;
        unsigned int isRotating:1;
        unsigned int isUsingOnePartRotationAnimation:1;
        unsigned int isHandlingContentRotation:1;
        unsigned int disableAutorotationCount:4;
        unsigned int needsAutorotationWhenReenabled:1;
        unsigned int forceTwoPartRotationAnimation:1;
        unsigned int orderKeyboardInAfterRotating:1;
        unsigned int roundedCorners:4;
        unsigned int resizesToFullScreen:1;
        unsigned int keepContextInBackground:1;
        unsigned int ignoreSetHidden:1;
        unsigned int forceVisibleOnInit:1;
        unsigned int settingFirstResponder:1;
    } _windowFlags;
    
    id _windowController;
}

@property(nonatomic,retain) UIScreen *screen __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2);  // default is [UIScreen mainScreen]. changing the screen may be an expensive operation and should not be done in performance-sensitive code

@property(nonatomic) UIWindowLevel windowLevel;                   // default = 0.0
@property(nonatomic,readonly,getter=isKeyWindow) BOOL keyWindow;
- (void)becomeKeyWindow;                               // override point for subclass. Do not call directly
- (void)resignKeyWindow;                               // override point for subclass. Do not call directly

- (void)makeKeyWindow;
- (void)makeKeyAndVisible;                             // convenience. most apps call this to show the main window and also make it key. otherwise use view hidden property

@property(nonatomic,retain) UIViewController *rootViewController __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);  // default is nil

- (void)sendEvent:(UIEvent *)event;                    // called by UIApplication to dispatch events to views inside the window

- (CGPoint)convertPoint:(CGPoint)point toWindow:(UIWindow *)window;    // can be used to convert to another window
- (CGPoint)convertPoint:(CGPoint)point fromWindow:(UIWindow *)window;  // pass in nil to mean screen
- (CGRect)convertRect:(CGRect)rect toWindow:(UIWindow *)window;
- (CGRect)convertRect:(CGRect)rect fromWindow:(UIWindow *)window;

@end

UIKIT_EXTERN const UIWindowLevel UIWindowLevelNormal;
UIKIT_EXTERN const UIWindowLevel UIWindowLevelAlert;
UIKIT_EXTERN const UIWindowLevel UIWindowLevelStatusBar;

UIKIT_EXTERN NSString *const UIWindowDidBecomeVisibleNotification; // nil
UIKIT_EXTERN NSString *const UIWindowDidBecomeHiddenNotification;  // nil
UIKIT_EXTERN NSString *const UIWindowDidBecomeKeyNotification;     // nil
UIKIT_EXTERN NSString *const UIWindowDidResignKeyNotification;     // nil

// Each notification includes a nil object and a userInfo dictionary containing the
// begining and ending keyboard frame in screen coordinates. Use the various UIView and
// UIWindow convertRect facilities to get the frame in the desired coordinate system.
// Animation key/value pairs are only available for the "will" family of notification.
UIKIT_EXTERN NSString *const UIKeyboardWillShowNotification;
UIKIT_EXTERN NSString *const UIKeyboardDidShowNotification; 
UIKIT_EXTERN NSString *const UIKeyboardWillHideNotification; 
UIKIT_EXTERN NSString *const UIKeyboardDidHideNotification;

UIKIT_EXTERN NSString *const UIKeyboardFrameBeginUserInfoKey        __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2); // NSValue of CGRect
UIKIT_EXTERN NSString *const UIKeyboardFrameEndUserInfoKey          __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2); // NSValue of CGRect
UIKIT_EXTERN NSString *const UIKeyboardAnimationDurationUserInfoKey __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0); // NSNumber of double
UIKIT_EXTERN NSString *const UIKeyboardAnimationCurveUserInfoKey    __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0); // NSNumber of NSUInteger (UIViewAnimationCurve)

// Like the standard keyboard notifications above, these additional notifications include
// a nil object and begin/end frames of the keyboard in screen coordinates in the userInfo dictionary.
UIKIT_EXTERN NSString *const UIKeyboardWillChangeFrameNotification  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
UIKIT_EXTERN NSString *const UIKeyboardDidChangeFrameNotification   __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

// These keys are superseded by UIKeyboardFrameBeginUserInfoKey and UIKeyboardFrameEndUserInfoKey.
UIKIT_EXTERN NSString *const UIKeyboardCenterBeginUserInfoKey   __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_2_0,__IPHONE_3_2);
UIKIT_EXTERN NSString *const UIKeyboardCenterEndUserInfoKey     __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_2_0,__IPHONE_3_2);
UIKIT_EXTERN NSString *const UIKeyboardBoundsUserInfoKey        __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_2_0,__IPHONE_3_2);
