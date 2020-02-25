#pragma once

#include "ofMain.h"
#include "ofxFaceTracker2.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ofxSiri.h"
//#include "ofxBox2d.h"
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        ofLight light;
        ofxFaceTracker2 tracker;
        ofVideoGrabber grabber;
        ofxSiri siri;
    
        ofxPanel gui;
        ofxIntSlider dotSize;
        ofxToggle blackWhite;
    
    
        ofImage filter;
        ofColor color;
    
    
        int count = 0;
    
    
};
