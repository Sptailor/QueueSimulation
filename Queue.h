/* 8/31/98 Mary Elaine Califf
 * a C++ array implementation of a queue of integers which may have length of up to 100
 *
 * Revised 12/25/2020
 */
// Suhail Tailor and Mary Elaine Califf S2021
// Header file for a queue of CustomerData objects

#ifndef QUEUE_H
#define QUEUE_H
#include "CustomerData.h"

class Queue
{
private:
  class Node
  {
  public:
    CustomerData data;
    Node *next;
  };

public:
  // constructor
  Queue();

  Queue(const Queue &rhs); // copy

  ~Queue(); // destructor

  // getter for size
  int getSize();

  // is the queue empty
  bool isEmpty();

  Queue &operator=(const Queue &rhs);

  // adds a new value to the queue
  // fails and returns false if the queue is full
  bool enqueue(CustomerData newValue);

  // removes a value from the queue and returns it
  // Precondition: queue must not be empty
  CustomerData dequeue();

  // return item at the front of the queue without removing it
  // Precondtion: queue must not be empty
  CustomerData front();

  const int MAX_QUEUE_SIZE = 500;
  int size;
  Node *head;
  Node *tail;

private:
  void copy(const Queue &rhs); // copy constructor helper method, creates deep copy
  void clear();                // destructor helper method
};

#endif
