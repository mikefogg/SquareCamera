//
//  UIViewController.h
//  UIKit
//
//  Copyright (c) 2007-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIApplication.h>

/*
  UIViewController is a generic controller base class that manages a view.  It has methods that are called
  when a view appears or disappears.
 
  Subclasses can override -loadView to create their custom view hierarchy, or specify a nib name to be loaded
  automatically.  This class is also a good place for delegate & datasource methods, and other controller
  stuff.
*/

@class UIView, UIImage;
@class UINavigationItem, UIBarButtonItem, UITabBarItem;
@class UITabBarController, UINavigationController, UISearchDisplayController;
@class UIPopoverController, UIDimmingView, UIDropShadowView;
@class UIStoryboard, UIStoryboardSegue;

typedef enum {
    UIModalTransitionStyleCoverVertical = 0,
    UIModalTransitionStyleFlipHorizontal,
    UIModalTransitionStyleCrossDissolve,
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_3_2
    UIModalTransitionStylePartialCurl,
#endif
} UIModalTransitionStyle;

typedef enum {
    UIModalPresentationFullScreen = 0,
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_3_2
    UIModalPresentationPageSheet,
    UIModalPresentationFormSheet,
    UIModalPresentationCurrentContext,
#endif
} UIModalPresentationStyle;


UIKIT_CLASS_AVAILABLE(2_0) @interface UIViewController : UIResponder <NSCoding, UIAppearanceContainer> {
    @package
    UIView           *_view;
    UITabBarItem     *_tabBarItem;
    UINavigationItem *_navigationItem;
    NSArray          *_toolbarItems;
    NSString         *_title;
    
    NSString         *_nibName;
    NSBundle         *_nibBundle;
    
    UIViewController *_parentViewController; // Nonretained
    
    UIViewController *_childModalViewController;
    UIViewController *_parentModalViewController; // Nonretained
    UIViewController *_previousRootViewController; // Nonretained    
    UIView           *_modalTransitionView;
    UIResponder	     *_modalPreservedFirstResponder;
    UIResponder      *_defaultFirstResponder;
    UIDimmingView    *_dimmingView;
    UIDropShadowView *_dropShadowView;

    id                _currentAction;
    UIStoryboard     *_storyboard;
    NSArray          *_storyboardSegueTemplates;
    NSDictionary     *_externalObjectsTableForViewLoading;
    
    UIView           *_savedHeaderSuperview;
    UIView           *_savedFooterSuperview;
    
    UIBarButtonItem  *_editButtonItem;
    
    UISearchDisplayController *_searchDisplayController;
    
    UIModalTransitionStyle _modalTransitionStyle;
    UIModalPresentationStyle _modalPresentationStyle;
    
    UIInterfaceOrientation _lastKnownInterfaceOrientation;

    UIPopoverController*    _popoverController;
    UIView *_containerViewInSheet;
    CGSize _contentSizeForViewInPopover;
    CGSize _formSheetSize;

    void (^_afterAppearance)(void);    
    NSInteger _explicitAppearanceTransitionLevel;

    struct {
        unsigned int appearState:2;
        unsigned int isEditing:1;
        unsigned int isPerformingModalTransition:1;
        unsigned int hidesBottomBarWhenPushed:1;
        unsigned int autoresizesArchivedViewToFullSize:1;
        unsigned int viewLoadedFromControllerNib:1;
        unsigned int isRootViewController:1;
        unsigned int isSheet:1;
        unsigned int isSuspended:1;
        unsigned int wasApplicationFrameAtSuspend:1;
        unsigned int wantsFullScreenLayout:1;
        unsigned int shouldUseFullScreenLayout:1;
        unsigned int allowsAutorotation:1;
        unsigned int searchControllerRetained:1;
        unsigned int oldModalInPopover:1;
        unsigned int isModalInPopover:1;
        unsigned int restoreDeepestFirstResponder:1;
        unsigned int isInWillRotateCallback:1;
        unsigned int disallowMixedOrientationPresentations:1;
        unsigned int isFinishingModalTransition:1;
        unsigned int definesPresentationContext:1;
        unsigned int providesPresentationContextTransitionStyle:1;        
        unsigned int containmentSupport:1;
        unsigned int isSettingAppearState:1;
        unsigned int isInAnimatedVCTransition:1;
        unsigned int presentationIsChanging:1;
        unsigned int containmentIsChanging:1;
        unsigned int explicitTransitionIsAppearing:1;
        unsigned int disableAppearanceTransitions:1;
        unsigned int needsDidMoveCleanup:1;        
        unsigned int suppressesBottomBar:1;
        unsigned int disableRootPromotion:1;
        unsigned int interfaceOrientationReentranceGuard:1;
        unsigned int isExecutingAfterAppearance:1;        
    } _viewControllerFlags;
}

/*
  The designated initializer. If you subclass UIViewController, you must call the super implementation of this
  method, even if you aren't using a NIB.  (As a convenience, the default init method will do this for you,
  and specify nil for both of this methods arguments.) In the specified NIB, the File's Owner proxy should
  have its class set to your view controller subclass, with the view outlet connected to the main view. If you
  invoke this method with a nil nib name, then this class' -loadView method will attempt to load a NIB whose
  name is the same as your view controller's class. If no such NIB in fact exists then you must either call
  -setView: before -view is invoked, or override the -loadView method to set up your views programatically.
*/
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil;

@property(nonatomic,retain) UIView *view; // The getter first invokes [self loadView] if the view hasn't been set yet. Subclasses must call super if they override the setter or getter.
- (void)loadView; // This is where subclasses should create their custom view hierarchy if they aren't using a nib. Should never be called directly.
- (void)viewWillUnload __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
- (void)viewDidLoad; // Called after the view has been loaded. For view controllers created in code, this is after -loadView. For view controllers unarchived from a nib, this is after the view is set.
- (void)viewDidUnload __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0); // Called after the view controller's view is released and set to nil. For example, a memory warning which causes the view to be purged. Not invoked as a result of -dealloc.
- (BOOL)isViewLoaded __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

@property(nonatomic, readonly, copy) NSString *nibName;     // The name of the nib to be loaded to instantiate the view.
@property(nonatomic, readonly, retain) NSBundle *nibBundle; // The bundle from which to load the nib.
@property(nonatomic, readonly, retain) UIStoryboard *storyboard __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

- (void)performSegueWithIdentifier:(NSString *)identifier sender:(id)sender __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

- (void)viewWillAppear:(BOOL)animated;    // Called when the view is about to made visible. Default does nothing
- (void)viewDidAppear:(BOOL)animated;     // Called when the view has been fully transitioned onto the screen. Default does nothing
- (void)viewWillDisappear:(BOOL)animated; // Called when the view is dismissed, covered or otherwise hidden. Default does nothing
- (void)viewDidDisappear:(BOOL)animated;  // Called after the view was dismissed, covered or otherwise hidden. Default does nothing

// Called just before the view controller's view's layoutSubviews method is invoked. Subclasses can implement as necessary. The default is a nop.
- (void)viewWillLayoutSubviews __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
// Called just after the view controller's view's layoutSubviews method is invoked. Subclasses can implement as necessary. The default is a nop.
- (void)viewDidLayoutSubviews __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

@property(nonatomic,copy) NSString *title;  // Localized title for use by a parent controller.

- (void)didReceiveMemoryWarning; // Called when the parent application receives a memory warning. Default implementation releases the view if it doesn't have a superview.

/*
  If this view controller is a child of a containing view controller (e.g. a navigation controller or tab bar
  controller,) this is the containing view controller.  Note that as of 5.0 this no longer will return the
  presenting view controller.
*/
@property(nonatomic,readonly) UIViewController *parentViewController;

// This property has been replaced by presentedViewController. It will be DEPRECATED, plan accordingly.
@property(nonatomic,readonly) UIViewController *modalViewController; 

// The view controller that was presented by this view controller or its nearest ancestor.
@property(nonatomic,readonly) UIViewController *presentedViewController  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

// The view controller that presented this view controller (or its farthest ancestor.)
@property(nonatomic,readonly) UIViewController *presentingViewController __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

/*
  Determines which parent view controller's view should be presented over for presentations of type
  UIModalPresentationCurrentContext.  If no ancestor view controller has this flag set, then the presenter
  will be the root view controller.
*/
@property(nonatomic,assign) BOOL definesPresentationContext __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

// A controller that defines the presentation context can also specify the modal transition style if this property is true.
@property(nonatomic,assign) BOOL providesPresentationContextTransitionStyle __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

/*
  These four methods can be used in a view controller's appearance callbacks to determine if it is being
  presented, dismissed, or added or removed as a child view controller. For example, a view controller can
  check if it is disappearing because it was dismissed or popped by asking itself in its viewWillDisappear:
  method by checking the expression ([self isDismissing] || [self isMovingFromParentViewController]).
*/

- (BOOL)isBeingPresented __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
- (BOOL)isBeingDismissed __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

- (BOOL)isMovingToParentViewController __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
- (BOOL)isMovingFromParentViewController __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

/*
  The next two methods are replacements for presentModalViewController:animated and
  dismissModalViewControllerAnimated: The completion handler, if provided, will be invoked after the presented
  controllers viewDidAppear: callback is invoked.
*/
- (void)presentViewController:(UIViewController *)viewControllerToPresent animated: (BOOL)flag completion:(void (^)(void))completion __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
// The completion handler, if provided, will be invoked after the dismissed controller's viewDidDisappear: callback is invoked.
- (void)dismissViewControllerAnimated: (BOOL)flag completion: (void (^)(void))completion __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

// Display another view controller as a modal child. Uses a vertical sheet transition if animated.This method has been replaced by presentViewController:animated:completion:
// It will be DEPRECATED, plan accordingly.
- (void)presentModalViewController:(UIViewController *)modalViewController animated:(BOOL)animated; 

// Dismiss the current modal child. Uses a vertical sheet transition if animated. This method has been replaced by dismissViewControllerAnimated:completion:
// It will be DEPRECATED, plan accordingly.
- (void)dismissModalViewControllerAnimated:(BOOL)animated;

/*
  Defines the transition style that will be used for this view controller when it is presented modally. Set
  this property on the view controller to be presented, not the presenter.  Defaults to
  UIModalTransitionStyleCoverVertical.
*/
@property(nonatomic,assign) UIModalTransitionStyle modalTransitionStyle __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
@property(nonatomic,assign) UIModalPresentationStyle modalPresentationStyle __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2);

// Presentation modes may keep the keyboard visible when not required. Default implementation affects UIModalPresentationFormSheet visibility.
- (BOOL)disablesAutomaticKeyboardDismissal __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_3);

@property(nonatomic,assign) BOOL wantsFullScreenLayout __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

@end

// To make it more convenient for applications to adopt rotation, a view controller may implement the below methods. Your UIWindow's frame should use [UIScreen mainScreen].bounds as its frame.
@interface UIViewController (UIViewControllerRotation)

// call this method when your return value from shouldAutorotateToInterfaceOrientation: changes
// if the current interface orientation does not match the current device orientation, a rotation may occur provided all relevant view controllers now return YES from shouldAutorotateToInterfaceOrientation:
+ (void)attemptRotationToDeviceOrientation __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

// Override to allow rotation. Default returns YES only for UIInterfaceOrientationPortrait
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation;

// The rotating header and footer views will slide out during the rotation and back in once it has completed.
- (UIView *)rotatingHeaderView;     // Must be in the view hierarchy. Default returns nil.
- (UIView *)rotatingFooterView;     // Must be in the view hierarchy. Default returns nil.

@property(nonatomic,readonly) UIInterfaceOrientation interfaceOrientation;

// Notifies when rotation begins, reaches halfway point and ends.
- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration;
- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation;

// Faster one-part variant, called from within a rotating animation block, for additional animations during rotation.
// A subclass may override this method, or the two-part variants below, but not both.
- (void)willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

// Slower two-part variant, called from within a rotating animation block, for additional animations during rotation.
// A subclass may override these methods, or the one-part variant above, but not both.
- (void)willAnimateFirstHalfOfRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_2_0,__IPHONE_5_0);
- (void)didAnimateFirstHalfOfRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_2_0,__IPHONE_5_0); // The rotating header and footer views are offscreen.
- (void)willAnimateSecondHalfOfRotationFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation duration:(NSTimeInterval)duration __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_2_0,__IPHONE_5_0); // A this point, our view orientation is set to the new orientation.

@end

// Many view controllers have a view that may be in an editing state or not- for example, a UITableView.  These view
// controllers can track the editing state, and generate an Edit|Done button to be used in a navigation bar.
@interface UIViewController (UIViewControllerEditing)

@property(nonatomic,getter=isEditing) BOOL editing;
- (void)setEditing:(BOOL)editing animated:(BOOL)animated; // Updates the appearance of the Edit|Done button item as necessary. Clients who override it must call super first.

- (UIBarButtonItem *)editButtonItem; // Return an Edit|Done button that can be used as a navigation item's custom view. Default action toggles the editing state with animation.

@end

@interface UIViewController (UISearchDisplayControllerSupport)

@property(nonatomic, readonly, retain) UISearchDisplayController *searchDisplayController;

@end


/*
  This exception is raised when a child view controller's view is added into the view hierarchy and the first
  superview of the child view controller's view that has a view controller is NOT the child view controller's
  parent.
*/
UIKIT_EXTERN NSString *const UIViewControllerHierarchyInconsistencyException __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);


/*
  The methods in the UIContainerViewControllerProtectedMethods and the UIContainerViewControllerCallbacks
  categories typically should only be called by subclasses which are implementing new container view
  controllers. They may be overridden but must call super.
*/
@interface UIViewController (UIContainerViewControllerProtectedMethods)

// An array of children view controllers. This array does not include any presented view controllers.
@property(nonatomic,readonly) NSArray *childViewControllers __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

/*
  If the child controller has a different parent controller, it will first be removed from its current parent
  by calling removeFromParentViewController. If this method is overridden then the super implementation must
  be called.
*/
- (void)addChildViewController:(UIViewController *)childController __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

/*
  Removes the the receiver from its parent's children controllers array. If this method is overridden then
  the super implementation must be called.
*/
- (void) removeFromParentViewController __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

/*
  This method can be used to transition between sibling child view controllers. The receiver of this method is
  their common parent view controller. (Use [UIViewController addChildViewController:] to create the
  parent/child relationship.) This method will add the toViewController's view to the superview of the
  fromViewController's view and the fromViewController's view will be removed from its superview after the
  transition completes. It is important to allow this method to add and remove the views. The arguments to
  this method are the same as those defined by UIView's block animation API. This method will fail with an
  NSInvalidArgumentException if the parent view controllers are not the same as the receiver, or if the
  receiver explicitly forwards its appearance and rotation callbacks to its children. Finally, the receiver
  should not be a subclass of an iOS container view controller. Note also that it is possible to use the
  UIView APIs directly. If they are used it is important to ensure that the toViewController's view is added
  to the visible view hierarchy while the fromViewController's view is removed.
*/
- (void)transitionFromViewController:(UIViewController *)fromViewController toViewController:(UIViewController *)toViewController duration:(NSTimeInterval)duration options:(UIViewAnimationOptions)options animations:(void (^)(void))animations completion:(void (^)(BOOL finished))completion __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

@end

@interface UIViewController (UIContainerViewControllerCallbacks)

/*
  This method is consulted to determine if a view controller manually forwards its containment callbacks to
  any children view controllers. Subclasses of UIViewController that implement containment logic may override
  this method. The default implementation returns YES. If it is overridden and returns NO, then the subclass is
  responsible for forwarding the following methods as appropriate - viewWillAppear: viewDidAppear: viewWillDisappear:
  viewDidDisappear: willRotateToInterfaceOrientation:duration:
  willAnimateRotationToInterfaceOrientation:duration: didRotateFromInterfaceOrientation:
*/
- (BOOL)automaticallyForwardAppearanceAndRotationMethodsToChildViewControllers __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

/*
  These two methods are public for container subclasses to call when transitioning between child
  controllers. If they are overridden, the overrides should ensure to call the super. The parent argument in
  both of these methods is nil when a child is being removed from its parent; otherwise it is equal to the new
  parent view controller.

  addChildViewController: will call [child willMoveToParentViewController:self] before adding the
  child. However, it will not call didMoveToParentViewController:. It is expected that a container view
  controller subclass will make this call after a transition to the new child has completed or, in the
  case of no transition, immediately after the call to addChildViewController:. Similarly
  removeFromParentViewController: does not call [self willMoveToParentViewController:nil] before removing the
  child. This is also the responsibilty of the container subclass. Container subclasses will typically define
  a method that transitions to a new child by first calling addChildViewController:, then executing a
  transition which will add the new child's view into the view hierarchy of its parent, and finally will call
  didMoveToParentViewController:. Similarly, subclasses will typically define a method that removes a child in
  the reverse manner by first calling [child willMoveToParentViewController:nil].
*/
- (void)willMoveToParentViewController:(UIViewController *)parent __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
- (void)didMoveToParentViewController:(UIViewController *)parent __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

@end
