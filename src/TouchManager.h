//
//  TouchManager.h
//  TouchSequencer
//
//  Created by Doron Roberts-Kedes on 10/26/15.
//
//

#ifndef __TouchSequencer__TouchManager__
#define __TouchSequencer__TouchManager__

#include <stdio.h>
#include "ofMain.h"
#include "ofxMultiTouchPad.h"
#include "ofxMultiTouchPad.h"

struct TOUCH_DATA
{
    std::vector<MTouch> heldTouches;
    std::vector<int> releasedTouchIds;
    std::vector<MTouch> newTouches;
};

class TouchManager
{
public:
    TouchManager();
    ~TouchManager();
    
    TOUCH_DATA updateState();
    
private:
    ofxMultiTouchPad pad;
    std::set<int> knownTouches;
};


#endif /* defined(__TouchSequencer__TouchManager__) */
