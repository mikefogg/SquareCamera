//
//  UIPageViewController.h
//  UIKit
//
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <UIKit/UIViewController.h>

enum {
    UIPageViewControllerNavigationOrientationHorizontal = 0,
    UIPageViewControllerNavigationOrientationVertical = 1
};
typedef NSInteger UIPageViewControllerNavigationOrientation;

enum {
    UIPageViewControllerSpineLocationNone = 0, // Returned if 'spineLocation' is queried when 'transitionStyle' is not 'UIPageViewControllerTransitionStylePageCurl'.
    UIPageViewControllerSpineLocationMin = 1,  // Requires one view controller.
    UIPageViewControllerSpineLocationMid = 2,  // Requires two view controllers.
    UIPageViewControllerSpineLocationMax = 3   // Requires one view controller.
};
typedef NSInteger UIPageViewControllerSpineLocation; // Only pertains to 'UIPageViewControllerTransitionStylePageCurl'.

enum {
    UIPageViewControllerNavigationDirectionForward,
    UIPageViewControllerNavigationDirectionReverse
};
typedef NSInteger UIPageViewControllerNavigationDirection; // For 'UIPageViewControllerNavigationOrientationHorizontal', 'forward' is right-to-left, like pages in a book. For 'UIPageViewControllerNavigationOrientationVertical', bottom-to-top, like pages in a wall calendar.

enum {
    UIPageViewControllerTransitionStylePageCurl = 0 // Navigate between views via a page curl transition.
};
typedef NSInteger UIPageViewControllerTransitionStyle;

// Key for specifying spine location in options dictionary argument to initWithTransitionStyle:navigationOrientation:options:.
// Value should be a 'UIPageViewControllerSpineLocation' wrapped in an NSNumber.
// Only valid for use with page view controllers with transition style 'UIPageViewControllerTransitionStylePageCurl'.
UIKIT_EXTERN NSString * const UIPageViewControllerOptionSpineLocationKey;

@protocol UIPageViewControllerDelegate, UIPageViewControllerDataSource;

UIKIT_CLASS_AVAILABLE(5_0) @interface UIPageViewController : UIViewController {
}

- (id)initWithTransitionStyle:(UIPageViewControllerTransitionStyle)style navigationOrientation:(UIPageViewControllerNavigationOrientation)navigationOrientation options:(NSDictionary *)options;

@property (nonatomic, assign) id <UIPageViewControllerDelegate> delegate;
@property (nonatomic, assign) id <UIPageViewControllerDataSource> dataSource; // If nil, user gesture-driven navigation will be disabled.
@property (nonatomic, readonly) UIPageViewControllerTransitionStyle transitionStyle;
@property (nonatomic, readonly) UIPageViewControllerNavigationOrientation navigationOrientation;
@property (nonatomic, readonly) UIPageViewControllerSpineLocation spineLocation; // If transition style is 'UIPageViewControllerTransitionStylePageCurl', default is 'UIPageViewControllerSpineLocationMin', otherwise 'UIPageViewControllerSpineLocationNone'.

// Whether client content appears on both sides of each page. If 'NO', content on page front will partially show through back.
// If 'UIPageViewControllerSpineLocationMid' is set, 'doubleSided' is set to 'YES'. Setting 'NO' when spine location is mid results in an exception.
@property (nonatomic, getter=isDoubleSided) BOOL doubleSided; // Default is 'NO'.

// An array of UIGestureRecognizers pre-configured to handle user interaction. Initially attached to a view in the UIPageViewController's hierarchy, they can be placed on an arbitrary view to change the region in which the page view controller will respond to user gestures.
@property(nonatomic, readonly) NSArray *gestureRecognizers;

@property (nonatomic, readonly) NSArray *viewControllers;

// Set visible view controllers, optionally with animation. Array should only include view controllers that will be visible after the animation has completed.
// For transition style 'UIPageViewControllerTransitionStylePageCurl', if 'doubleSided' is 'YES' and the spine location is not 'UIPageViewControllerSpineLocationMid', two view controllers must be included, as the latter view controller is used as the back.
- (void)setViewControllers:(NSArray *)viewControllers direction:(UIPageViewControllerNavigationDirection)direction animated:(BOOL)animated completion:(void (^)(BOOL finished))completion;

@end

@protocol UIPageViewControllerDelegate <NSObject>

@optional

// Sent when a gesture-initiated transition ends. The 'finished' parameter indicates whether the animation finished, while the 'completed' parameter indicates whether the transition completed or bailed out (if the user let go early).
- (void)pageViewController:(UIPageViewController *)pageViewController didFinishAnimating:(BOOL)finished previousViewControllers:(NSArray *)previousViewControllers transitionCompleted:(BOOL)completed;

// Delegate may specify a different spine location for after the interface orientation change. Only sent for transition style 'UIPageViewControllerTransitionStylePageCurl'.
// Delegate may set new view controllers or update double-sided state within this method's implementation as well.
- (UIPageViewControllerSpineLocation)pageViewController:(UIPageViewController *)pageViewController spineLocationForInterfaceOrientation:(UIInterfaceOrientation)orientation;

@end

@protocol UIPageViewControllerDataSource <NSObject>

@required

// In terms of navigation direction. For example, for 'UIPageViewControllerNavigationOrientationHorizontal', view controllers coming 'before' would be to the left of the argument view controller, those coming 'after' would be to the right.
// Return 'nil' to indicate that no more progress can be made in the given direction.
// For gesture-initiated transitions, the page view controller obtains view controllers via these methods, so use of setViewControllers:direction:animated:completion: is not required.
- (UIViewController *)pageViewController:(UIPageViewController *)pageViewController viewControllerBeforeViewController:(UIViewController *)viewController;
- (UIViewController *)pageViewController:(UIPageViewController *)pageViewController viewControllerAfterViewController:(UIViewController *)viewController;

@end
