#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    touchManager = new TouchManager();
    ofVec2f initialPos = ofVec2f(200, 200);
    ofVec2f nextPos = ofVec2f(204, 200);
    PlayheadSeed* seed = new PlayheadSeed(initialPos);
    seed->addTouchPosition(nextPos);
    playhead = seed->toPlayhead();
    node = ofVec2f(300, 300);
//    ofSetFrameRate(1);
}

//--------------------------------------------------------------
void ofApp::update()
{
    playhead->update();
    TOUCH_DATA touchData = touchManager->updateState();
    playheadMode(touchData);
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofEnableSmoothing();
    ofSetBackgroundColor(0, 0, 0);
    playhead->draw();
    
    for (std::vector<Playhead*>::iterator it = playheads.begin(); it != playheads.end(); ++it)
    {
        Playhead* playheadToDraw = *it;
        playheadToDraw->draw();
    }
    
    ofCircle(node, 25);
}

//--------------------------------------------------------------
void ofApp::playheadMode(TOUCH_DATA data)
{
    // add playhead seeds for new touches
    for(std::vector<MTouch>::iterator it = data.newTouches.begin(); it != data.newTouches.end(); ++it)
    {
        MTouch newTouch = *it;
        cerr << "newTouch.ID: " << newTouch.ID << endl;
        float x = newTouch.x;
        float y = newTouch.y;
        x = x * ofGetWindowWidth();
        y = y * ofGetWindowHeight();
        PlayheadSeed* newSeed = new PlayheadSeed(ofVec2f(x, y));
        playheadSeeds[newTouch.ID] = newSeed;
    }
    
    // add new touch points to existing playhead seeds for held touches
    for(std::vector<MTouch>::iterator it = data.heldTouches.begin(); it != data.heldTouches.end(); ++it)
    {
        MTouch heldTouch = *it;
        float x = heldTouch.x;
        float y = heldTouch.y;
        x = x * ofGetWindowWidth();
        y = y * ofGetWindowHeight();
        int id = heldTouch.ID;
        std::map<int, PlayheadSeed*>::iterator pair = playheadSeeds.find(id);
        if (pair != playheadSeeds.end())
        {
            PlayheadSeed* seed = pair->second;
            seed->addTouchPosition(ofVec2f(x, y));
        }
    }
    
    
    // convert playhead seeds to playheads for released touches
    for(std::vector<int>::iterator it = data.releasedTouchIds.begin(); it != data.releasedTouchIds.end(); ++it)
    {
        int releasedId = *it;
        std::map<int, PlayheadSeed*>::iterator pair = playheadSeeds.find(releasedId);
        if (pair != playheadSeeds.end())
        {
//            pair->first;
            PlayheadSeed* seed = pair->second;
            Playhead* newPlayhead = seed->toPlayhead();
            if (newPlayhead != NULL)
            {
                playheads.push_back(newPlayhead);
            }
            playheadSeeds.erase(releasedId);
            delete seed;
        }
    }
    
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//void ofApp::manageTouch()
//{
    /*
     Use the MTouch datatype for more information on touches
    //     */
    //    ofSetColor(255, 128, 0);
    //    std::vector<MTouch> mTouches = pad.getTouches();
    //    float scale = 100;
    //    for (std::vector<MTouch>::iterator touch=mTouches.begin(); touch!=mTouches.end(); ++touch)
    //    {
    //        float size = touch->size*scale;
    //        ofPushMatrix();
    //        ofTranslate(touch->x*ofGetWidth(), touch->y*ofGetHeight());
    //        ofRotate(touch->angle);
    //        ofEllipse(0, 0, size, size*.5);
    //        //        cerr << "id: " << touch->ID << endl;
    //        ofPopMatrix();
    //    }
    //    //    cerr << "end" << endl;
    //
    //    /*
    //     Iterate over all touches as a vector of ofPoints Ð very simple datatype though...
    //     */
    //    ofPushMatrix();
    //    ofSetColor(255, 255, 255);
    //    pad.getTouchesAsOfPoints(&touches);
    //    ofPoint size = ofPoint(ofGetWidth(),ofGetHeight(),0);
    //    ofSetRectMode(OF_RECTMODE_CENTER);
    //    for (vector<ofPoint>::iterator touch = touches.begin(); touch!=touches.end(); ++touch) {
    //        ofRect((*touch)*size, 10, 10);
    //    }
    //    ofPopMatrix();
    //
    //    string info = "Number of touches: "+ofToString(pad.getTouchCount(),0);
    //    ofDrawBitmapStringHighlight(info, 20, 20);
//}

