#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
    ofBackground(10, 10, 20);
    ofSetColor(ofColor::powderBlue);

    ofNoFill();

    currView_.encodeRotation(0, 1, 0, 0);
    lastMouseX_ = 0;
    lastMouseY_ = 0;

    qposes_.resize(3);
    qposes_[0].encodeRotation(M_PI/120, 1, 0, 1);
    qposes_[0].encodeTranslation(0, 0, 100);

    qposes_[1].encodeRotation(M_PI/120, -1, 0, 1);
    qposes_[1].encodeTranslation(0, 100, 0);

    qposes_[2].encodeRotation(M_PI/60, 1, 0, 0);
    qposes_[2].encodeTranslation(100, 0, 0);


}

//--------------------------------------------------------------
void ofApp::update(){
    std::vector<QPose<float>> rotations;
    rotations.resize(3);
    rotations[0].encodeRotation(M_PI/120, 1, 0, 1);
    rotations[0].encodeTranslation(0, 0, 0);

    rotations[1].encodeRotation(M_PI/120, -1, 0, 1);
    rotations[1].encodeTranslation(0, 0, 0);

    rotations[2].encodeRotation(M_PI/60, 0, 0, 1);
    rotations[2].encodeTranslation(0, 0, 0);

    qposes_[0] = rotations[0] * qposes_[0];
    qposes_[1] = rotations[1] * qposes_[1];
    qposes_[2] = rotations[2] * qposes_[2];



    cameraOrientation_ = currView_;
/// set initial camera position vector
    cameraPosition_.set(0, 0, 600);
/// rotate initial camera position vector
    cameraOrientation_.rotate(cameraPosition_[0],
                                   cameraPosition_[1],
                                   cameraPosition_[2]);
    worldCam_.setPosition(cameraPosition_);

    float angle, x, y, z;
    cameraOrientation_.getRotation(angle, x, y, z);

    ofQuaternion tempQuat;
    tempQuat.makeRotate(angle*(180/M_PI), x, y, z);

    worldCam_.setOrientation(tempQuat);
}


void ofApp::draw(){
    worldCam_.begin();

    ofRotateX(-90);   // point z axis up.
// Draw grid in the center of the screen
    ofDrawGrid(300, 6);

    ofDrawAxis(150);
    ofDrawSphere(0, 0, 0, 200);

    float x, y, z, roll, pitch, yaw;
    for (int i = 0; i < 3; ++i)
    {
        qposes_[i].get6DOF(x, y, z, roll, pitch, yaw);
        ofDrawSphere(x, y, z, 10);
    }

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

void ofApp::drawArrow(float x, float y, float z,
                      float rot_angle,
                      float rot_x, float rot_y, float rot_z,
                      float scale)
{
    ofPushMatrix(); // Save current pose
    ofTranslate(x, y, z);

    ofRotate(rot_angle, rot_x, rot_y, rot_z);
    ofDrawCylinder(0, scale * 20, 0, scale * 1, scale * 40);
    ofDrawCone(0, scale * 50, 0, scale * 5, scale * -20);
    ofPopMatrix();
}


void ofApp::drawArrow(float x, float y, float z,
                      float roll, float pitch, float yaw,
                      float scale)
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
