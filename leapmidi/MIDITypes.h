//
//  MIDITypes.h
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/5/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#ifndef leapmidi_MIDITypes_h
#define leapmidi_MIDITypes_h

namespace leapmidi {
    
typedef double midi_control_value_raw;
typedef unsigned short midi_control_value;

typedef double midi_note_value_raw;
typedef unsigned short midi_note_value;

typedef unsigned short midi_bodypart_index;
    
    const int MSG_NOTE = 0;
    const int MSG_CONTROL = 1;

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
    
enum midi_note_index {
        MIDI_NOTE_UNRECOGNIZED = 0,
        
        BALL_RADIUS_HAND_1_ON = 1,
        BALL_RADIUS_HAND_1_OFF,
    
        BALL_RADIUS_HAND_2_ON,
        BALL_RADIUS_HAND_2_OFF,
    
        PALM_HAND_1_X_ON,
        PALM_HAND_1_X_OFF,

        PALM_HAND_1_Y_ON,
        PALM_HAND_1_Y_OFF,

        PALM_HAND_1_Z_ON,
        PALM_HAND_1_Z_OFF,
    
        PALM_HAND_1_ROLL_ON,
        PALM_HAND_1_ROLL_OFF,

        PALM_HAND_1_PITCH_ON,
        PALM_HAND_1_PITCH_OFF,
    
        PALM_HAND_1_YAW_ON,
        PALM_HAND_1_YAW_OFF,

        PALM_HAND_2_X_ON,
        PALM_HAND_2_X_OFF,
    
        PALM_HAND_2_Y_ON,
        PALM_HAND_2_Y_OFF,
    
        PALM_HAND_2_Z_ON,
        PALM_HAND_2_Z_OFF,
    
        PALM_HAND_2_ROLL_ON,
        PALM_HAND_2_ROLL_OFF,
    
        PALM_HAND_2_PITCH_ON,
        PALM_HAND_2_PITCH_OFF,
    
        PALM_HAND_2_YAW_ON,
        PALM_HAND_2_YAW_OFF,
        
        FINGER_1_HAND_1_X_ON,
        FINGER_1_HAND_1_X_OFF,
    
        FINGER_1_HAND_1_Y_ON,
        FINGER_1_HAND_1_Y_OFF,
    
        FINGER_1_HAND_1_Z_ON,
        FINGER_1_HAND_1_Z_OFF,
    /*
        FINGER_2_HAND_1_X,
        FINGER_2_HAND_1_Y,
        FINGER_2_HAND_1_Z,
        
        FINGER_1_HAND_2_X,
        FINGER_1_HAND_2_Y,
        FINGER_1_HAND_2_Z,*/
        
        // etc...
    };


} // namespace leapmidi

#endif
