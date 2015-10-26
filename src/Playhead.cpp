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
    _position = _position + _direction;
    
    // wraparound the position when the playhead has passed all 4 corners of the window
    // the playhead should wrap to the corner opposite of the most recently passed window corner
    ofVec2f topLeftCorner = ofVec2f(0, 0);
    ofVec2f bottomLeftCorner = ofVec2f(0, ofGetWindowHeight());
    ofVec2f topRightCorner = ofVec2f(ofGetWindowWidth(), 0);
    ofVec2f bottomRightCorner = ofVec2f(ofGetWindowWidth(), ofGetWindowHeight());

    float distToTopLeftCorner = getDistance(topLeftCorner);
    float distToBottomLeftCorner = getDistance(bottomLeftCorner);
    float distToTopRightCorner = getDistance(topRightCorner);
    float distToBottomRightCorner = getDistance(bottomRightCorner);
    
    const float arr[] = {distToTopLeftCorner,distToBottomLeftCorner,distToTopRightCorner,distToBottomRightCorner};
    
    float maxDist = *std::max_element(arr, arr + 4);
    if (maxDist <= 0)
    {
        if (distToTopLeftCorner == maxDist)
        {
            _position.set(bottomRightCorner);
        } else if (distToBottomLeftCorner == maxDist)
        {
            _position.set(topRightCorner);
        }
        else if (distToTopRightCorner == maxDist)
        {
            _position.set(bottomLeftCorner);
        } else
        {
            _position.set(topLeftCorner);
        }
    }
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

float Playhead::getDistance(ofPoint p)
{
    ofVec2f centeredP = p - _position;
    ofVec2f normalizedDirection = _direction.getNormalized();
    return centeredP.dot(normalizedDirection);
}

