//
//  UIAccessibility.h
//  UIKit
//
//  Copyright (c) 2008-2011, Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

#import <UIKit/UIAccessibilityAdditions.h>
#import <UIKit/UIAccessibilityConstants.h>
#import <UIKit/UIAccessibilityElement.h>
#import <UIKit/UIAccessibilityIdentification.h>
#import <UIKit/UIAccessibilityZoom.h>

/*
 UIAccessibility
 
 UIAccessibility is implemented on all standard UIKit views and controls so
 that assistive applications can present them to users with disabilities.
 
 Custom items in a user interface should override aspects of UIAccessibility
 to supply details where the default value is incomplete.
 
 For example, a UIImageView subclass may need to override accessibilityLabel,
 but it does not need to override accessibilityFrame.
 
 A completely custom subclass of UIView might need to override all of the
 UIAccessibility methods except accessibilityFrame.
 */
@interface NSObject (UIAccessibility)

/*
 Return YES if the receiver should be exposed as an accessibility element. 
 default == NO
 default on UIKit controls == YES 
 Setting the property to YES will cause the receiver to be visible to assistive applications. 
 */
@property(nonatomic) BOOL isAccessibilityElement;

/*
 Returns the localized label that represents the element. 
 If the element does not display text (an icon for example), this method
 should return text that best labels the element. For example: "Play" could be used for
 a button that is used to play music. "Play button" should not be used, since there is a trait
 that identifies the control is a button.
 default == nil
 default on UIKit controls == derived from the title
 Setting the property will change the label that is returned to the accessibility client. 
 */
@property(nonatomic, copy) NSString *accessibilityLabel;

/*
 Returns a localized string that describes the result of performing an action on the element, when the result is non-obvious.
 The hint should be a brief phrase.
 For example: "Purchases the item." or "Downloads the attachment."
 default == nil
 Setting the property will change the hint that is returned to the accessibility client. 
 */
@property(nonatomic, copy) NSString *accessibilityHint;

/*
 Returns a localized string that represents the value of the element, such as the value 
 of a slider or the text in a text field. Use only when the label of the element
 differs from a value. For example: A volume slider has a label of "Volume", but a value of "60%".
 default == nil
 default on UIKit controls == values for appropriate controls 
 Setting the property will change the value that is returned to the accessibility client.  
 */
@property(nonatomic, copy) NSString *accessibilityValue;

/*
 Returns a UIAccessibilityTraits mask that is the OR combination of
 all accessibility traits that best characterize the element.
 See UIAccessibilityConstants.h for a list of traits.
 When overriding this method, remember to combine your custom traits
 with [super accessibilityTraits].
 default == UIAccessibilityTraitNone
 default on UIKit controls == traits that best characterize individual controls. 
 Setting the property will change the traits that are returned to the accessibility client. 
 */
@property(nonatomic) UIAccessibilityTraits accessibilityTraits;

/*
 Returns the frame of the element in screen coordinates.
 default == CGRectZero
 default on UIViews == the frame of the view
 Setting the property will change the frame that is returned to the accessibility client. 
 */
@property(nonatomic) CGRect accessibilityFrame;

/*
 Returns the activation point for an accessible element in screen coordinates.
 default == Mid-point of the accessibilityFrame.
 */
@property(nonatomic) CGPoint accessibilityActivationPoint __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

/*
 Returns the language code that the element's label, value and hint should be spoken in. 
 If no language is set, the user's language is used.
 The format for the language code should follow Internet BCP 47 for language tags.
 For example, en-US specifies U.S. English.
 default == nil
 */
@property(nonatomic, retain) NSString *accessibilityLanguage;

/*
 Marks all the accessible elements contained within as hidden.
 default == NO
 */
@property(nonatomic) BOOL accessibilityElementsHidden __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

/*
 Informs whether the receiving view should be considered modal by accessibility. If YES, then 
 elements outside this view will be ignored. Only elements inside this view will be exposed.
 default == NO
 */
@property(nonatomic) BOOL accessibilityViewIsModal __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

@end


/*
 UIAccessibilityContainer
 
 UIAccessibilityContainer methods can be overridden to vend individual elements
 that are managed by a single UIView.
 
 For example, a single UIView might draw several items that (to an
 end user) have separate meaning and functionality.  It is important to vend
 each item as an individual accessibility element.
 
 Sub-elements of a container that are not represented by concrete UIView
 instances (perhaps painted text or icons) can be represented using instances
 of UIAccessibilityElement class (see UIAccessibilityElement.h).
 
 Accessibility containers MUST return NO to -isAccessibilityElement.
 */
@interface NSObject (UIAccessibilityContainer)

/*
 Returns the number of accessibility elements in the container.
 */
- (NSInteger)accessibilityElementCount;

/*
 Returns the accessibility element in order, based on index.
 default == nil 
 */
- (id)accessibilityElementAtIndex:(NSInteger)index;

/*
 Returns the ordered index for an accessibility element
 default == NSNotFound 
 */
- (NSInteger)indexOfAccessibilityElement:(id)element;

@end

/*
 UIAccessibilityFocus
 
 Assistive technologies, like VoiceOver, maintain a virtual focus on an element
 that allows the user to inspect an element without activating it.
 */
@interface NSObject (UIAccessibilityFocus)

// Override the following methods to know when an assistive technology has set or unset its virtual focus on the element. 
- (void)accessibilityElementDidBecomeFocused __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_4_0);
- (void)accessibilityElementDidLoseFocus __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_4_0);

// Returns whether an assistive technology is focused on the element.
- (BOOL)accessibilityElementIsFocused __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_4_0);

@end

/*
 UIAccessibilityAction

 An element should implement methods in this category if it supports the action.
 */
@interface NSObject (UIAccessibilityAction)

/* 
 If an element has the UIAccessibilityTraitAdjustable trait, it must also implement
 the following methods. Incrementing will adjust the element so that it increases its content,
 while decrementing decreases its content. For example, accessibilityIncrement will increase the value
 of a UISlider, and accessibilityDecrement will decrease the value.
 */   
- (void)accessibilityIncrement __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_4_0);
- (void)accessibilityDecrement __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_4_0);

/*
 If the user interface requires a scrolling action (e.g. turning the page of a book), a view in the view 
 hierarchy should implement the following method. The return result indicates whether the action 
 succeeded for that direction. If the action failed, the method will be called on a view higher 
 in the hierarchy. If the action succeeds, UIAccessibilityPageScrolledNotification must be posted after
 the scrolling completes.
 default == NO
 */
typedef enum {
    UIAccessibilityScrollDirectionRight = 1,
    UIAccessibilityScrollDirectionLeft,
    UIAccessibilityScrollDirectionUp,
    UIAccessibilityScrollDirectionDown,
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_5_0
    UIAccessibilityScrollDirectionNext,
    UIAccessibilityScrollDirectionPrevious
#endif    
} UIAccessibilityScrollDirection;

- (BOOL)accessibilityScroll:(UIAccessibilityScrollDirection)direction __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_4_2);

/* 
 Implement accessibilityPerformEscape on an element or containing view to exit a modal or hierarchical interface view.
 For example, UIPopoverController implements accessibilityPerformEscape on it's root view, so that when
 called (as a result of a VoiceOver user action), it dismisses the popover.
 If your implementation successfully dismisses the current UI, return YES, otherwise return NO.
 default == NO
 */
- (BOOL)accessibilityPerformEscape __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

@end

/* 
 UIAccessibilityReadingContent
 
 Implemented on an element that represents content meant to be read, like a book or periodical. 
 Use in conjuction with UIAccessibilityTraitCausesPageTurn to provide a continuous reading experience with VoiceOver.
 */
@protocol UIAccessibilityReadingContent
@required

// Returns the line number given a point in the view's coordinate space.
- (NSInteger)accessibilityLineNumberForPoint:(CGPoint)point __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

// Returns the content associated with a line number as a string.
- (NSString *)accessibilityContentForLineNumber:(NSInteger)lineNumber __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

// Returns the on-screen rectangle for a line number.
- (CGRect)accessibilityFrameForLineNumber:(NSInteger)lineNumber __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

// Returns a string representing the text displayed on the current page.
- (NSString *)accessibilityPageContent __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

@end

/*
 UIAccessibilityPostNotification
 
 This function posts a notification to assistive applications.
 Some notifications specify a required or optional argument.
 Pass nil for the argument if the notification does not specify otherwise. 
 See UIAccessibilityConstants.h for a list of notifications.
 */
UIKIT_EXTERN void UIAccessibilityPostNotification(UIAccessibilityNotifications notification, id argument);


/* 
 Assistive Technology
 
 Use UIAccessibilityIsVoiceOverRunning() to determine if VoiceOver is running.
 Listen for UIAccessibilityVoiceOverStatusChanged to know when VoiceOver starts or stops.
 */
UIKIT_EXTERN BOOL UIAccessibilityIsVoiceOverRunning() __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
UIKIT_EXTERN NSString *const UIAccessibilityVoiceOverStatusChanged __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0); 

// Returns whether system audio is mixed down from stereo to mono.
UIKIT_EXTERN BOOL UIAccessibilityIsMonoAudioEnabled() __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
UIKIT_EXTERN NSString *const UIAccessibilityMonoAudioStatusDidChangeNotification __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

// Returns whether the system preference for closed captioning is enabled.
UIKIT_EXTERN BOOL UIAccessibilityIsClosedCaptioningEnabled() __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
UIKIT_EXTERN NSString *const UIAccessibilityClosedCaptioningStatusDidChangeNotification __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

