//
//  UIGestureRecognizerSubclass.h
//  UIKit
//
//  Copyright (c) 2008-2011, Apple Inc. All rights reserved.
//

#import <UIKit/UIGestureRecognizer.h>

// the extensions in this header are to be used only by subclasses of UIGestureRecognizer
// code that uses UIGestureRecognizers must never call these

@interface UIGestureRecognizer (ForSubclassEyesOnly)

// readonly for users of a gesture recognizer. may only be changed by direct subclasses of UIGestureRecognizer
@property(nonatomic,readwrite) UIGestureRecognizerState state;  // the current state of the gesture recognizer. can only be set by subclasses of UIGestureRecognizer, but can be read by consumers

- (void)ignoreTouch:(UITouch*)touch forEvent:(UIEvent*)event; // if a touch isn't part of this gesture it can be passed to this method to be ignored. ignored touches won't be cancelled on the view even if cancelsTouchesInView is YES

// the following methods are to be overridden by subclasses of UIGestureRecognizer
// if you override one you must call super

// called automatically by the runtime after the gesture state has been set to UIGestureRecognizerStateEnded
// any internal state should be reset to prepare for a new attempt to recognize the gesture
// after this is received all remaining active touches will be ignored (no further updates will be received for touches that had already begun but haven't ended)
- (void)reset;

// same behavior as the equivalent delegate methods, but can be used by subclasses to define class-wide prevention rules
// for example, a UITapGestureRecognizer never prevents another UITapGestureRecognizer with a higher tap count
- (BOOL)canPreventGestureRecognizer:(UIGestureRecognizer *)preventedGestureRecognizer;
- (BOOL)canBePreventedByGestureRecognizer:(UIGestureRecognizer *)preventingGestureRecognizer;

// mirror of the touch-delivery methods on UIResponder
// UIGestureRecognizers aren't in the responder chain, but observe touches hit-tested to their view and their view's subviews
// UIGestureRecognizers receive touches before the view to which the touch was hit-tested
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event;

@end
