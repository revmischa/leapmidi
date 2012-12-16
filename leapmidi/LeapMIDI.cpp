/*
 *  LeapMIDI.cpp
 *  LeapMIDI
 *
 *  Created by Mischa Spiegelmock on 11/28/12.
 *  Copyright (c) 2012 int80. All rights reserved.
 *
 */

#include "LeapMIDI.h"

const short MIDI_DEBUG = 1;

using namespace std;

namespace LeapMIDI {
    Listener::Listener() {
        initGestures();
    }
    
    Listener::~Listener() {
        // destroy each singleton
        for (vector<Gesture::Base *>::iterator it = gestureRecognizers.begin(); it != gestureRecognizers.end(); ++it) {
            delete *it;
        }
    }
    
    void Listener::initGestures() {
        // instantiate gesture recognizer singletons
//        Gesture::Ball *ballGesture = new Gesture::Ball();
//        gestureRecognizers.push_back(ballGesture);
        Gesture::Finger *fingerGesture = new Gesture::Finger();
        gestureRecognizers.push_back(fingerGesture);
    }

    void Listener::findControls(const Leap::Controller &controller) {
        // feed frames to recognizers
        for (vector<Gesture::Base *>::iterator it = gestureRecognizers.begin(); it != gestureRecognizers.end(); ++it) {
            // get controls recognized from gestures
            Gesture::Base *gesture = *it;
            vector<LeapMIDI::Control::Base *> recognizedControls = gesture->recognizedControls(controller);
            
            // call gesture recognized callback
            this->onGestureRecognized(controller, *gesture);
            
            for (vector<LeapMIDI::Control::Base *>::iterator ctl = recognizedControls.begin(); ctl != recognizedControls.end(); ++ctl) {
                Control::Base *control = *ctl;
                
                // skip control recognition failures
                if (control->controlIndex() == MIDI_CONTROL_UNRECOGNIZED)
                    continue;
                
                // call control updated callback
                this->onControlUpdated(controller, *gesture, *control);
                
                // done with control, it can go away now
                delete *ctl;
            }
        }
    }
    
    void Listener::onGestureRecognized(const Leap::Controller &controller, Gesture::Base &gesture) {
    }
    
    void Listener::onControlUpdated(const Leap::Controller &controller, Gesture::Base &gesture, Control::Base &control) {
        midi_control_value val = control.mappedValue();
        midi_control_index idx = control.controlIndex();
        
        if (MIDI_DEBUG) {
            cout << "recognized control index " << idx
            << " (" << control.description() << ")"
            << ", raw value: "
            << control.rawValue() << " mapped value: " << val << endl;
        }

    }

    void Listener::onInit(const Leap::Controller &controller) {
        cout << "Initialized" << endl;
    }

    void Listener::onConnect(const Leap::Controller &controller) {
        cout << "Connected" << endl;
    }

    void Listener::onDisconnect(const Leap::Controller &controller) {
        cout << "Disconnected" << endl;
    }

    void Listener::onFrame(const Leap::Controller &controller) {
        findControls(controller);

        return;
        
        // get most recent frame
        Leap::Frame frame = controller.frame();
                
        const std::vector<Leap::Hand>& hands = frame.hands();
        if (hands.empty()) return;
        
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
}
