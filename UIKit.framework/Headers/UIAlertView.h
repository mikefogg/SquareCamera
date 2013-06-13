//
//  UIAlertView.h
//  UIKit
//
//  Copyright 2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UITextField.h>
#import <UIKit/UIView.h>

typedef enum {
    UIAlertViewStyleDefault = 0,
    UIAlertViewStyleSecureTextInput,
    UIAlertViewStylePlainTextInput,
    UIAlertViewStyleLoginAndPasswordInput
} UIAlertViewStyle;

@protocol UIAlertViewDelegate;
@class UILabel, UIToolbar, UITabBar, UIWindow, UIBarButtonItem, UIPopoverController;

UIKIT_CLASS_AVAILABLE(2_0) @interface UIAlertView : UIView {
@private
    id <UIAlertViewDelegate> _delegate;
    UILabel   *_titleLabel;
    UILabel   *_subtitleLabel;
    UILabel   *_bodyTextLabel;
    UILabel   *_taglineTextLabel;
    CGFloat    _startY;
    CGPoint    _center;
    id         _context;
    NSInteger  _cancelButton;
    NSInteger  _defaultButton;
    NSInteger  _firstOtherButton;
    UIToolbar *_toolbar;
    UIWindow  *_originalWindow;
    UIWindow  *_dimWindow;
    NSInteger  _suspendTag;
    NSInteger  _dismissButtonIndex;
    CGFloat    _bodyTextHeight;
    NSMutableArray *_buttons;
    NSMutableArray *_textFields;
    UIView *_keyboard;
    UIView *_table;
    UIView *_dimView;
    UIView *_backgroundImageView;
    struct {
        unsigned int numberOfRows:7;
        unsigned int delegateAlertSheetButtonClicked:1;
        unsigned int delegateDidPresentAlertSheet:1;
        unsigned int delegateDidDismissAlertSheet:1;
        unsigned int hideButtonBar:1;
        unsigned int alertStyle:3;
        unsigned int dontDimBackground:1;
        unsigned int dismissSuspended:1;
        unsigned int dontBlockInteraction:1;
        unsigned int sheetWasPoppedUp:1;
        unsigned int animating:1;
        unsigned int hideWhenDoneAnimating:1;
        unsigned int layoutWhenDoneAnimating:1;
        unsigned int titleMaxLineCount:2;
        unsigned int bodyTextMaxLineCount:3;
        unsigned int runsModal:1;
        unsigned int runningModal:1;
        unsigned int addedTextView:1;
        unsigned int addedTableShadows:1;
        unsigned int showOverSBAlerts:1;
        unsigned int showMinTableContent:1;
        unsigned int bodyTextTruncated:1;
        unsigned int orientation:3;
        unsigned int groupsTextFields:1;
        unsigned int includesCancel:1;
        unsigned int useUndoStyle:1;
        unsigned int delegateBodyTextAlignment:1;
        unsigned int delegateClickedButtonAtIndex:1;
        unsigned int delegateClickedButtonAtIndex2:1;
        unsigned int delegateCancel:1;
        unsigned int delegateCancel2:1;
        unsigned int delegateWillPresent:1;
        unsigned int delegateWillPresent2:1;
        unsigned int delegateDidPresent:1;
        unsigned int delegateDidPresent2:1;
        unsigned int delegateWillDismiss:1;
        unsigned int delegateWillDismiss2:1;
        unsigned int delegateDidDismiss:1;
        unsigned int delegateDidDismiss2:1;
        unsigned int delegateShouldEnableFirstOtherButton:1;
        unsigned int forceHorizontalButtonsLayout:1; // for <rdar://problem/7309708> Apex8A118+kb root: Alert bleeds offscreen. Should be removed 
        unsigned int suppressKeyboardOnPopup:1; // the folder creation alert has text fields but we need to pop up without the keyboard 
        unsigned int keyboardShowing:1;
        unsigned int dontCallDismissDelegate:1;
        unsigned int useAutomaticKB:1;
        unsigned int manualKeyboardVisible:1;
		unsigned int rotatingManualKeybaord:1;
        unsigned int shouldHandleFirstKeyUpEvent:1; // when presenting with hardware KB we have to handle the first key up event we get so we don't end up repeating the last key
        unsigned int forceKeyboardUse:1;
        unsigned int cancelWhenDoneAnimating:1;
        unsigned int alertViewStyle:3;
        unsigned int isSBAlert:1;
        unsigned int isBeingDismissed:1; 
    } _modalViewFlags;
}

- (id)initWithTitle:(NSString *)title message:(NSString *)message delegate:(id /*<UIAlertViewDelegate>*/)delegate cancelButtonTitle:(NSString *)cancelButtonTitle otherButtonTitles:(NSString *)otherButtonTitles, ... NS_REQUIRES_NIL_TERMINATION;

@property(nonatomic,assign) id /*<UIAlertViewDelegate>*/ delegate;    // weak reference
@property(nonatomic,copy) NSString *title;
@property(nonatomic,copy) NSString *message;   // secondary explanation text


// adds a button with the title. returns the index (0 based) of where it was added. buttons are displayed in the order added except for the
// cancel button which will be positioned based on HI requirements. buttons cannot be customized.
- (NSInteger)addButtonWithTitle:(NSString *)title;    // returns index of button. 0 based.
- (NSString *)buttonTitleAtIndex:(NSInteger)buttonIndex;
@property(nonatomic,readonly) NSInteger numberOfButtons;
@property(nonatomic) NSInteger cancelButtonIndex;      // if the delegate does not implement -alertViewCancel:, we pretend this button was clicked on. default is -1

@property(nonatomic,readonly) NSInteger firstOtherButtonIndex;	// -1 if no otherButtonTitles or initWithTitle:... not used
@property(nonatomic,readonly,getter=isVisible) BOOL visible;

// shows popup alert animated.
- (void)show;

// hides alert sheet or popup. use this method when you need to explicitly dismiss the alert.
// it does not need to be called if the user presses on a button
- (void)dismissWithClickedButtonIndex:(NSInteger)buttonIndex animated:(BOOL)animated;

// Alert view style - defaults to UIAlertViewStyleDefault
@property(nonatomic,assign) UIAlertViewStyle alertViewStyle __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

/* Retrieve a text field at an index - raises NSRangeException when textFieldIndex is out-of-bounds. 
   The field at index 0 will be the first text field (the single field or the login field), the field at index 1 will be the password field. */
- (UITextField *)textFieldAtIndex:(NSInteger)textFieldIndex __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

@end

@protocol UIAlertViewDelegate <NSObject>
@optional

// Called when a button is clicked. The view will be automatically dismissed after this call returns
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex;

// Called when we cancel a view (eg. the user clicks the Home button). This is not called when the user clicks the cancel button.
// If not defined in the delegate, we simulate a click in the cancel button
- (void)alertViewCancel:(UIAlertView *)alertView;

- (void)willPresentAlertView:(UIAlertView *)alertView;  // before animation and showing view
- (void)didPresentAlertView:(UIAlertView *)alertView;  // after animation

- (void)alertView:(UIAlertView *)alertView willDismissWithButtonIndex:(NSInteger)buttonIndex; // before animation and hiding view
- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex;  // after animation

// Called after edits in any of the default fields added by the style
- (BOOL)alertViewShouldEnableFirstOtherButton:(UIAlertView *)alertView;

@end
