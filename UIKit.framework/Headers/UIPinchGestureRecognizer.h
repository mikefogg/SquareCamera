//
//  UIPinchGestureRecognizer.h
//  UIKit
//
//  Copyright (c) 2008-2011, Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIGestureRecognizer.h>

// Begins:  when two touches have moved enough to be considered a pinch
// Changes: when a finger moves while two fingers remain down
// Ends:    when both fingers have lifted

UIKIT_CLASS_AVAILABLE(3_2) @interface UIPinchGestureRecognizer : UIGestureRecognizer {
  @package
    CGFloat           _initialTouchDistance;
    CGFloat           _initialTouchScale;
    NSTimeInterval    _lastTouchTime;
    CGFloat           _velocity;
    CGFloat           _previousVelocity;
    CGFloat           _scaleThreshold;
    CGAffineTransform _transform;
    CGPoint           _anchorPoint;
    UITouch          *_touches[2];
    CGFloat           _hysteresis;
    id                _transformAnalyzer;
    unsigned int      _endsOnSingleTouch:1;
}

@property (nonatomic)          CGFloat scale;               // scale relative to the touch points in screen coordinates
@property (nonatomic,readonly) CGFloat velocity;            // velocity of the pinch in scale/second

@end
