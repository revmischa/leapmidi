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

namespace leapmidi {
    
class BallRadius : public Control {
public:
    BallRadius(midi_control_value_raw rawValue, int hand) : Control(rawValue, hand) {};
    
    virtual const std::string& description() {
        static const std::string desc = "Hand curvature";
        return desc;
    }
    
    virtual midi_control_value_raw minRawValue() { return 48; }
    virtual midi_control_value_raw maxRawValue() { return 100; }
    virtual midi_control_index controlIndex();
};

typedef std::shared_ptr<BallRadius> BallRadiusPtr;
    
}

#endif /* defined(__leapmidi__MIDIControlBallRadius__) */
