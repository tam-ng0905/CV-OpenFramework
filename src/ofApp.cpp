#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetDataPathRoot(ofFile("model/"));
    grabber.setup(1280,720);
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
    for(auto face : tracker.getInstances()){
    ofxFaceTracker2Landmarks markers = face.getLandmarks();
        int dist =(int) ofDist(markers.getImagePoint(63).x, markers.getImagePoint(63).y, markers.getImagePoint(67).x, markers.getImagePoint(67).y);
        
        int distSide =(int) ofDist(markers.getImagePoint(49).x, markers.getImagePoint(49).y, markers.getImagePoint(55).x, markers.getImagePoint(55).y);
        
        //Output result to the console
        cout <<dist ;
        cout <<" "  ;
        cout <<distSide;
        cout <<" eye ";
        
        //Calculate the distance for the sides of the eyes
        int distEye =(int) ofDist(markers.getImagePoint(38).x, markers.getImagePoint(38).y, markers.getImagePoint(42).x, markers.getImagePoint(42).y);
    
        
        
        if(dist > 40 && distSide > 50 && count <2){
            cout <<"You are smiling";
            cout << "       ";
            siri.speak();
            siri.sing();
            count += 1;
            color = ofColor(232,12,147,10);
            
        }
        if(distEye < 94 && count < 3){
            cout <<"You are blinking";
            cout << "       ";
            color = ofColor(57,64,88,10);
            siri.speak2();
            count += 1;
        }
        
        //reset the count to give control over the amount of
        //the other two ifs statement above
        if(dist <40 || distSide <40 || distEye > 90){
            count = 0;
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    grabber.draw(0, 0);
  
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
        float brightness = color.getBrightness();
        float radius = ofMap(brightness, 0, 255, 0, 8);
          float light = grabber.getPixels().getColor(i, j).getLightness();
          if(light > 200){
              ofDrawSphere(i, j, 10, radius + dotSize);
          }
          
        ofDrawCircle(i, j, radius + dotSize);
      }
    }
       tracker.drawDebug();
        gui.draw();
}

//--------------------------------------------------------------
