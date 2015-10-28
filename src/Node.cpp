//
//  Node.cpp
//  TouchSequencer
//
//  Created by Doron Roberts-Kedes on 10/26/15.
//
//

#include "Node.h"

Node::Node(ofVec2f position)
{
    _position = position;
    numBangs = 0;
    baseWidth = 100;
    baseHeight = 100;
    oscillationBaseSpeed = ofRandom(1.3, 2.0);
    oscillationExtraSpeed = 0;
    oscillationWidthPhase = ofRandom(0.0, 2 * pi);
//    oscillationHeightPhase = ofRandom(0.0, 2 * pi);
    oscillationWidthDelta = ofRandom(4.0, 7.5);
    oscillationHeightDelta = ofRandom(4.0, 7.5);
    innerBrightness = 0.0;
    brightnessDecayRate = 1.08;
    oscillationSpeedDecayRate = 1.02;
}

void Node::update(float elapsedTimeS)
{
    float oscillationSpeed = oscillationBaseSpeed + oscillationExtraSpeed;
    float widthScale = std::sin(oscillationSpeed*elapsedTimeS + oscillationWidthPhase);
    float heightScale = std::sin(oscillationSpeed*elapsedTimeS - pi - .2 + oscillationWidthPhase);
    drawWidthOuter = baseWidth + widthScale * oscillationWidthDelta;
    drawHeightOuter = baseHeight + heightScale * oscillationHeightDelta;
    float outerInnerRatio = 1.6;
    drawWidthInner = baseWidth/outerInnerRatio - widthScale / outerInnerRatio * oscillationWidthDelta;
    drawHeightInner = baseHeight/outerInnerRatio - heightScale / outerInnerRatio * oscillationHeightDelta;
    innerBrightness = innerBrightness / brightnessDecayRate;
    oscillationExtraSpeed = oscillationExtraSpeed / oscillationSpeedDecayRate;
}


void Node::draw(ofImage inner, ofImage outer)
{
    float xTopLeftOuter = _position.x - (drawWidthOuter / 2.0);
    float yTopLeftOuter = _position.y - (drawHeightOuter / 2.0);
    float xTopLeftInner = _position.x - (drawWidthInner / 2.0);
    float yTopLeftInner = _position.y - (drawHeightInner / 2.0);
    outer.draw(ofVec2f(xTopLeftOuter, yTopLeftOuter), drawWidthOuter, drawHeightOuter);
    
    unsigned char * pix = inner.getPixels();
    
    for(int i = 0; i < inner.getWidth() * inner.getHeight() * 4; i++){
        if (i % 4 < 2)
        {
            if (pix[i] > 25)
            {
                //this makes sure it doesn't go over 255 as it will wrap to 0 otherwise.
                pix[i] += MIN(innerBrightness, 255-pix[i]);
            }
        }
    }
    
    inner.update(); //refresh the image from the pixels.
    inner.draw(ofVec2f(xTopLeftInner, yTopLeftInner), drawWidthInner, drawHeightInner);
}

void Node::draw()
{
    ofCircle(_position, 25.0);
}

ofVec2f Node::getWindowPosition()
{
    return ofVec2f(_position);
}

ofVec2f Node::getRelativePosition()
{
    float x = _position.x;
    float y = _position.y;
    float relX = x / ofGetWindowWidth();
    float relY = y / ofGetWindowHeight();
    return ofVec2f(relX, relY);
}

void Node::bang()
{
    numBangs = numBangs + 1;
    float brightnessCeiling = 255;
    float oscillationSpeedCeiling = 2.5;
    innerBrightness = innerBrightness + (brightnessCeiling - innerBrightness) / 2;
    oscillationExtraSpeed = oscillationExtraSpeed + (oscillationSpeedCeiling - oscillationExtraSpeed) / 2;
//    cerr << "bang! " << numBangs << " " << _position << endl;
}