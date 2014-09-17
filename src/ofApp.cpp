#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	
	ofSetFrameRate(60);
    ofBackground(ofColor::dimGray);

    ofNoFill();

    currView.encodeRotation(0, 0, 0, 0);
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

    // Test QPoses:
    myPose = QPose<float> (0, -600, 0, 0, M_PI/2, -M_PI/2);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    //q1.rotate(myVec.x, myVec.y, myVec.z);
    q1.rotate(myVecs[0].x_, myVecs[0].y_, myVecs[0].z_);
    q2.rotate(myVecs[1].x_, myVecs[1].y_, myVecs[1].z_);
    q3.rotate(myVecs[2].x_, myVecs[2].y_, myVecs[2].z_);

    Quaternion<float> xView;
    Quaternion<float> yView;
    
    xView.encodeRotation(.001, 0, 0, 1); 
    yView.encodeRotation(.001, 1, 0, 0); 
    currView = currView * xView * yView;
}


void ofApp::draw(){

/// Flip orientation and location of window so that positive y grows UPwards.
    ofTranslate(0, ofGetHeight());
    ofScale(1, -1);

    ofTranslate(ofGetHeight()/2, ofGetWidth()/2);   // 'zero' cursor at center.
    ofRotateX(-90);                                  // Zplane is at eye level.



// Modify current viewpoint
    float angle, axisX, axisY, axisZ;

    
    ofDrawAxis(300);

    currView.getRotation(angle, axisX, axisY, axisZ);
    ofRotate(angle * (180/M_PI), axisX, axisY, axisZ);

/*   
    worldCam.begin();
    myQuat.set(currView.x_,
               currView.y_,
               currView.z_,
               currView.w_);
*/

// Draw grid in the center of the screen
    ofPushMatrix();
    ofDrawGrid(300, 5);
    ofDrawAxis(100);
    //ofDrawSphere(0, 0, 0, 200);    
    ofPopMatrix();



    float theta, x, y, z;

    ofPushMatrix();
    for (float theta = -M_PI; theta < M_PI; theta += ((2* M_PI)/100) )
    {
        ofRotate(angle * (180/M_PI), axisX, axisY, axisZ);
        drawArrow(300*cos(theta), 300*sin(theta), -200, 
                  0, 0, 90 + (theta * (180./M_PI)));
    }
    ofPopMatrix();
    
/*
    float qpx, qpy, qpz, qproll, qppitch, qpyaw;
    myPose.get6DOF(qpx, qpy, qpz, qproll, qppitch, qpyaw);
    drawArrow(qpx, qpy, qpz, qproll, qppitch, qpyaw);
*/

    
/*
    ofPushMatrix();
    ofTranslate(qpx, qpy, qpz);
    std::cout << "qproll:" << qproll << std::endl;
    std::cout << "qppitch:" << qppitch << std::endl;
    std::cout << "qpyaw:" << qpyaw << std::endl;
    ofRotateX(180/M_PI * qproll);
    ofRotateY(180/M_PI * qppitch);
    ofRotateZ(180/M_PI * qpyaw);
    ofDrawRotationAxes(40);
    ofPopMatrix();

    ofPushMatrix();
    ofTranslate(qpx, qpy, qpz);
    float testangle, axisx, axisy, axisz;
    myPose.real_.getRotation(testangle, axisz, axisy, axisz);
    ofRotate(180/M_PI * testangle, axisz, axisy, axisz);
    ofDrawRotationAxes(40);
    ofPopMatrix();
*/

    
/*
    ofGLRenderer ofGL;
    ofGL.setLineWidth(5);
    ofGL.drawLine(0,0,0,myVec.x, myVec.y, myVec.z);
    ofDrawSphere(myVec.x, myVec.y, myVec.z, 10);
*/
    
    for (int i = 0; i < 3; ++i)
        ofDrawSphere(myVecs[i].x_, myVecs[i].y_, myVecs[i].z_, 10);
    

// Modify current viewpoint
 //   worldCam.setOrientation(myQuat);
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
        currView = currView * yView;
    }
    if (key == 's')
    {
        Quaternion<float>yView;
        yView.encodeRotation(-0.1, 1, 0, 0); 
        currView = currView * yView;
    }
    if (key == 'a')
    {
        Quaternion<float>xView;
        xView.encodeRotation(0.1, 0, 1, 0); 
        currView = currView * xView;
    }
    if (key == 'd')
    {
        Quaternion<float>xView;
        xView.encodeRotation(-0.1, 0, 1, 0); 
        currView = currView * xView;
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

    Quaternion<float>xView;
    Quaternion<float>yView;

    xView.encodeRotation((x - lastMouseX_)*.005, 0, 0, 1); 
    yView.encodeRotation((y - lastMouseY_)*.005, 1, 0, 0); 

    currView = currView * xView * yView;


/*
    //ofVec2f mouse(x,y);
    ofQuaternion yRot((x-lastMouseX_)*0.4, ofVec3f(0,1,0));
    ofQuaternion xRot((y-lastMouseY_)*0.4, ofVec3f(-1,0,0));
    //curRot *= yRot*xRot;
    curRot = curRot * yRot * xRot;
    //lastMouse = mouse;
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
