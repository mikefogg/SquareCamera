/*
*
* SquareCamera Titanium Module.
*
* Original Author : Mike Fogg : github.com/mikefogg : June 2013
*
*/


var SquareCamera = require('com.mfogg.squarecamera');
Ti.API.info("module is => " + SquareCamera);

// open a single window
var win = Ti.UI.createWindow({backgroundColor:"#eee"});

var camera_view = SquareCamera.createView({
  top: 0,
  height: 320,
  width: 320,
  frontQuality: SquareCamera.QUALITY_HIGH,
  backQuality: SquareCamera.QUALITY_HD,
  backgroundColor: "#fff",
  camera: "front", // Set the view to open with the front camera
  detectCodes: true, // Available since v 0.7
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
    text:'No Code',
    font:{fontSize:10,fontFamily:'Helvetica Neue'},
    bottom: 100
});

var image_preview = Ti.UI.createImageView({
  right: 10,
  bottom: 10,
  width: 160,
  borderWidth:1,
  borderColor:'#ddd',
  height: 160,
  backgroundColor: '#444',
  image: 'loading_bg_sq.png'
});

// Event that listens for the flash to turn on
camera_view.addEventListener("onFlashOn", function(e){
  flash.title = "Flash On";
});

// Event that listens for the flash to turn off
camera_view.addEventListener("onFlashOff", function(e){
  flash.title = "Flash Off";
});

// Event that listens for the camera to switch
camera_view.addEventListener("onCameraChange", function(e){
  // New e.camera actually returns one of:
  //   "front" : using the front camera
  //   "back" : using the back camera

  Ti.API.info("Now using the "+e.camera+" camera"); // See what camera we're now using
});

// Event that listens for a photo to be taken
camera_view.addEventListener("success", function(e){

  Ti.API.info(JSON.stringify(e));

  Ti.API.info(e.media); // The actual blob
  Ti.API.info(e.camera); // The "front" or "back" string for where the picture was taken

  image_preview.image = e.media;
});

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

// Since 0.7 : 2d code detection. Requires detectCodes:true on the camera view.
camera_view.addEventListener("code", function(e){
  label_message.text = e.codeType+' : '+e.value;
});

// Take Photo Button
var take_photo = Ti.UI.createView({
  backgroundColor:"#6ac88d",
  height:60,
  left:10,
  width:90,
  bottom:10,
  borderRadius:30
});

win.add(label_message);
win.add(image_preview);

take_photo.addEventListener("click", function(e){
  camera_view.takePhoto();
});

win.add(take_photo);

// Flash

var flash_on = false; //Flash defaults to 'Off'

var flash = Ti.UI.createButton({
  top: 330,
  left: 10,
  borderWidth:0,
  borderRadius:20,
  width:90,
  height:40,
  color:'#444',
  title:'Flash Off',
  font:{fontSize:12,fontFamily:'Helvetica Neue'},
  backgroundColor:'#aca476',
  backgroundSelectedColor:'#aca476',
  borderColor:'#aca476'
});

flash.addEventListener("click", function(e){
  if(flash_on == true){
    camera_view.turnFlashOff();
    flash_on = false;
  } else {
    camera_view.turnFlashOn();
    flash_on = true;
  };
});

win.add(flash);

// Pause the camera
var pause = Ti.UI.createButton({
  top: 380,
  left: 10,
  borderWidth:0,
  borderRadius:20,
  width:90,
  height:40,
  color:'#444',
  title:'Pause',
  font:{fontSize:12,fontFamily:'Helvetica Neue'},
  backgroundColor:'#aca476',
  backgroundSelectedColor:'#aca476',
  borderColor:'#aca476'
});

pause.addEventListener("click", function(e){
  camera_view.pause();
});

win.add(pause);

// Pause the camera
var resume = Ti.UI.createButton({
  top: 430,
  left: 10,
  borderWidth:0,
  borderRadius:20,
  width:90,
  height:40,
  color:'#444',
  title:'Resume',
  font:{fontSize:12,fontFamily:'Helvetica Neue'},
  backgroundColor:'#aca476',
  backgroundSelectedColor:'#aca476',
  borderColor:'#aca476'
});

resume.addEventListener("click", function(e){
  camera_view.resume();
});

win.add(resume);

// Switch Camera

var change_camera = Ti.UI.createButton({
  top: 330,
  right: 10,
  borderWidth:0,
  borderRadius:20,
  width:90,
  height:40,
  color:'#444',
  title:'camera',
  font:{fontSize:12,fontFamily:'Helvetica Neue'},
  backgroundColor:'#aca476',
  backgroundSelectedColor:'#aca476',
  borderColor:'#aca476'
});

change_camera.addEventListener("click", function(e){
  if(camera_view.camera == "front"){
    camera_view.camera = "back";
  } else {
    camera_view.camera = "front";
  };
});

win.add(change_camera);

win.add(camera_view);
win.open();
