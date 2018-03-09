#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//OpenCV stuff
	camWidth = 640;
	camHeight = 480;
	webcam.initGrabber(camWidth, camHeight);
	analyzedVideoData = new unsigned char[camWidth * camHeight * 3];
	webcamTexture.allocate(camWidth, camHeight, GL_RGB);
	isDark = false;
	cout << isDark;
	//audioEngine stuff
	numberOfOscillators = 3;
	sampleRate = 48000;
	amplitude = 0.5;
	
	C.setValues(261.63, 0.0, amplitude, sampleRate);
	Db.setValues(277.18, 0.0, amplitude, sampleRate);
	D.setValues(293.66, 0.0, amplitude, sampleRate);
	Eb.setValues(311.13, 0.0, amplitude, sampleRate);
	E.setValues(329.63, 0.0, amplitude, sampleRate);
	F.setValues(349.23, 0.0, amplitude, sampleRate);
	Gb.setValues(369.99, 0.0, amplitude, sampleRate);
	G.setValues(392.00, 0.0, amplitude, sampleRate);
	Ab.setValues(415.30, 0.0, amplitude, sampleRate);
	A.setValues(440.00, 0.0, amplitude, sampleRate);
	Bb.setValues(466.16, 0.0, amplitude, sampleRate);
	B.setValues(493.88, 0.0, amplitude, sampleRate);


	ofSoundStreamSetup(2, 0, sampleRate, 1024, 4);
}

//--------------------------------------------------------------
void ofApp::update(){
	webcam.update();
	if (webcam.isFrameNew()) {
		unsigned char* pixelData = webcam.getPixels().getData();
		myPixels = webcam.getPixels();
		int nTotalBytes = camWidth * camHeight * 3;

		/* don't really need to do modifications to the pixel data yet
		do something to a copy of the data
		for (int i = 0; i < nTotalBytes; i++) {
			analyzedVideoData[i] = pixelData[i];
		}
		Load the data into a texture
		webcamTexture.loadData(analyzedVideoData, camWidth, camHeight, GL_RGB);
		*/
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(100, 100, 100);
	ofSetColor(255);
	webcam.draw(0, 0);
	ofNoFill();
}

void ofApp::audioOut(float* buffer, int bufferSize, int nChannels) {
	for (int i = 0; i < bufferSize; i++) {
		float currentSample = 0.0f;
		if (isDark == true) {
			currentSample += c_lydian();
		}
		else {
			currentSample += c_dorian();
		}
		currentSample *= 0.5; //lower the amplitude, cuz it's hella loud and obnoxious
		buffer[i * nChannels + 0] = currentSample;
		buffer[i * nChannels + 1] = currentSample;
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'k') {
		getImageInfo();
	}
}


void ofApp::mouseMoved(int x, int y) {
	position = ofMap(x, 0, ofGetWidth(), -1.0, 1.0);
	
}

void ofApp::getImageInfo() {
	int w = myPixels.getWidth();
	int h = myPixels.getHeight();

	float averageBrightness = 0;
	int warmPixels = 0;
	int coolPixels = 0;

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			ofColor colorAtXY = myPixels.getColor(x, y);
			if (colorAtXY.r > 125 && colorAtXY.b < 125 || colorAtXY.g < 125) {
				warmPixels += 1;
			}
			if (colorAtXY.r <= 125 && colorAtXY.b > 125 || colorAtXY.g > 125) {
				coolPixels += 1;
			}
			float brightnessOfColorAtXY = colorAtXY.getBrightness();
			averageBrightness += brightnessOfColorAtXY;
		}
	}
	averageBrightness /= (w*h);
	cout << "average brightness: " << averageBrightness << endl;
	cout << "Warm pixels: " << warmPixels << endl;
	cout << "Cool pixels: " << coolPixels << endl;
	if (warmPixels > coolPixels) {
		cout << "This photo is primarily warm." << endl;
	}
	else {
		cout << "This photo is primarily cool." << endl;
	}
	if (averageBrightness > 125) {
		isDark = true;
		cout << "This photo is primarily brighter." << endl << '\n';
	}
	else {
		isDark = false;
		cout << "This photo is primarily darker." << endl << '\n';
	}
}

float ofApp::c_lydian() {
	float currentSample = 0.0;
	currentSample += C.getSample();
	currentSample += E.getSample();
	currentSample += Gb.getSample();
	currentSample += B.getSample();
	return currentSample;
}

float ofApp::c_ionian() {
	float currentSample = 0.0;
	currentSample += C.getSample();
	currentSample += E.getSample();
	currentSample += G.getSample();
	currentSample += B.getSample();
	return currentSample;
}

float ofApp::c_mixolydian() {
	float currentSample = 0.0;
	currentSample += C.getSample();
	currentSample += E.getSample();
	currentSample += G.getSample();
	currentSample += Bb.getSample();
	return currentSample;
}

float ofApp::c_dorian() {
	float currentSample = 0.0;
	currentSample += C.getSample();
	currentSample += Eb.getSample();
	currentSample += G.getSample();
	currentSample += Bb.getSample();
	return currentSample;
}

float ofApp::c_aeolian() {
	float currentSample = 0.0;
	currentSample += C.getSample();
	currentSample += Eb.getSample();
	currentSample += G.getSample();
	currentSample += Ab.getSample();
	currentSample += Bb.getSample();
	return currentSample;
}

float ofApp::c_phrygian() {
	float currentSample = 0.0;
	currentSample += C.getSample();
	currentSample += Db.getSample();
	currentSample += Eb.getSample();
	currentSample += G.getSample();
	currentSample += Ab.getSample();
	currentSample += Bb.getSample();
	return currentSample;
}

float ofApp::c_locrian() {
	float currentSample = 0.0;
	currentSample += C.getSample();
	currentSample += Db.getSample();
	currentSample += Eb.getSample();
	currentSample += Gb.getSample();
	currentSample += Ab.getSample();
	currentSample += Bb.getSample();
	return currentSample;
}




void ofApp::exit() {
	ofSoundStreamClose();
}

