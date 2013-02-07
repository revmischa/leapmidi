//
//  leapmidi
//
//  Created by Mischa Spiegelmock on 1/5/13.
//  Copyright (c) 2013 int80. All rights reserved.
//

// Program to send live MIDI control messages

#include <stdio.h>
#include "MIDIProgramControl.h"

const short MIDI_DEBUG = 0;

using namespace std;

namespace LeapMIDI {
    namespace Program {
        Control::Control() {
            initGestures();
        }
        
        Control::~Control() {
            // destroy each singleton
            for (vector<Gesture::Base *>::iterator it = gestureRecognizers.begin(); it != gestureRecognizers.end(); ++it) {
                delete *it;
            }
        }
        
        void Control::initGestures() {
            // instantiate gesture recognizer singletons
            //        Gesture::Ball *ballGesture = new Gesture::Ball();
            //        gestureRecognizers.push_back(ballGesture);
            Gesture::Finger *fingerGesture = new Gesture::Finger();
            gestureRecognizers.push_back(fingerGesture);
        }
                
        void Control::onGestureRecognized(const Leap::Controller &controller, Gesture::Base &gesture) {
        }
        
        void Control::onControlUpdated(const Leap::Controller &controller, Gesture::Base &gesture, LeapMIDI::Control::Base &control) {
            midi_control_value val = control.mappedValue();
            midi_control_index idx = control.controlIndex();
            
            if (MIDI_DEBUG) {
                cout << "recognized control index " << idx
                << " (" << control.description() << ")"
                << ", raw value: "
                << control.rawValue() << " mapped value: " << val << endl;
            }
            
        }
    }
}

