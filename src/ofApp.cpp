#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	
	ofSetFrameRate(60);
    ofBackground(ofColor::dimGray);

    ofNoFill();
    
    q1.encodeRotation(M_PI/120, 1, 0, 1); 
    q2.encodeRotation(M_PI/120, -1, 0, 1);
    q3.encodeRotation(M_PI/60, 1, 0, 0);

    myVec.x = 0;
    myVec.y = 0;
    myVec.z = 300;

    myVecs = std::vector<vec3>(3);

    myVecs[0].x_ = 0;
    myVecs[0].y_ = 0;
    myVecs[0].z_ = 100;

    myVecs[1].x_ = 0;
    myVecs[1].y_ = 0;
    myVecs[1].z_ = 100;

    myVecs[2].x_ = 0;
    myVecs[2].y_ = 0;
    myVecs[2].z_ = 100;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    //q1.rotate(myVec.x, myVec.y, myVec.z);
    q1.rotate(myVecs[0].x_, myVecs[0].y_, myVecs[0].z_);
    q2.rotate(myVecs[1].x_, myVecs[1].y_, myVecs[1].z_);
    q3.rotate(myVecs[2].x_, myVecs[2].y_, myVecs[2].z_);
}


void ofApp::draw(){
/// Flip orientation and location of window so that positive y grows UPwards.
    ofTranslate(0, ofGetHeight());
    ofScale(1, -1);

   
// Draw grid in the center of the screen
    ofTranslate(ofGetHeight()/2, ofGetWidth()/2);   // move to center.
    ofRotateX(-90);                                  // Zplane is at eye level.
    ofDrawGrid(300, 5);
    ofDrawAxis(100);

    float theta, x, y, z;

    drawArrow(0, 0, 0, 0, 0, 0);

    for (float theta = -M_PI; theta < M_PI; theta += ((2* M_PI)/20) )
    {
        drawArrow(300*cos(theta), 300*sin(theta), -200, 
                  0, 0, 90 + (theta * (180./M_PI)));
    }

    
    ofGLRenderer ofGL;
    ofGL.setLineWidth(5);
    ofGL.drawLine(0,0,0,myVec.x, myVec.y, myVec.z);
    ofDrawSphere(myVec.x, myVec.y, myVec.z, 10);
    
    for (int i = 0; i < 3; ++i)
        ofDrawSphere(myVecs[i].x_, myVecs[i].y_, myVecs[i].z_, 10);

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
