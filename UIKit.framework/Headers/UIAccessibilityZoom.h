//
//  UIAccessibilityZoom.h
//  UIKit
//
//  Copyright (c) 2011, Apple Inc. All rights reserved.
//

/* 
 Use to inform system Zoom that focus has changed to a new location. 
 The frame should be in the coordinate space of the view.
 */
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_5_0
typedef enum {
    UIAccessibilityZoomTypeInsertionPoint,      // Used when the text insertion point has moved
} UIAccessibilityZoomType;
#endif

UIKIT_EXTERN void UIAccessibilityZoomFocusChanged(UIAccessibilityZoomType type, CGRect frame, UIView *view) __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

/*
 If your app uses multi-finger gestures that conflict with system Zoom gestures (by using three fingers), 
 calling this method will warn users of the conflict.
 */
UIKIT_EXTERN void UIAccessibilityRegisterGestureConflictWithZoom() __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

