//
//  UIActivityIndicator.h
//  UIKit
//
//  Copyright (c) 2005-2011, Apple Inc. All rights reserved.
//

#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>

typedef enum {
    UIActivityIndicatorViewStyleWhiteLarge,
    UIActivityIndicatorViewStyleWhite,
    UIActivityIndicatorViewStyleGray,
} UIActivityIndicatorViewStyle;

UIKIT_CLASS_AVAILABLE(2_0) @interface UIActivityIndicatorView : UIView <NSCoding>
{ 
  @package
    CFTimeInterval               _duration;
    BOOL                         _animating;
    UIActivityIndicatorViewStyle _activityIndicatorViewStyle;
    UIActivityIndicatorViewStyle _actualActivityIndicatorViewStyle;
    BOOL                         _hidesWhenStopped;
}

- (id)initWithActivityIndicatorStyle:(UIActivityIndicatorViewStyle)style;     // sizes the view according to the style

@property(nonatomic) UIActivityIndicatorViewStyle activityIndicatorViewStyle; // default is UIActivityIndicatorViewStyleWhite
@property(nonatomic) BOOL                         hidesWhenStopped;           // default is YES. calls -setHidden when animating gets set to NO

@property (readwrite, nonatomic, retain) UIColor *color __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;

- (void)startAnimating;
- (void)stopAnimating;
- (BOOL)isAnimating;
@end
