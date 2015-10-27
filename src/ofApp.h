#pragma once

#include "ofMain.h"
#include "Playhead.h"
#include "PlayheadSeed.h"
#include "Node.h"
#include "NodeSeed.h"
#include "TouchManager.h"

enum CREATE_MODE
{
    PLAYHEAD,
    NODE,
    CHILL
};


class ofApp : public ofBaseApp{
    std::vector<ofPoint> touches;

public:
    void setup();
    void update();
    void draw();


    void keyReleased(int key);
    void mousePressed(int x, int y, int button);

    void exit();

    
//    void windowResized(int w, int h);
//    void mouseReleased(int x, int y, int button);
//    void keyPressed(int key);
//    void mouseMoved(int x, int y );
//    void mouseDragged(int x, int y, int button);
//    void dragEvent(ofDragInfo dragInfo);
//    void gotMessage(ofMessage msg);
    
private:
    TouchManager* touchManager;
    std::map<int, PlayheadSeed*> playheadSeeds;
    std::vector<Playhead*> playheads;
    std::map<int, NodeSeed*> nodeSeeds;
    std::vector<Node*> nodes;
    // stores the distances from each playhead to each node
    std::map<Playhead*, std::map<Node*, float> > distances;
    
    
    // settings
    float playheadSpeedScale;
    CREATE_MODE createMode;
    
    // private methods
    void playheadCreateMode(TOUCH_DATA data);
    void nodeCreateMode(TOUCH_DATA data);
    void updateDistances();
    
    
};
