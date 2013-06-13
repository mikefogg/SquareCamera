//
//  UIAccessibilityConstants.h
//  UIKit
//
//  Copyright (c) 2009-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

/*
 Accessibility Traits
 
 Traits are combined in a mask to help assistive applications understand
 the meaning and intended use of a particular accessibility element.
 
 UIKit applies appropriate traits to all standard controls, however the
 following traits may be used in conjunction with custom controls.
 
 When setting accessiblity traits, combine custom traits with 
 [super accessibilityTraits]. An incorrect combination of custom traits
 will cause accessibility clients to incorrectly interpret the element.
 Use common sense when combining traits.
 */
typedef uint64_t UIAccessibilityTraits;

// Used when the element has no traits.
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitNone;

// Used when the element should be treated as a button.
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitButton;

// Used when the element should be treated as a link.
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitLink;

// Used when the text field element should also be treated as a search field.
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitSearchField;

// Used when the element should be treated as an image. Can be combined with button or link, for example.
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitImage;

/*
 Used when the element is selected.
 For example, a selected row in a table or a selected button within a segmented control.
 */
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitSelected;

// Used when the element plays its own sound when activated.
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitPlaysSound;

// Used when the element acts as a keyboard key.
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitKeyboardKey;

// Used when the element should be treated as static text that cannot change.
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitStaticText;

/*
 Used when an element can be used to provide a quick summary of current 
 conditions in the app when the app first launches.  For example, when Weather
 first launches, the element with today's weather conditions is marked with
 this trait.
 */
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitSummaryElement;

// Used when the control is not enabled and does not respond to user input.
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitNotEnabled;

/*
 Used when the element frequently updates its label or value, but too often to send notifications. 
 Allows an accessibility client to poll for changes. A stopwatch would be an example.
 */
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitUpdatesFrequently;

/*
 Used when activating an element starts a media session (e.g. playing a movie, recording audio) 
 that should not be interrupted by output from an assistive technology, like VoiceOver.
 */
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitStartsMediaSession __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_4_0);

/*
 Used when an element can be "adjusted" (e.g. a slider). The element must also 
 implement accessibilityIncrement and accessibilityDecrement.
 */
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitAdjustable __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_4_0);

// Used when an element allows direct touch interaction for VoiceOver users (for example, a view representing a piano keyboard).
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitAllowsDirectInteraction __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

/*
 Informs VoiceOver that it should scroll to the next page when it finishes reading the contents of the
 element. VoiceOver will scroll by calling accessibilityScroll: with UIAccessibilityScrollDirectionNext and will 
 stop scrolling when it detects the content has not changed.
 */
UIKIT_EXTERN UIAccessibilityTraits UIAccessibilityTraitCausesPageTurn __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

/*
 Accessibility Notifications
 
 UIKit posts notifications for standard events as appropriate, however the
 following notifications may be posted to accommodate custom controls
 and events.
 */
typedef uint32_t UIAccessibilityNotifications;

/*
 Should be posted when a new view appears that encompasses a major portion of the screen.
 No argument.
 */
UIKIT_EXTERN UIAccessibilityNotifications UIAccessibilityScreenChangedNotification;

/*
 Should be posted when the layout of a screen changes, for example when an individual
 element appears or disappears.
 No argument.
 */
UIKIT_EXTERN UIAccessibilityNotifications UIAccessibilityLayoutChangedNotification;

/*
 Should be posted when an announcement needs to be conveyed to the assistive technology. 
 The assistive technology will output the announcement string that is used as the argument.
 The argument is a NSString.
 */
UIKIT_EXTERN UIAccessibilityNotifications UIAccessibilityAnnouncementNotification __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_4_0);

/*
 Should be posted after accessibilityScroll: is called and the scrolling action has completed. 
 A string representing the status of the new scroll position should be used as the argument 
 (e.g. "Page 2 of 5"). If the same status is used repeatedly, the assistive technology will 
 indicate a border has been reached.
 The argument is a NSString.
 */
UIKIT_EXTERN UIAccessibilityNotifications UIAccessibilityPageScrolledNotification __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_4_2);

