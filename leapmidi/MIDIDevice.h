//
//  MIDIDevice.h
//  leapmidi
//
//  Created by Mischa Spiegelmock on 3/3/13.
//  Copyright (c) 2013 int80. All rights reserved.
//

#ifndef __leapmidi__MIDIDevice__
#define __leapmidi__MIDIDevice__

#include <iostream>
#include <queue>
#include <pthread.h>
#include <sys/time.h>
#include <CoreMIDI/CoreMIDI.h>
#include "LeapMIDI.h"

namespace leapmidi {
    
typedef struct {
    midi_control_index control_index;
    midi_control_value control_value;
    timeval timestamp;
} midi_message;
    
class Device {
public:
    Device();
    ~Device();
    void init();
    
    // send message later
    void queueControlMessage(midi_control_index controlIndex, midi_control_value controlValue);
    
    // immediate version
    void sendControlMessage(midi_control_index controlIndex, midi_control_value controlValue);
    
protected:
    void initPacketList();
    void createDevice();
    
    void *messageSendingThreadEntry();

    // thread-safe MIDI message queue
    std::queue<midi_message> midiMessageQueue;
    pthread_mutex_t messageQueueMutex;
    pthread_t messageQueueThread;
    pthread_cond_t messageQueueCond;
    
    // add MIDI control messages to the MIDI packet queue to transmit
    void _addControlPacket(midi_control_index control, midi_control_value value);
    void _addControlMessages(std::queue<midi_message> &messages);

    // send midi packets
    OSStatus _flushMessages();
    
    MIDIClientRef deviceClient;
    MIDIEndpointRef deviceEndpoint;
    MIDIPacketList *midiPacketList;
    unsigned int packetListSize;
    MIDIPacket *curPacket;
    
private:
    static void *_messageSendingThreadEntry(void * This) {
        ((Device *)This)->messageSendingThreadEntry(); return NULL;
    }
    
};
    
} // namespace leapmidi

#endif /* defined(__leapmidi__MIDIDevice__) */
