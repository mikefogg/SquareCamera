//
//  UIDatePicker.h
//  UIKit
//
//  Copyright (c) 2006-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIControl.h>
#import <UIKit/UIKitDefines.h>

typedef enum {
    UIDatePickerModeTime,           // Displays hour, minute, and optionally AM/PM designation depending on the locale setting (e.g. 6 | 53 | PM)
    UIDatePickerModeDate,           // Displays month, day, and year depending on the locale setting (e.g. November | 15 | 2007)
    UIDatePickerModeDateAndTime,    // Displays date, hour, minute, and optionally AM/PM designation depending on the locale setting (e.g. Wed Nov 15 | 6 | 53 | PM)
    UIDatePickerModeCountDownTimer  // Displays hour and minute (e.g. 1 | 53)
} UIDatePickerMode;

@class UIPickerView;

UIKIT_CLASS_AVAILABLE(2_0) @interface UIDatePicker : UIControl <NSCoding>
{
  @private
    UIPickerView *_pickerView;
}

@property(nonatomic) UIDatePickerMode datePickerMode;             // default is UIDatePickerModeDateAndTime

@property(nonatomic,retain) NSLocale      *locale __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA, __MAC_NA, __IPHONE_2_0, __IPHONE_5_0);
@property(nonatomic,retain) NSTimeZone    *timeZone;              // default is nil. use current time zone or time zone from calendar
@property(nonatomic,copy)   NSCalendar    *calendar;              // default is [NSCalendar currentCalendar]. setting nil returns to default

@property(nonatomic,retain) NSDate        *date;                  // default is current date when picker created. Ignored in countdown timer mode. for that mode, picker starts at 0:00

@property(nonatomic,retain) NSDate        *minimumDate;           // specify min/max date range. default is nil. When min > max, the values are ignored. Ignored in countdown timer mode
@property(nonatomic,retain) NSDate        *maximumDate;           // default is nil
@property(nonatomic)        NSTimeInterval countDownDuration;     // for UIDatePickerModeCountDownTimer, ignored otherwise. default is 0.0. limit is 23:59 (86,399 seconds)
@property(nonatomic)        NSInteger      minuteInterval;        // display minutes wheel with interval. interval must be evenly divided into 60. default is 1. min is 1, max is 30

- (void)setDate:(NSDate *)date animated:(BOOL)animated;           // if animated is YES, animate the wheels of time to display the new date

@end
