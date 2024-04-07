/* 8/31/98 Mary Elaine Califf
 * a C++ array implementation of queues
 */
// Modifications:
//    8/20/2003 Mary Elaine Califf
//        Changed to ANSI C++
// Revised 12/25/2020
// Suhail Tailor and Mary Elaine Califf S2021
// Implementation of a queue of CustomerData objects

#include <iostream>
#include "Queue.h"

using namespace std;

Queue::Queue() // constructor
{
  this->head = nullptr;
  this->tail = nullptr;
  this->size = 0;
}

Queue::Queue(const Queue &rhs)
{ // copy constructor
  copy(rhs);
}

Queue::~Queue()
{ // destructor
  clear();
  this->head = nullptr; // ensures all memeory freed
}

Queue &Queue::operator=(const Queue &rhs)
{ // assignment operator
  if (this != &rhs)
  {
    clear();
    copy(rhs);
  }
  return *this;
}

bool Queue::enqueue(CustomerData newValue) // add newValue to queue
{
  Node *newNode = new Node();
  newNode->data = newValue;

  if (!head) // empty queue
  {
    head = newNode;
  }
  else // standard insert logic
  {
    tail->next = newNode;
  }
  tail = newNode;
  size += 1;

  return true;
}

// remove customer
CustomerData Queue::dequeue()
{

  CustomerData retVal = this->head->data;
  Node *curr = head;
  head = head->next;
  delete curr;
  size--;
  // frontIndex = (frontIndex + 1) % MAX_QUEUE_SIZE;
  return retVal;
}

// show first customer
CustomerData Queue::front()
{
  return head->data;
}

int Queue::getSize() // returns size
{
  return size;
}

// is the queue empty
bool Queue::isEmpty()
{
  return (size == 0);
}

// helper method to copy
void Queue::copy(const Queue &rhs)
{
  this->head = nullptr;
  this->tail = nullptr;
  this->size = 0;
  Node *curr = rhs.head;

  while (curr != nullptr)
  { // copies all nodes data
    enqueue(curr->data);
    curr = curr->next;
  }
}

// helper method to delete
void Queue::clear()
{
  Node *curr;
  while (head != nullptr)
  { // deletes every node
    curr = head;
    head = head->next;
    delete curr;
  }
}