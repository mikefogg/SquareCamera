Appcelerator Titanium :: SquareCamera

An Appcelerator Titanium module that uses AVFoundation to allow for a much more customizable camera.

I have wanted (multiple times now) the option of being able to customize the camera size, shape, and functionality without just using the camera overlay. This lets you do that :)

* __NOTE:__ The name can be misleading, the camera __does not__ HAVE to be a square :)

<h2>Supports</h2>

<h3>Devices</h3>
  - iPhone (Tested with 3G, 3GS, 4, 4s, 5, 5c and 5s, 6, and 6s)
  - iPad (Tested with multiple iPads)
  - iPod Touch

<h3>iOS Versions</h3>
  - 6.0+ (up to the latest iOS 8)
  - [7.0+ for 2d code detection in module version 0.7]

<h3>Titanium SDK Versions</h3>
  - 3.2.0
  - 3.2.1
  - 3.2.3
  - 3.3.X
  - 3.4.0
  - 3.4.1
  - 3.4.2
  - 3.5.0.GA
  - 5.0.0.GA
  - 5.0.2.GA

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
  camera: "back" // Optional "back" or "front",
  forceHorizontal: true, // Optional sets the camera to horizontal mode if you app is horizontal only (Default false)
  detectCodes: true, // Since version 0.7 : optional boolean to activate 2d code detection. Dection fires "code" event contaning e.codeType and e.value -All codes types are supported. Will not work on iPhone 4 with iOS 7 (crashes upon adding SquareCamera to view).
  scanCrop: { // Available since v 0.8
    x: ((Ti.Platform.displayCaps.platformWidth-220)/2),
    y: ((Ti.Platform.displayCaps.platformHeight-220)/2),
    width: 220,
    height: 220
  },
  scanCropPreview: true, // Available since v 0.8
  barcodeTypes: [  // Available since v 0.8
    "UPCE",
    "UPCA",
    "EAN13",
    "CODE128"
  ]
});

var label_message = Ti.UI.createLabel({
    height:Ti.UI.SIZE,
    left:10,
    right:10,
    text:'ready',
    top:330,
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
// Since 0.7 : 2d code detection. Requires detectCodes:true on the camera view.
camera_view.addEventListener("code", function(e){
  label_message.text = e.codeType+' : '+e.value;
});

win.add(cameraView);
win.add(label_message);
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

<h2>Detect Codes</h2>

As of 0.7 @kosso added the ability to detect barcodes. I've extended this functionality to allow you to:

<h4>Set a certain area of the screen that is able to detect codes using scanCrop:</h4>

<pre><code>
scanCrop: {
  x: 0,
  y: 0,
  width: 220,
  height: 220
}

</code></pre>

<h4>Make the scanCrop area slightly red for testing/debugging:</h4>

<pre><code>
scanCropPreview: true

</code></pre>

<h4>Set which types of barcodes you'd like to scan when the view is initialized:</h4>

<pre><code>
barcodeTypes: [
  "UPCE",
  "EAN13"
]

Available Code Types:
 UPCE
 Code39
 Code39Mod43
 EAN13
 EAN8
 Code93
 Code128
 PDF417
 QR
 Aztec
 Interleaved2of5
 ITF14
 DataMatrix

</code></pre>

Note: Apple supports UPC-A by returning EAN13 with a leading zero (see https://developer.apple.com/library/ios/technotes/tn2325/_index.html#//apple_ref/doc/uid/DTS40013824-CH1-IS_UPC_A_SUPPORTED_)

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

<h3>"code"</h3>

Since 0.7. Fires when detectCodes:true

* __Note:__ detectCodes:true crashes iPhone 4 when SquareCamera view is added and made visible

<pre><code>
camera_view.addEventListener("code", function(e){
  // returns :
  //   e.value : The value.
  //   e.codeType : The 2D Code Type
  /*
  Available Code Types:
   UPCECode
   Code39Code
   Code39Mod43Code
   EAN13Code
   EAN8Code
   Code93Code
   Code128Code
   PDF417Code
   QRCode
   AztecCode
   Interleaved2of5Code
   ITF14Code
   DataMatrixCode
  */

  Ti.API.info("2D code detected : "+e.codeType+' : '+e.value);

});

</code></pre>

<h2>Known Issues and Future Improvements</h2>

1. Android support
2. detectCodes:true crashes iPhone 4 when SquareCamera view is added and made visible.  Probably won't be fixed since iPhone 4 no longer getting iOS updates from Apple.

... anything else :)

<h2>Please let me know if you'd like any additions or something isn't working!</h2>

<h3>License</h3>
Do whatever you want, however you want, whenever you want. And if you find a problem on your way, let me know so I can fix it for my own apps too :)

<h3>Other Stuff</h3>

<h4>Contributors (TONS of thanks!)</h4>
@Kosso
@reymundolopez
@yuhsak
