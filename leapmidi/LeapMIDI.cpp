/*
 *  LeapMIDI.cpp
 *  LeapMIDI
 *
 *  Created by Mischa Spiegelmock on 11/28/12.
 *  Copyright (c) 2012 int80. All rights reserved.
 *
 */

#include "LeapMIDI.h"
#include "MIDIProgramControl.h"

using namespace std;

namespace LeapMIDI {
    Listener::Listener() {
        currentProgram = new LeapMIDI::Program::Control();
    }
    
    void Listener::onInit(const Leap::Controller& controller) {
        std::cout << "Leap device initialized\n";
    }
    
    void LeapMIDI::Listener::onConnect(const Leap::Controller& controller) {
        std::cout << "Leap device connected\n";
    }
    
    void LeapMIDI::Listener::onDisconnect(const Leap::Controller& controller) {
        std::cout << "Leap device disconnected\n";
    }
    
    void LeapMIDI::Listener::onFrame(const Leap::Controller &controller) {
        currentProgram->findControls(controller);
    }
    
    void Listener::onGestureRecognized(const Leap::Controller &controller, LeapMIDI::Gesture::Base &gesture) {
        cout << "gesture recognized\n";
        currentProgram->onGestureRecognized(controller, gesture);
    }
    
    void Listener::onControlUpdated(const Leap::Controller &controller, LeapMIDI::Gesture::Base &gesture, LeapMIDI::Control::Base &control) {
        // call superclass method
        cout << "control updated\n";
        currentProgram->onControlUpdated(controller, gesture, control);
    }
}
