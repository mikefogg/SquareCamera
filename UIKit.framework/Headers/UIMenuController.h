//
//  UIMenuController.h
//  UIKit
//
//  Copyright (c) 2009-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>

typedef enum {
    UIMenuControllerArrowDefault, // up or down based on screen location
#if __IPHONE_3_2 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    UIMenuControllerArrowUp,
    UIMenuControllerArrowDown,
    UIMenuControllerArrowLeft,
    UIMenuControllerArrowRight,
#endif
} UIMenuControllerArrowDirection;

@class UIView;

UIKIT_CLASS_AVAILABLE(3_0) @interface UIMenuController : NSObject {
  @private
    CGRect _targetRect;
    UIMenuControllerArrowDirection _arrowDirection;
}

+ (UIMenuController *)sharedMenuController;

@property(nonatomic,getter=isMenuVisible) BOOL menuVisible;	    // default is NO
- (void)setMenuVisible:(BOOL)menuVisible animated:(BOOL)animated;

- (void)setTargetRect:(CGRect)targetRect inView:(UIView *)targetView;
@property(nonatomic) UIMenuControllerArrowDirection arrowDirection __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2); // default is UIMenuControllerArrowDefault
		
@property(nonatomic,copy) NSArray *menuItems __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2); // default is nil. these are in addition to the standard items

- (void)update;	

@property(nonatomic,readonly) CGRect menuFrame;

@end

UIKIT_EXTERN NSString *const UIMenuControllerWillShowMenuNotification;
UIKIT_EXTERN NSString *const UIMenuControllerDidShowMenuNotification;
UIKIT_EXTERN NSString *const UIMenuControllerWillHideMenuNotification;
UIKIT_EXTERN NSString *const UIMenuControllerDidHideMenuNotification;
UIKIT_EXTERN NSString *const UIMenuControllerMenuFrameDidChangeNotification;

UIKIT_CLASS_AVAILABLE(3_2) @interface UIMenuItem : NSObject {
  @private
    NSString *_title;
    SEL       _action;
    BOOL      _dontDismiss;
}

- (id)initWithTitle:(NSString *)title action:(SEL)action;

@property(nonatomic,copy) NSString *title;     // default is nil
@property(nonatomic)      SEL       action;    // default is NULL

@end
