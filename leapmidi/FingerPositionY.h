//
//  FingerPositionY.h
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/15/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#ifndef leapmidi_MIDIControlFingerPositionY_h
#define leapmidi_MIDIControlFingerPositionY_h

#include "FingerPosition.h"

namespace leapmidi {
    
class FingerPositionY : public FingerPosition {
public:
    FingerPositionY(midi_bodypart_index hi, midi_bodypart_index fi, double pos) : FingerPosition(hi, fi, pos) {}
    virtual ~FingerPositionY() {}
    
    virtual const midi_control_index controlIndexBase() { return FINGER_1_HAND_1_Y; }
    
    virtual const char *description() { return "Finger Y position"; }
    
    virtual const midi_control_value_raw minRawValue() { return 30; }
    virtual const midi_control_value_raw maxRawValue() { return 320; }
};

}


#endif
