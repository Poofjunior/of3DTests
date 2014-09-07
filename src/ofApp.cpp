#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	
	ofSetFrameRate(60);
    ofBackground(ofColor::dimGray);

    ofNoFill();
    
}

//--------------------------------------------------------------
void ofApp::update(){
}


void ofApp::draw(){
/// Flip orientation and location of window so that positive y grows UPwards.
    ofTranslate(0, ofGetHeight());
    ofScale(1, -1);

   
// Draw grid in the center of the screen
    //ofPushMatrix();
    ofTranslate(ofGetHeight()/2, ofGetWidth()/2);   // move to center.
    ofRotateX(-90);                                  // Zplane is at eye level.
    ofDrawGrid(300, 5);
    ofDrawAxis(100);
    //ofPopMatrix();

/*
    drawArrow(0, 0, 0, 90, 0, 0);
    drawArrow(0, 0, 0, 0, 90, 0);
    drawArrow(0, 0, 0, 0, 0, 90);
*/
    drawArrow(0, 0, 0, 0, 0, 0);

    for (float theta = -M_PI; theta < M_PI; theta += ((2* M_PI)/20) )
    {
        drawArrow(300*cos(theta), 300*sin(theta), -200, 
                  0, 0, 90 + (theta * (180./M_PI)));
    }

}



//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == 'e')
    {
        std::exit(2);
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{}

void ofApp::drawArrow(float x, float y, float z, float roll, float pitch, 
                      float yaw, float scale)
{
    ofPushMatrix(); // Save current pose
    ofTranslate(x, y, z);
    ofRotateX(roll);
    ofRotateY(pitch);
    ofRotateZ(yaw - 90 );   // default arrow is collinear with the +x axis.
    ofDrawCylinder(0, scale * 20, 0, scale * 1, scale * 40);
    ofDrawCone(0, scale * 50, 0, scale * 5, scale * -20);
    ofPopMatrix();
    
}
