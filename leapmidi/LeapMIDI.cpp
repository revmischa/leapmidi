/*
 *  LeapMIDI.cpp
 *  LeapMIDI
 *
 *  Created by Mischa Spiegelmock on 11/28/12.
 *  Copyright (c) 2012 int80. All rights reserved.
 *
 */

#include "LeapMIDI.h"

const short MIDI_DEBUG = 0;

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
    }
}
