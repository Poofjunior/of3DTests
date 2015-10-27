#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
    ofBackground(10, 10, 20);
    ofSetColor(ofColor::powderBlue);

    ofNoFill();

    lastMouseX_ = 0;
    lastMouseY_ = 0;

    startingCameraPose_.encodeRotation(0, 1, 0, 0);
    startingCameraPose_.encodeTranslation(0, 0, 600);

    cameraPose_ = startingCameraPose_;

    qposes_.resize(3);
/// Lay down some starting poses.
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


    float x, y, z, roll, pitch, yaw;
    float angle, axis_x, axis_y, axis_z;
    cameraPose_.getTranslation(x, y, z);
    worldCam_.setPosition(ofVec3f(x, y, z));

    ofQuaternion tempQuat;
    Quaternion<float>camRotationTemp = cameraPose_.getRotation();
    camRotationTemp.getRotation(angle, axis_x, axis_y, axis_z);
    tempQuat.makeRotate(angle*(180/M_PI), axis_x, axis_y, axis_z);
    worldCam_.setOrientation(tempQuat);
}


void ofApp::draw(){
    worldCam_.begin();
    ofRotateX(-90);   // point z axis up.

// Draw grid in the center of the screen
    ofDrawGrid(10, 6);

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
    float dampen = 0.4;

    QPose<float>xTransform, yTransform;
    xTransform.encodeRotation(-1*(x - lastMouseX_)*dampen * (M_PI/180.), 0, 1, 0);
    xTransform.encodeTranslation(0, 0, 0);
    yTransform.encodeRotation(-1*(y - lastMouseY_)*dampen * (M_PI/180.), 1, 0, 0);
    yTransform.encodeTranslation(0, 0, 0);

    scrollTransform_ = scrollTransform_ * yTransform * xTransform;
    scrollTransform_.normalizeRotation();

    cameraPose_ = scrollTransform_ * startingCameraPose_;
    cameraPose_.normalizeRotation();

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
