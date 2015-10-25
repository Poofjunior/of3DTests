#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
    ofBackground(ofColor::dimGray);

    ofNoFill();

    currView_.encodeRotation(0, 1, 0, 0);
    lastMouseX_ = 0;
    lastMouseY_ = 0;

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
    q1.rotate(myVecs[0].x_, myVecs[0].y_, myVecs[0].z_);
    q2.rotate(myVecs[1].x_, myVecs[1].y_, myVecs[1].z_);
    q3.rotate(myVecs[2].x_, myVecs[2].y_, myVecs[2].z_);

    std::cout << currView_ << std::endl;

    cameraOrientation_ = currView_;
    cameraPosition_.set(0, 0, 600);
    cameraOrientation_.rotate(cameraPosition_[0],
                                   cameraPosition_[1],
                                   cameraPosition_[2]);
    worldCam_.setPosition(cameraPosition_);

    float angle, x, y, z;
    cameraOrientation_.getRotation(angle, x, y, z);

    std::cout << "angle: " << angle << std::endl;
    std::cout << "axis: " << x << ", " << y << ", " << z << std::endl;

    ofQuaternion tempQuat;
    tempQuat.makeRotate(angle*(180/M_PI), x, y, z);

    worldCam_.setOrientation(tempQuat);
}


void ofApp::draw(){
    worldCam_.begin();

// Draw grid in the center of the screen
    ofDrawGrid(300, 5);

    ofDrawAxis(250);
    ofDrawSphere(0, 0, 0, 200);


    float theta, x, y, z;

    for (int i = 0; i < 3; ++i)
        ofDrawSphere(myVecs[i].x_, myVecs[i].y_, myVecs[i].z_, 10);

    worldCam_.end();
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

    Quaternion<float>xView;
    Quaternion<float>yView;

    float dampen = 0.4;
    yView.encodeRotation(-1*(y - lastMouseY_)*dampen * (M_PI/180.), 1, 0, 0);
    xView.encodeRotation(-1*(x - lastMouseX_)*dampen * (M_PI/180.), 0, 1, 0);
    //currView_ = xView * currView_ * yView;
    currView_ = currView_ * yView * xView;
    currView_.normalize();

    lastMouseX_ = x;
    lastMouseY_ = y;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    lastMouseX_ = mouseX;
    lastMouseY_ = mouseY;

}

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
