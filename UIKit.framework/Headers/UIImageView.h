//
//  UIImageView.h
//  UIKit
//
//  Copyright (c) 2006-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>

@class UIImage;

UIKIT_CLASS_AVAILABLE(2_0) @interface UIImageView : UIView {
  @private
    id _storage;
}

- (id)initWithImage:(UIImage *)image;
- (id)initWithImage:(UIImage *)image highlightedImage:(UIImage *)highlightedImage __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

@property(nonatomic,retain) UIImage *image;                                                     // default is nil
@property(nonatomic,retain) UIImage *highlightedImage __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);      // default is nil
@property(nonatomic,getter=isUserInteractionEnabled) BOOL userInteractionEnabled;               // default is NO

@property(nonatomic,getter=isHighlighted) BOOL highlighted __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0); // default is NO

// these allow a set of images to be animated. the array may contain multiple copies of the same

@property(nonatomic,copy) NSArray *animationImages;            // The array must contain UIImages. Setting hides the single image. default is nil
@property(nonatomic,copy) NSArray *highlightedAnimationImages __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);            // The array must contain UIImages. Setting hides the single image. default is nil

@property(nonatomic) NSTimeInterval animationDuration;         // for one cycle of images. default is number of images * 1/30th of a second (i.e. 30 fps)
@property(nonatomic) NSInteger      animationRepeatCount;      // 0 means infinite (default is 0)

- (void)startAnimating;
- (void)stopAnimating;
- (BOOL)isAnimating;

@end
