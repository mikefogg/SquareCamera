//
//  UIDataDetectors.h
//  UIKit
//
//  Copyright (c) 2009-2011, Apple Inc. All rights reserved.
//

enum {
    UIDataDetectorTypePhoneNumber   = 1 << 0,          // Phone number detection
    UIDataDetectorTypeLink          = 1 << 1,          // URL detection    
#if __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    UIDataDetectorTypeAddress       = 1 << 2,          // Street address detection
    UIDataDetectorTypeCalendarEvent = 1 << 3,          // Event detection
#endif    

    UIDataDetectorTypeNone          = 0,               // No detection at all
    UIDataDetectorTypeAll           = NSUIntegerMax    // All types
};

typedef NSUInteger UIDataDetectorTypes;
