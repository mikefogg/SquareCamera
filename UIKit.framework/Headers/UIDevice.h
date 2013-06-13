//
//  UIDevice.h
//  UIKit
//
//  Copyright (c) 2007-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

typedef enum {
    UIDeviceOrientationUnknown,
    UIDeviceOrientationPortrait,            // Device oriented vertically, home button on the bottom
    UIDeviceOrientationPortraitUpsideDown,  // Device oriented vertically, home button on the top
    UIDeviceOrientationLandscapeLeft,       // Device oriented horizontally, home button on the right
    UIDeviceOrientationLandscapeRight,      // Device oriented horizontally, home button on the left
    UIDeviceOrientationFaceUp,              // Device oriented flat, face up
    UIDeviceOrientationFaceDown             // Device oriented flat, face down
} UIDeviceOrientation;

typedef enum {
    UIDeviceBatteryStateUnknown,
    UIDeviceBatteryStateUnplugged,   // on battery, discharging
    UIDeviceBatteryStateCharging,    // plugged in, less than 100%
    UIDeviceBatteryStateFull,        // plugged in, at 100%
} UIDeviceBatteryState;              // available in iPhone 3.0

typedef enum {
#if __IPHONE_3_2 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    UIUserInterfaceIdiomPhone,           // iPhone and iPod touch style UI
    UIUserInterfaceIdiomPad,             // iPad style UI
#endif
} UIUserInterfaceIdiom;

/* The UI_USER_INTERFACE_IDIOM() macro is provided for use when deploying to a version of the iOS less than 3.2. If the earliest version of iPhone/iOS that you will be deploying for is 3.2 or greater, you may use -[UIDevice userInterfaceIdiom] directly.
 */
#define UI_USER_INTERFACE_IDIOM() ([[UIDevice currentDevice] respondsToSelector:@selector(userInterfaceIdiom)] ? [[UIDevice currentDevice] userInterfaceIdiom] : UIUserInterfaceIdiomPhone)

#define UIDeviceOrientationIsPortrait(orientation)  ((orientation) == UIDeviceOrientationPortrait || (orientation) == UIDeviceOrientationPortraitUpsideDown)
#define UIDeviceOrientationIsLandscape(orientation) ((orientation) == UIDeviceOrientationLandscapeLeft || (orientation) == UIDeviceOrientationLandscapeRight)

UIKIT_CLASS_AVAILABLE(2_0) @interface UIDevice : NSObject {
 @private
    NSInteger _numDeviceOrientationObservers;
    float     _batteryLevel;
    struct {
	unsigned int batteryMonitoringEnabled:1;
	unsigned int proximityMonitoringEnabled:1;
	unsigned int expectsFaceContactInLandscape:1;
        unsigned int orientation:3;
        unsigned int batteryState:2;
        unsigned int proximityState:1;
    } _deviceFlags;
}

+ (UIDevice *)currentDevice;

@property(nonatomic,readonly,retain) NSString    *name;              // e.g. "My iPhone"
@property(nonatomic,readonly,retain) NSString    *model;             // e.g. @"iPhone", @"iPod touch"
@property(nonatomic,readonly,retain) NSString    *localizedModel;    // localized version of model
@property(nonatomic,readonly,retain) NSString    *systemName;        // e.g. @"iOS"
@property(nonatomic,readonly,retain) NSString    *systemVersion;     // e.g. @"4.0"
@property(nonatomic,readonly) UIDeviceOrientation orientation;       // return current device orientation.  this will return UIDeviceOrientationUnknown unless device orientation notifications are being generated.
@property(nonatomic,readonly,retain) NSString    *uniqueIdentifier  __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_2_0,__IPHONE_5_0);  // a string unique to each device based on various hardware info.

@property(nonatomic,readonly,getter=isGeneratingDeviceOrientationNotifications) BOOL generatesDeviceOrientationNotifications;
- (void)beginGeneratingDeviceOrientationNotifications;      // nestable
- (void)endGeneratingDeviceOrientationNotifications;

@property(nonatomic,getter=isBatteryMonitoringEnabled) BOOL batteryMonitoringEnabled __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);  // default is NO
@property(nonatomic,readonly) UIDeviceBatteryState          batteryState __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);  // UIDeviceBatteryStateUnknown if monitoring disabled
@property(nonatomic,readonly) float                         batteryLevel __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);  // 0 .. 1.0. -1.0 if UIDeviceBatteryStateUnknown

@property(nonatomic,getter=isProximityMonitoringEnabled) BOOL proximityMonitoringEnabled __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0); // default is NO
@property(nonatomic,readonly)                            BOOL proximityState __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);  // always returns NO if no proximity detector

@property(nonatomic,readonly,getter=isMultitaskingSupported) BOOL multitaskingSupported __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

@property(nonatomic,readonly) UIUserInterfaceIdiom userInterfaceIdiom __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2);

- (void)playInputClick __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_2);  // Plays a click only if an enabling input view is on-screen and user has enabled input clicks.

@end

@protocol UIInputViewAudioFeedback <NSObject>
@optional

@property (nonatomic, readonly) BOOL enableInputClicksWhenVisible; // If YES, an input view will enable playInputClick.

@end

UIKIT_EXTERN NSString *const UIDeviceOrientationDidChangeNotification;
UIKIT_EXTERN NSString *const UIDeviceBatteryStateDidChangeNotification   __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
UIKIT_EXTERN NSString *const UIDeviceBatteryLevelDidChangeNotification   __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
UIKIT_EXTERN NSString *const UIDeviceProximityStateDidChangeNotification __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
