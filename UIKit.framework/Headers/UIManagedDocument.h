//
//  UIManagedDocument.h
//  UIKit
//
//  Copyright (c) 2011, Apple Inc.
//  All rights reserved.
//

#import <UIKit/UIDocument.h>

@class NSManagedObjectModel;
@class NSManagedObjectContext;
@class NSPersistentStoreCoordinator;

UIKIT_CLASS_AVAILABLE(5_0) @interface UIManagedDocument : UIDocument {
@private
    NSManagedObjectContext *_managedObjectContext;
    NSPersistentStoreCoordinator *_persistentStoreCoordinator;
    NSManagedObjectModel *_managedObjectModel;
    NSDictionary *_documentMetadata;
    struct __mdocFlags {
	unsigned int shouldWriteAdditionalContent:1;
	unsigned int _reserved:31;
    } _mdocFlags;

}

/* The name for the persistent store file inside the document's file wrapper.  When working with the Core Data APIs, this path component is appended to the document URL provided by the UIDocument APIs.  The default name is @"documentpersistentstore.db"
 */
+ (NSString *)persistentStoreName;

/* Persistent documents always have a managed object context and a persistent store coordinator through that context.  The managed object context is required to be initialized with the concurrency type NSMainQueueConcurrencyType and it must have a parent context initialized with the concurrency type NSPrivateQueueConcurrencyType.
 */
@property (nonatomic, retain, readonly) NSManagedObjectContext *managedObjectContext;

/* Persistent documents always have a managed object model.  The default model is the union of all models in the main bundle.
 */
@property (nonatomic, retain, readonly) NSManagedObjectModel* managedObjectModel;

/* Optionally provide a collection of store options to be passed when configuring the persistent store
 */
@property (nonatomic, copy) NSDictionary *persistentStoreOptions;

/* Optionally specify a model configuration name to be passed when configuring the persistent store
 */
@property (nonatomic, copy) NSString *modelConfiguration;

/* Customize the loading or creation of a persistent store to the coordinator.
 */
- (BOOL)configurePersistentStoreCoordinatorForURL:(NSURL *)storeURL ofType:(NSString *)fileType modelConfiguration:(NSString *)configuration storeOptions:(NSDictionary *)storeOptions error:(NSError **)error;

/* Returns the Core Data store type string for the given document fileType. The default returns NSSQLiteStoreType. See NSPersistentStoreCoordinator.h for store type information. 
 */
- (NSString *)persistentStoreTypeForFileType:(NSString *)fileType;

/* An optional call out by readFromURL:error: to handle non-Core Data content in the document's file wrapper.  It is not necessary to call super.
 */
- (BOOL)readAdditionalContentFromURL:(NSURL *)absoluteURL error:(NSError **)error;

/* An optional call out by contentsForType:error: to handle non-Core Data content in the document's file wrapper.  The returned object will be passed to -writeAdditionalContent: It is not necessary to call super.
 */
- (id)additionalContentForURL:(NSURL *)absoluteURL error:(NSError **)error;

/* An optional call out by writeContents:andAttributes:safelyToURL:forSaveOperation:error: to handle non-Core Data content in the document's file wrapper.  The Core Data content is handled by the primary UIDocument -writeContents:andAttributes:safelyToURL:forSaveOperation:error: method.  It is not necessary to call super.
 */
- (BOOL)writeAdditionalContent:(id)content toURL:(NSURL *)absoluteURL originalContentsURL:(NSURL *)absoluteOriginalContentsURL error:(NSError **)error;

@end
