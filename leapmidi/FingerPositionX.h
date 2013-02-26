//
//  FingerPositionX.h
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/15/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#ifndef __leapmidi__MIDIControlFingerPositionX__
#define __leapmidi__MIDIControlFingerPositionX__

#include "FingerPosition.h"

namespace leapmidi {
    
class FingerPositionX : public FingerPosition {
public:
    FingerPositionX(int hi, int fi, double pos) : FingerPosition(hi, fi, pos) {}
    
    virtual midi_control_index controlIndexBase() { return FINGER_1_HAND_1_X; }
    
    virtual const std::string &description() {
        static const std::string desc = "Finger X position";
        return desc;
    }
                
    virtual midi_control_value_raw minRawValue() { return -150; }
    virtual midi_control_value_raw maxRawValue() { return 150; }
};

}

#endif /* defined(__leapmidi__MIDIControlFingerPositionX__) */
