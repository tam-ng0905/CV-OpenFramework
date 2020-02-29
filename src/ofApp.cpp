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
    siri.setContent("You just smiled. You look pretty handsome ");
    
    // Setup gui
    gui.setup();
    gui.add(dotSize.setup("Dot Size", 10, 0, 20));
    gui.add(blackWhite.setup("Black and White", false));
    
    

    //this makes sure that the back of the model doesn't show through the front
    
    model.setPosition(ofGetWidth()*.5, ofGetHeight() * 0.75, 0);

    
    // Setup face tracker
    tracker.setup();
    
    // Initialize the color for the overplay circles
    color = ofColor(36,13,255,50);
    time = 0;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
       
       // Update tracker when there are new frames
       if(grabber.isFrameNew()){
           tracker.update(grabber);
       }
   //gets landmarks from all the faces
    for(auto face : tracker.getInstances()){
    ofxFaceTracker2Landmarks markers = face.getLandmarks();
        int distFaceWide =(int) ofDist(markers.getImagePoint(42).x, markers.getImagePoint(42).y, markers.getImagePoint(47).x, markers.getImagePoint(47).y);
        //int dist =(int) ofDist(markers.getImagePoint(63).x, markers.getImagePoint(63).y, markers.getImagePoint(67).x, markers.getImagePoint(67).y);
        
        int distMouth =(int) ofDist(markers.getImagePoint(49).x, markers.getImagePoint(49).y, markers.getImagePoint(55).x, markers.getImagePoint(55).y);
        
        
        
        //Calculate the distance for the sides of the eyes
        //int distEye =(int) ofDist(markers.getImagePoint(38).x, markers.getImagePoint(38).y, markers.getImagePoint(42).x, markers.getImagePoint(42).y);
    
        
        
        if(distMouth >= (0.95 * distFaceWide) && (time % 240 == 0)){
            cout <<"You are smiling";
            cout << "       ";
            siri.speak();
            siri.sing();
            //count += 1;
            smilePoint = ofPoint(markers.getImagePoint(67).x, markers.getImagePoint(67).y);
            smile = !smile;
            color = ofColor(232,12,147,10);
            
        }
        
        time ++;
       
    }
    
    //Detect if the screen is all black so that can reset it
    for (int i = 0; i < grabber.getWidth(); i+= 16) {
        for (int j = 0; j < grabber.getHeight(); j+= 16) {
            ofColor color1 = grabber.getPixels().getColor(i, j) + color;
            float bright = grabber.getPixels().getColor(i, j).getBrightness();
            
            if(bright < 20){
                brightnessCount ++;
                if(brightnessCount < (ofGetWidth()*ofGetHeight())){
                    smile = false;
                }
            }
            
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    //drawWithMesh();
    tracker.drawDebug();
    float myTime = ofGetSystemTimeMillis();
   
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
         
          float myNoise = 60.0 * ofSignedNoise(glm::vec2(i/400.0, myTime/8000.0));
        float brightness = color.getBrightness();
        float radius = ofMap(brightness, 0, 255, 0, 8);
          float light = grabber.getPixels().getColor(i, j).getLightness();
          if(light > 200){
              ofDrawSphere(i*myNoise, j*myNoise, 100*myNoise, radius + dotSize);
          }
        if(smile){
            ofTranslate(smilePoint.x, smilePoint.y);
             ofDrawCircle(i, j, radius + dotSize);
       } else {
            ofDrawCircle(i, j, radius + dotSize);
           }
      }
    }
    
    tracker.drawDebug();
    gui.draw();
       
}

//--------------------------------------------------------------



//The code below is a test method used to apply the 3d object onto the screen
/*void ofApp::drawWithMesh(){

    //get the model attributes we need
    for(auto face : tracker.getInstances()){
       ofxFaceTracker2Landmarks markers = face.getLandmarks();
        
        glm::vec3 scale = model.getScale();
        glm::vec3 position = model.getPosition();
        float normalizedScale = model.getNormalizedScale();
        ofVboMesh mesh = model.getMesh(0);
        ofTexture texture;
        ofxAssimpMeshHelper& meshHelper = model.getMeshHelper( 0 );
        bool bHasTexture = meshHelper.hasTexture();
        if( bHasTexture ) {
            texture = model.getTextureForMesh(0);
        }

        ofMaterial material = model.getMaterialForMesh(0);

        ofPushMatrix();

        //translate and scale based on the positioning.
        ofTranslate(position);
        ofRotateDeg(-markers.getImagePoint(34).x, 0, 1, 0);
        ofRotateDeg(90,1,0,0);


        ofScale(normalizedScale, normalizedScale, normalizedScale);
        ofScale(scale.x,scale.y,scale.z);

        //modify mesh with some noise
        float liquidness = 5;
        float amplitude = -markers.getImagePoint(34).y/100.0;
        float speedDampen = 5;
        auto &verts = mesh.getVertices();

        for(unsigned int i = 0; i < verts.size(); i++){
            
                    verts[i].x += ofSignedNoise(verts[i].x/liquidness, verts[i].y/liquidness,verts[i].z/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
                    verts[i].y += ofSignedNoise(verts[i].z/liquidness, verts[i].x/liquidness,verts[i].y/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
                    verts[i].z += ofSignedNoise(verts[i].y/liquidness, verts[i].z/liquidness,verts[i].x/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;

            
        }

        //draw the model manually
        if(bHasTexture) texture.bind();
        material.begin();
        mesh.drawWireframe(); //you can draw wireframe too
        mesh.drawFaces();
        material.end();
        if(bHasTexture) texture.unbind();

        ofPopMatrix();
    }

}*/
