// Suhail Tailor
#include "CashRegister.h"
#include "iostream"

using namespace std;

CashRegister::CashRegister(int max = 0, int rArriTime = 0, int custNumber = 0, bool available = false)
{
    this->max = rArriTime + max;
    this->custNumber = custNumber;
    this->rArrivTime = rArriTime;
    this->available = available;
}

bool CashRegister::isAvailable()
{ // checks register availability

    return this->available;
}

void CashRegister::addToReg(CustomerData cust, int timer)
{ // adds to register new values

    this->max = timer + cust.serviceTime;
    this->custNumber = cust.customerNumber;
    this->available = false;
    this->rArrivTime = cust.arrivalTime;
}
bool CashRegister::checkCompletion(int time)
{ // cheks completion and authorize change if complete

    return this->max == time;
}
int CashRegister::allowDeparture(int time)
{ // chekcs if customer has completed service

    if (this->checkCompletion(time) && !this->available)
    { // ensure customer is at register

        this->max = 0;
        this->available = true;  // make register available
        return this->custNumber; // return customer info
    }
    else
    {
        return -1; // customer has not finished service
    }
}
bool CashRegister::askFromQueue(bool allow, int time, Queue mainQ)
{
    if (this->available && !(mainQ.isEmpty()))
    { // if register is available and queue is not empty allows pulling customer to register

        this->available = false;
        allow = true;
    }

    return allow;
}
void CashRegister::toggleAvailable()
{ // changes availability.
    this->available = false;
}