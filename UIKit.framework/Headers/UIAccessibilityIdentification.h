//
//  UIAccessibilityIdentification.h
//  UIKit
//
//  Copyright 2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import <UIKit/UIImage.h>

@protocol UIAccessibilityIdentification <NSObject>
@required

/*
 A string that identifies the user interface element.
 default == nil
*/
@property(nonatomic, copy) NSString *accessibilityIdentifier __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

@end

@interface UIView (UIAccessibility) <UIAccessibilityIdentification>
@end

/*
 Defaults to the filename of the image, if available.
 The default identifier for a UIImageView will be the identifier of its UIImage.
 */
@interface UIImage (UIAccessibility) <UIAccessibilityIdentification>
@end
