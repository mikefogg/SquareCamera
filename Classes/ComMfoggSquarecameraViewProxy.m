/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#import "ComMfoggSquarecameraViewProxy.h"
#import "ComMfoggSquarecameraView.h"
#import "TiUtils.h"

@implementation ComMfoggSquarecameraViewProxy

  #ifndef USE_VIEW_FOR_UI_METHOD
    #define USE_VIEW_FOR_UI_METHOD(methodname)\
    -(void)methodname:(id)args\
    {\
      [self makeViewPerformSelector:@selector(methodname:) withObject:args createIfNeeded:YES waitUntilDone:NO];\
    }
  #endif

USE_VIEW_FOR_UI_METHOD(takePhoto);
USE_VIEW_FOR_UI_METHOD(turnFlashOn);
USE_VIEW_FOR_UI_METHOD(turnFlashOff);
USE_VIEW_FOR_UI_METHOD(pause);
USE_VIEW_FOR_UI_METHOD(resume);

@end
