/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

DigitalOut led1(LED1);
DigitalOut led2(D2);
DigitalOut led3(D3);


Queue<int, sizeof(int)> queue;
Queue<int, sizeof(int)> queue2;


Thread thread;
Thread thread2;
Thread thread3;



/* Send Thread */

void send_thread(void)
{
    int message = 0;
  

    while (true) {
            ThisThread::sleep_for(200ms);
             message++; // counter
            queue.try_put(&message);//Put counter to message queue
        }
    
}

void recieve_thread(void)
{
    while (true) {
        osEvent evt = queue.get(); //recieve message from queue
        if (evt.status == osEventMessage) { //check if message available
            int *message = (int*)evt.value.p; //copy message
            if(*message % 3 == 0){  //if counter is multiple of 3, then toggle LED 2 
                led2 = !led2;
            }
            queue2.try_put(message); //Put counter to message queue2
        }
    }
}
void recieve_thread2(void)
{
    while (true) {
        osEvent evt = queue2.get(); //recieve message from queue
        if (evt.status == osEventMessage) { //check if message available
            int *message = (int*)evt.value.p; //copy message
            if(*message % 7 == 0){  //if counter is multiple of 7, then toggle LED 3 
                led3 = !led3;
            }
        }      
    }
}



int main(void)

{
    thread.start(send_thread);
    thread2.start(recieve_thread);
    thread3.start(recieve_thread2);

    while (true) {
        ThisThread::sleep_for(2000ms);
    }

}