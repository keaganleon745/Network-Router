//Keagan Leon
//Unbiversity of Washington
//CSS 343

#pragma once
#include "FakeIPPacket.h"

using namespace std;

class Router
{
    public:
        Router();
        ~Router();
        void Enqueue(FakeIPPacket pkt);
        FakeIPPacket Dequeue(unsigned short t);
        void PrintStatistics();
        bool NotEmpty();
        
        //Helper Methods
        void CalculateStats(int priority, int timeStart, int timeEnd);
        int LargestChild(int current);
        void swap(int a, int b);
        
        void SetPriorityWeight(float weight);
        
    private:
        vector<queue<FakeIPPacket>> myQueue;
        vector<queue<int>> myTime;
        int EvaluatePriority(FakeIPPacket pkt);
};

class StochasticRouter : public Router
{
    // public:
        
    // weight = 1;
};
