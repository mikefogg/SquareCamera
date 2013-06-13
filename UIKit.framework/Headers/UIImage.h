//
//  UIImage.h
//  UIKit
//
//  Copyright (c) 2005-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <CoreImage/CoreImage.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIColor.h>
#import <UIKit/UIGeometry.h>

typedef enum {
    UIImageOrientationUp,            // default orientation
    UIImageOrientationDown,          // 180 deg rotation
    UIImageOrientationLeft,          // 90 deg CCW
    UIImageOrientationRight,         // 90 deg CW
    UIImageOrientationUpMirrored,    // as above but image mirrored along other axis. horizontal flip
    UIImageOrientationDownMirrored,  // horizontal flip
    UIImageOrientationLeftMirrored,  // vertical flip
    UIImageOrientationRightMirrored, // vertical flip
} UIImageOrientation;

UIKIT_CLASS_AVAILABLE(2_0) @interface UIImage : NSObject <NSCoding> {
  @package
    CFTypeRef _imageRef;
    CGFloat   _scale;
    struct {
	unsigned int named:1;
	unsigned int imageOrientation:3;
	unsigned int cached:1;
	unsigned int hasBeenCached:1;
	unsigned int hasPattern:1;
	unsigned int isCIImage:1;
    } _imageFlags;
}

+ (UIImage *)imageNamed:(NSString *)name;      // load from main bundle

+ (UIImage *)imageWithContentsOfFile:(NSString *)path;
+ (UIImage *)imageWithData:(NSData *)data;
+ (UIImage *)imageWithCGImage:(CGImageRef)cgImage;
+ (UIImage *)imageWithCGImage:(CGImageRef)cgImage scale:(CGFloat)scale orientation:(UIImageOrientation)orientation __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
+ (UIImage *)imageWithCIImage:(CIImage *)ciImage __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

- (id)initWithContentsOfFile:(NSString *)path;
- (id)initWithData:(NSData *)data;
- (id)initWithCGImage:(CGImageRef)cgImage;
- (id)initWithCGImage:(CGImageRef)cgImage scale:(CGFloat)scale orientation:(UIImageOrientation)orientation __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
- (id)initWithCIImage:(CIImage *)ciImage __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

@property(nonatomic,readonly) CGSize             size;             // reflects orientation setting. size is in pixels
@property(nonatomic,readonly) CGImageRef         CGImage;          // returns underlying CGImageRef or nil if CIImage based
@property(nonatomic,readonly) CIImage           *CIImage __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0); // returns underlying CIImage or nil if CGImageRef based
@property(nonatomic,readonly) UIImageOrientation imageOrientation; // this will affect how the image is composited
@property(nonatomic,readonly) CGFloat            scale __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

// animated images. When set as UIImageView.image, animation will play in an infinite loop until removed. Drawing will render the first image

+ (UIImage *)animatedImageNamed:(NSString *)name duration:(NSTimeInterval)duration __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);  // read sequnce of files with suffix starting at 0 or 1
+ (UIImage *)animatedResizableImageNamed:(NSString *)name capInsets:(UIEdgeInsets)capInsets duration:(NSTimeInterval)duration __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0); // squence of files
+ (UIImage *)animatedImageWithImages:(NSArray *)images duration:(NSTimeInterval)duration __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

@property(nonatomic,readonly) NSArray       *images   __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0); // default is nil for non-animated images
@property(nonatomic,readonly) NSTimeInterval duration __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0); // total duration for all frames. default is 0 for non-animated images

// the these draw the image 'right side up' in the usual coordinate system with 'point' being the top-left.

- (void)drawAtPoint:(CGPoint)point;                                                        // mode = kCGBlendModeNormal, alpha = 1.0
- (void)drawAtPoint:(CGPoint)point blendMode:(CGBlendMode)blendMode alpha:(CGFloat)alpha;
- (void)drawInRect:(CGRect)rect;                                                           // mode = kCGBlendModeNormal, alpha = 1.0
- (void)drawInRect:(CGRect)rect blendMode:(CGBlendMode)blendMode alpha:(CGFloat)alpha;

- (void)drawAsPatternInRect:(CGRect)rect; // draws the image as a CGPattern

// create a resizable version of this image. the interior is tiled when drawn.
- (UIImage *)resizableImageWithCapInsets:(UIEdgeInsets)capInsets __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
@property(nonatomic,readonly) UIEdgeInsets capInsets               __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);   // default is UIEdgeInsetsZero for non resizable images

@end

@interface UIImage(UIImageDeprecated)

// use resizableImageWithCapInsets: and capInsets.

- (UIImage *)stretchableImageWithLeftCapWidth:(NSInteger)leftCapWidth topCapHeight:(NSInteger)topCapHeight;
@property(nonatomic,readonly) NSInteger leftCapWidth;   // default is 0. if non-zero, horiz. stretchable. right cap is calculated as width - leftCapWidth - 1
@property(nonatomic,readonly) NSInteger topCapHeight;   // default is 0. if non-zero, vert. stretchable. bottom cap is calculated as height - topCapWidth - 1

@end


@interface CIImage(UIKitAdditions)

- (id)initWithImage:(UIImage *)image __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
- (id)initWithImage:(UIImage *)image options:(NSDictionary *)options __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

@end

UIKIT_EXTERN NSData *UIImagePNGRepresentation(UIImage *image);                               // return image as PNG. May return nil if image has no CGImageRef or invalid bitmap format
UIKIT_EXTERN NSData *UIImageJPEGRepresentation(UIImage *image, CGFloat compressionQuality);  // return image as JPEG. May return nil if image has no CGImageRef or invalid bitmap format. compression is 0(most)..1(least)
