#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//    pad = ofxMultiTouchPad();
    playhead = new Playhead(ofVec2f(2, 3), ofVec2f(1, 1));
    node = ofVec2f(300, 300);
}

//--------------------------------------------------------------
void ofApp::update()
{
    playhead->update();
}

void ofApp::manageTouch()
{
    /*
     Use the MTouch datatype for more information on touches
     */
    ofSetColor(255, 128, 0);
    std::vector<MTouch> mTouches = pad.getTouches();
    float scale = 100;
    for (std::vector<MTouch>::iterator touch=mTouches.begin(); touch!=mTouches.end(); ++touch)
    {
        float size = touch->size*scale;
        ofPushMatrix();
        ofTranslate(touch->x*ofGetWidth(), touch->y*ofGetHeight());
        ofRotate(touch->angle);
        ofEllipse(0, 0, size, size*.5);
        //        cerr << "id: " << touch->ID << endl;
        ofPopMatrix();
    }
    //    cerr << "end" << endl;
    
    /*
     Iterate over all touches as a vector of ofPoints Ð very simple datatype though...
     */
    ofPushMatrix();
    ofSetColor(255, 255, 255);
    pad.getTouchesAsOfPoints(&touches);
    ofPoint size = ofPoint(ofGetWidth(),ofGetHeight(),0);
    ofSetRectMode(OF_RECTMODE_CENTER);
    for (vector<ofPoint>::iterator touch = touches.begin(); touch!=touches.end(); ++touch) {
        ofRect((*touch)*size, 10, 10);
    }
    ofPopMatrix();
    
    string info = "Number of touches: "+ofToString(pad.getTouchCount(),0);
    ofDrawBitmapStringHighlight(info, 20, 20);
}


//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableSmoothing();
    ofSetBackgroundColor(0, 0, 0);
    playhead->draw();
    ofCircle(node, 25);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    float pe = playhead->getProjectionError(node);
    cerr << "pe: " << pe << endl;
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
