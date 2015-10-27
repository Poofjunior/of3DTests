/**
 * ofApp.h
 * \author The OF Team with some edits by Joshua Vasquez
 * \date June 8, 2014
 */
#pragma once

#include "ofMain.h"
#include <iostream> // TODO: remove after debugging
#include <cstdlib>
#include "../../QPose/src/quaternion.hpp"
#include "../../QPose/src/qpose.hpp"
#include <vector>

class ofApp : public ofBaseApp{

    public:
        static const int windowX_ = 1000;
        static const int windowY_ = 1000;

        void setup();
        void update();
        void draw();


        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void keyPressed(int key);

        void drawArrow(float x, float y, float z,
                       float rot_angle, float rot_x, float rot_y, float rot_z,
                       float scale);

        std::vector<QPose<float>> qposes_;


    private:
        static constexpr float pixelsPerMeter_ = 100.;

        QPose<float> scrollTransform_;
        float lastMouseX_;
        float lastMouseY_;


        QPose<float> startingCameraPose_;
        QPose<float> cameraPose_;

        ofCamera worldCam_;
        ofVec3f cameraPosition_;
        Quaternion<float> cameraOrientation_;

};


