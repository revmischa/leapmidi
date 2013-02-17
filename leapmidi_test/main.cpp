//
//  main.cpp
//  leapmidi_test
//
//  Created by Mischa Spiegelmock on 11/28/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

#include <iostream>
#include <LeapMIDI.h>
#include <Leap.h>

LeapMIDI::Listener listener;
Leap::Controller controller(&listener);

int main(int argc, const char * argv[]) {
    std::cout << "Press Enter to quit..." << std::endl;
    std::cin.get();
    
    return 0;
}

