//
//  UISplitViewController.h
//  UIKit
//
//  Copyright (c) 2009-2011, Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol UISplitViewControllerDelegate;

UIKIT_CLASS_AVAILABLE(3_2) @interface UISplitViewController : UIViewController {
  @package
    id                      _delegate;
    UIBarButtonItem         *_barButtonItem;
    NSString                *_buttonTitle;
    UIPopoverController     *_hiddenPopoverController;
    UIView                  *_rotationSnapshotView;
    float                   _masterColumnWidth;
    float                   _gutterWidth;
    float                   _cornerRadius;
    UIInterfaceOrientation  _rotatingFromOrientation;
    UIInterfaceOrientation  _lastPresentedOrientation;
    CGRect                  _rotatingFromMasterViewFrame;
    CGRect                  _rotatingToMasterViewFrame;
    
    NSArray                 *_cornerImageViews;
}

@property(nonatomic, copy) NSArray *viewControllers;  
@property(nonatomic, assign) id <UISplitViewControllerDelegate> delegate;
@end


@protocol UISplitViewControllerDelegate

@optional

// Called when a button should be added to a toolbar for a hidden view controller
- (void)splitViewController: (UISplitViewController*)svc willHideViewController:(UIViewController *)aViewController withBarButtonItem:(UIBarButtonItem*)barButtonItem forPopoverController: (UIPopoverController*)pc;

// Called when the view is shown again in the split view, invalidating the button and popover controller
- (void)splitViewController: (UISplitViewController*)svc willShowViewController:(UIViewController *)aViewController invalidatingBarButtonItem:(UIBarButtonItem *)barButtonItem;

// Called when the view controller is shown in a popover so the delegate can take action like hiding other popovers.
- (void)splitViewController: (UISplitViewController*)svc popoverController: (UIPopoverController*)pc willPresentViewController:(UIViewController *)aViewController;

// Returns YES if a view controller should be hidden by the split view controller in a given orientation.
// (This method is only called on the leftmost view controller and only discriminates portrait from landscape.)
- (BOOL)splitViewController: (UISplitViewController*)svc shouldHideViewController:(UIViewController *)vc inOrientation:(UIInterfaceOrientation)orientation  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

@end


@interface UIViewController (UISplitViewController)

@property(nonatomic,readonly,retain) UISplitViewController *splitViewController; // If the view controller has a split view controller as its ancestor, return it. Returns nil otherwise.

@end
