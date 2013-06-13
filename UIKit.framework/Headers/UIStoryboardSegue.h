//
//  UIStoryboardSegue.h
//  UIKit
//
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

@class UIViewController;

UIKIT_CLASS_AVAILABLE(5_0) @interface UIStoryboardSegue : NSObject

- (id)initWithIdentifier:(NSString *)identifier source:(UIViewController *)source destination:(UIViewController *)destination; // Designated initializer

@property (nonatomic, readonly) NSString *identifier;
@property (nonatomic, readonly) id sourceViewController;
@property (nonatomic, readonly) id destinationViewController;

- (void)perform;

@end
