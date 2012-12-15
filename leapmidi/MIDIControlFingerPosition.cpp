//
//  MIDIControlFingerPosition.cpp
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/13/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#include "MIDIControlFingerPosition.h"

namespace LeapMIDI {
    namespace Control {
        const midi_control_index FingerPosition::controlIndex() {
            if (fingerIndex() == 0 && handIndex() == 0) return FINGER_1_HAND_1_Y;
            if (fingerIndex() == 1 && handIndex() == 0) return FINGER_2_HAND_1_Y;
            //....
            
            
            std::cerr << "Too many hands detected for finger position control\n";
            return NONE;
        }
    }
}
