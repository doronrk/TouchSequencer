//
//  PlayheadSeed.h
//  TouchSequencer
//
//  Created by Doron Roberts-Kedes on 10/26/15.
//
//

#ifndef __TouchSequencer__PlayheadSeed__
#define __TouchSequencer__PlayheadSeed__

#include <stdio.h>
#include "ofMain.h"
#include "Playhead.h"

class PlayheadSeed
{
public:
    PlayheadSeed(ofVec2f initialPosition);
    ~PlayheadSeed();
    
    void addTouchPosition(ofVec2f position);
    
    /* Creates a playhead with position at the most recent touch position
     and with direction equal to the vector sum of the touches
     */
    Playhead* toPlayhead();
    
private:
    vector<ofVec2f> touchPoints;
};

#endif /* defined(__TouchSequencer__PlayheadSeed__) */
