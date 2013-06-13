//
//  UISwipeGestureRecognizer.h
//  UIKit
//
//  Copyright (c) 2009-2011, Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIGestureRecognizer.h>

// Recognizes: when numberOfTouchesRequired have moved mostly in the specified direction, enough to be considered a swipe.
//             a slow swipe requires high directional precision but a small distance
//             a fast swipe requires low directional precision but a large distance

// Touch Location Behaviors:
//     locationInView:         location where the swipe began. this is the centroid if more than one touch was involved
//     locationOfTouch:inView: location of a particular touch when the swipe began

typedef enum {
    UISwipeGestureRecognizerDirectionRight = 1 << 0,
    UISwipeGestureRecognizerDirectionLeft  = 1 << 1,
    UISwipeGestureRecognizerDirectionUp    = 1 << 2,
    UISwipeGestureRecognizerDirectionDown  = 1 << 3
} UISwipeGestureRecognizerDirection;

UIKIT_CLASS_AVAILABLE(3_2) @interface UISwipeGestureRecognizer : UIGestureRecognizer {
  @package
    CFTimeInterval    _maximumDuration;
    CGFloat           _minimumPrimaryMovement;
    CGFloat           _maximumPrimaryMovement;
    CGFloat           _minimumSecondaryMovement;
    CGFloat           _maximumSecondaryMovement;
    CGFloat           _rateOfMinimumMovementDecay;
    CGFloat           _rateOfMaximumMovementDecay;
    NSUInteger        _numberOfTouchesRequired;
    NSMutableArray   *_touches;
    UISwipeGestureRecognizerDirection _direction;
    
    CGPoint           _startLocation;
    CGPoint          *_startLocations;
    CFTimeInterval    _startTime;
    
    unsigned int      _failed:1;
}

@property(nonatomic) NSUInteger                        numberOfTouchesRequired; // default is 1. the number of fingers that must swipe
@property(nonatomic) UISwipeGestureRecognizerDirection direction;               // default is UISwipeGestureRecognizerDirectionRight. the desired direction of the swipe. multiple directions may be specified

@end
