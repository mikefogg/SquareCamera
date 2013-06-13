//
//  UIKitDefines.h
//  UIKit
//
//  Copyright (c) 2007-2011, Apple Inc. All rights reserved.
//

#import <Availability.h>

#ifdef __cplusplus
#define UIKIT_EXTERN		extern "C" __attribute__((visibility ("default")))
#else
#define UIKIT_EXTERN	        extern __attribute__((visibility ("default")))
#endif

#define UIKIT_STATIC_INLINE	static inline
#define UIKIT_CLASS_AVAILABLE(_iphoneIntro) __attribute__((visibility("default"))) NS_CLASS_AVAILABLE(NA, _iphoneIntro)
