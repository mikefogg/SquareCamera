//
//  UIGraphics.h
//  UIKit
//
//  Copyright (c) 2005-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>

@class UIImage;

UIKIT_EXTERN CGContextRef UIGraphicsGetCurrentContext(void);
UIKIT_EXTERN void UIGraphicsPushContext(CGContextRef context);
UIKIT_EXTERN void UIGraphicsPopContext(void);

UIKIT_EXTERN void UIRectFillUsingBlendMode(CGRect rect, CGBlendMode blendMode);
UIKIT_EXTERN void UIRectFill(CGRect rect);

UIKIT_EXTERN void UIRectFrameUsingBlendMode(CGRect rect, CGBlendMode blendMode);
UIKIT_EXTERN void UIRectFrame(CGRect rect);

UIKIT_EXTERN void UIRectClip(CGRect rect);

// UIImage context

UIKIT_EXTERN void     UIGraphicsBeginImageContext(CGSize size);
UIKIT_EXTERN void     UIGraphicsBeginImageContextWithOptions(CGSize size, BOOL opaque, CGFloat scale) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
UIKIT_EXTERN UIImage* UIGraphicsGetImageFromCurrentImageContext(void);
UIKIT_EXTERN void     UIGraphicsEndImageContext(void); 

// PDF context

UIKIT_EXTERN BOOL UIGraphicsBeginPDFContextToFile(NSString *path, CGRect bounds, NSDictionary *documentInfo) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2);
UIKIT_EXTERN void UIGraphicsBeginPDFContextToData(NSMutableData *data, CGRect bounds, NSDictionary *documentInfo) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2);
UIKIT_EXTERN void UIGraphicsEndPDFContext(void) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2);

UIKIT_EXTERN void UIGraphicsBeginPDFPage(void) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2);
UIKIT_EXTERN void UIGraphicsBeginPDFPageWithInfo(CGRect bounds, NSDictionary *pageInfo) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2);

UIKIT_EXTERN CGRect UIGraphicsGetPDFContextBounds(void) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2);

UIKIT_EXTERN void UIGraphicsSetPDFContextURLForRect(NSURL *url, CGRect rect) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2);
UIKIT_EXTERN void UIGraphicsAddPDFContextDestinationAtPoint(NSString *name, CGPoint point) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2);
UIKIT_EXTERN void UIGraphicsSetPDFContextDestinationForRect(NSString *name, CGRect rect) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2);
