//
//  UIAccessibilityAdditions.h
//  UIKit
//
//  Copyright (c) 2009-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIPickerView.h>

/* 
  Optionally implement the following methods in a UIPickerView delegate
  in order to provide accessibility information per component. 
  See UIAccessibility.h for more information about hints and labels.
*/
@protocol UIPickerViewAccessibilityDelegate <UIPickerViewDelegate>

@optional
- (NSString *)pickerView:(UIPickerView *)pickerView accessibilityLabelForComponent:(NSInteger)component;
- (NSString *)pickerView:(UIPickerView *)pickerView accessibilityHintForComponent:(NSInteger)component;

@end
