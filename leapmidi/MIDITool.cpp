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

    unsigned char MIDITool::lastControl_ = 0u;
        
    unsigned char MIDITool::getNextAvailableControl() {
        unsigned char new_control = lastControl_ + 1u;
        lastControl_ = new_control;
        return new_control;
    }
        
    MIDITool::MIDITool() {
        active_ = true;
    }

    void MIDITool::init() {
        control_ = getNextAvailableControl();
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
        deactivateTools();
        
        if (frame.hands().empty())
            return; // no hands detected
        
        // only support one hand at the moment
        Leap::Hand hand = frame.hands()[0];
        if (! hand.fingers().size())
            return;
        
        unsigned int control = (unsigned int)hand.fingers().size();
        if (! tool_map_[control]) {
            tool_map_[control] = MIDIToolPtr(new MIDITool());
            tool_map_[control]->init();
        }

        MIDIToolPtr tool = tool_map_[control];
        tool->setActive(true);
        int value = hand.fingers()[0].tip().position.y;
        if (value > 127) value = 127;
        std::cout << "finger control " << control << " Y: " << value << std::endl;
        tool->set_value(value);
        tool->setLeapValue(hand.fingers()[0].tip().position.y);
    }

    void MIDIToolController::deactivateTools() {
        for (std::map<LeapMIDIControl, MIDIToolPtr>::iterator
             it = tool_map_.begin(); it != tool_map_.end(); ++it) {
            it->second->setActive(false);
        }
    
    }
//    
//    void MIDIToolController::process_one_finger_tool(const Leap::Hand& hand) {
//        MIDIToolPtr tool;
//        
//        if (!tool_map_[MIDITool::ONE_FINGER]) {
//            tool_map_[MIDITool::ONE_FINGER] = MIDIToolPtr(new MIDITool());
//            tool_map_[MIDITool::ONE_FINGER]->init();
//        }
//        
//        tool = tool_map_[MIDITool::ONE_FINGER];
//        
//        tool->setActive(true);
//        
//        int value = hand.fingers()[0].tip().position.y;
//        if (value > 127) value = 127;
//        //std::cout << "finger 0 Y: " << value << std::endl;
//        tool->set_value(value);
//        
//        tool->setLeapValue(hand.fingers()[0].tip().position.y);
//    }
//
//    void MIDIToolController::process_two_finger_tool(const Leap::Hand& hand) {
//        
//    }
    
    

}