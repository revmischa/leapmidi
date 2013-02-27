//
//  MIDIControl.cpp
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/5/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#include "MIDIControl.h"

namespace leapmidi {

bool _controlRangeWarning = false;

midi_control_value Control::mappedValue() {
    midi_control_value_raw min = minRawValue();
    midi_control_value_raw max = maxRawValue();
    midi_control_value_raw raw = rawValue();
    
    if (raw < min) {
        if (_controlRangeWarning)
            std::cerr << "Warning, " << description() << " got raw value " << raw
                << " which is below the min of " << min << std::endl;
        raw = min;
    } else if (raw > max) {
        if (_controlRangeWarning)
            std::cerr << "Warning, " << description() << " got raw value " << raw
                << " which is above the max of " << max << std::endl;
        raw = max;
    }
    
    midi_control_value_raw inValNorm = raw - min;
    midi_control_value_raw upperNorm = max - min;
    midi_control_value_raw normPosition = inValNorm / upperNorm;
    midi_control_value_raw outVal = normPosition * 127;
    
    return outVal;
}
    
}

