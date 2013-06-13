//
//  UIPrintInteractionController.h
//  UIKit
//
//  Copyright 2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIApplication.h>
#import <UIKit/UIKitDefines.h>

@class UIPrintInteractionController, UIPrintInfo, UIPrintPaper, UIPrintPageRenderer, UIPrintFormatter;
@class UIView, UIBarButtonItem;

typedef void (^UIPrintInteractionCompletionHandler)(UIPrintInteractionController *printInteractionController, BOOL completed, NSError *error);

@protocol UIPrintInteractionControllerDelegate;

UIKIT_CLASS_AVAILABLE(4_2) @interface UIPrintInteractionController : NSObject {
  @private
    UIPrintInfo                             *_printInfo;
    id<UIPrintInteractionControllerDelegate> _delegate;
    BOOL                                     _showsPageRange;
    UIPrintPageRenderer                     *_printPageRenderer;
    UIPrintFormatter                        *_printFormatter;
    id                                       _printingItem;
    NSArray                                 *_printingItems;
    UIPrintPaper                            *_printPaper;
    UIPrintInteractionCompletionHandler      _completionHandler;
    UIBackgroundTaskIdentifier               _backgroundTaskIdentifier;
    id                                       _printState;
}

+ (BOOL)isPrintingAvailable;                    // return YES if system supports printing. use this to hide HI for unsupported devices.

+ (NSSet *)printableUTIs;                       // return set of all document UTI types we can print
+ (BOOL)canPrintURL:(NSURL *)url;
+ (BOOL)canPrintData:(NSData *)data;

+ (UIPrintInteractionController *)sharedPrintController;

@property(nonatomic,retain) UIPrintInfo                             *printInfo;      // changes to printInfo ignored while printing. default is nil
@property(nonatomic,assign) id<UIPrintInteractionControllerDelegate> delegate;       // not retained. default is nil
@property(nonatomic)        BOOL                                     showsPageRange; // default is NO.

@property(nonatomic,readonly) UIPrintPaper *printPaper;  // set after printer selection

@property(nonatomic,retain) UIPrintPageRenderer *printPageRenderer;  // calls class to render each page
@property(nonatomic,retain) UIPrintFormatter    *printFormatter;     // uses a single formatter to fill the pages
@property(nonatomic,copy)   id                   printingItem;       // single NSData, NSURL, UIImage, ALAsset
@property(nonatomic,copy)   NSArray             *printingItems;      // array of NSData, NSURL, UIImage, ALAsset. does not support page range

- (BOOL)presentAnimated:(BOOL)animated completionHandler:(UIPrintInteractionCompletionHandler)completion;                                                // iPhone
- (BOOL)presentFromRect:(CGRect)rect inView:(UIView *)view animated:(BOOL)animated completionHandler:(UIPrintInteractionCompletionHandler)completion;    // iPad
- (BOOL)presentFromBarButtonItem:(UIBarButtonItem *)item animated:(BOOL)animated completionHandler:(UIPrintInteractionCompletionHandler)completion;      // iPad

- (void)dismissAnimated:(BOOL)animated;

@end

@protocol UIPrintInteractionControllerDelegate <NSObject>
@optional

- (UIViewController *)printInteractionControllerParentViewController:(UIPrintInteractionController *)printInteractionController;

- (UIPrintPaper *)printInteractionController:(UIPrintInteractionController *)printInteractionController choosePaper:(NSArray *)paperList;

- (void)printInteractionControllerWillPresentPrinterOptions:(UIPrintInteractionController *)printInteractionController;
- (void)printInteractionControllerDidPresentPrinterOptions:(UIPrintInteractionController *)printInteractionController;
- (void)printInteractionControllerWillDismissPrinterOptions:(UIPrintInteractionController *)printInteractionController;
- (void)printInteractionControllerDidDismissPrinterOptions:(UIPrintInteractionController *)printInteractionController;

- (void)printInteractionControllerWillStartJob:(UIPrintInteractionController *)printInteractionController;
- (void)printInteractionControllerDidFinishJob:(UIPrintInteractionController *)printInteractionController;

@end
