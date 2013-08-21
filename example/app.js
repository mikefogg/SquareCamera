/*
* SquareCamera Titanium Module. 
* 
* Original Author : Mike Fogg : github.com/blirpit : June 2013
* 
* Modification and 'fixit attempts' : Kosso : August 2013
* 
*/ 


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

var image_preview = Ti.UI.createImageView({
	right: 10,
	bottom: 10,
	width: 160,
	borderWidth:1,
	borderColor:'#ddd',
	height: 160,
	backgroundColor: '#444',
	image: 'KS_nav_ui.png'
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
	//alert("Camera Switched");
});

// Event that listens for a photo to be taken
cameraView.addEventListener("success", function(e){

	Ti.API.info(JSON.stringify(e));

	Ti.API.info(e.media);

	image_preview.image = e.media;

	//alert("Picture Taken");


});

// Take Photo Button
var take_photo = Ti.UI.createView({
	backgroundColor: "#fff",
	height: 80,
	left: 10,
	width: 80,
	bottom: 10,
	borderRadius: 40
});



win.add(image_preview);


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
