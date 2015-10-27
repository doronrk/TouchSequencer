//
//  NodeSeed.h
//  TouchSequencer
//
//  Created by Doron Roberts-Kedes on 10/26/15.
//
//

#ifndef __TouchSequencer__NodeSeed__
#define __TouchSequencer__NodeSeed__

#include <stdio.h>
#include "ofMain.h"
#include "Node.h"

class NodeSeed
{
public:
    NodeSeed(ofVec2f initPosition);
    
    Node* toNode();
    void updatePosition(ofVec2f newPosition);
    
private:
    ofVec2f _position;
};

#endif /* defined(__TouchSequencer__NodeSeed__) */
