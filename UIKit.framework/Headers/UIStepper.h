//
//  UIStepper.h
//  UIKit
//
//  Copyright 2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIControl.h>

@class UIButton, UIImageView;

UIKIT_CLASS_AVAILABLE(5_0) @interface UIStepper : UIControl {
  @private
    BOOL _isRtoL;
    UIImageView *_middleView;
    UIButton *_plusButton;
    UIButton *_minusButton;
    NSTimer  *_repeatTimer;
    NSInteger _repeatCount;
}

@property(nonatomic,getter=isContinuous) BOOL continuous; // if YES, value change events are sent any time the value changes during interaction. default = YES
@property(nonatomic) BOOL autorepeat;                     // if YES, press & hold repeatedly alters value. default = YES
@property(nonatomic) BOOL wraps;                          // if YES, value wraps from min <-> max. default = NO

@property(nonatomic) double value;                        // default is 0. sends UIControlEventValueChanged. clamped to min/max
@property(nonatomic) double minimumValue;                 // default 0. must be less than maximumValue
@property(nonatomic) double maximumValue;                 // default 100. must be greater than minimumValue
@property(nonatomic) double stepValue;                    // default 1. must be greater than 0

@end
