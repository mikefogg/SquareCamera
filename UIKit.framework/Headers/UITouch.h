//
//  UITouch.h
//  UIKit
//
//  Copyright (c) 2007-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>

@class UIWindow, UIView;

typedef enum {
    UITouchPhaseBegan,             // whenever a finger touches the surface.
    UITouchPhaseMoved,             // whenever a finger moves on the surface.
    UITouchPhaseStationary,        // whenever a finger is touching the surface but hasn't moved since the previous event.
    UITouchPhaseEnded,             // whenever a finger leaves the surface.
    UITouchPhaseCancelled,         // whenever a touch doesn't end but we need to stop tracking (e.g. putting device to face)
} UITouchPhase;

/* Instance variables of any UIKit class should be considered private. For binary compatibility reasons, we cannot remove the UITouch instance variable symbols from UIKit at this time. However, applications which use iOS 4.0 and later must not access UITouch instance variables.
 */
#if defined (UITOUCH_INSTANCE_VARIABLE_GUARD)
#define UITOUCH_IVARS_PRIVATE
#else
#define UITOUCH_IVARS_PRIVATE @package
#endif

UIKIT_CLASS_AVAILABLE(2_0) @interface UITouch : NSObject
{
UITOUCH_IVARS_PRIVATE
    NSTimeInterval  _timestamp;
    UITouchPhase    _phase;
    UITouchPhase    _savedPhase;
    NSUInteger      _tapCount;

    UIWindow        *_window;
    UIView          *_view;
    UIView          *_gestureView;
    UIView          *_warpedIntoView;
    NSMutableArray  *_gestureRecognizers;
    NSMutableArray  *_forwardingRecord;

    CGPoint         _locationInWindow;
    CGPoint         _previousLocationInWindow;
    UInt8           _pathIndex;
    UInt8           _pathIdentity;
    float           _pathMajorRadius;
    struct {
        unsigned int _firstTouchForView:1;
        unsigned int _isTap:1;
        unsigned int _isDelayed:1;
        unsigned int _sentTouchesEnded:1;
        unsigned int _abandonForwardingRecord:1;
    } _touchFlags;
}

@property(nonatomic,readonly) NSTimeInterval      timestamp;
@property(nonatomic,readonly) UITouchPhase        phase;
@property(nonatomic,readonly) NSUInteger          tapCount;   // touch down within a certain point within a certain amount of time

@property(nonatomic,readonly,retain) UIWindow    *window;
@property(nonatomic,readonly,retain) UIView      *view;
@property(nonatomic,readonly,copy)   NSArray     *gestureRecognizers __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2);

- (CGPoint)locationInView:(UIView *)view;
- (CGPoint)previousLocationInView:(UIView *)view;

@end
