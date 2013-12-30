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

-(void)turnFlashOn:(id)args
{
	[[self view] performSelectorOnMainThread:@selector(turnFlashOn:) withObject:args waitUntilDone:NO];
}

-(void)turnFlashOff:(id)args
{
	[[self view] performSelectorOnMainThread:@selector(turnFlashOff:) withObject:args waitUntilDone:NO];
}

-(void)switchCamera:(id)args
{
	[[self view] performSelectorOnMainThread:@selector(switchCamera:) withObject:args waitUntilDone:NO];
}

@end
