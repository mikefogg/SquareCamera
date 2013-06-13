//
//  UIColor.h
//  UIKit
//
//  Copyright (c) 2005-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <CoreImage/CoreImage.h>
#import <UIKit/UIKitDefines.h>

@class UIImage;

UIKIT_CLASS_AVAILABLE(2_0) @interface UIColor : NSObject <NSCoding> {
  @private
}

// Convenience methods for creating autoreleased colors
+ (UIColor *)colorWithWhite:(CGFloat)white alpha:(CGFloat)alpha;
+ (UIColor *)colorWithHue:(CGFloat)hue saturation:(CGFloat)saturation brightness:(CGFloat)brightness alpha:(CGFloat)alpha;
+ (UIColor *)colorWithRed:(CGFloat)red green:(CGFloat)green blue:(CGFloat)blue alpha:(CGFloat)alpha;
+ (UIColor *)colorWithCGColor:(CGColorRef)cgColor;
+ (UIColor *)colorWithPatternImage:(UIImage *)image;
+ (UIColor *)colorWithCIColor:(CIColor *)ciColor __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

// Initializers for creating non-autoreleased colors
- (UIColor *)initWithWhite:(CGFloat)white alpha:(CGFloat)alpha;
- (UIColor *)initWithHue:(CGFloat)hue saturation:(CGFloat)saturation brightness:(CGFloat)brightness alpha:(CGFloat)alpha;
- (UIColor *)initWithRed:(CGFloat)red green:(CGFloat)green blue:(CGFloat)blue alpha:(CGFloat)alpha;
- (UIColor *)initWithCGColor:(CGColorRef)cgColor;
- (UIColor *)initWithPatternImage:(UIImage*)image;
- (UIColor *)initWithCIColor:(CIColor *)ciColor __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

// Some convenience methods to create colors.  These colors will be as calibrated as possible.
// These colors are cached.
+ (UIColor *)blackColor;      // 0.0 white 
+ (UIColor *)darkGrayColor;   // 0.333 white 
+ (UIColor *)lightGrayColor;  // 0.667 white 
+ (UIColor *)whiteColor;      // 1.0 white 
+ (UIColor *)grayColor;       // 0.5 white 
+ (UIColor *)redColor;        // 1.0, 0.0, 0.0 RGB 
+ (UIColor *)greenColor;      // 0.0, 1.0, 0.0 RGB 
+ (UIColor *)blueColor;       // 0.0, 0.0, 1.0 RGB 
+ (UIColor *)cyanColor;       // 0.0, 1.0, 1.0 RGB 
+ (UIColor *)yellowColor;     // 1.0, 1.0, 0.0 RGB 
+ (UIColor *)magentaColor;    // 1.0, 0.0, 1.0 RGB 
+ (UIColor *)orangeColor;     // 1.0, 0.5, 0.0 RGB 
+ (UIColor *)purpleColor;     // 0.5, 0.0, 0.5 RGB 
+ (UIColor *)brownColor;      // 0.6, 0.4, 0.2 RGB 
+ (UIColor *)clearColor;      // 0.0 white, 0.0 alpha 

// Set the color: Sets the fill and stroke colors in the current drawing context. Should be implemented by subclassers.
- (void)set;

// Set the fill or stroke colors individually. These should be implemented by subclassers.
- (void)setFill;
- (void)setStroke;

// Convenience methods for getting components.
// If the receiver is of a compatible color space, any non-NULL parameters are populated and 'YES' is returned. Otherwise, the parameters are left unchanged and 'NO' is returned.
- (BOOL)getWhite:(CGFloat *)white alpha:(CGFloat *)alpha;
- (BOOL)getHue:(CGFloat *)hue saturation:(CGFloat *)saturation brightness:(CGFloat *)brightness alpha:(CGFloat *)alpha;
- (BOOL)getRed:(CGFloat *)red green:(CGFloat *)green blue:(CGFloat *)blue alpha:(CGFloat *)alpha;

// Returns a color in the same color space as the receiver with the specified alpha component.
- (UIColor *)colorWithAlphaComponent:(CGFloat)alpha;

// Access the underlying CGColor or CIColor.
@property(nonatomic,readonly) CGColorRef CGColor;
@property(nonatomic,readonly) CIColor   *CIColor;

@end

@interface CIColor(UIKitAdditions)

- (id)initWithColor:(UIColor *)color __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

@end
