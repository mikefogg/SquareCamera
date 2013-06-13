//
//  UIToolbar.h
//  UIKit
//
//  Copyright (c) 2006-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIView.h>
#import <UIKit/UIInterface.h>
#import <UIKit/UIApplication.h>
#import <UIKit/UIBarButtonItem.h>

typedef enum {
    UIToolbarPositionAny = 0,
    UIToolbarPositionBottom = 1,
    UIToolbarPositionTop = 2,
} UIToolbarPosition;

@class UIBarButtonItem, UIColor;

UIKIT_CLASS_AVAILABLE(2_0) @interface UIToolbar : UIView {
  @private
    id                     _delegate;
    NSArray               *_items;
    UIColor               *_tintColor;
    struct {
        unsigned int barStyle:2;
        unsigned int mode:2;
        unsigned int alertShown:1;
        unsigned int wasEnabled:1;
        unsigned int downButtonSentAction:1;
        unsigned int isTranslucent:1;
        unsigned int forceTopBarAppearance:1;
    } _toolbarFlags;
    CFMutableDictionaryRef _groups;
    NSArray               *_buttonItems;
    NSInteger              _currentButtonGroup;
    CFMutableArrayRef      _hiddenItems;
    NSInteger              _pressedTag;
    CGFloat                _extraEdgeInsets;
    UIView                *_backgroundView;
    id                     _appearanceStorage;
}

@property(nonatomic)        UIBarStyle barStyle;    // default is UIBarStyleDefault (blue)
@property(nonatomic,copy)   NSArray   *items;       // get/set visible UIBarButtonItem. default is nil. changes not animated. shown in order
@property(nonatomic,assign,getter=isTranslucent) BOOL translucent __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0); // Default is NO. Always YES if barStyle is set to UIBarStyleBlackTranslucent

- (void)setItems:(NSArray *)items animated:(BOOL)animated;   // will fade in or out or reorder and adjust spacing

/* Default tintColor is nil. When non-nil, bordered buttons and segmented controls in the toolbar
 will pick up the same tint unless their tints are independently set.
 */
@property(nonatomic,retain) UIColor   *tintColor  UI_APPEARANCE_SELECTOR;

/* Use these methods to set and access custom background images for toolbars.
      Default is nil. When non-nil the image will be used instead of the system image for toolbars in the
 specified position.
      For the barMetrics argument, UIBarMetricsDefault is the fallback.
 
 DISCUSSION: Interdependence of barStyle, tintColor, backgroundImage.
 When barStyle or tintColor is set as well as the bar's background image,
 the bar buttons (unless otherwise customized) will inherit the underlying
 barStyle or tintColor.
 */
- (void)setBackgroundImage:(UIImage *)backgroundImage forToolbarPosition:(UIToolbarPosition)topOrBottom barMetrics:(UIBarMetrics)barMetrics __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;
- (UIImage *)backgroundImageForToolbarPosition:(UIToolbarPosition)topOrBottom barMetrics:(UIBarMetrics)barMetrics __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;

@end
