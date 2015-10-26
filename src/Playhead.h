//
//  Playhead.h
//  TouchSequencer
//
//  Created by Doron Roberts-Kedes on 10/26/15.
//
//

#ifndef __TouchSequencer__Playhead__
#define __TouchSequencer__Playhead__

#include <stdio.h>
#include "ofMain.h"

using namespace std;

class Playhead
{
public:
    Playhead(ofVec2f position, ofVec2f direction);
    ~Playhead();
    void draw();
    void update();
    
    // Returns the distance (projection error) from ofPoint p to the visible line of the playhead
    // Points to the left of the playhead will have a negative projection error, points to the right of the playhead will have a positive projection error.
    float getProjectionError(ofPoint p);
    
private:
    // A vector with magnitude corresponding to the speed of the playhead, elements corresponding to direction
    ofVec2f _direction;
    
    // A point that lies along the vector that is orthogonal to the direction
    ofVec2f _position;

};

#endif /* defined(__TouchSequencer__Playhead__) */
