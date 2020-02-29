#pragma once

#include "ofMain.h"
#include "ofxFaceTracker2.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ofxSiri.h"
#include "ofxAssimpModelLoader.h"
//#include "ofxBox2d.h"
class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();
    void drawWithMesh();
        ofLight light;
        ofxFaceTracker2 tracker;
        ofVideoGrabber grabber;
        ofxSiri siri;
        ofPoint smilePoint;
        ofxPanel gui;
        ofxIntSlider dotSize;
        ofxToggle blackWhite;
        string curFileInfo;
        ofxAssimpModelLoader model;
        ofImage filter;
        ofColor color;
        bool smile = false;
        float timer = 0;
        int count = 0;
    int time = 0;
    int brightnessCount = 0;
    
    
};
