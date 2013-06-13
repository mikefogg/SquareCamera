//
//  UIPrintPaper.h
//  UIKit
//
//  Copyright 2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>

UIKIT_CLASS_AVAILABLE(4_2) @interface UIPrintPaper : NSObject {
  @private
    int _paperOrientation;
    id  _internal;
}

+ (UIPrintPaper *)bestPaperForPageSize:(CGSize)contentSize withPapersFromArray:(NSArray *)paperList; // for use by delegate. pass in list

@property(readonly) CGSize paperSize;
@property(readonly) CGRect printableRect;

@end

//_____________________________________________

@interface UIPrintPaper(Deprecated_Nonfunctional)
- (CGRect)printRect;
@end
