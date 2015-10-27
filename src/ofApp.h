#pragma once

#include "ofMain.h"
#include "Playhead.h"
#include "PlayheadSeed.h"
#include "TouchManager.h"


class ofApp : public ofBaseApp{
    std::vector<ofPoint> touches;

public:
    void setup();
    void update();
    void draw();


    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
private:
    TouchManager* touchManager;
    ofVec2f node;
    std::map<int, PlayheadSeed*> playheadSeeds;
    std::vector<Playhead*> playheads;
    
    void playheadMode(TOUCH_DATA data);
    
//    void manageTouch();
    
};
