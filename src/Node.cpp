//
//  Node.cpp
//  TouchSequencer
//
//  Created by Doron Roberts-Kedes on 10/26/15.
//
//

#include "Node.h"

Node::Node(ofVec2f position)
{
    _position = position;
    numBangs = 0;
}

void Node::draw()
{
    ofCircle(_position, 25.0);
}

ofVec2f Node::getPosition()
{
    return ofVec2f(_position);
}

void Node::bang()
{
    numBangs = numBangs + 1;
    cerr << "bang! " << numBangs << " " << _position << endl;
}