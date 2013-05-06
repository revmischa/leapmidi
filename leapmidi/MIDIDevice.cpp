//
//  MIDIDevice.cpp
//  leapmidi
//
//  Created by Mischa Spiegelmock on 3/3/13.
//  Copyright (c) 2013 int80. All rights reserved.
//

#include "MIDIDevice.h"

using namespace std;

namespace leapmidi {
    
void Device::init() {
    initPacketList();
    createDevice();
    
    // start message sending queue
    int res = pthread_create(&messageQueueThread, NULL, _messageSendingThreadEntry, this);
    if (res) {
        std::cerr << "pthread_create failed " << res << std::endl;
        exit(1);
    }
}

void Device::queueControlMessage(midi_control_index controlIndex, midi_control_value controlValue) {
    midi_message msg;
    msg.control_index = controlIndex;
    msg.control_value = controlValue;
    gettimeofday(&msg.timestamp, NULL);

    pthread_mutex_lock(&messageQueueMutex);
    
    // critical section
    midiMessageQueue.push(msg);
    
    pthread_mutex_unlock(&messageQueueMutex);
    pthread_cond_signal(&messageQueueCond);
}
    
void Device::sendControlMessage(midi_control_index controlIndex, midi_control_value controlValue) {
    _addControlPacket(controlIndex, controlValue);
    _flushMessages();
}

/*******/

Device::Device() {    
    pthread_mutex_init(&messageQueueMutex, NULL);
    pthread_cond_init(&messageQueueCond, NULL);
    
    packetListSize = 512; // buffer size for midi packet messages
    deviceClient = NULL;
    deviceEndpoint = NULL;
    midiPacketList = NULL;
}

Device::~Device() {
    if (deviceEndpoint)
        MIDIEndpointDispose(deviceEndpoint);
    if (deviceClient)
        MIDIDeviceDispose(deviceClient);
    if (midiPacketList)
        free(midiPacketList);
    
    if (messageQueueThread)
        pthread_cancel(messageQueueThread);
    
    pthread_mutex_destroy(&messageQueueMutex);
    pthread_cond_destroy(&messageQueueCond);
    
    std::cout << "closed down device\n";
}

void Device::initPacketList() {
    if (midiPacketList) {
        free(midiPacketList);
        midiPacketList = NULL;
    }
    
    midiPacketList = (MIDIPacketList *)malloc(packetListSize * sizeof(char));
    curPacket = MIDIPacketListInit(midiPacketList);
}

void Device::createDevice() {
    OSStatus result;
    
    result = MIDIClientCreate(CFSTR("LeapMIDI Client"), NULL, NULL, &deviceClient);
    if (result) {
        cerr << "Failed to create MIDI client\n";
        exit(1);
    }
    
    result = MIDISourceCreate(deviceClient, CFSTR("LeapMIDI Source"), &deviceEndpoint);
    if (result) {
        cerr << "Failed to create MIDI source\n";
        exit(1);
    }
}

void *Device::messageSendingThreadEntry() {    
    while (1) {
        pthread_testcancel();
        
        // wait for next item to go in the queue
        pthread_mutex_lock(&messageQueueMutex);
        
        // check if we have anything in the queue to send
        if (midiMessageQueue.empty()) {            
            // wait until other thread posts a notif
            int res = pthread_cond_wait(&messageQueueCond, &messageQueueMutex);
            if (res != 0) {
                cerr << "unexpected pthread_cond_wait retval=" << res << endl;
                exit(1);
            }
            
            if (midiMessageQueue.empty()) {
                pthread_mutex_unlock(&messageQueueMutex);
                continue;
            }
        }
        
        // copy messages from shared queue into thread-local copy
        // (is there a cleaner way to do this?)
        queue<midi_message> queueCopy;
        while (! midiMessageQueue.empty()) {
            midi_message msg = midiMessageQueue.front();
            queueCopy.push(msg);
            midiMessageQueue.pop();
        }
        // unlock
        if (pthread_mutex_unlock(&messageQueueMutex) != 0) {
            cerr << "message queue mutex unlock failure\n";
            exit(1);
        }
        
        // add control messages to MIDI packet queue
        _addControlMessages(queueCopy);
        
        // send messages
        _flushMessages();
    }
    
    return NULL;
}

void Device::_addControlMessages(std::queue<midi_message> &messages) {
    struct timeval tv;
    
    while (! messages.empty()) {
        midi_message msg = messages.front();
        messages.pop();
        
        // figure out when this packet was added
        gettimeofday(&tv, NULL);
        double elapsedTime = (tv.tv_sec - msg.timestamp.tv_sec) * 1000.0;      // sec to ms
        elapsedTime += (tv.tv_usec - msg.timestamp.tv_usec) / 1000.0;   // us to ms
        if (elapsedTime > 2) {
            // message was triggered too long ago, we don't want to emit old messages
            std::cerr << "Warning, MIDI control message latency of " << elapsedTime << "ms detected.\n";
            continue; // drop message
        }
        
        _addControlPacket(msg.control_index, msg.control_value);
    }
}
    
OSStatus Device::_flushMessages() {
    // "send" a list of packets, really pretends that our virtual device source received a packet
    OSStatus res = MIDIReceived(deviceEndpoint, midiPacketList);
    
    // reinitialize packet list, MIDIReceived does not appear to flush the list
    // none of this is really documented but this seems to work ok
    initPacketList();
    
    return res;
}

// control = MIDI control #, 0-119
// value = MIDI control message value, 0-127
void Device::_addControlPacket(midi_control_index control, midi_control_value value) {
    assert(control < 120);
    assert(value <= 127);
    
    // assign channel value
    // (hardcoded to channel 0 for now)
    unsigned char channelBase = 0xB0;
    unsigned char channel = 0;
    unsigned char midiChannel = channelBase + channel;
    
    // assign control selector
    unsigned char controlBase = 0x00;
    unsigned char midiControl = controlBase + control;
    
    // build midi packet
    Byte packetOut[3];
    packetOut[0] = midiChannel;
    packetOut[1] = midiControl;
    packetOut[2] = value;
    
//    printf("Sending MIDI packet: ");
//    for (int z = 0; z < 3; z++)
//    {
//        if (z > 0) printf(":");
//        printf("%02X", packetOut[z]);
//    }
//    printf("\n");
    
    
    // add packet to packet list
    curPacket = MIDIPacketListAdd(midiPacketList, packetListSize, curPacket, 0, 3, packetOut);
    if (! curPacket) {
        std::cerr << "Buffer overrun on midi packet list\n";
        exit(1);
    }
}

} // namespace leapmidi
