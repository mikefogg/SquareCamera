//
//  UIPrintFormatter.h
//  UIKit
//
//  Copyright 2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIView.h>
#import <UIKit/UIStringDrawing.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UIKitDefines.h>

@class UIPrintPageRenderer;
@class UIView, UIFont, UIColor;

UIKIT_CLASS_AVAILABLE(4_2) @interface UIPrintFormatter : NSObject <NSCopying> {
  @private
    UIPrintPageRenderer *_printPageRenderer;
    CGFloat              _maximumContentHeight;
    CGFloat              _maximumContentWidth;
    UIEdgeInsets         _contentInsets;
    NSInteger            _startPage;
    NSInteger            _pageCount;
    BOOL                 _needsRecalc;
}

@property(nonatomic,readonly,assign) UIPrintPageRenderer *printPageRenderer; // default is nil. set when formatter added to a print page renderer
- (void)removeFromPrintPageRenderer;

@property(nonatomic) CGFloat      maximumContentHeight;      // default is 0.0. limits content to width
@property(nonatomic) CGFloat      maximumContentWidth;       // default is 0.0. limits content to height
@property(nonatomic) UIEdgeInsets contentInsets;             // default is UIEdgeInsetsZero. from edge of printableRect. applies to whole content. bottom inset unused

@property(nonatomic)          NSInteger startPage;           // default is NSNotFound
@property(nonatomic,readonly) NSInteger pageCount;           // calculated

- (CGRect)rectForPageAtIndex:(NSInteger)pageIndex;                     // returns empty rect if index out of range
- (void)drawInRect:(CGRect)rect forPageAtIndex:(NSInteger)pageIndex;   // override point to add custom drawing 

@end

//______________________________

UIKIT_CLASS_AVAILABLE(4_2) @interface UISimpleTextPrintFormatter : UIPrintFormatter {
}

- (id)initWithText:(NSString *)text;
@property(nonatomic,copy)     NSString       *text;                   // cannot change once drawing started
@property(nonatomic,retain)   UIFont         *font;
@property(nonatomic,retain)   UIColor        *color;
@property(nonatomic)          UITextAlignment textAlignment;

@end

//______________________________

UIKIT_CLASS_AVAILABLE(4_2) @interface UIMarkupTextPrintFormatter : UIPrintFormatter {
}

- (id)initWithMarkupText:(NSString *)markupText;
@property(nonatomic,copy) NSString *markupText;                    // cannot change once drawing started

@end

//______________________________

UIKIT_CLASS_AVAILABLE(4_2) @interface UIViewPrintFormatter : UIPrintFormatter {
  @private
    UIView *_view;
}

@property(nonatomic,readonly) UIView *view;

@end

//______________________________

@interface UIView(UIPrintFormatter)

- (UIViewPrintFormatter *)viewPrintFormatter;                                          // returns a new print formatter each time
- (void)drawRect:(CGRect)rect forViewPrintFormatter:(UIViewPrintFormatter *)formatter;     // default calls -drawRect:

@end
