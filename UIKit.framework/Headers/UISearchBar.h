//
//  UISearchBar.h
//  UIKit
//
//  Copyright (c) 2008-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import <UIKit/UIInterface.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UITextField.h>
#import <UIKit/UIKitDefines.h>

typedef enum {
    UISearchBarIconSearch, // The magnifying glass
    UISearchBarIconClear, // The circle with an x in it
    UISearchBarIconBookmark, // The open book icon
    UISearchBarIconResultsList, // The list lozenge icon
} UISearchBarIcon;

@protocol UISearchBarDelegate;
@class UITextField, UILabel, UIButton, UIColor;

UIKIT_CLASS_AVAILABLE(2_0) @interface UISearchBar : UIView { 
  @private
    UITextField            *_searchField;
    UILabel                *_promptLabel;
    UIButton               *_cancelButton;
    id<UISearchBarDelegate> _delegate;
    id                      _controller;
    UIColor                *_tintColor;
    UIImageView            *_separator;
    NSString               *_cancelButtonText;
    NSArray                *_scopes;
    NSInteger               _selectedScope;
    UIView                 *_background;
    UIView                 *_scopeBar;
    UIEdgeInsets            _contentInset;
    id                      _appearanceStorage;
    struct {
        unsigned int barStyle:3;
        unsigned int showsBookmarkButton:1;
        unsigned int showsCancelButton:1;
        unsigned int isTranslucent:1;
        unsigned int autoDisableCancelButton:1;
        unsigned int showsScopeBar:1;
        unsigned int hideBackground:1;
        unsigned int combinesLandscapeBars:1;
        unsigned int usesEmbeddedAppearance:1;
        unsigned int showsSearchResultsButton:1;
        unsigned int searchResultsButtonSelected:1;
        unsigned int pretendsIsInBar:1;
        unsigned int disabled:1;
    } _searchBarFlags;
}

@property(nonatomic)        UIBarStyle              barStyle;              // default is UIBarStyleDefault (blue)
@property(nonatomic,assign) id<UISearchBarDelegate> delegate;              // weak reference. default is nil
@property(nonatomic,copy)   NSString               *text;                  // current/starting search text
@property(nonatomic,copy)   NSString               *prompt;                // default is nil
@property(nonatomic,copy)   NSString               *placeholder;           // default is nil
@property(nonatomic)        BOOL                    showsBookmarkButton;   // default is NO
@property(nonatomic)        BOOL                    showsCancelButton;     // default is NO
@property(nonatomic)        BOOL                    showsSearchResultsButton __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2); // default is NO
@property(nonatomic, getter=isSearchResultsButtonSelected) BOOL searchResultsButtonSelected __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2); // default is NO
- (void)setShowsCancelButton:(BOOL)showsCancelButton animated:(BOOL)animated __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

@property(nonatomic,retain) UIColor                *tintColor;             // default is nil
@property(nonatomic,assign,getter=isTranslucent) BOOL translucent __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0); // Default is NO. Always YES if barStyle is set to UIBarStyleBlackTranslucent

// available text input traits
@property(nonatomic) UITextAutocapitalizationType autocapitalizationType;  // default is UITextAutocapitalizationTypeNone
@property(nonatomic) UITextAutocorrectionType     autocorrectionType;      // default is UITextAutocorrectionTypeDefault
@property(nonatomic) UITextSpellCheckingType      spellCheckingType;       // default is UITextSpellCheckingTypeDefault
@property(nonatomic) UIKeyboardType               keyboardType;            // default is UIKeyboardTypeDefault

@property(nonatomic,copy) NSArray   *scopeButtonTitles        __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0); // array of NSStrings. no scope bar shown unless 2 or more items
@property(nonatomic)      NSInteger  selectedScopeButtonIndex __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0); // index into array of scope button titles. default is 0. ignored if out of range
@property(nonatomic)      BOOL       showsScopeBar            __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0); // default is NO. if YES, shows the scope bar. call sizeToFit: to update frame

// 1pt wide images and resizable images will be scaled or tiled according to the resizable area, otherwise the image will be tiled
@property(nonatomic,retain) UIImage *backgroundImage __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;
@property(nonatomic,retain) UIImage *scopeBarBackgroundImage __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;

/* In general, you should specify a value for the normal state to be used by other states which don't have a custom value set
 */

/* The rounded-rect search text field image. Valid states are UIControlStateNormal and UIControlStateDisabled
 */
- (void)setSearchFieldBackgroundImage:(UIImage *)backgroundImage forState:(UIControlState)state __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;
- (UIImage *)searchFieldBackgroundImageForState:(UIControlState)state __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;

- (void)setImage:(UIImage *)iconImage forSearchBarIcon:(UISearchBarIcon)icon state:(UIControlState)state __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;
- (UIImage *)imageForSearchBarIcon:(UISearchBarIcon)icon state:(UIControlState)state __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;

//
// Customizing the appearance of the scope bar buttons.
//

/* If backgroundImage is an image returned from -[UIImage resizableImageWithCapInsets:] the cap widths will be calculated from the edge insets, otherwise, the cap width will be calculated by subtracting one from the image's width then dividing by 2. The cap widths will also be used as the margins for text placement. To adjust the margin use the margin adjustment methods.
 */
- (void)setScopeBarButtonBackgroundImage:(UIImage *)backgroundImage forState:(UIControlState)state __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR; 
- (UIImage *)scopeBarButtonBackgroundImageForState:(UIControlState)state __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;

/* To customize the segmented control appearance you will need to provide divider images to go between two unselected segments (leftSegmentState:UIControlStateNormal rightSegmentState:UIControlStateNormal), selected on the left and unselected on the right (leftSegmentState:UIControlStateSelected rightSegmentState:UIControlStateNormal), and unselected on the left and selected on the right (leftSegmentState:UIControlStateNormal rightSegmentState:UIControlStateSelected).
 */
- (void)setScopeBarButtonDividerImage:(UIImage *)dividerImage forLeftSegmentState:(UIControlState)leftState rightSegmentState:(UIControlState)rightState __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;
- (UIImage *)scopeBarButtonDividerImageForLeftSegmentState:(UIControlState)leftState rightSegmentState:(UIControlState)rightState __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;

/* You may specify the font, text color, text shadow color, and text shadow offset for the title in the text attributes dictionary, using the keys found in UIStringDrawing.h.
 */
- (void)setScopeBarButtonTitleTextAttributes:(NSDictionary *)attributes forState:(UIControlState)state __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;
- (NSDictionary *)scopeBarButtonTitleTextAttributesForState:(UIControlState)state __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;

/* To nudge the position of the search text field background in the search bar
 */
@property(nonatomic) UIOffset searchFieldBackgroundPositionAdjustment __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;

/* To nudge the position of the text within the search text field background
 */
@property(nonatomic) UIOffset searchTextPositionAdjustment __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;

/* To nudge the position of the icon within the search text field
 */
- (void)setPositionAdjustment:(UIOffset)adjustment forSearchBarIcon:(UISearchBarIcon)icon __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;
- (UIOffset)positionAdjustmentForSearchBarIcon:(UISearchBarIcon)icon __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;
@end

@protocol UISearchBarDelegate <NSObject>

@optional

- (BOOL)searchBarShouldBeginEditing:(UISearchBar *)searchBar;                      // return NO to not become first responder
- (void)searchBarTextDidBeginEditing:(UISearchBar *)searchBar;                     // called when text starts editing
- (BOOL)searchBarShouldEndEditing:(UISearchBar *)searchBar;                        // return NO to not resign first responder
- (void)searchBarTextDidEndEditing:(UISearchBar *)searchBar;                       // called when text ends editing
- (void)searchBar:(UISearchBar *)searchBar textDidChange:(NSString *)searchText;   // called when text changes (including clear)
- (BOOL)searchBar:(UISearchBar *)searchBar shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0); // called before text changes

- (void)searchBarSearchButtonClicked:(UISearchBar *)searchBar;                     // called when keyboard search button pressed
- (void)searchBarBookmarkButtonClicked:(UISearchBar *)searchBar;                   // called when bookmark button pressed
- (void)searchBarCancelButtonClicked:(UISearchBar *) searchBar;                    // called when cancel button pressed
- (void)searchBarResultsListButtonClicked:(UISearchBar *)searchBar __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_2); // called when search results button pressed

- (void)searchBar:(UISearchBar *)searchBar selectedScopeButtonIndexDidChange:(NSInteger)selectedScope __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

@end
