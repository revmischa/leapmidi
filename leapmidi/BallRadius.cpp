//
//  BallRadius.cpp
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/6/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#include "BallRadius.h"

namespace leapmidi {

const midi_control_index BallRadius::controlIndex() {
    if (handIndex() == 0) return BALL_RADIUS_HAND_1;
    if (handIndex() == 1) return BALL_RADIUS_HAND_2;
    
    throw "Too many hands detected for ball radius control!";
}
    
    const midi_note_index BallRadius::noteIndex() {
        if (handIndex() == 0) return BALL_RADIUS_HAND_1_ON;
        if (handIndex() == 1) return BALL_RADIUS_HAND_2_ON;
        
        throw "Too many hands detected for ball radius note!";
    }

}
