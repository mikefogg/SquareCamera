//
//  UIDocument.h
//  UIKit
//
//  Copyright (c) 1997-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

enum {
    UIDocumentChangeDone,
    UIDocumentChangeUndone,
    UIDocumentChangeRedone,
    UIDocumentChangeCleared
};
typedef NSInteger UIDocumentChangeKind;

enum {
    UIDocumentSaveForCreating,
    UIDocumentSaveForOverwriting
};
typedef NSInteger UIDocumentSaveOperation;

enum {
    UIDocumentStateNormal          = 0,
    UIDocumentStateClosed          = 1 << 0, // The document has either not been successfully opened, or has been since closed. Document properties may not be valid.
    UIDocumentStateInConflict      = 1 << 1, // Conflicts exist for the document's fileURL. They can be accessed through +[NSFileVersion otherVersionsOfItemAtURL:].
    UIDocumentStateSavingError     = 1 << 2, // An error has occurred that prevents the document from saving.
    UIDocumentStateEditingDisabled = 1 << 3  // Set before calling -disableEditing. The document is is busy and it is not currently safe to allow user edits. -enableEditing will be called when it becomes safe to edit again.
};
typedef NSInteger UIDocumentState;

UIKIT_EXTERN NSString *const UIDocumentStateChangedNotification __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

UIKIT_CLASS_AVAILABLE(5_0) @interface UIDocument : NSObject <NSFilePresenter> {
    @private
    NSURL *_fileURL;
    NSString *_fileType;
    NSString* _localizedName;
    NSUndoManager *_undoManager;
    NSDate *_fileModificationDate;
    dispatch_queue_t _fileAccessQueue;
    dispatch_queue_t _openingQueue;
    dispatch_semaphore_t _fileAccessSemaphore;
    NSOperationQueue *_filePresenterQueue;
    id _differenceDueToRecentChanges;
    id _differenceSincePreservingPreviousVersion;
    id _differenceSinceSaving;
    NSTimer *_autosavingTimer;
    CFAbsoluteTime _lastSaveTime;
    NSUInteger _fileContentsPreservationReason;
    CFAbsoluteTime _lastPreservationTime;
    id _versionWithoutRecentChanges;
    NSMutableArray *_versions;
    void *_conflictObserver;
    NSLock* _documentPropertyLock;
    id _alertPresenter;
    struct __docFlags {
	unsigned int inClose:1;
        unsigned int isOpen:1;
        unsigned int inOpen:1;
        unsigned int isAutosavingBecauseOfTimer:1;
        unsigned int versionWithoutRecentChangesIsNotLastOpened:1;
        unsigned int ignoreUndoAndRedoNotifications:1;
        unsigned int editingDisabled:1;
        unsigned int isRegisteredAsFilePresenter:1;
        unsigned int movingFile:1;
        unsigned int savingError:1;
        unsigned int inConflict:1;
    } _docFlags;
}

#pragma mark *** Initialization ***

// The designated initializer. Passing an empty URL will cause this method to throw an NSInvalidArgumentException.
- (id)initWithFileURL:(NSURL *)url;

#pragma mark *** Attributes Applicable to Every Kind of Document ***
// UIKit may call these methods on background threads, so subclasses that override them must have thread safe implementations.
// These values will be set by UIKit before the completion handlers to the opening, reverting, and saving methods are called.
// Clients that wish to access these properties outside of an open, save, or revert completion handler and wait for any pending file operations should wrap the accesses in -performAsynchronousFileAccessUsingBlock:

@property(readonly) NSURL *fileURL;
@property(readonly, copy) NSString *localizedName;  // The default implementation derives the name from the URL. Subclasses may override to provide a custom name for presentation to the user, such as in error strings.
@property(readonly, copy) NSString *fileType;       // The file's UTI. Derived from the fileURL by default.
@property(copy) NSDate *fileModificationDate;       // The last known modification date of the document's on-disk representation. Updated by openWithCompletionHandler:, revertToContentsOfURL:, and saveToURL: and will return nil if none of these has completed successfully at least once.

@property(readonly) UIDocumentState documentState;

#pragma mark *** Opening and Closing ***

// Subclassing this method without calling super should be avoided. Subclassers who don't call super must use NSFileCoordinator for coordinated reading themselves.
// Open the document located by the fileURL.  This will call readFromURL:error: on a background queue and then invoke the completionHandler on the current dispatch queue when openWithCompletionHandler: is invoked.
- (void)openWithCompletionHandler:(void (^)(BOOL success))completionHandler;

// Close the document. The default implementation calls [self autosaveWithCompletionHandler:completionHandler] which will save if [self hasUnsavedChanges] returns YES.
- (void)closeWithCompletionHandler:(void (^)(BOOL success))completionHandler;

#pragma mark *** Simple Reading and Writing ***

// These methods will be all most apps need to access files. Applications with complex reading and writing needs should see the Advanced Reading and Writing section below.

// Typical subclasses will implement this method to do reading. UIKit will pass NSData typed contents for flat files and NSFileWrapper typed contents for file packages.
// typeName is the UTI of the loaded file.
- (BOOL)loadFromContents:(id)contents ofType:(NSString *)typeName error:(NSError **)outError;

// Typical subclasses will implement this method and return an NSFileWrapper or NSData encapsulating a snapshot of their data to be written to disk during saving.
// Subclasses that return something other than a valid NSFileWrapper or NSData instance, or don't override this method must override one of the writing methods in the Advanced Saving section to write data to disk.
- (id)contentsForType:(NSString *)typeName error:(NSError **)outError;

#pragma mark *** Disabling and Enabling Editing
// Subclasses should override these methods so that they do not allow the user to edit the document between calls to -disableEditing and -enableEditing.
// UIKit will call -disableEditing when it is unsafe to make changes to the document, such as during a close or revert, and call -enableEditing when it is safe again.
// The default implementation of these methods do nothing.

- (void)disableEditing;
- (void)enableEditing;

#pragma mark *** Change Management ***

// The document's undo manager. Setting the undo manager also registers the document as an observer of various NSUndoManager notifications so that -updateChangeCount: is invoked as undoable changes are made to the document. 
// Asking for the undo manager creates a default one if one is not already set.
// Typically, when a subclass sets the undoManager, it does not need to override -hasUnsavedChanges or call updateChangeCount: manually.
@property(retain) NSUndoManager *undoManager;

// Subclasses should generally not need to override this. Instead they should use the undoManager or call -updateChangeCount: every time they get a change and UIKit will calculate -hasUnsavedChanges automatically.
// The default implementation of -autosaveWithCompletionHandler: initiates a save if [self hasUnsavedChanges] is YES.
- (BOOL)hasUnsavedChanges;

// Record the fact that a change affecting the value returned by -hasUnsavedChanges has occurred. Subclasses should not need to call this if they set the undoManager.
- (void)updateChangeCount:(UIDocumentChangeKind)change; 

// Change count tokens can be used to encapsulate the record of document changes being made in a particular save.
// Subclasses that don't register changes via -updateChangeCount: or by using the undoManager should implement these methods to determine if the model has new unsaved changes at the end of a save.
// -changeCountTokenForSaveOperation: is called at the beginning of a save operation and the token returned is passed to -updateChangeCountWithToken:forSaveOperation: at the conclusion of a save.
// The default implementation of updateChangeCountWithToken:forSaveOperation: calls [self updateChangeCount:UIDocumentChangeCleared] if no changes are made during the save.
- (id)changeCountTokenForSaveOperation:(UIDocumentSaveOperation)saveOperation; 
- (void)updateChangeCountWithToken:(id)changeCountToken forSaveOperation:(UIDocumentSaveOperation)saveOperation; 

#pragma mark *** Advanced Reading and Writing ***

// Subclassing this method without calling super should be avoided. Subclassers  who don't call super must use NSFileCoordinator for coordinated writing themselves.
// The default implementation of this method invokes [self contentsOfType:error:] synchronously on the calling queue, and then invokes [self writeContents:andAttributes:safelyToURL:ForSaveOperation:completionHandler:] on a background queue.
// The completion handler is executed on the calling queue.
- (void)saveToURL:(NSURL *)url forSaveOperation:(UIDocumentSaveOperation)saveOperation completionHandler:(void (^)(BOOL success))completionHandler;

// Clients should not need to call this method directly. It exists as an override point for subclasses that want to do special things with autosaving.
// The default implementation of this method invokes [self hasUnsavedChanges] and, if that returns YES, invokes [self saveToURL:[self fileURL] forSaveOperation:UIDocumentSaveForOverwriting completionHandler:completionHandler].
- (void)autosaveWithCompletionHandler:(void (^)(BOOL success))completionHandler;

- (NSString *)savingFileType; // The default implementation returns the current file type. saveToURL: will save to an extension based on this type so subclasses can override this to allow moving the document to a new type.
- (NSString *)fileNameExtensionForType:(NSString *)typeName saveOperation:(UIDocumentSaveOperation)saveOperation; // For a specified type, and a particular kind of save operation, return a file name extension that can be appended to a base file name.

// This method is responsible for doing document writing in a way that minimizes the danger of leaving the disk to which writing is being done in an inconsistent state in the event of an application crash, system crash, hardware failure, power outage, etc.
// Because it does several different things, and because the things are likely to change in future releases of iOS, it's probably not a good idea to override this method without invoking super.
- (BOOL)writeContents:(id)contents andAttributes:(NSDictionary *)additionalFileAttributes safelyToURL:(NSURL *)url forSaveOperation:(UIDocumentSaveOperation)saveOperation error:(NSError **)outError;

// Called by -writeContents:andAttributes:safelyToURL:forSaveOperation:error: to write the data to disk. Override point for subclasses that need access to the on-disk representation of the document while saving.
- (BOOL)writeContents:(id)contents toURL:(NSURL *)url forSaveOperation:(UIDocumentSaveOperation)saveOperation originalContentsURL:(NSURL *)originalContentsURL error:(NSError **)outError;

// Called by -saveToURL: before executing asynchronous writing to get a dictionary of attributes understood by NSFileManager for writing to the file.
// The attributes are passed to -writeContents:andAttributes:safelyToURL:forSaveOperation:error: for writing to the file
- (NSDictionary *)fileAttributesToWriteToURL:(NSURL *)url forSaveOperation:(UIDocumentSaveOperation)saveOperation error:(NSError **)outError;

// Direct calls to this method should not be necessary for typical subclasses where the entire file is read during opening.
// If direct calls are used, the client must use NSFileCoordinator API to ensure coordinated reads and performAsynchronousFileAccessUsingBlock: to serialize with any active writes.
// Default implementation calls [self loadFromContents:ofType:error:] on the queue that called openWithCompletionHandler:, or the main queue if called directly, with NSData or NSFileWrapper contents.
- (BOOL)readFromURL:(NSURL *)url error:(NSError **)outError;

#pragma mark *** File Access Serialization ***

// The default implementations of saveToURL: and openWithCompletionHandler: both use this to serialize file access. Direct calls to reading and writing methods should use this method to serialize file access on a background queue.
- (void)performAsynchronousFileAccessUsingBlock:(void (^)(void))block;

#pragma mark *** Error Presentation ***
// These are advanced methods for dealing with errors in UIDocument.
// Most clients should not need to override or call them.
// Instead, they should respond to the UIDocumentStateChangedNotification to give the user the proper feedback when the document is in UIDocumentStateSavingError.

// Called by the default implementations of -openWithCompletionHandler: and -saveToURL:forSaveOperation:completionHandler:.
// Subclasses should call -handleError:userInteractionPermitted: with any errors that arise from direct calls to the advanced reading and writing methods that return NSErrors by indirection.
// Notes for overriding:
// 1. Subclasses that do not call super are responsible for calling -finishedHandlingError: when done with the error (i.e. when the app will not require any additional user feedback from the error).
// 2. Subclasses that do not call super are also responsible for implementing -userInteractionNoLongerPermittedForError: to wrap up error handling immediately when required.
// 3. If the userInteractionPermitted flag is NO, you should immediately handle the error and call [self finishedHandlingError:] within the context of -handleError:userInteractionPermitted:
- (void)handleError:(NSError *)error userInteractionPermitted:(BOOL)userInteractionPermitted;

// Called when handling of an error (including any user interaction) is complete.
// Subclasses only need to call this method if they override -handleError:userInteractionPermitted: and do not call super.
// If overridden, subclasses must call super
- (void)finishedHandlingError:(NSError *)error recovered:(BOOL)recovered;

// UIKit calls this method when it is no longer safe to proceed without immediately handling the error, such as when the app is being suspended.
// Subclasses must immediately wrap up error handling (including dismissing any interactive UI) and call [self finishedHandlingError:] before returning.
// It is only necessary to override this method if you override -handleError:userInteractionPermitted: without calling super
- (void)userInteractionNoLongerPermittedForError:(NSError *)error;

#pragma mark *** Reverting ***

// Discard all unsaved document modifications and replace the document's contents by reading a file or file package located by a URL.
// Default implementation calls [self disableEditing] in the beginning and [self enableEditing] on completion to indicate that the document should not accept changes from the user while this is happening.
// The default implementation also calls [self openWithCompletionHandler:] after updating the fileURL.
// Subclasses that override this method must call super or use NSFileCoordinator directly to initiate a coordinated read.
- (void)revertToContentsOfURL:(NSURL *)url completionHandler:(void (^)(BOOL success))completionHandler;

@end
