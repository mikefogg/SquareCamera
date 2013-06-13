//
//  UITapGestureRecognizer.h
//  UIKit
//
//  Copyright (c) 2008-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIGestureRecognizer.h>

// Recognizes: when numberOfTouchesRequired have tapped numberOfTapsRequired times

// Touch Location Behaviors:
//     locationInView:         location of the tap, from the first tap in the sequence if numberOfTapsRequired > 1. this is the centroid if numberOfTouchesRequired > 1
//     locationOfTouch:inView: location of a particular touch, from the first tap in the sequence if numberOfTapsRequired > 1

UIKIT_CLASS_AVAILABLE(3_2) @interface UITapGestureRecognizer : UIGestureRecognizer {
  @package
    CGPoint      _locationInView;
    id           _imp;
    unsigned int _delaysRecognitionForGreaterTapCounts;
}

@property (nonatomic) NSUInteger  numberOfTapsRequired;       // Default is 1. The number of taps required to match
@property (nonatomic) NSUInteger  numberOfTouchesRequired;    // Default is 1. The number of fingers required to match

@end
