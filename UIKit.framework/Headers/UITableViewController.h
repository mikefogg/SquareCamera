//
//  UITableViewController.h
//  UIKit
//
//  Copyright (c) 2008-2011, Apple Inc. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <UIKit/UIViewController.h>
#import <UIKit/UITableView.h>
#import <UIKit/UIKitDefines.h>

// Creates a table view with the correct dimensions and autoresizing, setting the datasource and delegate to self.
// In -viewWillAppear:, it reloads the table's data if it's empty. Otherwise, it deselects all rows (with or without animation) if clearsSelectionOnViewWillAppear is YES.
// In -viewDidAppear:, it flashes the table's scroll indicators.
// Implements -setEditing:animated: to toggle the editing state of the table.

UIKIT_CLASS_AVAILABLE(2_0) @interface UITableViewController : UIViewController <UITableViewDelegate, UITableViewDataSource> {
  @private
    UITableViewStyle _tableViewStyle;
    id               _keyboardSupport;
    id               _staticDataSource;
    struct {
        int clearsSelectionOnViewWillAppear:1;
    } _tableViewControllerFlags;
}

- (id)initWithStyle:(UITableViewStyle)style;

@property(nonatomic,retain) UITableView *tableView;
@property(nonatomic) BOOL clearsSelectionOnViewWillAppear __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_3_2); // defaults to YES. If YES, any selection is cleared in viewWillAppear:

@end
