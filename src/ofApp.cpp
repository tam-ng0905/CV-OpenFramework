#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetDataPathRoot(ofFile("model/"));
    grabber.setup(1280,768);
    light.setup();
    // Setup tracker
    light.setup();
    siri.setSpeaker("Samantha");
    siri.setSinger("Bad News");
    siri.setContent("You just smiled. You looks pretty handsome ");
    siri.setContent2("You just blink");
    
    // Setup gui
    gui.setup();
    gui.add(dotSize.setup("Dot Size", 10, 0, 20));
    gui.add(blackWhite.setup("Black and White", false));
    
    
    // Setup face tracker
    tracker.setup();
    
    // Initialize the color for the overplay circles
    color = ofColor(36,13,255,50);
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
       
       // Update tracker when there are new frames
       if(grabber.isFrameNew()){
           tracker.update(grabber);
       }
    timer+= 3;
    for(auto face : tracker.getInstances()){
    ofxFaceTracker2Landmarks markers = face.getLandmarks();
        int distFaceWide =(int) ofDist(markers.getImagePoint(42).x, markers.getImagePoint(42).y, markers.getImagePoint(47).x, markers.getImagePoint(47).y);
        //int dist =(int) ofDist(markers.getImagePoint(63).x, markers.getImagePoint(63).y, markers.getImagePoint(67).x, markers.getImagePoint(67).y);
        
        int distMouth =(int) ofDist(markers.getImagePoint(49).x, markers.getImagePoint(49).y, markers.getImagePoint(55).x, markers.getImagePoint(55).y);
        
        //Output result to the console
       // cout <<dist ;
        //cout <<" "  ;
     //   cout <<distSide;
     //   cout <<" eye ";
        
        //Calculate the distance for the sides of the eyes
        //int distEye =(int) ofDist(markers.getImagePoint(38).x, markers.getImagePoint(38).y, markers.getImagePoint(42).x, markers.getImagePoint(42).y);
    
        
        
        if(distMouth >= (0.9 * distFaceWide) && count < 2){
            cout <<"You are smiling";
            cout << "       ";
            siri.speak();
            siri.sing();
            count += 1;
            smilePoint = ofPoint(markers.getImagePoint(67).x, markers.getImagePoint(67).y);
            smile = !true;
            color = ofColor(232,12,147,10);
            
        } else {
            count = 0;
        }
       
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    float myTime = ofGetSystemTimeMillis();
   // grabber.draw(0, 0);
  // float time = ofGetTimelapsed();
    //draw the grids of colored circled that overlay the image
    for (int i = 0; i < grabber.getWidth(); i+= 16) {
      for (int j = 0; j < grabber.getHeight(); j+= 16) {
          ofColor color1 = grabber.getPixels().getColor(i, j) + color;
       
          if(blackWhite){
              ofColor colorBW = ofColor(0,0,0,20);
              ofSetColor(colorBW);
          } else{
              ofSetColor(color1);
          }
          float Noisew = ofNoise(i/30.0+timer/6, timer/3);
          float Noisex = ofNoise(i/60.0+timer/6, timer/3);
          float Noisey = ofNoise(i/40.0+timer/6, timer/3);
          float myNoise = 60.0 * ofSignedNoise(glm::vec2(i/400.0, myTime/8000.0));
        float brightness = color.getBrightness();
        float radius = ofMap(brightness, 0, 255, 0, 8);
          float light = grabber.getPixels().getColor(i, j).getLightness();
          if(light > 200){
              ofDrawSphere(i+myNoise, j+myNoise, 100+myNoise, radius + dotSize);
          }
        if(smile){
            ofTranslate(smilePoint.x, smilePoint.y);
        }
        ofDrawCircle(i, j, radius + dotSize);
      }
    }
       tracker.drawDebug();
        gui.draw();
}

//--------------------------------------------------------------
