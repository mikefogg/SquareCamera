Appcelerator Titanium :: SquareCamera
=============

An Appcelerator Titanium module that uses AVFoundation to allow for a much more customizable camera.

I have wanted (multiple times now) the option of being able to customize the camera size, shape, and functionality without just using the camera overlay. This lets you do that :)

* __NOTE:__ The name can be misleading, the camera __does not__ HAVE to be a square :)

<h2>Supports</h2>

<h3>Devices</h3>
  - iPhone (Tested with 3G, 3GS, 4, 4s, 5, 5c and 5s, and 6)
  - iPad (Tested with multiple iPads)
  - iPod Touch

<h3>iOS Versions</h3>
  - 6.0+ (up to the latest iOS 8)

<h3>Titanium SDK Versions</h3>
  - 3.2.0
  - 3.2.1
  - 3.2.3
  - 3.3.X
  - 3.4.0
  - 3.4.0
  - 3.4.1
  - 3.4.2

  * __Note:__ I am sure it works on many more versions than this, but these are just the one's I've used

<h2>Setup</h2>

Include the module in your tiapp.xml:

<pre><code>
com.mfogg.squarecamera

</code></pre>

<h2>Usage</h2>

<pre><code>
var SquareCamera = require('com.mfogg.squarecamera'); // Initialize the SquareCamera module

// open a single window
var win = Ti.UI.createWindow({backgroundColor:"#eee"});

var camera_view = SquareCamera.createView({
  top: 0,
  height: 320,
  width: 320,
  backgroundColor: "#fff",
  frontQuality: SquareCamera.QUALITY_HIGH, // Optional Defaults to QUALITY_HIGH
  backQuality: SquareCamera.QUALITY_HD, // Optional Defaults to QUALITY_HD
  camera: "back" // Optional "back" or "front"
});

var image_preview = Ti.UI.createImageView({
  right: 10,
  bottom: 10,
  width: 160,
  borderWidth:1,
  borderColor:'#ddd',
  height: 160,
  backgroundColor: '#444'
});

camera_view.addEventListener("success", function(e){
  image_preview.image = e.media;
});

win.add(cameraView);
win.add(image_preview);
win.open();

</code></pre>
* __NOTE:__ The created view (ex. 'camera_view' above) can have other views added on top of it to act as a camera overlay (exactly how you would a standard Ti.UI.view)

<h2>Camera Quality</h2>

You are now able to change the quality when initializing the camera by setting frontQuality and backQuality parameters.

<pre><code>
SquareCamera.QUALITY_LOW // AVCaptureSessionPresetLow
SquareCamera.QUALITY_MEDIUM // AVCaptureSessionPresetMedium
SquareCamera.QUALITY_HIGH // AVCaptureSessionPresetHigh
SquareCamera.QUALITY_HD // AVCaptureSessionPreset1920x1080 (Note: back camera only)

</code></pre>

<h2>Functions</h2>

<h3>camera_view.takePhoto();</h3>

Takes the photo (and fires the "success" event)

<h3>camera_view.turnFlashOff();</h3>

Turns the flash off (and fires the "onFlashOff" event)

<h3>camera_view.turnFlashOn();</h3>

Turns the flash on (and fires the "onFlashOn" event)

<h3>camera_view.setCamera(camera);</h3>

Takes the parameters "front" or "back" to change the position of the camera (and fires the "onCameraChange" event)

<h3>camera_view.pause();</h3>

Pauses the camera feed (and fires the "onStateChange" event with the state param "paused")

<h3>camera_view.resume();</h3>

Resumes the camera feed (and fires the "onStateChange" event with the state param "resumed")

<h2>Listeners</h2>

<h3>"success"</h3>

Will fire when a picture is taken.

<pre><code>
camera_view.addEventListener("success", function(e){

  Ti.API.info(JSON.stringify(e));

  Ti.API.info(e.media); // The actual blob data
  Ti.API.info(e.camera); // The "front" or "back" string for where the picture was taken

  image_preview.image = e.media;
});

</code></pre>

<h3>"onFlashOn"</h3>

Will fire when the flash is turned on.

<pre><code>
camera_view.addEventListener("onFlashOn", function(e){
  Ti.API.info("Flash Turned On");
});

</code></pre>

<h3>"onFlashOff"</h3>

Will fire when the flash is turned off.

<pre><code>
camera_view.addEventListener("onFlashOff", function(e){
  Ti.API.info("Flash Turned Off");
});

</code></pre>

<h3>"onCameraChange"</h3>

Will fire when the camera is changed between front and back

<pre><code>
camera_view.addEventListener("onCameraChange", function(e){
  // e.camera returns one of:
  //   "front" : using the front camera
  //   "back" : using the back camera
  
  Ti.API.info("Now using the "+e.camera+" camera"); // See what camera we're now using
});

</code></pre>

<h3>"onStateChange"</h3>

Will fire when the camera itself changes states

<pre><code>
// Event that listens for the camera to switch
camera_view.addEventListener("stateChange", function(e){
  // Camera state change event:
  //   "started" : The camera has started running!
  //   "stopped" : The camera has been stopped (and is being torn down)
  //   "paused" : You've paused the camera
  //   "resumed" : You've resumed the camera after pausing
  
  // e.state = The new state of the camera (one of the above options)
  
  Ti.API.info("Camera state changed to "+e.state);
});

</code></pre>

<h2>Known Issues and Future Improvements</h2>

1. Android support

... anything else :)

<h2>Please let me know if you'd like any additions or something isn't working!</h2>

<h3>License</h3>
Do whatever you want, however you want, whenever you want. And if you find a problem on your way, let me know so I can fix it for my own apps too :)

<h3>Other Stuff</h3>

<h4>Contributors (TONS of thanks!)</h4>
@Kosso
@reymundolopez
