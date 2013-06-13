//
//  UIStringDrawing.h
//  UIKit
//
//  Copyright (c) 2005-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
#import <CoreGraphics/CoreGraphics.h>
#endif

/* Keys for text attributes dictionaries.
 */
// Key to the font in the text attributes dictionary. A UIFont instance is expected. Use a font with size 0.0 to get the default font size for the situation.
UIKIT_EXTERN NSString *const UITextAttributeFont __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0); 
// Key to the text color in the text attributes dictionary. A UIColor instance is expected.
UIKIT_EXTERN NSString *const UITextAttributeTextColor __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
// Key to the text shadow color in the text attributes dictionary.  A UIColor instance is expected.
UIKIT_EXTERN NSString *const UITextAttributeTextShadowColor __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0); 
// Key to the offset used for the text shadow in the text attributes dictionary. An NSValue instance wrapping a UIOffset struct is expected.
UIKIT_EXTERN NSString *const UITextAttributeTextShadowOffset __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0); 

typedef enum {		
    UILineBreakModeWordWrap = 0,            // Wrap at word boundaries
    UILineBreakModeCharacterWrap,           // Wrap at character boundaries
    UILineBreakModeClip,                    // Simply clip when it hits the end of the rect
    UILineBreakModeHeadTruncation,          // Truncate at head of line: "...wxyz". Will truncate multiline text on first line
    UILineBreakModeTailTruncation,          // Truncate at tail of line: "abcd...". Will truncate multiline text on last line
    UILineBreakModeMiddleTruncation,        // Truncate middle of line:  "ab...yz". Will truncate multiline text in the middle
} UILineBreakMode;

typedef enum {
    UITextAlignmentLeft = 0,
    UITextAlignmentCenter,
    UITextAlignmentRight,                   // could add justified in future
} UITextAlignment;

typedef enum {
    UIBaselineAdjustmentAlignBaselines = 0, // default. used when shrinking text to position based on the original baseline
    UIBaselineAdjustmentAlignCenters,
    UIBaselineAdjustmentNone,
} UIBaselineAdjustment;

@class UIFont;

// these methods draw using a UIFont. draw methods return size of actual string. all draw in the current context using the current color

@interface NSString(UIStringDrawing)

// Single line, no wrapping. Truncation based on the UILineBreakMode.
- (CGSize)sizeWithFont:(UIFont *)font; // Uses UILineBreakModeWordWrap
- (CGSize)sizeWithFont:(UIFont *)font forWidth:(CGFloat)width lineBreakMode:(UILineBreakMode)lineBreakMode;

// Single line, no wrapping. Truncation based on the UILineBreakMode.
- (CGSize)drawAtPoint:(CGPoint)point withFont:(UIFont *)font; // Uses UILineBreakModeWordWrap
- (CGSize)drawAtPoint:(CGPoint)point forWidth:(CGFloat)width withFont:(UIFont *)font lineBreakMode:(UILineBreakMode)lineBreakMode;

// Wrapping to fit horizontal and vertical size. Text will be wrapped and truncated using the UILineBreakMode. If the height is less than a line of text, it may return
// a vertical size that is bigger than the one passed in.
// If you size your text using the constrainedToSize: methods below, you should draw the text using the drawInRect: methods using the same line break mode for consistency
- (CGSize)sizeWithFont:(UIFont *)font constrainedToSize:(CGSize)size; // Uses UILineBreakModeWordWrap
- (CGSize)sizeWithFont:(UIFont *)font constrainedToSize:(CGSize)size lineBreakMode:(UILineBreakMode)lineBreakMode; // UITextAlignment is not needed to determine size

// Wrapping to fit horizontal and vertical size.
- (CGSize)drawInRect:(CGRect)rect withFont:(UIFont *)font; // Uses UILineBreakModeWordWrap and UITextAlignmentLeft
- (CGSize)drawInRect:(CGRect)rect withFont:(UIFont *)font lineBreakMode:(UILineBreakMode)lineBreakMode; // Uses UITextAlignmentLeft
- (CGSize)drawInRect:(CGRect)rect withFont:(UIFont *)font lineBreakMode:(UILineBreakMode)lineBreakMode alignment:(UITextAlignment)alignment;

// These methods will behave identically to the above single line methods if the string will fit in the specified width in the specified font.
// If not, the font size will be reduced until either the string fits or the minimum font size is reached.  If the minimum font
// size is reached and the string still won't fit, the string will be truncated and drawn at the minimum font size.
// The first two methods are used together, and the actualFontSize returned in the sizeWithFont method should be passed to the drawAtPoint method.
// The last method will do the sizing calculation and drawing in one operation.
- (CGSize)sizeWithFont:(UIFont *)font minFontSize:(CGFloat)minFontSize actualFontSize:(CGFloat *)actualFontSize forWidth:(CGFloat)width lineBreakMode:(UILineBreakMode)lineBreakMode;

- (CGSize)drawAtPoint:(CGPoint)point forWidth:(CGFloat)width withFont:(UIFont *)font fontSize:(CGFloat)fontSize lineBreakMode:(UILineBreakMode)lineBreakMode baselineAdjustment:(UIBaselineAdjustment)baselineAdjustment; // default is UIBaselineAdjustmentAlignBaselines

- (CGSize)drawAtPoint:(CGPoint)point forWidth:(CGFloat)width withFont:(UIFont *)font minFontSize:(CGFloat)minFontSize actualFontSize:(CGFloat *)actualFontSize lineBreakMode:(UILineBreakMode)lineBreakMode baselineAdjustment:(UIBaselineAdjustment)baselineAdjustment; // default is UIBaselineAdjustmentAlignBaselines

@end
