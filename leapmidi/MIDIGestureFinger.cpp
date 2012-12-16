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
            
            size_t handCount = frame.hands().size();
            for (int i = 0; i < handCount; i++) {
                // gonna assume the user only has two hands. sometimes leap thinks otherwise.
                if (i > 1) break;

                Leap::Hand hand = frame.hands()[i];
                
                // we need at least one finger to make this work
                size_t fingerCount = hand.fingers().size();
                if (! fingerCount)
                    continue;
                
                // calculate average X/Y/Z coords
                double x=0, y=0, z=0;
                for (int fingerIndex = 0; fingerIndex < fingerCount; fingerIndex++) {
                    Leap::Finger finger = hand.fingers()[fingerIndex];
                    
                    x += finger.tip().position.x;
                    y += finger.tip().position.y;
                    z += finger.tip().position.z;
                }
                x /= fingerCount;
                y /= fingerCount;
                z /= fingerCount;
                
                
                // generate one finger position control per hand coordinate, determined by number of fingers
                LeapMIDI::Control::FingerPosition *fingerPosControlX = new LeapMIDI::Control::FingerPositionX(handCount, fingerCount, x);
                LeapMIDI::Control::FingerPosition *fingerPosControlY = new LeapMIDI::Control::FingerPositionY(handCount, fingerCount, y);
                LeapMIDI::Control::FingerPosition *fingerPosControlZ = new LeapMIDI::Control::FingerPositionZ(handCount, fingerCount, z);
                controls.push_back(fingerPosControlX);
                controls.push_back(fingerPosControlY);
                controls.push_back(fingerPosControlZ);
            }
            
            return controls;
        }
    }
}
