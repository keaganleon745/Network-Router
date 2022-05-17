//Keagan Leon
//University of Washington
//CSS 343

#include "Router.h"

//Constructor
Router::Router()
{ 
}

//Destructor
Router::~Router()
{ 
}

//Enqueue: puts the packet into the queue based on its priority
void Router::Enqueue(FakeIPPacket pkt)
{
    if (!NotEmpty())  //when queue is empty, create new queue from packet
    {
        queue<FakeIPPacket> newQueue;
        newQueue.push(pkt);
        myQueue.push_back(newQueue);
    }
    
    else  //when queue is not empty, insert packet to existing queue
    {
        for (int i = 0; i < myQueue.size(); i++)  //iterates through vector size
        {
            if (EvaluatePriority(myQueue[i].front()) == EvaluatePriority(pkt))  
            //checks queues for priority 0 - 6
            {
                myQueue[i].push(pkt);
                return;
            }
        }
        queue<FakeIPPacket> newQueue;
        newQueue.push(pkt);
        myQueue.push_back(newQueue);
        int currentIndex = myQueue.size() - 1;  //getting index of last added queue
        while (currentIndex != 0)  //while current queue index is not 0, compare priorities of other queues
        {
            int parentIndex = (currentIndex - 1) / 2;
            int currentPriority = EvaluatePriority(myQueue[currentIndex].front());
            int parentPriority = EvaluatePriority(myQueue[parentIndex].front());
            if (currentPriority > parentPriority)
            {
                swap(currentIndex, parentIndex);  //queues are swapped
            }
            currentIndex = parentIndex;  //current index becomes parent 
        }
    }
    cout << "added packet with TOS of " << (unsigned short) pkt.getTOS() << " and length of " << pkt.getLength() << " bytes" << endl;
}

//Dequeue: removes and returns a packet from the highest priority queue.  This would be a good time to collect statistics too.
FakeIPPacket Router::Dequeue(unsigned short t)
{
    FakeIPPacket frontPacket;
    
    if (!NotEmpty())  //when queue is empty, return empty packet
    {
        return frontPacket;
    }
    
    else if (myQueue.front().size() > 1)  //if front queue has more than one packet
    {
        frontPacket = myQueue[0].front();  //saving packet to return
        myQueue[0].pop();  //delete packet from queue
        CalculateStats(EvaluatePriority(frontPacket), frontPacket.getTime(), t);  //record time
        cout << "removing packet at time " << t << endl;
        return frontPacket;
    }
    
    else  //if front queue has one packet
    {
        swap(0, myQueue.size() - 1);  //swap first and last queues
        frontPacket = myQueue.back().front();  //saving packet to return
        myQueue.pop_back();  //delete front queue
        int currentIndex = 0;  //getting index of root queue
        while (currentIndex < myQueue.size())  //while current queue index less than vector, compare priorities of other queues
        {
            int childIndex = LargestChild(currentIndex);  //calls getLargestChild() to get index
            if (childIndex == -1)
            {
                break;
            }
            swap(currentIndex, childIndex);  //queues are swapped
            currentIndex = childIndex;  //current index becomes largest child 
        }
        CalculateStats(EvaluatePriority(frontPacket), frontPacket.getTime(), t);  //record time
        cout << "removing packet at time " << t << endl;
        return frontPacket;
    }
}

//PrintStatistics: prints the average amount of time each packet stays in the queue for each priority value and the overall average amount of time each packet is in the queue.
void Router::PrintStatistics()
{
    cout << "\nStatistical data report:\n" << endl;
    int totalPackets = 0;
    int totalTime = 0;
    for (int i = 0; i < myTime.size(); i++)  //cycles through time heap to get queue averages
    {
        int currentPriorityValue;
        currentPriorityValue = i;  //priority value
        int queueTime = 0;
        int queuePackets = 0;
        for (int j = 0; j < myTime[i].size(); j++)
        {
            queueTime += myTime[i].front();  //adding packet times
            myTime[i].pop();  //taking front time out of queue
            ++queuePackets;  //one packet added to queue total
            ++totalPackets;  //one packet added to overall total
        }
        totalTime = totalTime + queueTime;  //total time accumulating 
        queueTime = queueTime / queuePackets;  //average time for queue
        
        cout << "\tAverage time for priority " << currentPriorityValue << " of 6: " << queueTime << endl;
    }
    cout << "\nAverage time each packet is in the queue is " << (totalTime / totalPackets) << endl;
    //cout << "done" << endl;
}

//NotEmpty: checks if queue is not empty
bool Router::NotEmpty()
{
    return !myQueue.empty();
}

//SetPriorityWeight: weight should be between 0 and 1
void SetPriorityWeight(float weight)
{
    weight == 0;
    //call in first priority packet
    //give weight value (packetTime/totalTime)
    //call in random packet
    //give weight value (packetTime/totalTime)
}

//EvaluatePriority: returns the priority value for the packet
int Router::EvaluatePriority(FakeIPPacket pkt)
{
     return (pkt.getTOS() + pkt.getLength()) % 7;
}

//---------------Helper Methods-------------------
//Updates the statistics after each IP packes is dequeued.*/
void Router::CalculateStats(int priority, int startTime, int endTime)
{
    int packetTime = endTime - startTime;  //find time difference
    for (int i = 0; i < myTime.size(); i++)
    {
        if (myTime[i].front() == i)
        {
            myTime[i].push(packetTime);
            return;
        }
    }
    queue<int> newPriority;
    newPriority.push(priority);
    newPriority.push(packetTime);
    myTime.push_back(newPriority);
}

//LargestChild: finds index of the largest child
int Router::LargestChild(int currentIndex)
{
    int leftChildIndex = (2 * currentIndex) + 1;
    int rightChildIndex = (2 * currentIndex) + 2;
    int leftChild = -1;  //takes account of 0 priority
    int rightChild = -1;
    if (leftChildIndex <= myQueue.size() - 1)  //left child value
    {
        leftChild = EvaluatePriority(myQueue[leftChildIndex].front());
    }
    if (rightChildIndex <= myQueue.size() - 1)  //right child value
    {
        rightChild = EvaluatePriority(myQueue[rightChildIndex].front());
    }
    if (leftChild == -1 && rightChild == -1)  //no values
    {
        return -1;
    }
    return (leftChild >= rightChild) ? leftChildIndex : rightChildIndex;  //left or right index chosen
}

//Swap: swaps 2 variables
void Router::swap(int x, int y)
{
    queue<FakeIPPacket> temp = myQueue[x];
    myQueue[x] = myQueue[y];
    myQueue[y] = temp;
}
