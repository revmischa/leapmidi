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
    FingerPositionZ(int hi, int fi, double pos) : FingerPosition(hi, fi, -pos) {}
    
    virtual midi_control_index controlIndexBase() { return FINGER_1_HAND_1_Z; }

    virtual const std::string &description() {
        static const std::string desc = "Finger Z position";
        return desc;
    }
    
    virtual midi_control_value_raw minRawValue() { return -160; }
    virtual midi_control_value_raw maxRawValue() { return 160; }
};

}

#endif
