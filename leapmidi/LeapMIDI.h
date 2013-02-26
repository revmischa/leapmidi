//
//  leapmidi.h
//
//  Created by Mischa Spiegelmock on 2/16/13.
//  Copyright (c) 2013 int80. All rights reserved.
//

#ifndef leapmidi_leapmidi_h
#define leapmidi_leapmidi_h

#include <memory>

namespace leapmidi {    
    
typedef double midi_control_value_raw;
typedef unsigned short midi_control_value;

// MIDI control number offsets
enum midi_control_index {
    BALL_RADIUS_HAND_1 = 1,
    BALL_RADIUS_HAND_2,
    
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

class Gesture;
class Control;

typedef std::shared_ptr<Control> ControlPtr;
typedef std::shared_ptr<Gesture> GesturePtr;
    
} // namespace leapmidi

#endif
