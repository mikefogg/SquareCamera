//
//  UINavigationBar.h
//  UIKit
//
//  Copyright (c) 2005-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIView.h>
#import <UIKit/UIInterface.h>
#import <UIKit/UIFont.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIButton.h>
#import <UIKit/UIBarButtonItem.h>

@class UINavigationItem, UIBarButtonItem, UIImage, UIColor;
@protocol UINavigationBarDelegate;

UIKIT_CLASS_AVAILABLE(2_0) @interface UINavigationBar : UIView <NSCoding> {
  @private
    NSMutableArray *_itemStack;
    CGFloat         _rightMargin;
    unsigned        _state;
    id              _delegate;
    UIView         *_backgroundView;
    UIView         *_titleView;
    NSArray        *_leftViews;
    NSArray        *_rightViews;
    UIView         *_prompt;
    UIView         *_accessoryView;
    UIColor        *_tintColor;
    id              _appearanceStorage;
    struct {
        unsigned int animate:1;
        unsigned int animationDisabledCount:10;
        unsigned int transitioningBarStyle:1;
        unsigned int newBarStyle:3;
        unsigned int barStyle:3;
        unsigned int isTranslucent:1;
        unsigned int disableLayout:1;
        unsigned int backPressed:1;
        unsigned int animatePromptChange:1;
        unsigned int pendingHideBackButton:1;
        unsigned int titleAutosizesToFit:1;
        unsigned int usingNewAPI:1;
        unsigned int minibar:1;
        unsigned int forceFullHeightInLandscape:1;
        unsigned int isLocked:1;
        unsigned int shouldUpdatePromptAfterTransition:1;
        unsigned int crossfadeItems:1;
        unsigned int autoAdjustTitle:1;
        unsigned int isContainedInPopover:1;
        unsigned int needsDrawRect:1;
        unsigned int animationCleanupCancelled:1;
        unsigned int forceLayout:1;
        unsigned int layoutInProgress:1;
    } _navbarFlags;
}

@property(nonatomic,assign) UIBarStyle barStyle;
@property(nonatomic,assign) id delegate;
@property(nonatomic,assign,getter=isTranslucent) BOOL translucent __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0); // Default is NO. Always YES if barStyle is set to UIBarStyleBlackTranslucent

// Pushing a navigation item displays the item's title in the center of the navigation bar.
// The previous top navigation item (if it exists) is displayed as a "back" button on the left.
- (void)pushNavigationItem:(UINavigationItem *)item animated:(BOOL)animated;
- (UINavigationItem *)popNavigationItemAnimated:(BOOL)animated; // Returns the item that was popped.

@property(nonatomic,readonly,retain) UINavigationItem *topItem;
@property(nonatomic,readonly,retain) UINavigationItem *backItem;

@property(nonatomic,copy) NSArray *items;
- (void)setItems:(NSArray *)items animated:(BOOL)animated; // If animated is YES, then simulate a push or pop depending on whether the new top item was previously in the stack.

@property(nonatomic,retain) UIColor *tintColor UI_APPEARANCE_SELECTOR;

/* In general, you should specify a value for the normal state to be used by other states which don't have a custom value set.
 
 Similarly, when a property is dependent on the bar metrics (on the iPhone in landscape orientation, bars have a different height from standard), be sure to specify a value for UIBarMetricsDefault.
 
 DISCUSSION: Interdependence of barStyle, tintColor, backgroundImage.
 When barStyle or tintColor is set as well as the bar's background image,
 the bar buttons (unless otherwise customized) will inherit the underlying
 barStyle or tintColor.
 */
- (void)setBackgroundImage:(UIImage *)backgroundImage forBarMetrics:(UIBarMetrics)barMetrics __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;
- (UIImage *)backgroundImageForBarMetrics:(UIBarMetrics)barMetrics __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;

/* You may specify the font, text color, text shadow color, and text shadow offset for the title in the text attributes dictionary, using the keys found in UIStringDrawing.h.
 */
@property(nonatomic,copy) NSDictionary *titleTextAttributes __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;

- (void)setTitleVerticalPositionAdjustment:(CGFloat)adjustment forBarMetrics:(UIBarMetrics)barMetrics __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;
- (CGFloat)titleVerticalPositionAdjustmentForBarMetrics:(UIBarMetrics)barMetrics __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;

@end

@protocol UINavigationBarDelegate <NSObject>

@optional

- (BOOL)navigationBar:(UINavigationBar *)navigationBar shouldPushItem:(UINavigationItem *)item; // called to push. return NO not to.
- (void)navigationBar:(UINavigationBar *)navigationBar didPushItem:(UINavigationItem *)item;    // called at end of animation of push or immediately if not animated
- (BOOL)navigationBar:(UINavigationBar *)navigationBar shouldPopItem:(UINavigationItem *)item;  // same as push methods
- (void)navigationBar:(UINavigationBar *)navigationBar didPopItem:(UINavigationItem *)item;

@end

UIKIT_CLASS_AVAILABLE(2_0) @interface UINavigationItem : NSObject <NSCoding> {
 @private
    NSString        *_title;
    NSString        *_backButtonTitle;
    UIBarButtonItem *_backBarButtonItem;
    NSString        *_prompt;
    NSInteger        _tag;
    id               _context;
    UINavigationBar *_navigationBar;
    UIView          *_defaultTitleView;
    UIView          *_titleView;
    UIView          *_backButtonView;
    NSArray         *_leftBarButtonItems;
    NSArray         *_rightBarButtonItems;
    NSArray         *_customLeftViews;
    NSArray         *_customRightViews;
    BOOL             _hidesBackButton;
    BOOL             _leftItemsSupplementBackButton;
    UIImageView     *_frozenTitleView;
}

- (id)initWithTitle:(NSString *)title;

@property(nonatomic,copy)   NSString        *title;             // Title when topmost on the stack. default is nil
@property(nonatomic,retain) UIBarButtonItem *backBarButtonItem; // Bar button item to use for the back button in the child navigation item.
@property(nonatomic,retain) UIView          *titleView;         // Custom view to use in lieu of a title. May be sized horizontally. Only used when item is topmost on the stack.

@property(nonatomic,copy)   NSString *prompt;     // Explanatory text to display above the navigation bar buttons.

@property(nonatomic,assign) BOOL hidesBackButton; // If YES, this navigation item will hide the back button when it's on top of the stack.
- (void)setHidesBackButton:(BOOL)hidesBackButton animated:(BOOL)animated;

/* Use these properties to set multiple items in a navigation bar.
 The older single properties (leftBarButtonItem and rightBarButtonItem) now refer to 
 the first item in the respective array of items.
 
 NOTE: You'll achieve the best results if you use either the singular properties or
 the plural properties consistently and don't try to mix them.
 
   leftBarButtonItems are placed in the navigation bar left to right with the first
 item in the list at the left outside edge and left aligned.
   rightBarButtonItems are placed right to left with the first item in the list at
 the right outside edge and right aligned.
 */
@property(nonatomic,copy) NSArray *leftBarButtonItems __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
@property(nonatomic,copy) NSArray *rightBarButtonItems __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
- (void)setLeftBarButtonItems:(NSArray *)items animated:(BOOL)animated __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0); 
- (void)setRightBarButtonItems:(NSArray *)items animated:(BOOL)animated __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

/* By default, the leftItemsSupplementBackButton property is NO. In this case, 
 the back button is not drawn and the left item or items replace it. If you
 would like the left items to appear in addition to the back button (as opposed to instead of it)
 set leftItemsSupplementBackButton to YES.
 */
@property(nonatomic) BOOL leftItemsSupplementBackButton __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);


// Some navigation items want to display a custom left or right item when they're on top of the stack.
// A custom left item replaces the regular back button unless you set leftItemsSupplementBackButton to YES
@property(nonatomic,retain) UIBarButtonItem *leftBarButtonItem;
@property(nonatomic,retain) UIBarButtonItem *rightBarButtonItem;
- (void)setLeftBarButtonItem:(UIBarButtonItem *)item animated:(BOOL)animated;
- (void)setRightBarButtonItem:(UIBarButtonItem *)item animated:(BOOL)animated;

@end
