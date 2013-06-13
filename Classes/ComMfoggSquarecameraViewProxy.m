/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#import "ComMfoggSquarecameraViewProxy.h"
#import "ComMfoggSquarecameraView.h"

@implementation ComMfoggSquarecameraViewProxy

-(void)takePhoto:(id)args
{
	[[self view] performSelectorOnMainThread:@selector(takePhoto:) withObject:args waitUntilDone:NO];
}

@end
