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
#include "Node.h"

using namespace std;

class Playhead
{
public:
    Playhead(ofVec2f position, ofVec2f direction);
    ~Playhead();
    void draw();
    void update(float speedScale);
//    void scaleSpeed(float scale);
    
    // Returns the distance (projection error) from ofPoint p to the visible line of the playhead
    // Points that lie in the direction of the playhead will have a positive distance.
    // Points that lie behind the direction of the playhead will have a negative distance.
    float getDistance(ofPoint p);
    
    float getDistance(Node* n);
    
    // A vector with magnitude corresponding to the speed of the playhead, elements corresponding to direction
    ofVec2f _direction;
    
private:
//    // A vector with magnitude corresponding to the speed of the playhead, elements corresponding to direction
//    ofVec2f _direction;
    
    // A point that lies along the vector that is orthogonal to the direction
    ofVec2f _position;

};

#endif /* defined(__TouchSequencer__Playhead__) */
