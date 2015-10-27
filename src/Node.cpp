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
}

void Node::draw()
{
    ofCircle(_position, 25.0);
}