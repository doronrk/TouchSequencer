//
//  TouchManager.cpp
//  TouchSequencer
//
//  Created by Doron Roberts-Kedes on 10/26/15.
//
//

#include "TouchManager.h"

TouchManager::TouchManager()
{
    pad = ofxMultiTouchPad();
}

TOUCH_DATA TouchManager::updateState()
{
    std::vector<MTouch> touches = pad.getTouches();
    TOUCH_DATA data;
    std::set<int> newKnownTouches;
    for(std::vector<MTouch>::iterator it = touches.begin(); it != touches.end(); ++it)
    {
        MTouch touch = *it;
        if (*knownTouches.find(touch.ID))
        {
            data.heldTouches.push_back(touch);
        } else
        {
            data.newTouches.push_back(touch);
        }
        newKnownTouches.insert(touch.ID);
        knownTouches.erase(touch.ID);
    }
    
    for(std::set<int>::iterator it = knownTouches.begin(); it != knownTouches.end(); ++it)
    {
        int removedId = *it;
        data.releasedTouchIds.push_back(removedId);
    }
    knownTouches = newKnownTouches;
    return data;
}
