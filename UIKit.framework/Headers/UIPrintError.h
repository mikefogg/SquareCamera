//
//  UIPrintError.h
//  UIKit
//
//  Copyright 2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

UIKIT_EXTERN NSString *const UIPrintErrorDomain;

enum {
    UIPrintingNotAvailableError = 1,  // cannot print at this time
    UIPrintNoContentError,            // empty list of files or images
    UIPrintUnknownImageFormatError,   // unrecognized image format
    UIPrintJobFailedError,            // internal error with print job
};
