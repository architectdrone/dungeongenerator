#include <iostream>

template <typename T>
LinkedListElement<T>::LinkedListElement()
{
  nextPtr = nullptr;
}

template <typename T>
LinkedListElement<T>* LinkedListElement<T>::getNextPtr()
{
  return nextPtr;
}

template <typename T>
T LinkedListElement<T>::getElement()
{
  return element;
}

template <typename T>
void LinkedListElement<T>::setNextPtr(LinkedListElement<T>* n)
{
  nextPtr = n;
}

template <typename T>
void LinkedListElement<T>::setElement(T e)
{
  element = e;
}
