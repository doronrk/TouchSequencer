//
//  Node.h
//  TouchSequencer
//
//  Created by Doron Roberts-Kedes on 10/26/15.
//
//

#ifndef __TouchSequencer__Node__
#define __TouchSequencer__Node__

#include <stdio.h>
#include "ofMain.h"

class Node
{
public:
    
    Node(ofVec2f position);
    ~Node();
    
    void update(float elapsedTimeS);
    void draw();
    void draw(ofImage inner, ofImage outer);
    ofVec2f getWindowPosition();
    ofVec2f getRelativePosition();
    void bang();
    
private:
    ofVec2f _position;
    int numBangs;
    float baseHeight;
    float baseWidth;
    float drawHeightOuter;
    float drawWidthOuter;
    float drawHeightInner;
    float drawWidthInner;
    float oscillationBaseSpeed;
    float oscillationExtraSpeed;
    float oscillationWidthPhase;
//    float oscillationHeightPhase;
    float oscillationWidthDelta;
    float oscillationHeightDelta;
    float innerBrightness;
    float brightnessDecayRate;
    float oscillationSpeedDecayRate;
};

#endif /* defined(__TouchSequencer__Node__) */
