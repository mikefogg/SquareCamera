//
//  UIApplication.h
//  UIKit
//
//  Copyright (c) 2005-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIResponder.h>
#import <UIKit/UIInterface.h>
#import <UIKit/UIDevice.h>
#import <UIKit/UIAlert.h>

typedef enum {
    UIStatusBarStyleDefault,
    UIStatusBarStyleBlackTranslucent,
    UIStatusBarStyleBlackOpaque
} UIStatusBarStyle;

typedef enum {
    UIStatusBarAnimationNone,
#if __IPHONE_3_2 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    UIStatusBarAnimationFade,
    UIStatusBarAnimationSlide,
#endif
} UIStatusBarAnimation;

// Note that UIInterfaceOrientationLandscapeLeft is equal to UIDeviceOrientationLandscapeRight (and vice versa).
// This is because rotating the device to the left requires rotating the content to the right.
typedef enum {
    UIInterfaceOrientationPortrait           = UIDeviceOrientationPortrait,
    UIInterfaceOrientationPortraitUpsideDown = UIDeviceOrientationPortraitUpsideDown,
    UIInterfaceOrientationLandscapeLeft      = UIDeviceOrientationLandscapeRight,
    UIInterfaceOrientationLandscapeRight     = UIDeviceOrientationLandscapeLeft
} UIInterfaceOrientation;

#define UIDeviceOrientationIsValidInterfaceOrientation(orientation) ((orientation) == UIDeviceOrientationPortrait || (orientation) == UIDeviceOrientationPortraitUpsideDown || (orientation) == UIDeviceOrientationLandscapeLeft || (orientation) == UIDeviceOrientationLandscapeRight)
#define UIInterfaceOrientationIsPortrait(orientation)  ((orientation) == UIInterfaceOrientationPortrait || (orientation) == UIInterfaceOrientationPortraitUpsideDown)
#define UIInterfaceOrientationIsLandscape(orientation) ((orientation) == UIInterfaceOrientationLandscapeLeft || (orientation) == UIInterfaceOrientationLandscapeRight)

#if __IPHONE_3_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED
typedef enum {
    UIRemoteNotificationTypeNone    = 0,
    UIRemoteNotificationTypeBadge   = 1 << 0,
    UIRemoteNotificationTypeSound   = 1 << 1,
    UIRemoteNotificationTypeAlert   = 1 << 2,
    UIRemoteNotificationTypeNewsstandContentAvailability = 1 << 3,
} UIRemoteNotificationType;
#endif

#if __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED
typedef enum {
    UIApplicationStateActive,
    UIApplicationStateInactive,
    UIApplicationStateBackground
} UIApplicationState;

typedef NSUInteger UIBackgroundTaskIdentifier;
UIKIT_EXTERN const UIBackgroundTaskIdentifier UIBackgroundTaskInvalid  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
UIKIT_EXTERN const NSTimeInterval UIMinimumKeepAliveTimeout  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
#endif

#if __IPHONE_5_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED
typedef enum {
    UIUserInterfaceLayoutDirectionLeftToRight,
    UIUserInterfaceLayoutDirectionRightToLeft,
} UIUserInterfaceLayoutDirection;
#endif

@class UIView, UIWindow, UIStatusBar, UIStatusBarWindow, UILocalNotification;
@protocol UIApplicationDelegate;

UIKIT_CLASS_AVAILABLE(2_0) @interface UIApplication : UIResponder <UIActionSheetDelegate>
{
  @package
    id <UIApplicationDelegate>  _delegate;
    CFMutableDictionaryRef      _touchMap;
    NSMutableSet               *_exclusiveTouchWindows;
    UIEvent                    *_event;
    UIEvent                    *_touchesEvent;
    UIEvent                    *_motionEvent;
    UIEvent                    *_remoteControlEvent;
    NSInteger                   _remoteControlEventObservers;
    NSArray                    *_topLevelNibObjects;
    NSInteger                   _networkResourcesCurrentlyLoadingCount;
    NSTimer                    *_hideNetworkActivityIndicatorTimer;
    id                          _editAlertView;
    UIStatusBar                *_statusBar;
    UIStatusBarWindow          *_statusBarWindow;
    NSMutableArray             *_observerBlocks;
    NSString                   *_mainStoryboardName;
    struct {
        unsigned int deactivatingReasonFlags:8;
        unsigned int isSuspended:1;
        unsigned int isSuspendedEventsOnly:1;
        unsigned int isLaunchedSuspended:1;
        unsigned int calledNonSuspendedLaunchDelegate:1;
        unsigned int isHandlingURL:1;
        unsigned int isHandlingRemoteNotification:1;
        unsigned int isHandlingLocalNotification:1;
        unsigned int statusBarShowsProgress:1;
        unsigned int statusBarRequestedStyle:4;
        unsigned int statusBarHidden:1;
        unsigned int blockInteractionEvents:4;
        unsigned int receivesMemoryWarnings:1;
        unsigned int showingProgress:1;
        unsigned int receivesPowerMessages:1;
        unsigned int launchEventReceived:1;
        unsigned int systemIsAnimatingApplicationLifecycleEvent:1; // suspension, resumption, or system gesture
        unsigned int isResuming:1;
        unsigned int isSuspendedUnderLock:1;
        unsigned int shouldExitAfterSendSuspend:1;
        unsigned int shouldExitAfterTaskCompletion:1;
        unsigned int terminating:1;
        unsigned int isHandlingShortCutURL:1;
        unsigned int idleTimerDisabled:1;
        unsigned int deviceOrientation:3;
        unsigned int delegateShouldBeReleasedUponSet:1;
        unsigned int delegateHandleOpenURL:1;
        unsigned int delegateOpenURL:1;
        unsigned int delegateDidReceiveMemoryWarning:1;
        unsigned int delegateWillTerminate:1;
        unsigned int delegateSignificantTimeChange:1;
        unsigned int delegateWillChangeInterfaceOrientation:1;
        unsigned int delegateDidChangeInterfaceOrientation:1;
        unsigned int delegateWillChangeStatusBarFrame:1;
        unsigned int delegateDidChangeStatusBarFrame:1;
        unsigned int delegateDeviceAccelerated:1;
        unsigned int delegateDeviceChangedOrientation:1;
        unsigned int delegateDidBecomeActive:1;
        unsigned int delegateWillResignActive:1;
        unsigned int delegateDidEnterBackground:1;
        unsigned int delegateDidEnterBackgroundWasSent:1;
        unsigned int delegateWillEnterForeground:1;
        unsigned int delegateWillSuspend:1;
        unsigned int delegateDidResume:1;
        unsigned int userDefaultsSyncDisabled:1;
        unsigned int headsetButtonClickCount:4;
        unsigned int isHeadsetButtonDown:1;
        unsigned int isFastForwardActive:1;
        unsigned int isRewindActive:1;
        unsigned int disableViewGroupOpacity:1;
        unsigned int disableViewEdgeAntialiasing:1;
        unsigned int shakeToEdit:1;
        unsigned int isClassic:1;
        unsigned int zoomInClassicMode:1;
        unsigned int ignoreHeadsetClicks:1;
        unsigned int touchRotationDisabled:1;
        unsigned int taskSuspendingUnsupported:1;
        unsigned int taskSuspendingOnLockUnsupported:1;
        unsigned int isUnitTests:1;
        unsigned int requiresHighResolution:1;
        unsigned int disableViewContentScaling:1;
        unsigned int singleUseLaunchOrientation:3;
        unsigned int defaultInterfaceOrientation:3;
        unsigned int delegateWantsNextResponder:1;
        unsigned int isRunningInApplicationSwitcher:1;
        unsigned int isSendingEventForProgrammaticTouchCancellation:1;
    } _applicationFlags;
}

+ (UIApplication *)sharedApplication;

@property(nonatomic,assign) id<UIApplicationDelegate> delegate;

- (void)beginIgnoringInteractionEvents;               // nested. set should be set during animations & transitions to ignore touch and other events
- (void)endIgnoringInteractionEvents;
- (BOOL)isIgnoringInteractionEvents;                  // returns YES if we are at least one deep in ignoring events

@property(nonatomic,getter=isIdleTimerDisabled)       BOOL idleTimerDisabled;	  // default is NO

- (BOOL)openURL:(NSURL*)url;
- (BOOL)canOpenURL:(NSURL *)url __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

- (void)sendEvent:(UIEvent *)event;

@property(nonatomic,readonly) UIWindow *keyWindow;
@property(nonatomic,readonly) NSArray  *windows;

- (BOOL)sendAction:(SEL)action to:(id)target from:(id)sender forEvent:(UIEvent *)event;

@property(nonatomic,getter=isNetworkActivityIndicatorVisible) BOOL networkActivityIndicatorVisible; // showing network spinning gear in status bar. default is NO

@property(nonatomic) UIStatusBarStyle statusBarStyle; // default is UIStatusBarStyleDefault
- (void)setStatusBarStyle:(UIStatusBarStyle)statusBarStyle animated:(BOOL)animated;

@property(nonatomic,getter=isStatusBarHidden) BOOL statusBarHidden;
- (void)setStatusBarHidden:(BOOL)hidden withAnimation:(UIStatusBarAnimation)animation __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2);

// Rotate to a specific orientation.  This only rotates the status bar and updates the statusBarOrientation property.
// This does not change automatically if the device changes orientation.
@property(nonatomic) UIInterfaceOrientation statusBarOrientation;
- (void)setStatusBarOrientation:(UIInterfaceOrientation)interfaceOrientation animated:(BOOL)animated;

@property(nonatomic,readonly) NSTimeInterval statusBarOrientationAnimationDuration; // Returns the animation duration for the status bar during a 90 degree orientation change.  It should be doubled for a 180 degree orientation change.
@property(nonatomic,readonly) CGRect statusBarFrame; // returns CGRectZero if the status bar is hidden

@property(nonatomic) NSInteger applicationIconBadgeNumber;  // set to 0 to hide. default is 0

@property(nonatomic) BOOL applicationSupportsShakeToEdit __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

@property(nonatomic,readonly) UIApplicationState applicationState __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
@property(nonatomic,readonly) NSTimeInterval backgroundTimeRemaining __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

- (UIBackgroundTaskIdentifier)beginBackgroundTaskWithExpirationHandler:(void(^)(void))handler  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
- (void)endBackgroundTask:(UIBackgroundTaskIdentifier)identifier __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

- (BOOL)setKeepAliveTimeout:(NSTimeInterval)timeout handler:(void(^)(void))keepAliveHandler __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
- (void)clearKeepAliveTimeout __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

@property(nonatomic,readonly,getter=isProtectedDataAvailable) BOOL protectedDataAvailable __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

@property(nonatomic,readonly) UIUserInterfaceLayoutDirection userInterfaceLayoutDirection __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

@end

@interface UIApplication (UIRemoteNotifications)

- (void)registerForRemoteNotificationTypes:(UIRemoteNotificationType)types __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
- (void)unregisterForRemoteNotifications __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);       // calls -registerForRemoteNotificationTypes with UIRemoteNotificationTypeNone

// returns the enabled types, also taking into account any systemwide settings; doesn't relate to connectivity
- (UIRemoteNotificationType)enabledRemoteNotificationTypes __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

@end

@interface UIApplication (UILocalNotifications)

- (void)presentLocalNotificationNow:(UILocalNotification *)notification __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

- (void)scheduleLocalNotification:(UILocalNotification *)notification __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);  // copies notification
- (void)cancelLocalNotification:(UILocalNotification *)notification __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
- (void)cancelAllLocalNotifications __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
@property(nonatomic,copy) NSArray *scheduledLocalNotifications __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);         // setter added in iOS 4.2

@end

@interface UIApplication (UIRemoteControlEvents)

- (void)beginReceivingRemoteControlEvents __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
- (void)endReceivingRemoteControlEvents __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

@end

@interface UIApplication (UINewsstand)
- (void)setNewsstandIconImage:(UIImage *)image;
@end

@protocol UIApplicationDelegate<NSObject>

@optional

- (void)applicationDidFinishLaunching:(UIApplication *)application;
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

- (void)applicationDidBecomeActive:(UIApplication *)application;
- (void)applicationWillResignActive:(UIApplication *)application;
- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url;  // Will be deprecated at some point, please replace with application:openURL:sourceApplication:annotation:
- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_2); // no equiv. notification. return NO if the application can't open for some reason

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application;      // try to clean up as much memory as possible. next step is to terminate app
- (void)applicationWillTerminate:(UIApplication *)application;
- (void)applicationSignificantTimeChange:(UIApplication *)application;        // midnight, carrier time update, daylight savings time change

- (void)application:(UIApplication *)application willChangeStatusBarOrientation:(UIInterfaceOrientation)newStatusBarOrientation duration:(NSTimeInterval)duration;
- (void)application:(UIApplication *)application didChangeStatusBarOrientation:(UIInterfaceOrientation)oldStatusBarOrientation;

- (void)application:(UIApplication *)application willChangeStatusBarFrame:(CGRect)newStatusBarFrame;   // in screen coordinates
- (void)application:(UIApplication *)application didChangeStatusBarFrame:(CGRect)oldStatusBarFrame;

// one of these will be called after calling -registerForRemoteNotifications
- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
- (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

- (void)applicationDidEnterBackground:(UIApplication *)application __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
- (void)applicationWillEnterForeground:(UIApplication *)application __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

- (void)applicationProtectedDataWillBecomeUnavailable:(UIApplication *)application __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
- (void)applicationProtectedDataDidBecomeAvailable:(UIApplication *)application    __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

@property (nonatomic, retain) UIWindow *window __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

@end

@interface UIApplication(UIApplicationDeprecated)

@property(nonatomic,getter=isProximitySensingEnabled) BOOL proximitySensingEnabled __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_2_0,__IPHONE_3_0); // default is NO. see UIDevice for replacement
- (void)setStatusBarHidden:(BOOL)hidden animated:(BOOL)animated __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_2_0,__IPHONE_3_2); // use -setStatusBarHidden:withAnimation:

@end

// If nil is specified for principalClassName, the value for NSPrincipalClass from the Info.plist is used. If there is no
// NSPrincipalClass key specified, the UIApplication class is used. The delegate class will be instantiated using init.
UIKIT_EXTERN int UIApplicationMain(int argc, char *argv[], NSString *principalClassName, NSString *delegateClassName);

UIKIT_EXTERN NSString *const UITrackingRunLoopMode;

// These notifications are sent out after the equivalent delegate message is called
UIKIT_EXTERN NSString *const UIApplicationDidEnterBackgroundNotification       __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
UIKIT_EXTERN NSString *const UIApplicationWillEnterForegroundNotification      __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
UIKIT_EXTERN NSString *const UIApplicationDidFinishLaunchingNotification;
UIKIT_EXTERN NSString *const UIApplicationDidBecomeActiveNotification;
UIKIT_EXTERN NSString *const UIApplicationWillResignActiveNotification;
UIKIT_EXTERN NSString *const UIApplicationDidReceiveMemoryWarningNotification;
UIKIT_EXTERN NSString *const UIApplicationWillTerminateNotification;
UIKIT_EXTERN NSString *const UIApplicationSignificantTimeChangeNotification;
UIKIT_EXTERN NSString *const UIApplicationWillChangeStatusBarOrientationNotification; // userInfo contains NSNumber with new orientation
UIKIT_EXTERN NSString *const UIApplicationDidChangeStatusBarOrientationNotification;  // userInfo contains NSNumber with old orientation
UIKIT_EXTERN NSString *const UIApplicationStatusBarOrientationUserInfoKey;            // userInfo dictionary key for status bar orientation
UIKIT_EXTERN NSString *const UIApplicationWillChangeStatusBarFrameNotification;       // userInfo contains NSValue with new frame
UIKIT_EXTERN NSString *const UIApplicationDidChangeStatusBarFrameNotification;        // userInfo contains NSValue with old frame
UIKIT_EXTERN NSString *const UIApplicationStatusBarFrameUserInfoKey;                  // userInfo dictionary key for status bar frame
UIKIT_EXTERN NSString *const UIApplicationLaunchOptionsURLKey                __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0); // userInfo contains NSURL with launch URL
UIKIT_EXTERN NSString *const UIApplicationLaunchOptionsSourceApplicationKey  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0); // userInfo contains NSString with launch app bundle ID
UIKIT_EXTERN NSString *const UIApplicationLaunchOptionsRemoteNotificationKey __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0); // userInfo contains NSDictionary with payload
UIKIT_EXTERN NSString *const UIApplicationLaunchOptionsLocalNotificationKey  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0); // userInfo contains a UILocalNotification
UIKIT_EXTERN NSString *const UIApplicationLaunchOptionsAnnotationKey         __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2); // userInfo contains object with annotation property list
UIKIT_EXTERN NSString *const UIApplicationProtectedDataWillBecomeUnavailable __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
UIKIT_EXTERN NSString *const UIApplicationProtectedDataDidBecomeAvailable    __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
UIKIT_EXTERN NSString *const UIApplicationLaunchOptionsLocationKey           __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0); // app was launched in response to a CoreLocation event.
UIKIT_EXTERN NSString *const UIApplicationLaunchOptionsNewsstandDownloadsKey __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0); // userInfo contains an NSArray of NKAssetDownload identifiers

