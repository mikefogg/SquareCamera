//
//  UIPanGestureRecognizer.h
//  UIKit
//
//  Copyright (c) 2008-2011, Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIGestureRecognizer.h>

// Begins:  when at least minimumNumberOfTouches have moved enough to be considered a pan
// Changes: when a finger moves while at least minimumNumberOfTouches are down
// Ends:    when all fingers have lifted

UIKIT_CLASS_AVAILABLE(3_2) @interface UIPanGestureRecognizer : UIGestureRecognizer {
  @package
    CGPoint         _firstScreenLocation;
    CGPoint         _lastScreenLocation;
    NSTimeInterval  _lastTouchTime;
    id              _velocitySample;
    id              _previousVelocitySample;
    NSMutableArray  *_touches;
    NSUInteger      _lastTouchCount;
    NSUInteger      _minimumNumberOfTouches;
    NSUInteger      _maximumNumberOfTouches;
    CGFloat         _hysteresis;
    CGPoint         _lastUnadjustedScreenLocation;
    unsigned int    _failsPastMaxTouches:1;
    unsigned int    _canPanHorizontally:1;
    unsigned int    _canPanVertically:1;
}

@property (nonatomic)          NSUInteger minimumNumberOfTouches;   // default is 1. the minimum number of touches required to match
@property (nonatomic)          NSUInteger maximumNumberOfTouches;   // default is UINT_MAX. the maximum number of touches that can be down

- (CGPoint)translationInView:(UIView *)view;                        // translation in the coordinate system of the specified view
- (void)setTranslation:(CGPoint)translation inView:(UIView *)view;

- (CGPoint)velocityInView:(UIView *)view;                           // velocity of the pan in pixels/second in the coordinate system of the specified view

@end
