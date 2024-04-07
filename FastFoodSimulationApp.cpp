// Simulation to demonstrate that one queue feeding multiple cash registers is more efficient than have one queue per cash register
// Suhail Tailor

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Queue.h"
#include "CashRegister.h"
#include <iomanip>

using namespace std;

bool checkCustArrival(int time, int expected); // checks if customer arrived

void checkDeparture(CashRegister arr[], int time, ofstream &out);                                      // checks if cutomer has to leave
int addFromQueue(CashRegister arr[], int time, Queue &mainQ, ofstream &out, int &count, int &maxTime); // adds to reg
int searchAvailable(CashRegister arr[]);                                                               // search for available reg

int findShortest(Queue arr[]);                                                                                                 // find shortest queue
int checkQueueLength(Queue toCheck, int maxLength);                                                                            // checks if length is new max
void process(int tracker, CashRegister &reg, int time, int &timercalc, Queue &queue, ofstream &out, int &count, int &maxTime); // proccess each customer and register

int checkMultiLength(Queue arr[], int maxMultiLength);                                                         // checks if length is new max
int addFromCorresponding(CashRegister arr[], int time, Queue qArr[], ofstream &out, int &count, int &maxTime); // add from queue to register

int main(int argc, char **argv)
{
    std::ofstream output1("singleline.txt");
    std::ofstream output2("multiplelines.txt");

    // code to get the command line arguments
    if (argc < 4)
    {
        std::cout << "Usage: " << argv[0] << " maxTimeBetweenCustomers maxServiceTime randomSeed" << endl;
        return 1;
    }
    int maxTimeBetweenCustomers = atoi(argv[1]);
    int maxServiceTime = atoi(argv[2]);
    int randomSeed = atoi(argv[3]);
    int maxSingleLength = 0; ////stores max length in single queue simulation
    int maxMultiLength = 0;  /// stores max length for mutli queue simulation
    int custServedSingle = 0;
    int custServedMulti = 0;
    if (randomSeed > 0)
    {
        srand(randomSeed);
    }
    else
    {
        srand(time(nullptr));
    }

    Queue mainQ = Queue();
    int customerNum = 0;

    int nextArrTime = (rand() % maxTimeBetweenCustomers + 1);

    int queueNums = 3; // would be changed after input code is modified

    Queue qArr[queueNums]; // make array of Queues for multiple registers

    CashRegister arr[queueNums];      // array of registers for 1 queue
    CashRegister multiArr[queueNums]; // array for many

    int totalTimeSingle = 0;
    int totalTimeMulti = 0;
    double averageSingle = 0;
    double averageMulti = 0;
    int maxTimeSingle = 0;
    int maxTimeMulti = 0;

    for (int time = nextArrTime; time <= 720; time++)
    { // time begins

        // Checks for service completed

        checkDeparture(multiArr, time, output2);

        checkDeparture(arr, time, output1);

        if (!(mainQ.isEmpty())) // if customer is in queue ,add to available register
        {

            totalTimeSingle += addFromQueue(arr, time, mainQ, output1, custServedSingle, maxTimeSingle); // counts time in single Queue
        }

        totalTimeMulti += addFromCorresponding(multiArr, time, qArr, output2, custServedMulti, maxTimeMulti); // counts time waited in multi queue

        // if a customer as arrived
        if (checkCustArrival(time, nextArrTime))
        {

            int servTime = (rand() % maxServiceTime + 1); // generate service time

            customerNum += 1;                                                               // increment customer number
            output1 << "Customer " << customerNum << " arrived at " << time << "." << endl; // inform arrival

            output2 << "Customer " << customerNum << " arrived at " << time << "." << endl; // inform arrival

            CustomerData cust = CustomerData(customerNum, time, servTime); // create customer

            int k = 0;
            k = searchAvailable(arr);       // searches for available register
                                            // Single line sim
            if (mainQ.isEmpty() && k != -1) // case that customer find no queue,gets added straight to next available register
            {

                arr[k].addToReg(cust, time); // adds to the free register
                custServedSingle += 1;
                output1 << "Customer " << cust.customerNumber << " served by " << (k + 1) << " at " << time << "." << endl;

                arr[k].toggleAvailable(); // register availability to unavailable//
            }
            else
            {                                                               // queue is not empty or register is not available
                mainQ.enqueue(cust);                                        // add to queue
                maxSingleLength = checkQueueLength(mainQ, maxSingleLength); // check Queue length
            }

            // MultiLine sim
            int emptyRegister = searchAvailable(multiArr); // find empty register

            if (emptyRegister != -1 && qArr[emptyRegister].isEmpty()) // if register is empty and corresponding Q is empty
            {
                multiArr[emptyRegister].addToReg(cust, time); // add to register

                multiArr[emptyRegister].toggleAvailable(); // change avalablity
                output2 << "Customer " << cust.customerNumber << " served by " << (emptyRegister + 1) << " at " << time << "." << endl;
                custServedMulti += 1; // increment customers served
            }
            else
            {
                // Adding to shortest Queue
                int s = findShortest(qArr); // find shortest queue
                qArr[s].enqueue(cust);
                maxMultiLength = checkMultiLength(qArr, maxMultiLength); // update maximum length found
            }

            nextArrTime = (rand() % maxTimeBetweenCustomers + 1 + time); // Next arrival time generated
        }
    }

    // calculation of average wait times
    averageSingle = (double(totalTimeSingle) / double(custServedSingle));
    averageMulti = (double(totalTimeMulti) / double(custServedMulti));

    // separate simulation from statistics
    output1 << "\n";
    output2 << "\n";

    // output avg wait times to required files
    output1 << std::fixed << "Average wait time: " << std::setprecision(1) << averageSingle << " minutes" << endl;
    output2 << std::fixed << "Average wait time: " << std::setprecision(1) << averageMulti << " minutes" << endl;

    // output max wait times to required files
    output1 << "Maximum wait time: " << maxTimeSingle << " minutes" << endl;
    output2 << "Maximum wait time: " << maxTimeMulti << " minutes" << endl;

    // output max queue lenghts to required files
    output1 << "Maximum line length: " << maxSingleLength << " customers" << endl;
    output2 << "Maximum line length: " << maxMultiLength << " customers" << endl;

    // if doing extra credit -- need to handle additional OPTIONAL command line argument
} // end main

/*


Methods implemented below


*/

void checkDeparture(CashRegister arr[], int time, ofstream &out)
{ // allows depature in CashRegister based of time
    for (int i = 0; i < 3; i++)
    {                                        // checks all registers
        int x = arr[i].allowDeparture(time); // gets departed customer number
        if (x != -1)
        {

            out << "Customer " << x << " departed at " << time << "." << endl; // print to required file
        }
    }
}

void process(int tracker, CashRegister &reg, int time, int &timercalc, Queue &queue, ofstream &out, int &count, int &maxTime)
{
    // bool change=false;

    bool change = reg.askFromQueue(false, time, queue); // if register can accept customer

    if (change && !(queue.isEmpty()))
    {                                               // ensure queue has customer to add
        CustomerData nextCust = queue.dequeue();    // get customer from queue
        int waited = (time - nextCust.arrivalTime); // calculated waited time
        if (waited > maxTime)
        {
            maxTime = waited; // if this is the new max waited time
        }
        reg.addToReg(nextCust, time);                                                                                     // add customer to register
        timercalc += waited;                                                                                              // increment time waited
        count += 1;                                                                                                       // increment number of customer served
        out << "Customer " << nextCust.customerNumber << " served by " << (tracker + 1) << " at " << time << "." << endl; // adds if reg is free and prints to required file
    }
}

int addFromQueue(CashRegister arr[], int time, Queue &mainQ, ofstream &out, int &count, int &maxTime)
{ // adds customer from queue and returns time calculations to single

    int timercalc = 0;

    for (int i = 0; i < 3; i++)
    { // lopps through registers

        process(i, arr[i], time, timercalc, mainQ, out, count, maxTime); // calls process on single queue
    }
    return timercalc;
}

int addFromCorresponding(CashRegister arr[], int time, Queue qArr[], ofstream &out, int &count, int &maxTime)
{ // adds customer from queue returns total time waited
    int timeWaited = 0;

    for (int i = 0; i < 3; i++)
    { // loops through all queues

        process(i, arr[i], time, timeWaited, qArr[i], out, count, maxTime); // calls process but uses array of Queues
    }
    return timeWaited;
}

int checkQueueLength(Queue toCheck, int maxLength)
{                                      // checks queue length for singleline simulation
    if (toCheck.getSize() > maxLength) // checks for new max length
    {
        maxLength = toCheck.getSize(); // update max if needed
    }
    return maxLength;
}
int checkMultiLength(Queue arr[], int maxMultiLength)
{ // measure length of multi line array
    int total = 0;
    for (int i = 0; i < 3; i++)
    {                              // loops through provided array
        total += arr[i].getSize(); // adds up length of all queues
    }
    if (total > maxMultiLength)
    { // checks if this total is the new maximum length
        maxMultiLength = total;
    }

    return maxMultiLength;
}

bool checkCustArrival(int time, int expected)
{ // compares expected time to current time

    return time == expected;
}
int searchAvailable(CashRegister arr[])
{ // search for available register in array

    for (int i = 0; i < 3; i++)
    {
        if (arr[i].isAvailable())
        {

            return i; // return register number
        }
    }
    return -1; // no register is empty
}

int findShortest(Queue arr[])
{                                    // searches for shortest queue
    int shortest = arr[0].getSize(); // initialize
    int position = 0;

    for (int i = 0; i < (3); i++)
    { // loops through array

        int curr = arr[i].getSize();
        if (curr < shortest)
        {
            position = i; // shortest queue is found to be 0

            shortest = curr; // keep track of shortest size
        }
    }
    return position; // return shortest queue
}
