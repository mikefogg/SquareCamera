//
//  UISwitch.h
//  UIKit
//
//  Copyright (c) 2008-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIControl.h>
#import <UIKit/UIKitDefines.h>

UIKIT_CLASS_AVAILABLE(2_0) @interface UISwitch : UIControl <NSCoding> {
  @private
    id _control;
}

@property(nonatomic, retain) UIColor* onTintColor __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0) UI_APPEARANCE_SELECTOR;
@property(nonatomic,getter=isOn) BOOL on;

- (id)initWithFrame:(CGRect)frame;              // This class enforces a size appropriate for the control. The frame size is ignored.

- (void)setOn:(BOOL)on animated:(BOOL)animated; // does not send action

@end
