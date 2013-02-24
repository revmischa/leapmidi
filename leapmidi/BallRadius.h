//
//  BallRadius.h
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/6/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#ifndef __leapmidi__MIDIControlBallRadius__
#define __leapmidi__MIDIControlBallRadius__

#include <iostream>
#include "LeapMIDI.h"
#include "MIDIControl.h"

using namespace std;

namespace leapmidi {
    
class BallRadius : public Control {
public:
    BallRadius(midi_bodypart_index hi, midi_bodypart_index fi, double radius) : Control(hi, fi, radius) {}
    virtual ~BallRadius() {}
    
    virtual const string description() {
        static const string desc = "Hand curvature";
        return desc;
    }
    
    virtual const midi_control_value_raw minRawValue() { return 48; }
    virtual const midi_control_value_raw maxRawValue() { return 145; }
    virtual const midi_control_index controlIndex();
};

typedef shared_ptr<BallRadius> BallRadiusPtr;
    
}

#endif /* defined(__leapmidi__MIDIControlBallRadius__) */
