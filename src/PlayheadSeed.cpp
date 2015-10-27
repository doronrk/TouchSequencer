//
//  PlayheadSeed.cpp
//  TouchSequencer
//
//  Created by Doron Roberts-Kedes on 10/26/15.
//
//

#include "PlayheadSeed.h"

PlayheadSeed::PlayheadSeed(ofVec2f initialPosition)
{
    touchPoints.push_back(initialPosition);
}

PlayheadSeed::~PlayheadSeed()
{
    
}


void PlayheadSeed::addTouchPosition(ofVec2f position)
{
    touchPoints.push_back(position);
}

Playhead* PlayheadSeed::toPlayhead()
{
    if (touchPoints.size() < 2)
    {
        return NULL;
    }
    ofVec2f position = touchPoints.back();
    ofVec2f direction = ofVec2f(0, 0);
    for(std::vector<ofVec2f>::iterator it = touchPoints.begin(); it != touchPoints.end(); ++it) {
        ofVec2f touch = *it;
        std::vector<ofVec2f>::iterator next = it + 1;
        if (next != touchPoints.end())
        {
            ofVec2f nextTouch = *next;
            direction += nextTouch - touch;
        }
    }
    // divide by num touch points so that the duration of the touch doesn't impact the magnitude of the direction
    // the average distance between touch points should determine the magnitude of the direction
    direction = direction / (float) touchPoints.size();
    return new Playhead(position, direction);
}