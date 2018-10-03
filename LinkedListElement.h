#ifndef LINKED_LIST_ELEMENT_H
#define LINKED_LIST_ELEMENT_H

template <typename T>
class LinkedListElement
{
private:
  LinkedListElement<T>* nextPtr;
  T element;

public:

  //CONSTRUCTORS

  LinkedListElement();

  //GETTERS

  /** getNextPtr
  * @post returns pointer to next in list, or nullptr if end.
  **/
  LinkedListElement<T>* getNextPtr();
  /** getElement
  * @post returns element
  **/
  T getElement();

  //SETTERS

  /** setNextPtr
  * @pre n points to an element in the same linked list.
  * @post now recognizes that the next element in the chain is &n
  * @param n: a Pointer to the next element in the linked list
  **/
  void setNextPtr(LinkedListElement<T>* n);
  /** setElement
  * @post associated element is now e
  * @param e: new Element
  **/
  void setElement(T e);
};

#include "LinkedListElement.cpp"
#endif
