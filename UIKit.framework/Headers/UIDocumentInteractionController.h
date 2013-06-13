//
//  UIDocumentInteractionController.h
//  UIKit
//
//  Copyright (c) 2009-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIViewController.h>

@protocol UIDocumentInteractionControllerDelegate;

@class UIImage, UIView, UIPopoverController;

UIKIT_CLASS_AVAILABLE(3_2) @interface UIDocumentInteractionController : NSObject <UIActionSheetDelegate> {
@private
    id <UIDocumentInteractionControllerDelegate> _delegate;
    id _previewItemProxy;
    NSArray     *_icons;
    id           _annotation;
    NSString    *_uniqueIdentifier;
    
    UIPopoverController *_popoverController;
    UIViewController    *_presentingViewController;

    id           _previewController;
    NSArray     *_gestureRecognizers;
    
    CGRect       _presentRect;
    UIView      *_presentView;
    UIBarButtonItem *_presentItem;
    
    NSArray     *_availableApplications;
    UIViewController    *_openInViewController;

    UIActionSheet *_optionsMenu;
    UIActionSheet *_openInMenu;
    NSInteger    _quickLookButtonIndex;
    NSInteger    _defaultOpenButtonIndex;
    NSInteger    _alternateOpenButtonIndex;
    NSInteger    _copyButtonIndex;
    NSInteger    _printButtonIndex;
    
    CGSize      _openInTableViewSize;

    BOOL        _shouldUnzipDocument;
    NSURL       *_unzippedDocumentURL;
    id          _applicationToOpen;

    struct {
        unsigned int delegateViewControllerForPreview:1;
        unsigned int delegateRectForPreview:1;
        unsigned int delegateViewForPreview:1;
        unsigned int transitionImageForPreview:1;
        unsigned int delegateWillBeginPreview:1;
        unsigned int delegateDidEndPreviewPreview:1;
        unsigned int delegateWillPresentOptionsMenu:1;
        unsigned int delegateDidDismissOptionsMenu:1;
        unsigned int delegateWillPresentOpenInMenu:1;
        unsigned int delegateDidDismissOpenInMenu:1;
        unsigned int delegateWillBeginSendingToApplication:1;
        unsigned int delegateDidEndSendingToApplication:1;
        unsigned int delegateCanPerformAction:1;
        unsigned int delegatePerformAction:1;
        unsigned int delegateUnzipURL:1;
    } _documentInteractionControllerFlags;
}

+ (UIDocumentInteractionController *)interactionControllerWithURL:(NSURL *)url; 		// use file to determine UTI. assumes file is complete

@property(nonatomic,assign) id<UIDocumentInteractionControllerDelegate> delegate;	// default is nil

@property(retain)   NSURL    *URL;             // default is nil. if set, updates UTI, icon and name
@property(nonatomic,copy)     NSString *UTI;             // determined from name if set, URL otherwise, override if the name or URL uses a custom scheme and the UTI can't be determined automatically
@property(copy)               NSString *name;            // determined from URL, override if the URL uses a custom scheme and the name can't be determined automatically
@property(nonatomic,readonly) NSArray  *icons;           // determined from name if set, URL otherwise. will return a generic document icon if an icon cannot be determined. returns an array of icons sorted from smallest to largest.
@property(nonatomic,retain)   id        annotation;      // additional plist information for application to pass to receiver (must be a plist object). default is nil.

- (BOOL)presentOptionsMenuFromRect:(CGRect)rect inView:(UIView *)view animated:(BOOL)animated;
- (BOOL)presentOptionsMenuFromBarButtonItem:(UIBarButtonItem *)item animated:(BOOL)animated;
// This is the default method you should call to give your users the option to quick look, open, or copy the document.
// Presents a menu allowing the user to Quick Look, open, or copy the item specified by URL.
// This automatically determines the correct application or applications that can open the item at URL.
// Returns NO if the options menu contained no options and was not opened.
// Note that you must implement the delegate method documentInteractionControllerViewControllerForPreview: to get the Quick Look menu item.

- (BOOL)presentPreviewAnimated:(BOOL)animated;
// Bypasses the menu and opens the full screen preview window for the item at URL.  Returns NO if the item could not be previewed.
// Note that you must implement the delegate method documentInteractionControllerViewControllerForPreview: to preview the document.

- (BOOL)presentOpenInMenuFromRect:(CGRect)rect inView:(UIView *)view animated:(BOOL)animated;
- (BOOL)presentOpenInMenuFromBarButtonItem:(UIBarButtonItem *)item animated:(BOOL)animated;
// Presents a menu allowing the user to open the document in another application.  The menu
// will contain all applications that can open the item at URL.
// Returns NO if there are no applications that can open the item at URL.

- (void)dismissPreviewAnimated:(BOOL)animated;
// Dismiss the full screen quick look window if it is visible.
- (void)dismissMenuAnimated:(BOOL)animated;
// Dismiss any visible menus.

@property(nonatomic,readonly) NSArray *gestureRecognizers;
// Returns an array of gesture recognizers preconfigured to manage the quick look and options menu.
// These gesture recognizers should only be installed on your view when the file has been copied locally and is present at URL.

@end

@protocol UIDocumentInteractionControllerDelegate <NSObject>

@optional

- (UIViewController *)documentInteractionControllerViewControllerForPreview:(UIDocumentInteractionController *)controller;
// If preview is supported, this provides the view controller on which the preview will be presented.
// This method is required if preview is supported.
// If presenting atop a navigation stack, provide the navigation controller in order to animate in a manner consistent with the rest of the platform.

- (CGRect)documentInteractionControllerRectForPreview:(UIDocumentInteractionController *)controller;
- (UIView *)documentInteractionControllerViewForPreview:(UIDocumentInteractionController *)controller;
// If preview is supported, these provide the view and rect that will be used as the starting point for the animation to the full screen preview.
// The actual animation that is performed depends upon the platform and other factors.
// If documentInteractionControllerRectForPreview is not implemented, the specified view's bounds will be used.
// If documentInteractionControllerViewForPreview is not implemented, the preview controller will simply fade in instead of scaling up.

- (void)documentInteractionControllerWillBeginPreview:(UIDocumentInteractionController *)controller;
- (void)documentInteractionControllerDidEndPreview:(UIDocumentInteractionController *)controller;
// Preview presented/dismissed on document.  Use to set up any HI underneath.

- (void)documentInteractionControllerWillPresentOptionsMenu:(UIDocumentInteractionController *)controller;
- (void)documentInteractionControllerDidDismissOptionsMenu:(UIDocumentInteractionController *)controller;
// Options menu presented/dismissed on document.  Use to set up any HI underneath.

- (void)documentInteractionControllerWillPresentOpenInMenu:(UIDocumentInteractionController *)controller;
- (void)documentInteractionControllerDidDismissOpenInMenu:(UIDocumentInteractionController *)controller;
// Open in menu presented/dismissed on document.  Use to set up any HI underneath.

- (void)documentInteractionController:(UIDocumentInteractionController *)controller willBeginSendingToApplication:(NSString *)application;	 // bundle ID
- (void)documentInteractionController:(UIDocumentInteractionController *)controller didEndSendingToApplication:(NSString *)application;
// Synchronous.  May be called when inside preview.  Usually followed by app termination.  Can use willBegin... to set annotation.

- (BOOL)documentInteractionController:(UIDocumentInteractionController *)controller canPerformAction:(SEL)action;
- (BOOL)documentInteractionController:(UIDocumentInteractionController *)controller performAction:(SEL)action;
// Used to handle additional menu items that can be performed on the item specified by URL.  Currently only supports the "copy:" and "print:" actions.

@end 
