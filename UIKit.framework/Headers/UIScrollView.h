//
//  UIScrollView.h
//  UIKit
//
//  Copyright (c) 2007-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIView.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UIKitDefines.h>

typedef enum {
    UIScrollViewIndicatorStyleDefault,     // black with white border. good against any background
    UIScrollViewIndicatorStyleBlack,       // black only. smaller. good against a white background
    UIScrollViewIndicatorStyleWhite        // white only. smaller. good against a black background
} UIScrollViewIndicatorStyle;

UIKIT_EXTERN const float UIScrollViewDecelerationRateNormal __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
UIKIT_EXTERN const float UIScrollViewDecelerationRateFast __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

@class UIEvent, UIImageView, UIPanGestureRecognizer, UIPinchGestureRecognizer;
@protocol UIScrollViewDelegate;

UIKIT_CLASS_AVAILABLE(2_0) @interface UIScrollView : UIView <NSCoding> {
  @package
    CGSize       _contentSize;
    UIEdgeInsets _contentInset;
    id           _delegate;
    UIImageView* _verticalScrollIndicator;
    UIImageView* _horizontalScrollIndicator;
    UIEdgeInsets _scrollIndicatorInset;
    struct {
        unsigned int tracking:1;
        unsigned int dragging:1;
        unsigned int verticalBounceEnabled:1;
        unsigned int horizontalBounceEnabled:1;
        unsigned int verticalBouncing:1;
        unsigned int horizontalBouncing:1;
        unsigned int bouncesZoom:1;
        unsigned int zoomBouncing:1;
        unsigned int alwaysBounceHorizontal:1;
        unsigned int alwaysBounceVertical:1;
        unsigned int canCancelContentTouches:1;
        unsigned int delaysContentTouches:1;
        unsigned int programmaticScrollDisabled:1;
        unsigned int scrollDisabled:1;
        unsigned int zoomDisabled:1;
        unsigned int scrollTriggered:1;
        unsigned int scrollDisabledOnTouchBegan:1;
        unsigned int ignoreNextTouchesMoved:1;
        unsigned int cancelNextContentTouchEnded:1;
        unsigned int inContentViewCall:1;
        unsigned int dontSelect:1;
        unsigned int contentTouched:1;
        unsigned int cantCancel:1;
        unsigned int directionalLockEnabled:1;	
        unsigned int directionalLockAutoEnabled:1;
        unsigned int lockVertical:1;
        unsigned int lockHorizontal:1;
        unsigned int keepLocked:1;	
        unsigned int showsHorizontalScrollIndicator:1;
        unsigned int showsVerticalScrollIndicator:1;
        unsigned int indicatorStyle:2;
        unsigned int inZoom:1;
        unsigned int hideIndicatorsInZoom:1;
        unsigned int pushedTrackingMode:1;
        unsigned int multipleDrag:1;
        unsigned int displayingScrollIndicators:1;
        unsigned int verticalIndicatorShrunk:1;
        unsigned int horizontalIndicatorShrunk:1;
        unsigned int contentFitDisableScrolling:1;
        unsigned int pagingEnabled:1;
        unsigned int pagingLeft:1;
        unsigned int pagingRight:1;
        unsigned int pagingUp:1;
        unsigned int pagingDown:1;
        unsigned int lastHorizontalDirection:1;
        unsigned int lastVerticalDirection:1;
        unsigned int dontScrollToTop:1;
        unsigned int scrollingToTop:1;
        unsigned int useGestureRecognizers:1;
        unsigned int autoscrolling:1;
        unsigned int automaticContentOffsetAdjustmentDisabled:1;
        unsigned int skipStartOffsetAdjustment:1;
        unsigned int delegateScrollViewDidScroll:1;
        unsigned int delegateScrollViewDidZoom:1;
        unsigned int delegateContentSizeForZoomScale:1;
        unsigned int preserveCenterDuringRotation:1;
        unsigned int delaysTrackingWhileDecelerating:1;
        unsigned int pinnedZoomMin:1;
        unsigned int pinnedXMin:1;
        unsigned int pinnedYMin:1;
        unsigned int pinnedXMax:1;
        unsigned int pinnedYMax:1;
        unsigned int skipLinkChecks:1;
        unsigned int staysCenteredDuringPinch:1;
        unsigned int wasDelayingPinchForSystemGestures:1;
        unsigned int systemGesturesRecognitionPossible:1;
        unsigned int disableContentOffsetRounding:1;
        unsigned int adjustedDecelerationTargetX:1;
        unsigned int adjustedDecelerationTargetY:1;
    } _scrollViewFlags;
    CGFloat           _farthestDistance;
    CGPoint           _initialTouchPosition;
    CGPoint           _startTouchPosition;
    CFTimeInterval    _startTouchTime;
    double            _startOffsetX;
    double            _startOffsetY;
    double            _lastUpdateOffsetX;
    double            _lastUpdateOffsetY;
    CGPoint           _lastTouchPosition;
    CFTimeInterval    _lastTouchTime;
    CFTimeInterval    _lastUpdateTime;
    UIView           *_contentView;
    float             _minimumZoomScale;
    float             _maximumZoomScale;
    UIView           *_zoomView;
    double            _horizontalVelocity;
    double            _verticalVelocity;
    double            _previousHorizontalVelocity;
    double            _previousVerticalVelocity;
    CFTypeRef         _scrollHeartbeat;
    CGPoint           _pageDecelerationTarget;
    CGSize            _decelerationFactor;
    CGPoint           _adjustedDecelerationTarget;
    CGSize            _adjustedDecelerationFactor;
    double            _decelerationLnFactorH;
    double            _decelerationLnFactorV;
    NSArray*          _deferredBeginTouchesInfo;
    UIImageView * __strong *_shadows;
    id                _scrollNotificationViews;
    CFTimeInterval    _contentOffsetAnimationDuration;
    id                _animation;
    id                _pinch;
    id                _pan;
    id                _swipe;
    CGFloat           _pagingSpringPull;
    CGFloat           _pagingFriction;
    NSInteger         _fastScrollCount;
    CGFloat           _fastScrollMultiplier;
    CGFloat           _fastScrollStartMultiplier;
    CFTimeInterval    _fastScrollEndTime;
    CGPoint           _parentAdjustment;
    CGPoint           _rotationCenterPoint;
    CGFloat           _accuracy;
    CGFloat           _hysteresis;
    NSUInteger        _zoomAnimationCount;
}

@property(nonatomic)         CGPoint                      contentOffset;                  // default CGPointZero
@property(nonatomic)         CGSize                       contentSize;                    // default CGSizeZero
@property(nonatomic)         UIEdgeInsets                 contentInset;                   // default UIEdgeInsetsZero. add additional scroll area around content
@property(nonatomic,assign) id<UIScrollViewDelegate>      delegate;                       // default nil. weak reference
@property(nonatomic,getter=isDirectionalLockEnabled) BOOL directionalLockEnabled;         // default NO. if YES, try to lock vertical or horizontal scrolling while dragging
@property(nonatomic)         BOOL                         bounces;                        // default YES. if YES, bounces past edge of content and back again
@property(nonatomic)         BOOL                         alwaysBounceVertical;           // default NO. if YES and bounces is YES, even if content is smaller than bounds, allow drag vertically
@property(nonatomic)         BOOL                         alwaysBounceHorizontal;         // default NO. if YES and bounces is YES, even if content is smaller than bounds, allow drag horizontally
@property(nonatomic,getter=isPagingEnabled) BOOL          pagingEnabled;                  // default NO. if YES, stop on multiples of view bounds
@property(nonatomic,getter=isScrollEnabled) BOOL          scrollEnabled;                  // default YES. turn off any dragging temporarily
@property(nonatomic)         BOOL                         showsHorizontalScrollIndicator; // default YES. show indicator while we are tracking. fades out after tracking
@property(nonatomic)         BOOL                         showsVerticalScrollIndicator;   // default YES. show indicator while we are tracking. fades out after tracking
@property(nonatomic)         UIEdgeInsets                 scrollIndicatorInsets;          // default is UIEdgeInsetsZero. adjust indicators inside of insets
@property(nonatomic)         UIScrollViewIndicatorStyle   indicatorStyle;                 // default is UIScrollViewIndicatorStyleDefault
@property(nonatomic)         float                        decelerationRate __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

- (void)setContentOffset:(CGPoint)contentOffset animated:(BOOL)animated;  // animate at constant velocity to new offset
- (void)scrollRectToVisible:(CGRect)rect animated:(BOOL)animated;         // scroll so rect is just visible (nearest edges). nothing if rect completely visible

- (void)flashScrollIndicators;             // displays the scroll indicators for a short time. This should be done whenever you bring the scroll view to front.

/*
 Scrolling with no scroll bars is a bit complex. on touch down, we don't know if the user will want to scroll or track a subview like a control.
 on touch down, we start a timer and also look at any movement. if the time elapses without sufficient change in position, we start sending events to
 the hit view in the content subview. if the user then drags far enough, we switch back to dragging and cancel any tracking in the subview.
 the methods below are called by the scroll view and give subclasses override points to add in custom behaviour.
 you can remove the delay in delivery of touchesBegan:withEvent: to subviews by setting delaysContentTouches to NO.
 */

@property(nonatomic,readonly,getter=isTracking)     BOOL tracking;        // returns YES if user has touched. may not yet have started dragging
@property(nonatomic,readonly,getter=isDragging)     BOOL dragging;        // returns YES if user has started scrolling. this may require some time and or distance to move to initiate dragging
@property(nonatomic,readonly,getter=isDecelerating) BOOL decelerating;    // returns YES if user isn't dragging (touch up) but scroll view is still moving

@property(nonatomic) BOOL delaysContentTouches;       // default is YES. if NO, we immediately call -touchesShouldBegin:withEvent:inContentView:
@property(nonatomic) BOOL canCancelContentTouches;    // default is YES. if NO, then once we start tracking, we don't try to drag if the touch moves

// override points for subclasses to control delivery of touch events to subviews of the scroll view
// called before touches are delivered to a subview of the scroll view. if it returns NO the touches will not be delivered to the subview
// default returns YES
- (BOOL)touchesShouldBegin:(NSSet *)touches withEvent:(UIEvent *)event inContentView:(UIView *)view;
// called before scrolling begins if touches have already been delivered to a subview of the scroll view. if it returns NO the touches will continue to be delivered to the subview and scrolling will not occur
// not called if canCancelContentTouches is NO. default returns YES if view isn't a UIControl
- (BOOL)touchesShouldCancelInContentView:(UIView *)view;

/*
 the following properties and methods are for zooming. as the user tracks with two fingers, we adjust the offset and the scale of the content. When the gesture ends, you should update the content
 as necessary. Note that the gesture can end and a finger could still be down. While the gesture is in progress, we do not send any tracking calls to the subview.
 the delegate must implement both viewForZoomingInScrollView: and scrollViewDidEndZooming:withView:atScale: in order for zooming to work and the max/min zoom scale must be different
 note that we are not scaling the actual scroll view but the 'content view' returned by the delegate. the delegate must return a subview, not the scroll view itself, from viewForZoomingInScrollview:
 */

@property(nonatomic) float minimumZoomScale;     // default is 1.0
@property(nonatomic) float maximumZoomScale;     // default is 1.0. must be > minimum zoom scale to enable zooming

@property(nonatomic) float zoomScale __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);            // default is 1.0
- (void)setZoomScale:(float)scale animated:(BOOL)animated __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
- (void)zoomToRect:(CGRect)rect animated:(BOOL)animated __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

@property(nonatomic) BOOL  bouncesZoom;          // default is YES. if set, user can go past min/max zoom while gesturing and the zoom will animate to the min/max value at gesture end

@property(nonatomic,readonly,getter=isZooming)       BOOL zooming;       // returns YES if user in zoom gesture
@property(nonatomic,readonly,getter=isZoomBouncing)  BOOL zoomBouncing;  // returns YES if we are in the middle of zooming back to the min/max value

// When the user taps the status bar, the scroll view beneath the touch which is closest to the status bar will be scrolled to top, but only if its `scrollsToTop` property is YES, its delegate does not return NO from `shouldScrollViewScrollToTop`, and it is not already at the top.
// On iPhone, we execute this gesture only if there's one on-screen scroll view with `scrollsToTop` == YES. If more than one is found, none will be scrolled.
@property(nonatomic) BOOL  scrollsToTop;          // default is YES.

// Use these accessors to configure the scroll view's built-in gesture recognizers.
// Do not change the gestures' delegates or override the getters for these properties.
@property(nonatomic, readonly) UIPanGestureRecognizer *panGestureRecognizer __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);
// `pinchGestureRecognizer` will return nil when zooming is disabled.
@property(nonatomic, readonly) UIPinchGestureRecognizer *pinchGestureRecognizer __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

@end

@protocol UIScrollViewDelegate<NSObject>

@optional

- (void)scrollViewDidScroll:(UIScrollView *)scrollView;                                               // any offset changes
- (void)scrollViewDidZoom:(UIScrollView *)scrollView __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2); // any zoom scale changes

// called on start of dragging (may require some time and or distance to move)
- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView;
// called on finger up if the user dragged. velocity is in points/second. targetContentOffset may be changed to adjust where the scroll view comes to rest. not called when pagingEnabled is YES
- (void)scrollViewWillEndDragging:(UIScrollView *)scrollView withVelocity:(CGPoint)velocity targetContentOffset:(inout CGPoint *)targetContentOffset __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
// called on finger up if the user dragged. decelerate is true if it will continue moving afterwards
- (void)scrollViewDidEndDragging:(UIScrollView *)scrollView willDecelerate:(BOOL)decelerate;

- (void)scrollViewWillBeginDecelerating:(UIScrollView *)scrollView;   // called on finger up as we are moving
- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView;      // called when scroll view grinds to a halt

- (void)scrollViewDidEndScrollingAnimation:(UIScrollView *)scrollView; // called when setContentOffset/scrollRectVisible:animated: finishes. not called if not animating

- (UIView *)viewForZoomingInScrollView:(UIScrollView *)scrollView;     // return a view that will be scaled. if delegate returns nil, nothing happens
- (void)scrollViewWillBeginZooming:(UIScrollView *)scrollView withView:(UIView *)view __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2); // called before the scroll view begins zooming its content
- (void)scrollViewDidEndZooming:(UIScrollView *)scrollView withView:(UIView *)view atScale:(float)scale; // scale between minimum and maximum. called after any 'bounce' animations

- (BOOL)scrollViewShouldScrollToTop:(UIScrollView *)scrollView;   // return a yes if you want to scroll to the top. if not defined, assumes YES
- (void)scrollViewDidScrollToTop:(UIScrollView *)scrollView;      // called when scrolling animation finished. may be called immediately if already at top

@end
