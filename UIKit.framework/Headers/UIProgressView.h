//
//  UIProgressView.h
//  UIKit
//
//  Copyright (c) 2005-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>

@class UIImageView;

typedef enum {
    UIProgressViewStyleDefault,     // normal progress bar
    UIProgressViewStyleBar,         // for use in a toolbar
} UIProgressViewStyle;

UIKIT_CLASS_AVAILABLE(2_0) @interface UIProgressView : UIView <NSCoding>
{ 
  @private
    UIProgressViewStyle _progressViewStyle;
    float               _progress;
    UIBarStyle          _barStyle;
    UIColor*            _progressTintColor;
    UIColor*            _trackTintColor;
    UIImageView*        _trackView;
    UIImageView*        _progressViews[3];
    BOOL                _isAnimating;
}

- (id)initWithProgressViewStyle:(UIProgressViewStyle)style; // sets the view height according to the style

@property(nonatomic) UIProgressViewStyle progressViewStyle; // default is UIProgressViewStyleDefault
@property(nonatomic) float progress;                        // 0.0 .. 1.0, default is 0.0. values outside are pinned.
@property(nonatomic, retain) UIColor* progressTintColor     __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;
@property(nonatomic, retain) UIColor* trackTintColor     __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;
@property(nonatomic, retain) UIImage* progressImage __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;
@property(nonatomic, retain) UIImage* trackImage __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;

- (void)setProgress:(float)progress animated:(BOOL)animated __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

@end
