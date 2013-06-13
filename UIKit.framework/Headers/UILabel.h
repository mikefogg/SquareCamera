//
//  UILabel.h
//  UIKit
//
//  Copyright (c) 2006-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIView.h>
#import <UIKit/UIStringDrawing.h>
#import <UIKit/UIKitDefines.h>

@class UIColor, UIFont;

UIKIT_CLASS_AVAILABLE(2_0) @interface UILabel : UIView <NSCoding>
{
  @private
    CGSize     _size;
    NSString  *_text;
    UIColor   *_color;
    UIColor   *_highlightedColor;
    UIColor   *_shadowColor;
    UIFont    *_font;
    CGSize     _shadowOffset;
    CGFloat    _minFontSize;
    CGFloat    _actualFontSize;
    NSInteger  _numberOfLines;
    CGFloat    _lastLineBaseline;
    NSInteger  _lineSpacing;
    struct {
        unsigned int lineBreakMode:3;
        unsigned int highlighted:1;
        unsigned int autosizeTextToFit:1;
        unsigned int autotrackTextToFit:1;
        unsigned int baselineAdjustment:2;
        unsigned int alignment:2;
        unsigned int enabled:1;
        unsigned int wordRoundingEnabled:1;
        unsigned int explicitAlignment:1;
        unsigned int marqueeEnabled:1;
        unsigned int marqueeRunable:1;
        unsigned int marqueeRequired:1;
        unsigned int drawsLetterpress:1;
        unsigned int drawsUnderline:1;
    } _textLabelFlags;
}

@property(nonatomic,copy)   NSString       *text;            // default is nil
@property(nonatomic,retain) UIFont         *font;            // default is nil (system font 17 plain)
@property(nonatomic,retain) UIColor        *textColor;       // default is nil (text draws black)
@property(nonatomic,retain) UIColor        *shadowColor;     // default is nil (no shadow)
@property(nonatomic)        CGSize          shadowOffset;    // default is CGSizeMake(0, -1) -- a top shadow
@property(nonatomic)        UITextAlignment textAlignment;   // default is UITextAlignmentLeft
@property(nonatomic)        UILineBreakMode lineBreakMode;   // default is UILineBreakModeTailTruncation. used for single and multiple lines of text

// the 'highlight' property is used by subclasses for such things as pressed states. it's useful to make it part of the base class as a user property

@property(nonatomic,retain)               UIColor *highlightedTextColor; // default is nil
@property(nonatomic,getter=isHighlighted) BOOL     highlighted;          // default is NO

@property(nonatomic,getter=isUserInteractionEnabled) BOOL userInteractionEnabled;  // default is NO
@property(nonatomic,getter=isEnabled)                BOOL enabled;                 // default is YES. changes how the label is drawn

// this determines the number of lines to draw and what to do when sizeToFit is called. default value is 1 (single line). A value of 0 means no limit
// if the height of the text reaches the # of lines or the height of the view is less than the # of lines allowed, the text will be
// truncated using the line break mode.

@property(nonatomic) NSInteger numberOfLines;

// these next 3 property allow the label to be autosized to fit a certain width by shrinking the font size to a minimum font size
// and to specify how the text baseline moves when it needs to shrink the font. this only affects single line text (lineCount == 1)

@property(nonatomic) BOOL adjustsFontSizeToFitWidth;          // default is NO
@property(nonatomic) CGFloat minimumFontSize;                 // default is 0.0
@property(nonatomic) UIBaselineAdjustment baselineAdjustment; // default is UIBaselineAdjustmentAlignBaselines

// override points. can adjust rect before calling super. draw may be called twice to also draw shadow
// label has default content mode of UIViewContentModeRedraw

- (CGRect)textRectForBounds:(CGRect)bounds limitedToNumberOfLines:(NSInteger)numberOfLines;
- (void)drawTextInRect:(CGRect)rect;

@end
