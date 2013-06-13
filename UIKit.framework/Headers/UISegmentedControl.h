//
//  UISegmentedControl.h
//  UIKit
//
//  Copyright (c) 2005-2011, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIControl.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIApplication.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UIBarButtonItem.h>

typedef enum {
    UISegmentedControlStylePlain,     // large plain
    UISegmentedControlStyleBordered,  // large bordered
    UISegmentedControlStyleBar,       // small button/nav bar style. tintable
    UISegmentedControlStyleBezeled,   // large bezeled style. tintable
} UISegmentedControlStyle;

enum {
    UISegmentedControlNoSegment = -1   // segment index for no selected segment
};

typedef enum {
    UISegmentedControlSegmentAny = 0,
    UISegmentedControlSegmentLeft = 1,   // The capped, leftmost segment. Only applies when numSegments > 1.
    UISegmentedControlSegmentCenter = 2, // Any segment between the left and rightmost segments. Only applies when numSegments > 2.
    UISegmentedControlSegmentRight = 3,  // The capped,rightmost segment. Only applies when numSegments > 1.
    UISegmentedControlSegmentAlone = 4,  // The standalone segment, capped on both ends. Only applies when numSegments = 1.
} UISegmentedControlSegment;

@class UIImage, UIColor;

UIKIT_CLASS_AVAILABLE(2_0) @interface UISegmentedControl : UIControl <NSCoding>
{
  @private
  // Note: all instance variables will become private in the future. Do not access directly.
    NSMutableArray *_segments;
    NSInteger       _selectedSegment;
    NSInteger       _highlightedSegment;
    UIView*         _removedSegment;
    id              _delegate;
    UIColor        *_tintColor;
    UIBarStyle      _barStyle;
    id              _appearanceStorage;
    UIView         *_backgroundBarView;
    CGFloat         _enabledAlpha;
    struct {
        unsigned int style:3;
        unsigned int size:2;
        unsigned int showsDisclosure:1;
        unsigned int delegateSelectedSegmentChanged:1;
        unsigned int delegateDisclosureButtonClicked:1;
        unsigned int delegateAlwaysNotifiesDelegateOfSegmentClicks:1;
        unsigned int momentaryClick:1;
        unsigned int dontAlwaysToggleForTwoSegments:1;
        unsigned int tracking:1;
        unsigned int mouseInside:1;
        unsigned int autosizeToFitSegments:1;
        unsigned int isSizingToFit:1;
        unsigned int autosizeText:1;
        unsigned int transparentBackground:1;
        unsigned int useProportionalWidthSegments:1;
        unsigned int translucentBackground:1;
    } _segmentedControlFlags;
}

- (id)initWithItems:(NSArray *)items; // items can be NSStrings or UIImages. control is automatically sized to fit content

@property(nonatomic) UISegmentedControlStyle segmentedControlStyle; // default is UISegmentedControlStylePlain
@property(nonatomic,getter=isMomentary) BOOL momentary;             // if set, then we don't keep showing selected state after tracking ends. default is NO
@property(nonatomic,readonly) NSUInteger numberOfSegments;

// For segments whose width value is 0, setting this property to YES attempts to adjust segment widths based on their content widths. Default is NO.
@property(nonatomic) BOOL apportionsSegmentWidthsByContent __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

- (void)insertSegmentWithTitle:(NSString *)title atIndex:(NSUInteger)segment animated:(BOOL)animated; // insert before segment number. 0..#segments. value pinned
- (void)insertSegmentWithImage:(UIImage *)image  atIndex:(NSUInteger)segment animated:(BOOL)animated;
- (void)removeSegmentAtIndex:(NSUInteger)segment animated:(BOOL)animated;
- (void)removeAllSegments;

- (void)setTitle:(NSString *)title forSegmentAtIndex:(NSUInteger)segment;      // can only have image or title, not both. must be 0..#segments - 1 (or ignored). default is nil
- (NSString *)titleForSegmentAtIndex:(NSUInteger)segment;

- (void)setImage:(UIImage *)image forSegmentAtIndex:(NSUInteger)segment;       // can only have image or title, not both. must be 0..#segments - 1 (or ignored). default is nil
- (UIImage *)imageForSegmentAtIndex:(NSUInteger)segment;

- (void)setWidth:(CGFloat)width forSegmentAtIndex:(NSUInteger)segment;         // set to 0.0 width to autosize. default is 0.0
- (CGFloat)widthForSegmentAtIndex:(NSUInteger)segment;

- (void)setContentOffset:(CGSize)offset forSegmentAtIndex:(NSUInteger)segment; // adjust offset of image or text inside the segment. default is (0,0)
- (CGSize)contentOffsetForSegmentAtIndex:(NSUInteger)segment;

- (void)setEnabled:(BOOL)enabled forSegmentAtIndex:(NSUInteger)segment;        // default is YES
- (BOOL)isEnabledForSegmentAtIndex:(NSUInteger)segment;

// ignored in momentary mode. returns last segment pressed. default is UISegmentedControlNoSegment until a segment is pressed
// the UIControlEventValueChanged action is invoked when the segment changes via a user event. set to UISegmentedControlNoSegment to turn off selection
@property(nonatomic) NSInteger selectedSegmentIndex;

/* Default tintColor is nil. Only used if style is UISegmentedControlStyleBar or UISegmentedControlStyleBezeled
 */
@property(nonatomic,retain) UIColor *tintColor UI_APPEARANCE_SELECTOR;

/* If backgroundImage is an image returned from -[UIImage resizableImageWithCapInsets:] the cap widths will be calculated from that information, otherwise, the cap width will be calculated by subtracting one from the image's width then dividing by 2. The cap widths will also be used as the margins for text placement. To adjust the margin use the margin adjustment methods.
 
 In general, you should specify a value for the normal state to be used by other states which don't have a custom value set.
 
 Similarly, when a property is dependent on the bar metrics (on the iPhone in landscape orientation, bars have a different height from standard), be sure to specify a value for UIBarMetricsDefault.
 In the case of the segmented control, appearance properties for UIBarMetricsLandscapePhone are only respected for segmented controls in the smaller navigation and toolbars that are used in landscape orientation on the iPhone.
 */
- (void)setBackgroundImage:(UIImage *)backgroundImage forState:(UIControlState)state barMetrics:(UIBarMetrics)barMetrics __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR; 
- (UIImage *)backgroundImageForState:(UIControlState)state barMetrics:(UIBarMetrics)barMetrics __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;

/* To customize the segmented control appearance you will need to provide divider images to go between two unselected segments (leftSegmentState:UIControlStateNormal rightSegmentState:UIControlStateNormal), selected on the left and unselected on the right (leftSegmentState:UIControlStateSelected rightSegmentState:UIControlStateNormal), and unselected on the left and selected on the right (leftSegmentState:UIControlStateNormal rightSegmentState:UIControlStateSelected).
 */
- (void)setDividerImage:(UIImage *)dividerImage forLeftSegmentState:(UIControlState)leftState rightSegmentState:(UIControlState)rightState barMetrics:(UIBarMetrics)barMetrics __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;
- (UIImage *)dividerImageForLeftSegmentState:(UIControlState)leftState rightSegmentState:(UIControlState)rightState barMetrics:(UIBarMetrics)barMetrics  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;

/* You may specify the font, text color, text shadow color, and text shadow offset for the title in the text attributes dictionary, using the keys found in UIStringDrawing.h.
 */
- (void)setTitleTextAttributes:(NSDictionary *)attributes forState:(UIControlState)state __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;
- (NSDictionary *)titleTextAttributesForState:(UIControlState)state __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;

/* For adjusting the position of a title or image within the given segment of a segmented control.
 */
- (void)setContentPositionAdjustment:(UIOffset)adjustment forSegmentType:(UISegmentedControlSegment)leftCenterRightOrAlone barMetrics:(UIBarMetrics)barMetrics __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR; 
- (UIOffset)contentPositionAdjustmentForSegmentType:(UISegmentedControlSegment)leftCenterRightOrAlone barMetrics:(UIBarMetrics)barMetrics __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0) UI_APPEARANCE_SELECTOR;

@end

