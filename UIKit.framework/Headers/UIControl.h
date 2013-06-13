//
//  UIControl.h
//  UIKit
//
//  Copyright (c) 2005-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>

enum {
    UIControlEventTouchDown           = 1 <<  0,      // on all touch downs
    UIControlEventTouchDownRepeat     = 1 <<  1,      // on multiple touchdowns (tap count > 1)
    UIControlEventTouchDragInside     = 1 <<  2,
    UIControlEventTouchDragOutside    = 1 <<  3,
    UIControlEventTouchDragEnter      = 1 <<  4,
    UIControlEventTouchDragExit       = 1 <<  5,
    UIControlEventTouchUpInside       = 1 <<  6,
    UIControlEventTouchUpOutside      = 1 <<  7,
    UIControlEventTouchCancel         = 1 <<  8,

    UIControlEventValueChanged        = 1 << 12,     // sliders, etc.

    UIControlEventEditingDidBegin     = 1 << 16,     // UITextField
    UIControlEventEditingChanged      = 1 << 17,
    UIControlEventEditingDidEnd       = 1 << 18,
    UIControlEventEditingDidEndOnExit = 1 << 19,     // 'return key' ending editing

    UIControlEventAllTouchEvents      = 0x00000FFF,  // for touch events
    UIControlEventAllEditingEvents    = 0x000F0000,  // for UITextField
    UIControlEventApplicationReserved = 0x0F000000,  // range available for application use
    UIControlEventSystemReserved      = 0xF0000000,  // range reserved for internal framework use
    UIControlEventAllEvents           = 0xFFFFFFFF
};
typedef NSUInteger UIControlEvents;

typedef enum {
    UIControlContentVerticalAlignmentCenter  = 0,
    UIControlContentVerticalAlignmentTop     = 1,
    UIControlContentVerticalAlignmentBottom  = 2,
    UIControlContentVerticalAlignmentFill    = 3,
} UIControlContentVerticalAlignment;

typedef enum {
    UIControlContentHorizontalAlignmentCenter = 0,
    UIControlContentHorizontalAlignmentLeft   = 1,
    UIControlContentHorizontalAlignmentRight  = 2,
    UIControlContentHorizontalAlignmentFill   = 3,
} UIControlContentHorizontalAlignment;

enum {
    UIControlStateNormal       = 0,                       
    UIControlStateHighlighted  = 1 << 0,                  // used when UIControl isHighlighted is set
    UIControlStateDisabled     = 1 << 1,
    UIControlStateSelected     = 1 << 2,                  // flag usable by app (see below)
    UIControlStateApplication  = 0x00FF0000,              // additional flags available for application use
    UIControlStateReserved     = 0xFF000000               // flags reserved for internal framework use
};
typedef NSUInteger UIControlState;

@class UITouch;
@class UIEvent;

//______________________________________________________

UIKIT_CLASS_AVAILABLE(2_0) @interface UIControl : UIView {
  @package
    NSMutableArray* _targetActions;
    CGPoint         _previousPoint;
    CFAbsoluteTime  _downTime;
    struct {
        unsigned int disabled:1;
        unsigned int tracking:1;
        unsigned int touchInside:1;
        unsigned int touchDragged:1;
        unsigned int requiresDisplayOnTracking:1;
        unsigned int highlighted:1;
        unsigned int dontHighlightOnTouchDown:1;
        unsigned int delayActions:1;
        unsigned int allowActionsToQueue:1;
        unsigned int pendingUnhighlight:1;
        unsigned int selected:1;
	unsigned int verticalAlignment:2;
	unsigned int horizontalAlignment:2;
    } _controlFlags;
}

@property(nonatomic,getter=isEnabled) BOOL enabled;                                  // default is YES. if NO, ignores touch events and subclasses may draw differently
@property(nonatomic,getter=isSelected) BOOL selected;                                // default is NO may be used by some subclasses or by application
@property(nonatomic,getter=isHighlighted) BOOL highlighted;                          // default is NO. this gets set/cleared automatically when touch enters/exits during tracking and cleared on up
@property(nonatomic) UIControlContentVerticalAlignment contentVerticalAlignment;     // how to position content vertically inside control. default is center
@property(nonatomic) UIControlContentHorizontalAlignment contentHorizontalAlignment; // how to position content hozontally inside control. default is center

@property(nonatomic,readonly) UIControlState state;                  // could be more than one state (e.g. disabled|selected). synthesized from other flags.
@property(nonatomic,readonly,getter=isTracking) BOOL tracking;
@property(nonatomic,readonly,getter=isTouchInside) BOOL touchInside; // valid during tracking only

- (BOOL)beginTrackingWithTouch:(UITouch *)touch withEvent:(UIEvent *)event;
- (BOOL)continueTrackingWithTouch:(UITouch *)touch withEvent:(UIEvent *)event;
- (void)endTrackingWithTouch:(UITouch *)touch withEvent:(UIEvent *)event;
- (void)cancelTrackingWithEvent:(UIEvent *)event;   // event may be nil if cancelled for non-event reasons, e.g. removed from window

// add target/action for particular event. you can call this multiple times and you can specify multiple target/actions for a particular event.
// passing in nil as the target goes up the responder chain. The action may optionally include the sender and the event in that order
// the action cannot be NULL. Note that the target is not retained.
- (void)addTarget:(id)target action:(SEL)action forControlEvents:(UIControlEvents)controlEvents;

// remove the target/action for a set of events. pass in NULL for the action to remove all actions for that target
- (void)removeTarget:(id)target action:(SEL)action forControlEvents:(UIControlEvents)controlEvents;

// get info about target & actions. this makes it possible to enumerate all target/actions by checking for each event kind
- (NSSet *)allTargets;                                                                     // set may include NSNull to indicate at least one nil target
- (UIControlEvents)allControlEvents;                                                       // list of all events that have at least one action
- (NSArray *)actionsForTarget:(id)target forControlEvent:(UIControlEvents)controlEvent;    // single event. returns NSArray of NSString selector names. returns nil if none

// send the action. the first method is called for the event and is a point at which you can observe or override behavior. it is called repeately by the second.
- (void)sendAction:(SEL)action to:(id)target forEvent:(UIEvent *)event;
- (void)sendActionsForControlEvents:(UIControlEvents)controlEvents;                        // send all actions associated with events

@end
