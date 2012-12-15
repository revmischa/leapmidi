//
//  MIDIGestureFinger.cpp
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/13/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#include "MIDIGestureFinger.h"

namespace LeapMIDI {
    namespace Gesture {
        std::vector<LeapMIDI::Control::Base *> Finger::recognizedControls(const Leap::Controller &controller) {
            Leap::Frame frame = controller.frame();
            
            // hands detected?
            if (! frame.hands().size())
                return MIDI_GESTURES_EMPTY;
            
            std::vector<LeapMIDI::Control::Base *> controls;
            
            for (int i = 0; i < frame.hands().size(); i++) {
                // gonna assume the user only has two hands. sometimes leap thinks otherwise.
                if (i > 1) break;

                Leap::Hand hand = frame.hands()[i];
                
                for (int fingerIndex = 0; fingerIndex < hand.fingers().size(); fingerIndex++) {
                    Leap::Finger finger = hand.fingers()[fingerIndex];
                    
                    double y = finger.tip().position.y;
                
                    LeapMIDI::Control::FingerPosition *fingerPosControl = new LeapMIDI::Control::FingerPosition(i, fingerIndex, y);
                    controls.push_back(fingerPosControl);
                }
            }
            
            return controls;
        }
    }
}
