//
//  UILocalNotification.h
//  UIKit
//
//  Copyright (c) 2007-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

UIKIT_CLASS_AVAILABLE(4_0) @interface UILocalNotification : NSObject<NSCopying, NSCoding>       // added in iOS 4.0

// scheduling
@property(nonatomic,copy) NSDate *fireDate;
// the time zone to interpret fireDate in. pass nil if fireDate is an absolute GMT time (e.g. for an egg timer).
// pass a time zone to interpret fireDate as a wall time to be adjusted automatically upon time zone changes (e.g. for an alarm clock).
@property(nonatomic,copy) NSTimeZone *timeZone;

@property(nonatomic) NSCalendarUnit repeatInterval;      // 0 means don't repeat
@property(nonatomic,copy) NSCalendar *repeatCalendar;

// alerts
@property(nonatomic,copy) NSString *alertBody;      // defaults to nil. pass a string or localized string key to show an alert
@property(nonatomic) BOOL hasAction;                // defaults to YES. pass NO to hide launching button/slider
@property(nonatomic,copy) NSString *alertAction;    // used in UIAlert button or 'slide to unlock...' slider in place of unlock
@property(nonatomic,copy) NSString *alertLaunchImage;   // used as the launch image (UILaunchImageFile) when launch button is tapped

// sound
@property(nonatomic,copy) NSString *soundName;      // name of resource in app's bundle to play or UILocalNotificationDefaultSoundName

// badge
@property(nonatomic) NSInteger applicationIconBadgeNumber;  // 0 means no change. defaults to 0

// user info
@property(nonatomic,copy) NSDictionary *userInfo;   // throws if contains non-property list types

@end


UIKIT_EXTERN NSString *const UILocalNotificationDefaultSoundName __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
