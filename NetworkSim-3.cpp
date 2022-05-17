//Keagan Leon
//University of Washington
//CSS 343

#include "Router.h"
#include "FakeIPPacket.h"
int main() {
srand((unsigned)time(0));
int t = 0;
Router router;
    while (router.NotEmpty() || t < TIME_TO_RUN) {  // run until there are no more 
packets left
        for (t = 0; t < TIME_TO_RUN; t++) {   // packet generator Time loop
                int numPackets = rand() % MAX_PACKETS;
                for (int i = 0; i < numPackets; i++) { // packet generator loop
                        // generate packet
                        FakeIPPacket pkt;
                        pkt.assignTOS(rand() % 256);
                        pkt.assignLength(rand() % 65535 + 1);
                        pkt.assignTime(t);
                        // Enqueue packet
                        router.Enqueue(pkt);
                }
                // Dequeue packet, 1 per second
                router.Dequeue(t);
        }
        while (router.NotEmpty() && t >= TIME_TO_RUN) {
                t++;
                router.Dequeue(t);
        }
    }
router.PrintStatistics();
}
// Desired output for PrintStatistics:
// Average time for Priority 0 of 6: 
// Average time for Priority 1 of 6:
// Average time for Priority 2 of 6:
// Average time for Priority 3 of 6:
// Average time for Priority 4 of 6:
// Average time for Priority 5 of 6:
// Average time for Priority 6 of 6:
