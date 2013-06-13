//
//  UITextView.h
//  UIKit
//
//  Copyright (c) 2007-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIScrollView.h>
#import <UIKit/UIStringDrawing.h>
#import <UIKit/UITextInput.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIDataDetectors.h>

@class DOMHTMLElement;
@class UIDelayedAction;
@class UIEvent, UITouch, UIFont, UIColor;
@class UITextInputTraits;
@class UITextInteractionAssistant;
@class UIWebDocumentView;
@class WebCoreFrameBridge;
@class WebFrame;
@class UITextInteractionAssistant;
@class UITextSelectionView;
@class UITextView;


@protocol UITextViewDelegate <NSObject, UIScrollViewDelegate>

@optional

- (BOOL)textViewShouldBeginEditing:(UITextView *)textView;
- (BOOL)textViewShouldEndEditing:(UITextView *)textView;

- (void)textViewDidBeginEditing:(UITextView *)textView;
- (void)textViewDidEndEditing:(UITextView *)textView;

- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text;
- (void)textViewDidChange:(UITextView *)textView;

- (void)textViewDidChangeSelection:(UITextView *)textView;

@end


UIKIT_CLASS_AVAILABLE(2_0) @interface UITextView : UIScrollView <UITextInput> 
{
  @package
    WebFrame           *m_frame;
    DOMHTMLElement     *m_body;
    int                 m_marginTop;
    UIDelayedAction    *m_selectionTimer;
    UIDelayedAction    *m_longPressAction;
    BOOL                m_editable;
    BOOL                m_editing;
    BOOL                m_becomesEditableWithGestures;
    BOOL                m_reentrancyGuard;
    BOOL                m_readyForScroll;
    BOOL                m_hasExplicitTextAlignment;
    BOOL                m_hasExplicitLineHeight;
    
    // Gesture recognition.
    UITextInteractionAssistant *m_interactionAssistant;
    UITextSelectionView *m_selectionView;
    
    // property ivars
    UIWebDocumentView  *m_webView;
    UIFont             *m_font;
    UIColor            *m_textColor;
    UITextAlignment     m_textAlignment;
    UIView             *m_inputView;
    UIView             *m_inputAccessoryView;
    float               m_lineHeight;
    BOOL                m_skipScrollContainingView;
}

@property(nonatomic,assign) id<UITextViewDelegate> delegate;
@property(nonatomic,copy) NSString *text;
@property(nonatomic,retain) UIFont *font;
@property(nonatomic,retain) UIColor *textColor;
@property(nonatomic) UITextAlignment textAlignment;    // default is UITextAlignmentLeft
@property(nonatomic) NSRange selectedRange;            // only ranges of length 0 are supported
@property(nonatomic,getter=isEditable) BOOL editable;
@property(nonatomic) UIDataDetectorTypes dataDetectorTypes __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_3_0);

- (BOOL)hasText;
- (void)scrollRangeToVisible:(NSRange)range;


// Presented when object becomes first responder.  If set to nil, reverts to following responder chain.  If
// set while first responder, will not take effect until reloadInputViews is called.
@property (readwrite, retain) UIView *inputView;             
@property (readwrite, retain) UIView *inputAccessoryView;

@end

UIKIT_EXTERN NSString * const UITextViewTextDidBeginEditingNotification;
UIKIT_EXTERN NSString * const UITextViewTextDidChangeNotification;
UIKIT_EXTERN NSString * const UITextViewTextDidEndEditingNotification;
