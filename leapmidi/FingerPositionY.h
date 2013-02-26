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
    FingerPositionY(int hi, int fi, double pos) : FingerPosition(hi, fi, pos) {}
    
    virtual midi_control_index controlIndexBase() { return FINGER_1_HAND_1_Y; }

    virtual const std::string &description() {
        static const std::string desc = "Finger Y position";
        return desc;
    }
    
    virtual midi_control_value_raw minRawValue() { return 30; }
    virtual midi_control_value_raw maxRawValue() { return 320; }
};

}


#endif
