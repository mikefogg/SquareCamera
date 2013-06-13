//
//  UIReferenceLibraryViewController.h
//  UIKit
//
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <UIKit/UIViewController.h>

UIKIT_CLASS_AVAILABLE(5_0)
@interface UIReferenceLibraryViewController : UIViewController {}

/* Returns YES if any installed dictionary has a definition for the provided term.
 */
+ (BOOL)dictionaryHasDefinitionForTerm:(NSString *)term;

/* Initializes an instance of a UIReferenceLibraryViewController with the term provided.
 */
- (id)initWithTerm:(NSString *)term;

@end
