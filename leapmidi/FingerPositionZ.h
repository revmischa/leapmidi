//
//  FingerPositionZ.h
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/15/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#ifndef leapmidi_MIDIControlFingerPositionZ_h
#define leapmidi_MIDIControlFingerPositionZ_h

#include "FingerPosition.h"

namespace leapmidi {
    
class FingerPositionZ : public FingerPosition {
public:
    FingerPositionZ(midi_bodypart_index hi, midi_bodypart_index fi, double pos) : FingerPosition(hi, fi, -pos) {}
    virtual ~FingerPositionZ() {}
    
    virtual const midi_control_index controlIndexBase() { return FINGER_1_HAND_1_Z; }
    virtual const midi_note_index noteIndexBase() { return FINGER_1_HAND_1_Z_ON; }

    virtual const char *description() { return "Finger Z position"; }
    
    virtual const midi_control_value_raw minRawValue() { return -160; }
    virtual const midi_control_value_raw maxRawValue() { return 160; }
};

}

#endif
