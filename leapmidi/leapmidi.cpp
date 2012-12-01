/*
 *  leapmidi.cpp
 *  leapmidi
 *
 *  Created by Mischa Spiegelmock on 11/28/12.
 *  Copyright (c) 2012 int80. All rights reserved.
 *
 */

#include <iostream>
#include <math.h>
#include "leapmidi.h"

leapmidi::listener::listener() {
    smoothing = lm_default_smoothing;
    frames = new std::deque<Leap::Frame *>;
    std::cout << "leapmidi constructed, using frame window size " << smoothing << "\n";
}

void leapmidi::listener::set_smoothing(unsigned int window) {
    smoothing = window;
}

void leapmidi::listener::onInit(const Leap::Controller& controller) {
    std::cout << "Initialized" << std::endl;
}

void leapmidi::listener::onConnect(const Leap::Controller& controller) {
    std::cout << "Connected" << std::endl;
}

void leapmidi::listener::onDisconnect(const Leap::Controller& controller) {
    std::cout << "Disconnected" << std::endl;
}

void leapmidi::listener::onFrame(const Leap::Controller& controller) {
    // get most recent frame
    const Leap::Frame frame = controller.frame();
    
    // add frame to frame history buffer
    
    
    
    const std::vector<Leap::Hand>& hands = frame.hands();
    const size_t numHands = hands.size();
    std::cout << "Frame id: " << frame.id()
    << ", timestamp: " << frame.timestamp()
    << ", hands: " << numHands << std::endl;
    
    if (numHands >= 1) {
        // Get the first hand
        const Leap::Hand& hand = hands[0];
        
        // Check if the hand has any fingers
        const std::vector<Leap::Finger>& fingers = hand.fingers();
        const size_t numFingers = fingers.size();
        if (numFingers >= 1) {
            // Calculate the hand's average finger tip position
            Leap::Vector pos(0, 0, 0);
            for (size_t i = 0; i < numFingers; ++i) {
                const Leap::Finger& finger = fingers[i];
                const Leap::Ray& tip = finger.tip();
                pos.x += tip.position.x;
                pos.y += tip.position.y;
                pos.z += tip.position.z;
            }
            pos = Leap::Vector(pos.x/numFingers, pos.y/numFingers, pos.z/numFingers);
            std::cout << "Hand has " << numFingers << " fingers with average tip position"
            << " (" << pos.x << ", " << pos.y << ", " << pos.z << ")" << std::endl;
        }
        
        // Check if the hand has a palm
        const Leap::Ray* palmRay = hand.palm();
        if (palmRay != NULL) {
            // Get the palm position and wrist direction
            const Leap::Vector palm = palmRay->position;
            const Leap::Vector wrist = palmRay->direction;
            std::cout << "Palm position: ("
            << palm.x << ", " << palm.y << ", " << palm.z << ")" << std::endl;
            
            // Check if the hand has a normal vector
            const Leap::Vector* normal = hand.normal();
            if (normal != NULL) {
                // Calculate the hand's pitch, roll, and yaw angles
                double pitchAngle = -atan2(normal->z, normal->y) * 180/M_PI + 180;
                double rollAngle = -atan2(normal->x, normal->y) * 180/M_PI + 180;
                double yawAngle = atan2(wrist.z, wrist.x) * 180/M_PI - 90;
                // Ensure the angles are between -180 and +180 degrees
                if (pitchAngle > 180) pitchAngle -= 360;
                if (rollAngle > 180) rollAngle -= 360;
                if (yawAngle > 180) yawAngle -= 360;
                std::cout << "Pitch: " << pitchAngle << " degrees,  "
                << "roll: " << rollAngle << " degrees,  "
                << "yaw: " << yawAngle << " degrees" << std::endl;
            }
        }
        
        // Check if the hand has a ball
        const Leap::Ball* ball = hand.ball();
        if (ball != NULL) {
            std::cout << "Hand curvature radius: " << ball->radius << " mm" << std::endl;
        }
    }
}
