/*
@author Owen Mellema
@file LinkedList.h
@date 9-20-18
@brief A Linked List Implementation.
*/
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "ListInterface.h"
#include "LinkedListElement.h"

template <typename T>
class LinkedList: public ListInterface <T>
{
private:
   LinkedListElement<T> *firstEntryPtr;
   int length;
   //void validation(int pos, bool endPlus) throw (std::runtime_error); //Add one to the end of the allowed range if endPlus is true (see insert for why endPlus might be used)
   LinkedListElement<T>* getLinkedListElement(int pos) const;


public:

  //CONSTRUCTOR

  LinkedList();
  LinkedList(const LinkedList<T> &LL2);

  //DESTRUCTOR

  ~LinkedList();

  //GETTERS
  void printer();

  /** getLength
  * @pre None
  * @post Returns length
  **/
  int getLength() const;

  //SPECIAL

  /** isEmpty
  * @post Returns true if length == 0, else false
  **/
  bool isEmpty() const;
  /** insert
  * @pre The position is between 0 and the list's length
  * @post Entry is assigned to the new position. All Entries after (if there are any) have a position of (x+1)
  * @param position:  0 <= position <= length
  * @param entry: A new entry to put in the list
  * @throw std::runtime_error if the position is invalid.
  **/
  void insert(int position, T entry) throw (std::runtime_error);
  /** remove
  * @pre The position is between 0 and the list's length-1
  * @post Removes entry. All Entries after (if there are any) have a position of (x-1)
  * @param position:  0 <= position <= length-1
  * @throw std::runtime_error if the position is invalid.
  **/
  void remove(int position) throw (std::runtime_error);
  /** clear
  * @post Removes all entries.
  **/
  void clear();
  /** getEntry
  * @pre The position is between 0 and the list's length-1
  * @post Gets entry at the given position.
  * @param position:  0 <= position <= length-1
  * @throw std::runtime_error if the position is invalid.
  **/
  T getEntry(int position) const throw (std::runtime_error);
  /** replace
  * @pre The position is between 0 and the list's length-1
  * @post The entry at the given position is replaced with the new entry
  * @param position:  0<= position <= length
  * @param newEntry: A new entry to put in the list
  * @throw std::runtime_error if the position is invalid.
  **/
  void replace(int position, T newEntry) throw (std::runtime_error);
};

#include "LinkedList.cpp"
#endif
