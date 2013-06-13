//
//  UIActionSheet.h
//  UIKit
//
//  Copyright 2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UITextField.h>
#import <UIKit/UIView.h>


@protocol UIActionSheetDelegate;
@class UILabel, UIToolbar, UITabBar, UIWindow, UIBarButtonItem, UIPopoverController;

typedef enum {
    UIActionSheetStyleAutomatic        = -1,       // take appearance from toolbar style otherwise uses 'default'
    UIActionSheetStyleDefault          = UIBarStyleDefault,
    UIActionSheetStyleBlackTranslucent = UIBarStyleBlackTranslucent,
    UIActionSheetStyleBlackOpaque      = UIBarStyleBlackOpaque,
} UIActionSheetStyle;

UIKIT_CLASS_AVAILABLE(2_0) @interface UIActionSheet : UIView {
@private
    id <UIActionSheetDelegate> _delegate;
    UILabel   *_titleLabel;
    UILabel   *_subtitleLabel;
    UILabel   *_bodyTextLabel;
    UILabel   *_taglineTextLabel;
    CGFloat    _startY;
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
    NSMutableArray *_buttonsInTable;
    NSMutableArray *_textFields;
    UIView *_keyboard;
    UIView *_table;
    UIView *_buttonTableView;
    UIView *_dimView;
    UIPopoverController * _popoverController;
    CGFloat _fontSizeInTableView; // font size for 'complex' buttons (phone numbers || doc interaction controller)
    CGFloat _iconOffset; // doc interaction controller app icon
    CGFloat _labelOffset; // phone numbers layout 
    CGFloat _labelWidth;
    CGFloat _titleWidth;
    BOOL _oldIgnoreTapsValue;
    
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
        unsigned int sheetWasShown:1;
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
        unsigned int popupFromPoint:1;
        unsigned int inPopover:1;
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
        unsigned int dontCallDismissDelegate:1;
        unsigned int useAutomaticKB:1;
        unsigned int twoColumnsLayoutMode:7; // one column || even width (leaves empty space) || first button wider || last button wider
        unsigned int threeColumnsLayoutMode:7; // one column || even width (leaves empty space) || first button wider || last button wider
        unsigned int shouldHandleFirstKeyUpEvent:1; // when presenting with hardware KB we have to handle the first key up event we get so we don't end up repeating the last key
        unsigned int cancelWhenDoneAnimating:1;
        unsigned int useThreePartButtons:1; // phone numbers layout
        unsigned int useTwoPartButtons:1; // doc interaction layout
        unsigned int displaySelectedButtonGlyph:1;
        int indexOfSelectedButton:7; // default -1 (no checkmark) otherwise will display a checkbox (this for the airtunes action sheet)
        unsigned int useCustomSelectedButtonGlyph:1;
    } _modalViewFlags;
    UIActionSheetStyle _actionSheetStyle;
    UIImage *_selectedButtonGlyphImage;
    UIImage *_selectedButtonGlyphHighlightedImage;
}

- (id)initWithTitle:(NSString *)title delegate:(id<UIActionSheetDelegate>)delegate cancelButtonTitle:(NSString *)cancelButtonTitle destructiveButtonTitle:(NSString *)destructiveButtonTitle otherButtonTitles:(NSString *)otherButtonTitles, ... NS_REQUIRES_NIL_TERMINATION;

@property(nonatomic,assign) id<UIActionSheetDelegate> delegate;    // weak reference
@property(nonatomic,copy) NSString *title;
@property(nonatomic) UIActionSheetStyle actionSheetStyle; // default is UIActionSheetStyleAutomatic. ignored if alert is visible

// adds a button with the title. returns the index (0 based) of where it was added. buttons are displayed in the order added except for the
// destructive and cancel button which will be positioned based on HI requirements. buttons cannot be customized.
- (NSInteger)addButtonWithTitle:(NSString *)title;    // returns index of button. 0 based.
- (NSString *)buttonTitleAtIndex:(NSInteger)buttonIndex;
@property(nonatomic,readonly) NSInteger numberOfButtons;
@property(nonatomic) NSInteger cancelButtonIndex;      // if the delegate does not implement -actionSheetCancel:, we pretend this button was clicked on. default is -1
@property(nonatomic) NSInteger destructiveButtonIndex;        // sets destructive (red) button. -1 means none set. default is -1. ignored if only one button

@property(nonatomic,readonly) NSInteger firstOtherButtonIndex;	// -1 if no otherButtonTitles or initWithTitle:... not used
@property(nonatomic,readonly,getter=isVisible) BOOL visible;

// show a sheet animated. you can specify either a toolbar, a tab bar, a bar butto item or a plain view. We do a special animation if the sheet rises from
// a toolbar, tab bar or bar button item and we will automatically select the correct style based on the bar style. if not from a bar, we use
// UIActionSheetStyleDefault if automatic style set
- (void)showFromToolbar:(UIToolbar *)view;
- (void)showFromTabBar:(UITabBar *)view;
- (void)showFromBarButtonItem:(UIBarButtonItem *)item animated:(BOOL)animated __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_3_2);
- (void)showFromRect:(CGRect)rect inView:(UIView *)view animated:(BOOL)animated __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_3_2);
- (void)showInView:(UIView *)view;

// hides alert sheet or popup. use this method when you need to explicitly dismiss the alert.
// it does not need to be called if the user presses on a button
- (void)dismissWithClickedButtonIndex:(NSInteger)buttonIndex animated:(BOOL)animated;

@end


@protocol UIActionSheetDelegate <NSObject>
@optional

// Called when a button is clicked. The view will be automatically dismissed after this call returns
- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex;

// Called when we cancel a view (eg. the user clicks the Home button). This is not called when the user clicks the cancel button.
// If not defined in the delegate, we simulate a click in the cancel button
- (void)actionSheetCancel:(UIActionSheet *)actionSheet;

- (void)willPresentActionSheet:(UIActionSheet *)actionSheet;  // before animation and showing view
- (void)didPresentActionSheet:(UIActionSheet *)actionSheet;  // after animation

- (void)actionSheet:(UIActionSheet *)actionSheet willDismissWithButtonIndex:(NSInteger)buttonIndex; // before animation and hiding view
- (void)actionSheet:(UIActionSheet *)actionSheet didDismissWithButtonIndex:(NSInteger)buttonIndex;  // after animation

@end

