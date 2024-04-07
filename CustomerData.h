//Nick Dunne S2021
//CustomerData struct for the queue program

#ifndef CUSTOMERDATA_H
#define CUSTOMERDATA_H

struct CustomerData {
    int customerNumber;
    int arrivalTime;
    int serviceTime;

    //Constructors
    CustomerData() {}
    CustomerData(int cust, int arr, int serv) : customerNumber(cust), arrivalTime(arr), serviceTime(serv) {}
};

#endif // !CUSTOMERDATA_H