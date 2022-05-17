# Network-Router
A network router simulation was implemented to makes prioritization decisions based on the Type of Service (TOS) and length fields in the IP header of a network packet

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

This project will simulate a network router and the network packets that come through it.  A simplified IP packet class and a network simulation have been built.  Your responsibility is to build a StochasticRouter class and a Router class.  These Routers will be implemented as priority queues built on a heap.   You may use std::vector and std::queue for this assignment.  Your EvaluatePriority function must include both TOS and length of the packet as part of the evaluation.  It is up to you to decide what the TOS values mean and whether you want to prefer long packets or short packets.   You may experiment with how you evaluate those and how many different priority values you use. 

Router must implement the following methods: 

Public:
Constructor/Destructor
void Enqueue (FakeIPPacket pkt)  // puts the packet into the queue based on its priority
FakeIPPacket Dequeue(int time)  // removes and returns a packet from the highest priority queue.  This would be a good time to collect statistics too.
void PrintStatistics()  // prints the average amount of time each packet stays in the queue for each priority value and the overall average amount of time each packet is in the queue.  

Private:
int EvaluatePriority(FakeIPPacket pkt)  // returns the priority value for the packet
 

StochasticRouter will inherit from Router and add the following method:

void SetPriorityWeight(float weight);  // weight should be between 0 and 1

StochasticRouter will select from the top priority queue with a probability of weight (0.9 = 90% of the time, for example) and will select a random packet from any queue otherwise.  The packet will be selected from a uniform distribution across all packets (note, not across all queues as queues will be of different sizes) when you call the dequeue method.

You will run this code with a variety of weights (or unweighted).  Analyze the results and discuss how the weighting affected the delays to each different priority level.  Comment on how your experiments with number of priority values and the function of TOS and packet length affected your results.  Include a figure showing your results for each priority level as a function of weight.
