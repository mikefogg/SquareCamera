//
//  UINavigationController.h
//  UIKit
//
//  Copyright (c) 2007-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIViewController.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIInterface.h>
#import <UIKit/UIGeometry.h>

/*!
 UINavigationController manages a stack of view controllers and a navigation bar.
 It performs horizontal view transitions for pushed and popped views while keeping the navigation bar in sync.
 
 To use in your application, add its view to the view hierarchy, then push and pop controllers.
 Most clients will not need to subclass UINavigationController.
 
 If a navigation controller is nested in a toolbar controller, it uses the title and toolbar attributes of the bottom view controller on the stack.
 
 UINavigationController is rotatable if its top view controller is rotatable.
 Navigation between controllers with non-uniform rotatability is currently not supported.
*/

UIKIT_EXTERN const CGFloat UINavigationControllerHideShowBarDuration;

@class UIView, UINavigationBar, UINavigationItem, UIToolbar, UILayoutContainerView;
@protocol UINavigationControllerDelegate;

UIKIT_CLASS_AVAILABLE(2_0) @interface UINavigationController : UIViewController {
  @package
    UIView           *_containerView;
    UINavigationBar  *_navigationBar;
    Class             _navigationBarClass;
    UIToolbar 	     *_toolbar;
    UIView           *_navigationTransitionView;

    UIEdgeInsets      _currentScrollContentInsetDelta;
    UIEdgeInsets      _previousScrollContentInsetDelta;
    CGFloat           _previousScrollContentOffsetDelta;
    CGFloat			  _bottomInsetDelta;
    
    UIViewController *_disappearingViewController;
    
    id <UINavigationControllerDelegate> _delegate;

    UIBarStyle _savedNavBarStyleBeforeSheet;
    UIBarStyle _savedToolBarStyleBeforeSheet;

    struct {
        unsigned int isAppearingAnimated:1;
        unsigned int isAlreadyPoppingNavigationItem:1;
        unsigned int isNavigationBarHidden:1;
        unsigned int isToolbarShown:1;
        unsigned int needsDeferredTransition:1;
        unsigned int isTransitioning:1;
        unsigned int lastOperation:4;
        unsigned int lastOperationAnimated:1;
        unsigned int deferredTransition:8;
        unsigned int didPreloadKeyboardAnimation:1;
        unsigned int didHideBottomBar:1;
        unsigned int isChangingOrientationForPop:1;
        unsigned int pretendNavBarHidden:1;
        unsigned int avoidMovingNavBarOffscreenBeforeUnhiding:1;
        unsigned int searchBarHidNavBar:1; 
        unsigned int useSystemPopoverBarAppearance:1;
    } _navigationControllerFlags;
}

- (id)initWithRootViewController:(UIViewController *)rootViewController; // Convenience method pushes the root view controller without animation.

- (void)pushViewController:(UIViewController *)viewController animated:(BOOL)animated; // Uses a horizontal slide transition. Has no effect if the view controller is already in the stack.

- (UIViewController *)popViewControllerAnimated:(BOOL)animated; // Returns the popped controller.
- (NSArray *)popToViewController:(UIViewController *)viewController animated:(BOOL)animated; // Pops view controllers until the one specified is on top. Returns the popped controllers.
- (NSArray *)popToRootViewControllerAnimated:(BOOL)animated; // Pops until there's only a single view controller left on the stack. Returns the popped controllers.

@property(nonatomic,readonly,retain) UIViewController *topViewController; // The top view controller on the stack.
@property(nonatomic,readonly,retain) UIViewController *visibleViewController; // Return modal view controller if it exists. Otherwise the top view controller.

@property(nonatomic,copy) NSArray *viewControllers; // The current view controller stack.
- (void)setViewControllers:(NSArray *)viewControllers animated:(BOOL)animated __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0); // If animated is YES, then simulate a push or pop depending on whether the new top view controller was previously in the stack.

@property(nonatomic,getter=isNavigationBarHidden) BOOL navigationBarHidden;
- (void)setNavigationBarHidden:(BOOL)hidden animated:(BOOL)animated; // Hide or show the navigation bar. If animated, it will transition vertically using UINavigationControllerHideShowBarDuration.
@property(nonatomic,readonly) UINavigationBar *navigationBar; // The navigation bar managed by the controller. Pushing, popping or setting navigation items on a managed navigation bar is not supported.

@property(nonatomic,getter=isToolbarHidden) BOOL toolbarHidden __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0); // Defaults to YES, i.e. hidden.
- (void)setToolbarHidden:(BOOL)hidden animated:(BOOL)animated __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0); // Hide or show the toolbar at the bottom of the screen. If animated, it will transition vertically using UINavigationControllerHideShowBarDuration.
@property(nonatomic,readonly) UIToolbar *toolbar __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0); // For use when presenting an action sheet.

@property(nonatomic, assign) id<UINavigationControllerDelegate> delegate;

@end

@protocol UINavigationControllerDelegate <NSObject>

@optional

// Called when the navigation controller shows a new top view controller via a push, pop or setting of the view controller stack.
- (void)navigationController:(UINavigationController *)navigationController willShowViewController:(UIViewController *)viewController animated:(BOOL)animated;
- (void)navigationController:(UINavigationController *)navigationController didShowViewController:(UIViewController *)viewController animated:(BOOL)animated;

@end

@interface UIViewController (UINavigationControllerItem)

@property(nonatomic,readonly,retain) UINavigationItem *navigationItem; // Created on-demand so that a view controller may customize its navigation appearance.
@property(nonatomic) BOOL hidesBottomBarWhenPushed; // If YES, then when this view controller is pushed into a controller hierarchy with a bottom bar (like a tab bar), the bottom bar will slide out. Default is NO.
@property(nonatomic,readonly,retain) UINavigationController *navigationController; // If this view controller has been pushed onto a navigation controller, return it.

@end

@interface UIViewController (UINavigationControllerContextualToolbarItems)

@property (nonatomic, retain) NSArray *toolbarItems __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
- (void)setToolbarItems:(NSArray *)toolbarItems animated:(BOOL)animated __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

@end
