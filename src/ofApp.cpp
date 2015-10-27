#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    touchManager = new TouchManager();
    
    // settings
    playheadSpeedScale = .4;
    createMode = NODE;
//    ofSetFrameRate(1);
}

//--------------------------------------------------------------
void ofApp::update()
{
    for (std::vector<Playhead*>::iterator it = playheads.begin(); it != playheads.end(); ++it)
    {
        Playhead* playhead = *it;
        playhead->update(playheadSpeedScale);
    }
    
    TOUCH_DATA touchData = touchManager->updateState();
    switch (createMode)
    {
        case PLAYHEAD:
            playheadCreateMode(touchData);
            break;
        case NODE:
            nodeCreateMode(touchData);
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofEnableSmoothing();
    ofSetBackgroundColor(0, 0, 0);
    
    for (std::vector<Playhead*>::iterator it = playheads.begin(); it != playheads.end(); ++it)
    {
        Playhead* playhead = *it;
        playhead->draw();
    }
    
    for (std::vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
    {
        Node* node = *it;
        node->draw();
    }
}

//--------------------------------------------------------------
void ofApp::playheadCreateMode(TOUCH_DATA data)
{
    // add playhead seeds for new touches
    for(std::vector<MTouch>::iterator it = data.newTouches.begin(); it != data.newTouches.end(); ++it)
    {
        MTouch newTouch = *it;
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
void ofApp::nodeCreateMode(TOUCH_DATA data)
{
    // add node seeds for new touches
    for(std::vector<MTouch>::iterator it = data.newTouches.begin(); it != data.newTouches.end(); ++it)
    {
        MTouch newTouch = *it;
        float x = newTouch.x;
        float y = newTouch.y;
        x = x * ofGetWindowWidth();
        y = y * ofGetWindowHeight();
        NodeSeed* newSeed = new NodeSeed(ofVec2f(x, y));
        nodeSeeds[newTouch.ID] = newSeed;
    }
    
    // update touch points to existing node seeds for held touches
    for(std::vector<MTouch>::iterator it = data.heldTouches.begin(); it != data.heldTouches.end(); ++it)
    {
        MTouch heldTouch = *it;
        float x = heldTouch.x;
        float y = heldTouch.y;
        x = x * ofGetWindowWidth();
        y = y * ofGetWindowHeight();
        int id = heldTouch.ID;
        std::map<int, NodeSeed*>::iterator pair = nodeSeeds.find(id);
        if (pair != nodeSeeds.end())
        {
            NodeSeed* seed = pair->second;
            seed->updatePosition(ofVec2f(x, y));
        }
    }
    
    // convert node seeds to nodes for released touches
    for(std::vector<int>::iterator it = data.releasedTouchIds.begin(); it != data.releasedTouchIds.end(); ++it)
    {
        int releasedId = *it;
        std::map<int, NodeSeed*>::iterator pair = nodeSeeds.find(releasedId);
        if (pair != nodeSeeds.end())
        {
            //            pair->first;
            NodeSeed* seed = pair->second;
            Node* newNode = seed->toNode();
            if (newNode != NULL)
            {
                nodes.push_back(newNode);
            }
            nodeSeeds.erase(releasedId);
            delete seed;
        }
    }
}


void ofApp::keyReleased(int key)
{
    if (key == OF_KEY_BACKSPACE || key == OF_KEY_DEL)
    {
        if (! playheads.empty())
        {
            playheads.pop_back();
        }
    } else if (key == OF_KEY_ESC)
    {
        exit();
    }
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    
}


//--------------------------------------------------------------
void ofApp::exit()
{
    ofExit();
}



