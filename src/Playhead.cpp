//
//  Playhead.cpp
//  TouchSequencer
//
//  Created by Doron Roberts-Kedes on 10/26/15.
//
//

#include "Playhead.h"

Playhead::Playhead(ofVec2f position, ofVec2f direction)
{
    _position.set(position);
    _direction.set(direction);
}


void Playhead::update()
{
    ofVec2f bottomRightCorner = ofVec2f(ofGetWindowWidth(), ofGetWindowHeight());
    
    _position = _position + _direction;
    
    // wraparound the position when the visible line has passed both the bottomright and topright corners
}

void Playhead::draw()
{
    ofCircle(_position, 25.0);
    // update visible line
    ofVec2f ortho = _direction.getPerpendicular();
    float maxLength = 1000;
    ofPoint top = _position - ortho.getNormalized().getScaled(maxLength);
    ofPoint bottom = _position + ortho.getNormalized().getScaled(maxLength);
    ofPolyline visibleLine;
    visibleLine.addVertex(top);
    visibleLine.addVertex(bottom);
    visibleLine.close();
    visibleLine.draw();
}

float Playhead::getProjectionError(ofPoint p)
{
    ofVec2f centeredP = p - _position;
    ofVec2f normalizedDirection = _direction.getNormalized();
    return centeredP.dot(normalizedDirection);
}

