//
//  UITabBarController.h
//  UIKit
//
//  Copyright (c) 2007-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIViewController.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UITabBar.h>

/*!
 UITabBarController manages a button bar and transition view, for an application with multiple top-level modes.
 
 To use in your application, add its view to the view hierarchy, then add top-level view controllers in order.
 Most clients will not need to subclass UITabBarController.

 If more than five view controllers are added to a tab bar controller, only the first four will display.
 The rest will be accessible under an automatically generated More item.
 
 UITabBarController is rotatable if all of its view controllers are rotatable.
 */

@class UIView, UIImage, UINavigationController, UITabBarItem;
@protocol UITabBarControllerDelegate;

UIKIT_CLASS_AVAILABLE(2_0) @interface UITabBarController : UIViewController <UITabBarDelegate, NSCoding> {
  @package
    UITabBar               *_tabBar;
    
    UIView                 *_containerView;
    UIView                 *_viewControllerTransitionView;

    id                      _tabBarItemsToViewControllers;
    UIViewController       *_selectedViewController;

    UINavigationController *_moreNavigationController;
    NSArray                *_customizableViewControllers;
    
    id<UITabBarControllerDelegate> _delegate;
    
    UIViewController       *_selectedViewControllerDuringWillAppear;
        
    UIViewController       *_transientViewController;
    
    NSUInteger              _maxItems;
    
    struct {
	unsigned int isShowingMoreItem:1;
	unsigned int needsToRebuildItems:1;
	unsigned int isBarHidden:1;
    unsigned int editButtonOnLeft:1;
    } _tabBarControllerFlags;
}

@property(nonatomic,copy) NSArray *viewControllers;
// If the number of view controllers is greater than the number displayable by a tab bar, a "More" navigation controller will automatically be shown.
// The "More" navigation controller will not be returned by -viewControllers, but it may be returned by -selectedViewController.
- (void)setViewControllers:(NSArray *)viewControllers animated:(BOOL)animated;

@property(nonatomic,assign) UIViewController *selectedViewController; // This may return the "More" navigation controller if it exists.
@property(nonatomic) NSUInteger selectedIndex;

@property(nonatomic,readonly) UINavigationController *moreNavigationController; // Returns the "More" navigation controller, creating it if it does not already exist.
@property(nonatomic,copy) NSArray *customizableViewControllers; // If non-nil, then the "More" view will include an "Edit" button that displays customization UI for the specified controllers. By default, all view controllers are customizable.

@property(nonatomic,readonly) UITabBar *tabBar __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0); // Provided for -[UIActionSheet showFromTabBar:]. Attempting to modify the contents of the tab bar directly will throw an exception.

@property(nonatomic,assign) id<UITabBarControllerDelegate> delegate;

@end

@protocol UITabBarControllerDelegate <NSObject>
@optional
- (BOOL)tabBarController:(UITabBarController *)tabBarController shouldSelectViewController:(UIViewController *)viewController __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
- (void)tabBarController:(UITabBarController *)tabBarController didSelectViewController:(UIViewController *)viewController;

- (void)tabBarController:(UITabBarController *)tabBarController willBeginCustomizingViewControllers:(NSArray *)viewControllers __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
- (void)tabBarController:(UITabBarController *)tabBarController willEndCustomizingViewControllers:(NSArray *)viewControllers changed:(BOOL)changed __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
- (void)tabBarController:(UITabBarController *)tabBarController didEndCustomizingViewControllers:(NSArray *)viewControllers changed:(BOOL)changed;
@end

@interface UIViewController (UITabBarControllerItem)

@property(nonatomic,retain) UITabBarItem *tabBarItem; // Automatically created lazily with the view controller's title if it's not set explicitly.

@property(nonatomic,readonly,retain) UITabBarController *tabBarController; // If the view controller has a tab bar controller as its ancestor, return it. Returns nil otherwise.

@end
