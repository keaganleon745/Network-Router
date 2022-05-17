//Keagan Leon
//University of Washington
//CSS 343

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cstdlib>
#include <ctime>

#define MAX_PACKETS 5
#define TIME_TO_RUN 1000

using namespace std;

class FakeIPPacket {
    public:
    FakeIPPacket() {
        TOS = 0;
        length = 0;
        time = 0;
    }
  
    FakeIPPacket(unsigned char tos, unsigned short l, unsigned short t) {
        TOS = tos;
        length = l;
        time = t;
    }
  
    void assignTOS(int tos) { TOS = tos; };
    void assignLength(int l) { length = l; };
    void assignTime(int t) { time = t; } ;
    unsigned char getTOS() { return TOS;};
    unsigned short getLength() {return length;};
    unsigned short getTime() { return time;};
  
    private:
    // see https://tools.ietf.org/html/rfc791#section-3.1 for details of a real 
    IP packet 
    unsigned char TOS;
    unsigned short length;
    unsigned short time;  
  
};
