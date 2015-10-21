#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
    ofBackground(ofColor::dimGray);

    ofNoFill();

    currView_.encodeRotation(0, 0, 0, 1);
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


    cameraPositionRotation_ = currView_;
    cameraPosition_.set(0, 0, 600);
    cameraPositionRotation_.rotate(cameraPosition_[0],
                                   cameraPosition_[1],
                                   cameraPosition_[2]);
    worldCam_.setPosition(cameraPosition_);
    float angle, x, y, z;
    cameraPositionRotation_.getRotation(angle, x, y, z);

    ofQuaternion tempQuat;
    tempQuat.makeRotate(angle*(180/M_PI), x, y, z);

    worldCam_.setOrientation(tempQuat);

    //worldCam_.setOrientation(curRot);
    //worldCam_.rotate(0.5, 0, 0, 1)
}


void ofApp::draw(){
    worldCam_.begin();

/// Flip orientation and location of window so that positive y grows UPwards.
/*
    ofTranslate(0, ofGetHeight());
*/
    ofScale(1, -1);


/*
    ofTranslate(ofGetHeight()/2, ofGetWidth()/2);   // 'zero' cursor at center.
    ofRotateX(-90);                                  // Zplane is at eye level.
*/



// Modify current viewpoint
    //float angle, axisX, axisY, axisZ;
    float my_angle, my_axis_x, my_axis_y, my_axis_z;


// Draw grid in the center of the screen
    ofDrawGrid(300, 5);

    currView_.getRotation(my_angle, my_axis_x, my_axis_y, my_axis_z);
    std::cout << "my angle axis: " << my_angle * (180/M_PI) << ", "
              << my_axis_x << ", " << my_axis_y << ", "
              << my_axis_z << std::endl;

    ofVec3f axis;
    float angle;
    curRot.getRotate(angle, axis);
    std::cout << "of angle axis: " << angle << ", " << axis.x
              << ", " << axis.y << ", " << axis.z << std::endl;
    //ofRotate(-angle, axis.x, axis.y, axis.z);
    //ofRotate(-my_angle * (180/M_PI), my_axis_x, my_axis_y, my_axis_z);

    ofDrawAxis(250);
    ofDrawSphere(0, 0, 0, 200);


    float theta, x, y, z;

/*
    ofPushMatrix();
    for (float theta = -M_PI; theta < M_PI; theta += ((2* M_PI)/100) )
    {
        ofRotate(angle * (180/M_PI), axisX, axisY, axisZ);
        drawArrow(300*cos(theta), 300*sin(theta), -200,
                  0, 0, 90 + (theta * (180./M_PI)));
    }
    ofPopMatrix();
*/


    for (int i = 0; i < 3; ++i)
        ofDrawSphere(myVecs[i].x_, myVecs[i].y_, myVecs[i].z_, 10);

    worldCam_.end();
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == 'e')
    {
        std::exit(2);
    }
    if (key == 'w')
    {
        Quaternion<float>yView;
        yView.encodeRotation(0.1, 1, 0, 0); 
        currView_ = currView_ * yView;
    }
    if (key == 's')
    {
        Quaternion<float>yView;
        yView.encodeRotation(-0.1, 1, 0, 0); 
        currView_ = currView_ * yView;
    }
    if (key == 'a')
    {
        Quaternion<float>xView;
        xView.encodeRotation(0.1, 0, 1, 0); 
        currView_ = currView_ * xView;
    }
    if (key == 'd')
    {
        Quaternion<float>xView;
        xView.encodeRotation(-0.1, 0, 1, 0); 
        currView_ = currView_ * xView;
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

    Quaternion<float>xView;
    Quaternion<float>yView;

    float dampen = 0.4;
    yView.encodeRotation(-1*(y - lastMouseY_)*dampen * (M_PI/180.), 1, 0, 0);
    xView.encodeRotation(-1*(x - lastMouseX_)*dampen * (M_PI/180.), 0, 1, 0);
    currView_ = currView_ * yView * xView;

    ofQuaternion yRot((y-lastMouseY_)*dampen, ofVec3f(1,0,0));
    ofQuaternion xRot((x-lastMouseX_)*dampen, ofVec3f(0,0,1));
    curRot = curRot * yRot * xRot;

/*
    std::cout << "myVersion: " << currView_ << std::endl;
    std::cout << "ofVersion: " << curRot.w() << ", "
              << curRot.x() << ", "  << curRot.y()
              << ", " << curRot.z() << std::endl;
*/



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
