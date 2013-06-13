//
//  UIStoryboardPopoverSegue.h
//  UIKit
//
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <UIKit/UIStoryboardSegue.h>

@class UIPopoverController;

UIKIT_CLASS_AVAILABLE(5_0) @interface UIStoryboardPopoverSegue : UIStoryboardSegue {
}

@property (nonatomic, retain, readonly) UIPopoverController *popoverController;

@end
