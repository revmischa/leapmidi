//
//  MIDITypes.h
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/5/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#ifndef leapmidi_MIDITypes_h
#define leapmidi_MIDITypes_h

namespace LeapMIDI {
    typedef double midi_control_value_raw;
    typedef unsigned short midi_control_value;
    typedef unsigned short midi_bodypart_index;

    // MIDI control number offsets
    enum midi_control_index {
        MIDI_CONTROL_UNRECOGNIZED = 0,
        
        BALL_RADIUS_HAND_1 = 1,
        BALL_RADIUS_HAND_2,
        
        PALM_HAND_1_X,
        PALM_HAND_1_Y,
        PALM_HAND_1_Z,
        PALM_HAND_1_ROLL,
        PALM_HAND_1_PITCH,
        PALM_HAND_1_YAW,
        
        PALM_HAND_2_X,
        PALM_HAND_2_Y,
        PALM_HAND_2_Z,
        PALM_HAND_2_ROLL,
        PALM_HAND_2_PITCH,
        PALM_HAND_2_YAW,
        
        FINGER_1_HAND_1_X,
        FINGER_1_HAND_1_Y,
        FINGER_1_HAND_1_Z,
        FINGER_2_HAND_1_X,
        FINGER_2_HAND_1_Y,
        FINGER_2_HAND_1_Z,
        
        FINGER_1_HAND_2_X,
        FINGER_1_HAND_2_Y,
        FINGER_1_HAND_2_Z,
        
        // etc...
    };
}

#endif
