#ifndef OF_APP_H
#define OF_APP_H
#pragma once

#include "ofMain.h"
#include "audioTools.h"

class ofApp : public ofBaseApp{

	public:
		//openFrameworks
		void setup();
		void update();
		void draw();
		void exit();
		void keyPressed(int key);
		void mouseMoved(int x, int y);

		//These chords are ordered in terms of descending brightness
		//Brightest -> Lydian
		//Darkest -> Locrian
		float playCLydian();
		float playCIonian();
		float playCMixolydian();
		float playCDorian();
		float playCAeolian();
		float playCPhrygian();
		float playCLocrian();

		void determineChord();

		//OpenCV
		void getImageInfo();
		ofImage sampleImage;
		ofVideoGrabber webcam;
		ofTexture webcamTexture;
		ofPixels myPixels;

		//Oscillators
		vector<Oscillator> oscillators;
		Oscillator sineTone;
		Oscillator C; //261.63Hz
		Oscillator Db; //277.18Hz
		Oscillator D; //293.66Hz
		Oscillator Eb; //311.13Hz
		Oscillator E; //329.63Hz
		Oscillator F; //349.23Hz
		Oscillator Gb; //369.99Hz
		Oscillator G; //392.00Hz
		Oscillator Ab; //415.30Hz
		Oscillator A; //440.00Hz
		Oscillator Bb; //466.16Hz
		Oscillator B; //493.88Hz

		int numberOfOscillators;

		//Panner
		Panner myPanner;
		stereoFrame currentFrame;
		float position;
		float leftChannelScale;
		float rightChannelScale;

		//OpenCV
		unsigned char* analyzedVideoData;
		int camWidth;
		int camHeight;
		bool isDark;

		//Audio Out
		void audioOut(float* buffer, int bufferSize, int nChannels);
		float frequency;
		float phase;
		float amplitude;
		int sampleRate;
		int c;
};
#endif