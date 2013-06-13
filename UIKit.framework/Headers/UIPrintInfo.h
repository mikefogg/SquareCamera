//
//  UIPrintInfo.h
//  UIKit
//
//  Copyright 2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>

typedef enum {
    UIPrintInfoOutputGeneral,     // B&W or color, normal quality output for mixed text, graphics, and images
    UIPrintInfoOutputPhoto,       // B&W or color, best quality output for images
    UIPrintInfoOutputGrayscale,   // B&W content only
} UIPrintInfoOutputType;

typedef enum {
    UIPrintInfoOrientationPortrait,
    UIPrintInfoOrientationLandscape,
} UIPrintInfoOrientation;

typedef enum {
    UIPrintInfoDuplexNone,
    UIPrintInfoDuplexLongEdge,       // flip back page along long edge (same orientation in portrait, flipped for landscape)
    UIPrintInfoDuplexShortEdge,      // flip back page along short edge (flipped orientation for portrait, same in landscape)
} UIPrintInfoDuplex;

UIKIT_CLASS_AVAILABLE(4_2) @interface UIPrintInfo : NSObject <NSCopying, NSCoding> { 
  @private
    NSString                *_printerID;
    NSString                *_jobName;
    UIPrintInfoOutputType    _outputType;
    UIPrintInfoOrientation   _orientation;
    UIPrintInfoDuplex        _duplex;
    NSInteger                _copies;
    BOOL                     _scaleUp;
}

+ (UIPrintInfo *)printInfo;
+ (UIPrintInfo *)printInfoWithDictionary:(NSDictionary *)dictionary;

- (NSDictionary *)dictionaryRepresentation;

@property(nonatomic,copy)     NSString                *printerID;         // default is nil. set after user selects printer
@property(nonatomic,copy)     NSString                *jobName;           // default is application name
@property(nonatomic)          UIPrintInfoOutputType    outputType;        // default is UIPrintInfoOutputGeneral
@property(nonatomic)          UIPrintInfoOrientation   orientation;       // default is UIPrintInfoOrientationPortrait
@property(nonatomic)          UIPrintInfoDuplex        duplex;            // default is based on document type (none for photo, long edge for other)

@end
