//
//  UIPasteboard.h
//  UIKit
//
//  Copyright (c) 2008-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

UIKIT_EXTERN NSString *const UIPasteboardNameGeneral;
UIKIT_EXTERN NSString *const UIPasteboardNameFind;

@class UIColor, UIImage;

UIKIT_CLASS_AVAILABLE(3_0) @interface UIPasteboard : NSObject { 
  @private
    NSString *_name;
}

+ (UIPasteboard *)generalPasteboard;
+ (UIPasteboard *)pasteboardWithName:(NSString *)pasteboardName create:(BOOL)create;
+ (UIPasteboard *)pasteboardWithUniqueName;

@property(readonly,nonatomic) NSString *name;

+ (void)removePasteboardWithName:(NSString *)pasteboardName;

@property(getter=isPersistent,nonatomic) BOOL persistent;
@property(readonly,nonatomic) NSInteger changeCount;

// First item

- (NSArray *)pasteboardTypes;
- (BOOL)containsPasteboardTypes:(NSArray *)pasteboardTypes;
- (NSData *)dataForPasteboardType:(NSString *)pasteboardType;

- (id)valueForPasteboardType:(NSString *)pasteboardType;

- (void)setValue:(id)value forPasteboardType:(NSString *)pasteboardType;
- (void)setData:(NSData *)data forPasteboardType:(NSString *)pasteboardType;

// Multiple items

@property(readonly,nonatomic) NSInteger numberOfItems;
- (NSArray *)pasteboardTypesForItemSet:(NSIndexSet*)itemSet;		
- (BOOL)containsPasteboardTypes:(NSArray *)pasteboardTypes inItemSet:(NSIndexSet *)itemSet;	
- (NSIndexSet *)itemSetWithPasteboardTypes:(NSArray *)pasteboardTypes;
- (NSArray *)valuesForPasteboardType:(NSString *)pasteboardType inItemSet:(NSIndexSet *)itemSet;	
- (NSArray *)dataForPasteboardType:(NSString *)pasteboardType inItemSet:(NSIndexSet *)itemSet;

// Direct access

@property(nonatomic,copy) NSArray *items;
- (void)addItems:(NSArray *)items;

@end

// Notification

UIKIT_EXTERN NSString *const UIPasteboardChangedNotification;
UIKIT_EXTERN NSString *const    UIPasteboardChangedTypesAddedKey;
UIKIT_EXTERN NSString *const    UIPasteboardChangedTypesRemovedKey;

UIKIT_EXTERN NSString *const UIPasteboardRemovedNotification;

// Extensions

UIKIT_EXTERN NSArray *UIPasteboardTypeListString;
UIKIT_EXTERN NSArray *UIPasteboardTypeListURL;
UIKIT_EXTERN NSArray *UIPasteboardTypeListImage;
UIKIT_EXTERN NSArray *UIPasteboardTypeListColor;

@interface UIPasteboard(UIPasteboardDataExtensions)

@property(nonatomic,copy) NSString *string;
@property(nonatomic,copy) NSArray *strings;

@property(nonatomic,copy) NSURL *URL;
@property(nonatomic,copy) NSArray *URLs;

@property(nonatomic,copy) UIImage *image;
@property(nonatomic,copy) NSArray *images;

@property(nonatomic,copy) UIColor *color;
@property(nonatomic,copy) NSArray *colors;

@end
