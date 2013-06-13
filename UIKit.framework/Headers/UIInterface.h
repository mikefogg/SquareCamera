//
//  UIInterface.h
//  UIKit
//
//  Copyright (c) 2005-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIColor.h>
#import <UIKit/UIFont.h>

// for UINavigationBar and UIToolBar

typedef enum {
    UIBarStyleDefault          = 0,
    UIBarStyleBlack            = 1,
    
    UIBarStyleBlackOpaque      = 1, // Deprecated. Use UIBarStyleBlack
    UIBarStyleBlackTranslucent = 2, // Deprecated. Use UIBarStyleBlack and set the translucent property to YES
} UIBarStyle;

// System colors

@interface UIColor (UIColorSystemColors)
+ (UIColor *)lightTextColor;                // for a dark background
+ (UIColor *)darkTextColor;                 // for a light background
+ (UIColor *)groupTableViewBackgroundColor;
+ (UIColor *)viewFlipsideBackgroundColor;
+ (UIColor *)scrollViewTexturedBackgroundColor __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_3_2);
+ (UIColor *)underPageBackgroundColor __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);
@end

// System fonts

@interface UIFont (UIFontSystemFonts)
+ (CGFloat)labelFontSize;
+ (CGFloat)buttonFontSize;
+ (CGFloat)smallSystemFontSize;
+ (CGFloat)systemFontSize;
@end
