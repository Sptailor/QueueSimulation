#ifndef CLASSREGISTER_H
#define CLASSREGISTER_H

// Suhail Tailor
#include "CustomerData.h"
#include "Queue.h"

class CashRegister
{
private:
    int rArrivTime;
    int custNumber;
    int max;
    bool available;

public:
    CashRegister() : max(0), rArrivTime(0), custNumber(0), available(true){}; // default constructor
    CashRegister(int max, int rArrivTime, int custNumber, bool available);    // overloaded constructor

    void addToReg(CustomerData cust, int timer); // adds customer to queue
    bool isAvailable();                          // checks availability of register

    bool checkCompletion(int time);                       // checks if customer has completed service
    int allowDeparture(int time);                         // checks timing of customer at register and returns time of departure
    bool askFromQueue(bool allow, int time, Queue mainQ); // determines weether customer can be added from queue or directly
    void toggleAvailable();                               // changes register availability
};
#endif
