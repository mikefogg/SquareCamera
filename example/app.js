// This is a test harness for your module
// You should do something interesting in this harness 
// to test out the module and to provide instructions 
// to users on how to use it by example.

var SquareCamera = require('com.mfogg.squarecamera');
Ti.API.info("module is => " + SquareCamera);

// open a single window
var win = Ti.UI.createWindow({backgroundColor:"#000"});

var cameraView = SquareCamera.createView({
	top: 60,
	height: 300,
	width: 300,
	backgroundColor: "#fff"
});

// Event that listens for the flash to turn on
cameraView.addEventListener("onFlashOn", function(e){
	alert("Flash Turned On");
});

// Event that listens for the flash to turn off
cameraView.addEventListener("onFlashOff", function(e){
	alert("Flash Turned Off");
});

// Event that listens for the camera to switch
cameraView.addEventListener("onSwitchCamera", function(e){
	alert("Camera Switched");
});

// Event that listens for a photo to be taken
cameraView.addEventListener("onTakePhoto", function(e){
	alert("Picture Taken");
});

// Take Photo Button
var take_photo = Ti.UI.createView({
	backgroundColor: "#fff",
	height: 80,
	width: 80,
	bottom: 10,
	borderRadius:40
});

take_photo.addEventListener("click", function(e){
	cameraView.takePhoto();
});

win.add(take_photo);

// Flash

var flash_on = false; //Flash defaults to 'Off'

var flash = Ti.UI.createView({
	backgroundColor: "#fff",
	height: 40,
	width: 40,
	top: 10,
	left: 10
});

flash.addEventListener("click", function(e){
	if(flash_on == true){
		cameraView.turnFlashOff();
		flash_on = false;
	} else {
		cameraView.turnFlashOn();
		flash_on = true;
	};
});

win.add(flash);

// Switch Camera

var switch_camera = Ti.UI.createView({
	backgroundColor: "#fff",
	height: 40,
	width: 40,
	top: 10,
	right: 10
});

switch_camera.addEventListener("click", function(e){
	cameraView.switchCamera();
});

win.add(switch_camera);

win.add(cameraView);
win.open();
