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
    FingerPositionX(midi_bodypart_index hi, midi_bodypart_index fi, double pos) : FingerPosition(hi, fi, pos) {}
    virtual ~FingerPositionX() {}
    
    virtual const midi_control_index controlIndexBase() { return FINGER_1_HAND_1_X; }
    
    virtual const char *description() { return "Finger X position"; }
                
    virtual const midi_control_value_raw minRawValue() { return -150; }
    virtual const midi_control_value_raw maxRawValue() { return 150; }
};

}

#endif /* defined(__leapmidi__MIDIControlFingerPositionX__) */
