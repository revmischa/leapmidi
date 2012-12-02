//
//  MIDITool.cpp
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/1/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#include "MIDITool.h"
#include <iostream>

namespace LeapMIDI {

int MIDITool::last_channel_ = 0;
    
int MIDITool::get_next_available_channel() {
    int new_chan = last_channel_ + 1;
    last_channel_ = new_chan;
    return new_chan;
}
    
MIDITool::MIDITool() {
}

void MIDITool::init() {
    channel_ = get_next_available_channel();
}
  
MIDIToolController* MIDIToolController::instance_ = NULL;
    
MIDIToolController& MIDIToolController::instance() {
    if (instance_ == NULL) {
        instance_ = new MIDIToolController();
        instance_->init();
    }
    
    return *instance_;
}

MIDIToolController::MIDIToolController() {
    
}

void MIDIToolController::init() {
    
}
    
void MIDIToolController::process_frame(const Leap::Frame &frame) {
    if (frame.hands().empty())
        return; // no hands detected
    
    // only support one hand at the moment
    Leap::Hand hand = frame.hands()[0];
    
    if (hand.fingers().size() == 1)
        process_one_finger_tool(hand);
    else if (hand.fingers().size() == 2)
        process_two_finger_tool(hand);
}

void MIDIToolController::process_one_finger_tool(const Leap::Hand& hand) {
    MIDIToolPtr tool;
    
    if (!tool_map_[MIDITool::ONE_FINGER]) {
        tool_map_[MIDITool::ONE_FINGER] = MIDIToolPtr(new MIDITool());
        tool_map_[MIDITool::ONE_FINGER]->init();
    }
    
    tool = tool_map_[MIDITool::ONE_FINGER];
    
    int value = hand.fingers()[0].tip().position.y;
    value = value > 127 ? 127 : value;
    std::cout << "finger 0 Y: " << value << std::endl;
    tool->set_value(value);
}

void MIDIToolController::process_two_finger_tool(const Leap::Hand& hand) {
    
}
    
    

}