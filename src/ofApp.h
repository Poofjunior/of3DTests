/**
 * ofApp.h
 * \author The OF Team with some edits by Joshua Vasquez
 * \date June 8, 2014
 */
#pragma once

#include "ofMain.h"
#include <iostream> // TODO: remove after debugging
#include <cstdlib>

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

        void drawArrow(float x, float y, float z, float roll, float pitch,
                       float yaw, float scale = 1);


    private:
        static constexpr float pixelsPerMeter_ = 100.;
};


