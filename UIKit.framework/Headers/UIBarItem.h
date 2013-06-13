//
//  UIBarItem.h
//  UIKit
//
//  Copyright (c) 2008-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIAppearance.h>
#import <UIKit/UIControl.h>

@class UIImage;

UIKIT_CLASS_AVAILABLE(2_0) @interface UIBarItem : NSObject <UIAppearance> {
  @private
}

@property(nonatomic,getter=isEnabled) BOOL         enabled;      // default is YES
@property(nonatomic,copy)             NSString    *title;        // default is nil
@property(nonatomic,retain)           UIImage     *image;        // default is nil
@property(nonatomic,retain)           UIImage     *landscapeImagePhone __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0); // default is nil
@property(nonatomic)                  UIEdgeInsets imageInsets;  // default is UIEdgeInsetsZero
@property(nonatomic)                  UIEdgeInsets landscapeImagePhoneInsets __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);  // default is UIEdgeInsetsZero. These insets apply only when the landscapeImagePhone property is set.
@property(nonatomic)                  NSInteger    tag;          // default is 0

/* You may specify the font, text color, text shadow color, and text shadow offset for the title in the text attributes dictionary, using the keys found in UIStringDrawing.h.
 */
- (void)setTitleTextAttributes:(NSDictionary *)attributes forState:(UIControlState)state __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;
- (NSDictionary *)titleTextAttributesForState:(UIControlState)state __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;

@end
