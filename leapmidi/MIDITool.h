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
        
        int channel() { return channel_; }
        
        int value() { return value_; }
        void set_value(int v) { value_ = v; }
        
        enum ToolDescription {
            ONE_FINGER = 0,
            TWO_FINGERS,
            THREE_FINGERS
        };

        ToolDescription tool_description() { return tool_description_; }
        
    private:
        void setup_channel();
        
        int channel_;
        int value_;
        ToolDescription tool_description_;
        
        static int last_channel_;
        
        static int get_next_available_channel();
        
    };
        
    typedef std::shared_ptr<MIDITool> MIDIToolPtr;
        
    class MIDIToolController {
    public:
        static MIDIToolController& instance();
        
        void process_frame(const Leap::Frame& frame);
        
        const std::map<MIDITool::ToolDescription, MIDIToolPtr>& tools() { return tool_map_; }
        
        std::map<MIDITool::ToolDescription, MIDIToolPtr> tool_map_;
        
    private:
        MIDIToolController();
        void init();
        
        void process_one_finger_tool(const Leap::Hand&);
        void process_two_finger_tool(const Leap::Hand&);
        
        static MIDIToolController* instance_;
        
        
    };
}


#endif
