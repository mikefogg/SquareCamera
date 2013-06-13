//
//  UIWebView.h
//  UIKit
//
//  Copyright (c) 2007-2011, Apple Inc. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIDataDetectors.h>
#import <UIKit/UIScrollView.h>

typedef enum {
    UIWebViewNavigationTypeLinkClicked,
    UIWebViewNavigationTypeFormSubmitted,
    UIWebViewNavigationTypeBackForward,
    UIWebViewNavigationTypeReload,
    UIWebViewNavigationTypeFormResubmitted,
    UIWebViewNavigationTypeOther
} UIWebViewNavigationType;

@class UIWebViewInternal;
@protocol UIWebViewDelegate;

UIKIT_CLASS_AVAILABLE(2_0) @interface UIWebView : UIView <NSCoding, UIScrollViewDelegate> { 
 @private
    UIWebViewInternal *_internal;
}

@property(nonatomic,assign) id<UIWebViewDelegate> delegate;

@property(nonatomic,readonly,retain) UIScrollView *scrollView __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

- (void)loadRequest:(NSURLRequest *)request;
- (void)loadHTMLString:(NSString *)string baseURL:(NSURL *)baseURL;
- (void)loadData:(NSData *)data MIMEType:(NSString *)MIMEType textEncodingName:(NSString *)textEncodingName baseURL:(NSURL *)baseURL;

@property(nonatomic,readonly,retain) NSURLRequest *request;

- (void)reload;
- (void)stopLoading;

- (void)goBack;
- (void)goForward;

@property(nonatomic,readonly,getter=canGoBack) BOOL canGoBack;
@property(nonatomic,readonly,getter=canGoForward) BOOL canGoForward;
@property(nonatomic,readonly,getter=isLoading) BOOL loading;

- (NSString *)stringByEvaluatingJavaScriptFromString:(NSString *)script;

@property(nonatomic) BOOL scalesPageToFit;

@property(nonatomic) BOOL detectsPhoneNumbers __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA, __MAC_NA, __IPHONE_2_0, __IPHONE_3_0);
@property(nonatomic) UIDataDetectorTypes dataDetectorTypes __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_3_0);

@property (nonatomic) BOOL allowsInlineMediaPlayback __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_4_0); // iPhone Safari defaults to NO. iPad Safari defaults to YES
@property (nonatomic) BOOL mediaPlaybackRequiresUserAction __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_4_0); // iPhone and iPad Safari both default to YES

@property (nonatomic) BOOL mediaPlaybackAllowsAirPlay __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0); // iPhone and iPad Safari both default to YES

@end

@protocol UIWebViewDelegate <NSObject>

@optional
- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType;
- (void)webViewDidStartLoad:(UIWebView *)webView;
- (void)webViewDidFinishLoad:(UIWebView *)webView;
- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error;

@end
