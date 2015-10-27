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

ofVec2f Node::getWindowPosition()
{
    return ofVec2f(_position);
}

ofVec2f Node::getRelativePosition()
{
    float x = _position.x;
    float y = _position.y;
    float relX = x / ofGetWindowWidth();
    float relY = y / ofGetWindowHeight();
    return ofVec2f(relX, relY);
}

void Node::bang()
{
    numBangs = numBangs + 1;
    cerr << "bang! " << numBangs << " " << _position << endl;
}