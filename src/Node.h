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
    
    void draw();
    
private:
    ofVec2f _position;
};

#endif /* defined(__TouchSequencer__Node__) */
