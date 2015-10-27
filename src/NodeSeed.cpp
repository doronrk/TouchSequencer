//
//  NodeSeed.cpp
//  TouchSequencer
//
//  Created by Doron Roberts-Kedes on 10/26/15.
//
//

#include "NodeSeed.h"

NodeSeed::NodeSeed(ofVec2f initPos)
{
    _position.set(initPos);
}

void NodeSeed::updatePosition(ofVec2f newPosition)
{
    _position.set(newPosition);
}

Node* NodeSeed::toNode()
{
    return new Node(_position);
}