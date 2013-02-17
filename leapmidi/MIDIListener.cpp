/*
 *  MIDIListener.cpp
 *  LeapMIDI
 *
 *  Created by Mischa Spiegelmock on 11/28/12.
 *  Copyright (c) 2012 int80. All rights reserved.
 *
 */

#include "MIDIListener.h"

using namespace std;

namespace leapmidi {
    
Listener::Listener() {
    currentProgram = NULL;
}

void Listener::onInit(const Leap::Controller& controller) {
    std::cout << "Leap device initialized\n";
}

void Listener::onConnect(const Leap::Controller& controller) {
    std::cout << "Leap device connected\n";
}

void Listener::onDisconnect(const Leap::Controller& controller) {
    std::cout << "Leap device disconnected\n";
}

void Listener::onFrame(const Leap::Controller &controller) {
    if (! currentProgram) return;
}

void Listener::onGestureRecognized(const Leap::Controller &controller, GesturePtr gesture) {
    cout << "gesture recognized\n";
    
    if (currentProgram)
        currentProgram->onGestureRecognized(controller, gesture);
}

void Listener::onControlUpdated(const Leap::Controller &controller, GesturePtr gesture, ControlPtr control) {
    // call superclass method
    cout << "control updated\n";
    
    if (currentProgram)
        currentProgram->onControlUpdated(controller, gesture, control);
}
    
}
