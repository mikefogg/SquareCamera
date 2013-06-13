//
//  UIScreenMode.h
//  UIKit
//
//  Copyright (c) 2009-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <CoreGraphics/CoreGraphics.h>

UIKIT_CLASS_AVAILABLE(3_2) @interface UIScreenMode : NSObject {
  @private
    id _mode;
}

@property(readonly,nonatomic) CGSize  size;             // The width and height in pixels
@property(readonly,nonatomic) CGFloat pixelAspectRatio; // The aspect ratio of a single pixel. The ratio is defined as X/Y.

@end
