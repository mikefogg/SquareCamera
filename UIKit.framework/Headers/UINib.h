//
//  UINib.h
//  UIKit
//
//  Copyright (c) 2008-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

UIKIT_CLASS_AVAILABLE(4_0) @interface UINib : NSObject {
  @private
    id storage;
}

// If the bundle parameter is nil, the main bundle is used.
// Releases resources in response to memory pressure (e.g. memory warning), reloading from the bundle when necessary.
+ (UINib *)nibWithNibName:(NSString *)name bundle:(NSBundle *)bundleOrNil;

// If the bundle parameter is nil, the main bundle is used.
+ (UINib *)nibWithData:(NSData *)data bundle:(NSBundle *)bundleOrNil;

// Returns an array containing the top-level objects from the NIB.
// The owner and options parameters may both be nil.
// If the owner parameter is nil, connections to File's Owner are not permitted.
// Options are identical to the options specified with -[NSBundle loadNibNamed:owner:options:]
- (NSArray *)instantiateWithOwner:(id)ownerOrNil options:(NSDictionary *)optionsOrNil;
@end
