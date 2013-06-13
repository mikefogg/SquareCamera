//
//  UIView.h
//  UIKit
//
//  Copyright (c) 2005-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIResponder.h>
#import <UIKit/UIInterface.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIAppearance.h>

typedef enum {
    UIViewAnimationCurveEaseInOut,         // slow at beginning and end
    UIViewAnimationCurveEaseIn,            // slow at beginning
    UIViewAnimationCurveEaseOut,           // slow at end
    UIViewAnimationCurveLinear
} UIViewAnimationCurve;

typedef enum {
    UIViewContentModeScaleToFill,
    UIViewContentModeScaleAspectFit,      // contents scaled to fit with fixed aspect. remainder is transparent
    UIViewContentModeScaleAspectFill,     // contents scaled to fill with fixed aspect. some portion of content may be clipped.
    UIViewContentModeRedraw,              // redraw on bounds change (calls -setNeedsDisplay)
    UIViewContentModeCenter,              // contents remain same size. positioned adjusted.
    UIViewContentModeTop,
    UIViewContentModeBottom,
    UIViewContentModeLeft,
    UIViewContentModeRight,
    UIViewContentModeTopLeft,
    UIViewContentModeTopRight,
    UIViewContentModeBottomLeft,
    UIViewContentModeBottomRight,
} UIViewContentMode;

typedef enum {
    UIViewAnimationTransitionNone,
    UIViewAnimationTransitionFlipFromLeft,
    UIViewAnimationTransitionFlipFromRight,
    UIViewAnimationTransitionCurlUp,
    UIViewAnimationTransitionCurlDown,
} UIViewAnimationTransition;

enum {
    UIViewAutoresizingNone                 = 0,
    UIViewAutoresizingFlexibleLeftMargin   = 1 << 0,
    UIViewAutoresizingFlexibleWidth        = 1 << 1,
    UIViewAutoresizingFlexibleRightMargin  = 1 << 2,
    UIViewAutoresizingFlexibleTopMargin    = 1 << 3,
    UIViewAutoresizingFlexibleHeight       = 1 << 4,
    UIViewAutoresizingFlexibleBottomMargin = 1 << 5
};
typedef NSUInteger UIViewAutoresizing;

#if __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED
enum {
    UIViewAnimationOptionLayoutSubviews            = 1 <<  0,
    UIViewAnimationOptionAllowUserInteraction      = 1 <<  1, // turn on user interaction while animating
    UIViewAnimationOptionBeginFromCurrentState     = 1 <<  2, // start all views from current value, not initial value
    UIViewAnimationOptionRepeat                    = 1 <<  3, // repeat animation indefinitely
    UIViewAnimationOptionAutoreverse               = 1 <<  4, // if repeat, run animation back and forth
    UIViewAnimationOptionOverrideInheritedDuration = 1 <<  5, // ignore nested duration
    UIViewAnimationOptionOverrideInheritedCurve    = 1 <<  6, // ignore nested curve
    UIViewAnimationOptionAllowAnimatedContent      = 1 <<  7, // animate contents (applies to transitions only)
    UIViewAnimationOptionShowHideTransitionViews   = 1 <<  8, // flip to/from hidden state instead of adding/removing
    
    UIViewAnimationOptionCurveEaseInOut            = 0 << 16, // default
    UIViewAnimationOptionCurveEaseIn               = 1 << 16,
    UIViewAnimationOptionCurveEaseOut              = 2 << 16,
    UIViewAnimationOptionCurveLinear               = 3 << 16,
    
    UIViewAnimationOptionTransitionNone            = 0 << 20, // default
    UIViewAnimationOptionTransitionFlipFromLeft    = 1 << 20,
    UIViewAnimationOptionTransitionFlipFromRight   = 2 << 20,
    UIViewAnimationOptionTransitionCurlUp          = 3 << 20,
    UIViewAnimationOptionTransitionCurlDown        = 4 << 20,
    UIViewAnimationOptionTransitionCrossDissolve   = 5 << 20,
    UIViewAnimationOptionTransitionFlipFromTop     = 6 << 20,
    UIViewAnimationOptionTransitionFlipFromBottom  = 7 << 20,
};
typedef NSUInteger UIViewAnimationOptions;
#endif

@class UIEvent, UIWindow, UIViewController, UIColor, UIGestureRecognizer, CALayer;

UIKIT_CLASS_AVAILABLE(2_0) @interface UIView : UIResponder<NSCoding, UIAppearance, UIAppearanceContainer> {
  @package
    CALayer        *_layer;
    id              _tapInfo;
    id              _gestureInfo;
    NSMutableArray *_gestureRecognizers;
    NSArray        *_subviewCache;
    float           _charge;
    NSInteger       _tag;
    UIViewController *_viewDelegate;
    NSString         *_backgroundColorSystemColorName;
    struct {
        unsigned int userInteractionDisabled:1;
        unsigned int implementsDrawRect:1;
        unsigned int implementsDidScroll:1;
        unsigned int implementsMouseTracking:1;
        unsigned int hasBackgroundColor:1;
        unsigned int isOpaque:1;
        unsigned int becomeFirstResponderWhenCapable:1;
        unsigned int interceptMouseEvent:1;
        unsigned int deallocating:1;
        unsigned int debugFlash:1;
        unsigned int debugSkippedSetNeedsDisplay:1;
        unsigned int debugScheduledDisplayIsRequired:1;
        unsigned int isInAWindow:1;
        unsigned int isAncestorOfFirstResponder:1;
        unsigned int dontAutoresizeSubviews:1;
        unsigned int autoresizeMask:6;
        unsigned int patternBackground:1;
        unsigned int fixedBackgroundPattern:1;
        unsigned int dontAnimate:1;
        unsigned int superLayerIsView:1;
        unsigned int layerKitPatternDrawing:1;
        unsigned int multipleTouchEnabled:1;
        unsigned int exclusiveTouch:1;
        unsigned int hasViewController:1;
        unsigned int needsDidAppearOrDisappear:1;
        unsigned int gesturesEnabled:1;
        unsigned int deliversTouchesForGesturesToSuperview:1;
        unsigned int chargeEnabled:1;
        unsigned int skipsSubviewEnumeration:1;
        unsigned int needsDisplayOnBoundsChange:1;
        unsigned int hasTiledLayer:1;
        unsigned int hasLargeContent:1;
        unsigned int isInAnimatedVCTransition:1;
        unsigned int traversalMark:1;
        unsigned int appearanceIsInvalid:1;
        unsigned int monitorsSubtree:1;
    } _viewFlags;
}

+ (Class)layerClass;                        // default is [CALayer class]. Used when creating the underlying layer for the view.

- (id)initWithFrame:(CGRect)frame;          // default initializer

@property(nonatomic,getter=isUserInteractionEnabled) BOOL userInteractionEnabled;  // default is YES. if set to NO, user events (touch, keys) are ignored and removed from the event queue.
@property(nonatomic)                                 NSInteger tag;                // default is 0
@property(nonatomic,readonly,retain)                 CALayer  *layer;              // returns view's layer. Will always return a non-nil value. view is layer's delegate

@end

@interface UIView(UIViewGeometry)

// animatable. do not use frame if view is transformed since it will not correctly reflect the actual location of the view. use bounds + center instead.
@property(nonatomic) CGRect            frame;

// use bounds/center and not frame if non-identity transform. if bounds dimension is odd, center may be have fractional part
@property(nonatomic) CGRect            bounds;      // default bounds is zero origin, frame size. animatable
@property(nonatomic) CGPoint           center;      // center is center of frame. animatable
@property(nonatomic) CGAffineTransform transform;   // default is CGAffineTransformIdentity. animatable
@property(nonatomic) CGFloat           contentScaleFactor __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

@property(nonatomic,getter=isMultipleTouchEnabled) BOOL multipleTouchEnabled;   // default is NO
@property(nonatomic,getter=isExclusiveTouch) BOOL       exclusiveTouch;         // default is NO

- (UIView *)hitTest:(CGPoint)point withEvent:(UIEvent *)event;   // recursively calls -pointInside:withEvent:. point is in the receiver's coordinate system
- (BOOL)pointInside:(CGPoint)point withEvent:(UIEvent *)event;   // default returns YES if point is in bounds

- (CGPoint)convertPoint:(CGPoint)point toView:(UIView *)view;
- (CGPoint)convertPoint:(CGPoint)point fromView:(UIView *)view;
- (CGRect)convertRect:(CGRect)rect toView:(UIView *)view;
- (CGRect)convertRect:(CGRect)rect fromView:(UIView *)view;

@property(nonatomic) BOOL               autoresizesSubviews; // default is YES. if set, subviews are adjusted according to their autoresizingMask if self.bounds changes
@property(nonatomic) UIViewAutoresizing autoresizingMask;    // simple resize. default is UIViewAutoresizingNone

- (CGSize)sizeThatFits:(CGSize)size;     // return 'best' size to fit given size. does not actually resize view. Default is return existing view size
- (void)sizeToFit;                       // calls sizeThatFits: with current view bounds and changes bounds size.

@end

@interface UIView(UIViewHierarchy)

@property(nonatomic,readonly) UIView       *superview;
@property(nonatomic,readonly,copy) NSArray *subviews;
@property(nonatomic,readonly) UIWindow     *window;

- (void)removeFromSuperview;
- (void)insertSubview:(UIView *)view atIndex:(NSInteger)index;
- (void)exchangeSubviewAtIndex:(NSInteger)index1 withSubviewAtIndex:(NSInteger)index2;

- (void)addSubview:(UIView *)view;
- (void)insertSubview:(UIView *)view belowSubview:(UIView *)siblingSubview;
- (void)insertSubview:(UIView *)view aboveSubview:(UIView *)siblingSubview;

- (void)bringSubviewToFront:(UIView *)view;
- (void)sendSubviewToBack:(UIView *)view;

- (void)didAddSubview:(UIView *)subview;
- (void)willRemoveSubview:(UIView *)subview;

- (void)willMoveToSuperview:(UIView *)newSuperview;
- (void)didMoveToSuperview;
- (void)willMoveToWindow:(UIWindow *)newWindow;
- (void)didMoveToWindow;

- (BOOL)isDescendantOfView:(UIView *)view;  // returns YES for self.
- (UIView *)viewWithTag:(NSInteger)tag;     // recursive search. includes self

// Allows you to perform layout before the drawing cycle happens. -layoutIfNeeded forces layout early
- (void)setNeedsLayout;
- (void)layoutIfNeeded;

- (void)layoutSubviews;    // override point. called by layoutIfNeeded automatically. base implementation does nothing

@end

@interface UIView(UIViewRendering)

- (void)drawRect:(CGRect)rect;

- (void)setNeedsDisplay;
- (void)setNeedsDisplayInRect:(CGRect)rect;

@property(nonatomic)                 BOOL              clipsToBounds;              // When YES, content and subviews are clipped to the bounds of the view. Default is NO.
@property(nonatomic,copy)            UIColor          *backgroundColor;            // default is nil
@property(nonatomic)                 CGFloat           alpha;                      // animatable. default is 1.0
@property(nonatomic,getter=isOpaque) BOOL              opaque;                     // default is YES. opaque views must fill their entire bounds or the results are undefined. the active CGContext in drawRect: will not have been cleared and may have non-zeroed pixels
@property(nonatomic)                 BOOL              clearsContextBeforeDrawing; // default is YES. ignored for opaque views. for non-opaque views causes the active CGContext in drawRect: to be pre-filled with transparent pixels
@property(nonatomic,getter=isHidden) BOOL              hidden;                     // default is NO. doesn't check superviews
@property(nonatomic)                 UIViewContentMode contentMode;                // default is UIViewContentModeScaleToFill
@property(nonatomic)                 CGRect            contentStretch __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0); // animatable. default is unit rectangle {{0,0} {1,1}}

@end

@interface UIView(UIViewAnimation)

+ (void)beginAnimations:(NSString *)animationID context:(void *)context;  // additional context info passed to will start/did stop selectors. begin/commit can be nested
+ (void)commitAnimations;                                                 // starts up any animations when the top level animation is commited

// no getters. if called outside animation block, these setters have no effect.
+ (void)setAnimationDelegate:(id)delegate;                          // default = nil
+ (void)setAnimationWillStartSelector:(SEL)selector;                // default = NULL. -animationWillStart:(NSString *)animationID context:(void *)context
+ (void)setAnimationDidStopSelector:(SEL)selector;                  // default = NULL. -animationDidStop:(NSString *)animationID finished:(NSNumber *)finished context:(void *)context
+ (void)setAnimationDuration:(NSTimeInterval)duration;              // default = 0.2
+ (void)setAnimationDelay:(NSTimeInterval)delay;                    // default = 0.0
+ (void)setAnimationStartDate:(NSDate *)startDate;                  // default = now ([NSDate date])
+ (void)setAnimationCurve:(UIViewAnimationCurve)curve;              // default = UIViewAnimationCurveEaseInOut
+ (void)setAnimationRepeatCount:(float)repeatCount;                 // default = 0.0.  May be fractional
+ (void)setAnimationRepeatAutoreverses:(BOOL)repeatAutoreverses;    // default = NO. used if repeat count is non-zero
+ (void)setAnimationBeginsFromCurrentState:(BOOL)fromCurrentState;  // default = NO. If YES, the current view position is always used for new animations -- allowing animations to "pile up" on each other. Otherwise, the last end state is used for the animation (the default).

+ (void)setAnimationTransition:(UIViewAnimationTransition)transition forView:(UIView *)view cache:(BOOL)cache;  // current limitation - only one per begin/commit block

+ (void)setAnimationsEnabled:(BOOL)enabled;                         // ignore any attribute changes while set.
+ (BOOL)areAnimationsEnabled;

@end

@interface UIView(UIViewAnimationWithBlocks)

+ (void)animateWithDuration:(NSTimeInterval)duration delay:(NSTimeInterval)delay options:(UIViewAnimationOptions)options animations:(void (^)(void))animations completion:(void (^)(BOOL finished))completion __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

+ (void)animateWithDuration:(NSTimeInterval)duration animations:(void (^)(void))animations completion:(void (^)(BOOL finished))completion __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0); // delay = 0.0, options = 0

+ (void)animateWithDuration:(NSTimeInterval)duration animations:(void (^)(void))animations __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0); // delay = 0.0, options = 0, completion = NULL

+ (void)transitionWithView:(UIView *)view duration:(NSTimeInterval)duration options:(UIViewAnimationOptions)options animations:(void (^)(void))animations completion:(void (^)(BOOL finished))completion __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

+ (void)transitionFromView:(UIView *)fromView toView:(UIView *)toView duration:(NSTimeInterval)duration options:(UIViewAnimationOptions)options completion:(void (^)(BOOL finished))completion __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0); // toView added to fromView.superview, fromView removed from its superview

@end

@interface UIView (UIViewGestureRecognizers)

@property(nonatomic,copy) NSArray *gestureRecognizers __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2);

- (void)addGestureRecognizer:(UIGestureRecognizer*)gestureRecognizer __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2);
- (void)removeGestureRecognizer:(UIGestureRecognizer*)gestureRecognizer __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2);

@end
