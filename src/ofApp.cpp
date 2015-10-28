#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(0, 0, 0);
    
    // initialization and setup
    touchManager = new TouchManager();
    sender.setup(OSC_HOST, OSC_PORT);
//    nodeImg.loadImage("images/blue-eye.png");
    nodeImgOuter.loadImage("images/blue-node.png");
    nodeImgInner.loadImage("images/inner-blur.png");
    // settings
    playheadSpeedScale = .4;
    createMode = NODE;
}

//--------------------------------------------------------------
void ofApp::update()
{
    float elapsedTimeS = ofGetElapsedTimef();
    for (std::vector<Playhead*>::iterator it = playheads.begin(); it != playheads.end(); ++it)
    {
        Playhead* playhead = *it;
        playhead->update(playheadSpeedScale);
    }
    
    for (std::vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
    {
        Node* node = *it;
        node->update(elapsedTimeS);
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
        case CHILL:
            // just chill ... |-_-| ...
            break;
        default:
            break;
    }
    
    updateDistances();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofEnableSmoothing();

    for (std::vector<Playhead*>::iterator it = playheads.begin(); it != playheads.end(); ++it)
    {
        Playhead* playhead = *it;
        playhead->draw();
    }
    
    for (std::vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
    {
        Node* node = *it;
        node->draw(nodeImgInner, nodeImgOuter);
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


void ofApp::updateDistances()
{
    for (std::vector<Playhead*>::iterator itP = playheads.begin(); itP != playheads.end(); ++itP)
    {
        for (std::vector<Node*>::iterator itN = nodes.begin(); itN != nodes.end(); ++ itN)
        {
            Playhead* playhead = *itP;
            Node* node = *itN;
            float newDistance = playhead->getDistance(node);
            
            std::map<Playhead* , std::map<Node*, float> >::iterator playheadPair = distances.find(playhead);
            // this playhead is already in the map
            if (playheadPair != distances.end())
            {
                std::map<Node*, float> nodeDistances = playheadPair->second;
                std::map<Node*, float>::iterator nodePair = nodeDistances.find(node);
                // this node is already in the map
                if (nodePair != nodeDistances.end())
                {
                    float oldDistance = nodePair->second;
                    // the playhead has crossed the node if these conditions are met
                    if ((oldDistance < 0.0 && newDistance >= 0.0) ||
                        (oldDistance > 0.0 && newDistance <= 0.0))
                    {
                        // the delta is used to avoid banging the nodes when the playheads wraparound the screen
                        float delta = std::abs(oldDistance - newDistance);
                        if (delta <  100)
                        {
                            ofxOscMessage m;
                            m.setAddress("/node/bang");
                            ofVec2f relPos = node->getRelativePosition();
                            m.addFloatArg(relPos.x);
                            m.addFloatArg(relPos.y);
                            sender.sendMessage(m);
                            node->bang();
                        }
                    }
                    
                }
                // this node is not in the map yet
                else
                {
                    nodeDistances[node] = newDistance;
                }
            }
            distances[playhead][node] = newDistance;
        }
    }
}

void ofApp::keyReleased(int key)
{
    if (key == OF_KEY_BACKSPACE || key == OF_KEY_DEL)
    {
        switch (createMode)
        {
            case PLAYHEAD:
                if (! playheads.empty())
                {
                    playheads.pop_back();
                }
                break;
            case NODE:
                if (! nodes.empty())
                {
                    nodes.pop_back();
                }
                break;
            case CHILL:
                // just chill
                break;
            default:
                break;
        }

    } else if (key == OF_KEY_ESC)
    {
        exit();
    } else if (key == 'p')
    {
        createMode = PLAYHEAD;
    } else if (key == 'n')
    {
        createMode = NODE;
    } else if (key == 'c')
    {
        createMode = CHILL;
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

