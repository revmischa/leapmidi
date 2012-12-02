//
//  MIDITool.h
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/1/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#ifndef leapmidi_MIDITool_h
#define leapmidi_MIDITool_h

#include <map>
#include <memory>

#include <Leap.h>

namespace LeapMIDI {
    class MIDIChannel {
        
    };
    
    class MIDITool {
    public:
        MIDITool();
        void init();
        
        unsigned char control() { return control_; }
        
        unsigned char value() { return value_; }
        void set_value(unsigned char v) { value_ = v; }
        
        int leapValue() { return leapValue_; }
        void setLeapValue(int v) { leapValue_ = v; }
        
        enum ToolDescription {
            ONE_FINGER = 0,
            TWO_FINGERS,
            THREE_FINGERS
        };
        
        bool active() { return active_; }
        void setActive(bool a) { active_ = a; }

        ToolDescription tool_description() { return tool_description_; }
        
    private:
        unsigned char control_;
        unsigned char value_;
        
        int leapValue_;
        
        ToolDescription tool_description_;
        bool active_;
        
        static unsigned char lastControl_;
        
        static unsigned char getNextAvailableControl();
        
    };
        
    typedef std::shared_ptr<MIDITool> MIDIToolPtr;
    
    // TODO: figure out all the tools we need
    class FingerTool : public MIDITool {
        
    };
    
    class RotateTool : public MIDITool {
        
    };
        
    class MIDIToolController {
    public:
        static MIDIToolController& instance();
        
        void process_frame(const Leap::Frame& frame);
        
        const std::map<MIDITool::ToolDescription, MIDIToolPtr>& tools() { return tool_map_; }
        
        
    private:
        MIDIToolController();
        void init();
        
        void deactivateTools();
        
        void process_one_finger_tool(const Leap::Hand&);
        void process_two_finger_tool(const Leap::Hand&);
        
        std::map<MIDITool::ToolDescription, MIDIToolPtr> tool_map_;
        
        static MIDIToolController* instance_;
        
        
    };
}


#endif
