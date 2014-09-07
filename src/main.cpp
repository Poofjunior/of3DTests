#include "ofMain.h"
#include "ofApp.h"
#include <cstdlib>

//========================================================================
int main( ){

// bulk of the top-level code is in the update() and draw() member functions
// of ofApp.cpp

    ofApp* myApp =  new ofApp();
    ofSetupOpenGL(myApp->windowX_, myApp->windowY_, 
                  OF_WINDOW); 

    ofRunApp( myApp);
    
    delete myApp;

    // ofApp is deleted on exit.
    std::exit(2);

}
