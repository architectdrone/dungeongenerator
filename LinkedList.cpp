#include <iostream>
#include <string>
#include "LinkedListElement.h"
template <typename T>
LinkedList<T>::LinkedList()
{
  length = 0;
  firstEntryPtr = nullptr;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &LL2)
{
  //std::cout << "[COPY] Copy Constructor Called." << std::endl;
  int newLength = LL2.getLength();
  length = 0;


  for (int i = 0; i < (newLength); i++)
  {
    //std::cout << "[COPY] Adding element " << i << " from LL2" << std::endl;
    insert(i, LL2.getEntry(i));
  }
}

template <typename T>
LinkedList<T>::~LinkedList()
{
  while (true)
	{
		if (length == 0)
		{
			break;
		}
		else
		{
      LinkedListElement<T>* interimPtr = firstEntryPtr;
      firstEntryPtr = (firstEntryPtr -> getNextPtr());
      delete interimPtr;
      length--;
		}
	}
}

template <typename T>
LinkedListElement<T>* LinkedList<T>::getLinkedListElement(int position) const
{
  if (position < 0)
  {
    throw std::runtime_error("Error: Index out of Bounds (glle)"); // can't be less than 0.
  }
  else if (position > (length - 1))
  {
      throw std::runtime_error("Error: Index out of Bounds (glle)");
  }
   //Check to make sure if it is a valid position.

	LinkedListElement<T>* current = firstEntryPtr;
	LinkedListElement<T>* next = current -> getNextPtr();

	//Keep iterating until curPos is equal to position.
	int curPos = 0;
  if (curPos != position)
  {

    while (curPos != position)
  	{
      //std::cout << "  (GLLE)            " << current << "  -> " << next << std::endl;
  		current = next;
  		next = (current -> getNextPtr());
  		curPos++;
  	}
  }
	//Then return it
  //std::cout << "  (GLLE) RETURNING [" << current << "] -> " << next << std::endl;
	return current;
}

/*
template <typename T>
void LinkedList<T>::validation(int position, bool endPlus) throw (std::runtime_error)
{

	if (position < 0)
	{
		throw std::runtime_error("Error: Index out of Bounds"); // can't be less than 0.
	}
	if (endPlus == true) //Make sure we aren't out of bounds.
	{
		if (position > length)
		{
			throw std::runtime_error("Error: Index out of Bounds");
		}
	}
	else
	{
		if (position > (length - 1))
		{
			throw std::runtime_error("Error: Index out of Bounds");
		}
	}
}
*/

template <typename T>
int LinkedList<T>::getLength() const
{
  return length;
}

template <typename T>
bool LinkedList<T>::isEmpty() const
{
  if (length == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

template <typename T>
void LinkedList<T>::insert(int position, T entry) throw (std::runtime_error)
{
  //printer();
  //-------------------------validation
  if (position < 0)
  {
    throw std::runtime_error("Index is too low. (<0)");
  }
  else if ((getLength() == 0)&&(position != 0))
  {
    throw std::runtime_error("To insert an item into an empty list, please use index 0.");
  }
  else if (position > getLength())
  {
    throw std::runtime_error("Sorry, index is too high.");
  }
  //-------------------------validation
	//Create a new LinkedListElement

	LinkedListElement<T>* A = new LinkedListElement<T>;
  A -> setElement(entry);

  if (length == 0)
  {
    //If we are the only ones here, we don't do any of that. Just set first pointer.
    firstEntryPtr = A;
  }
  else if (position == length)
  {
    //If we are at the end, we just set the previous to connect to us.
    getLinkedListElement(position - 1) -> setNextPtr(A);
  }
  else if (position == 0)
  {
    //If we are at the start, we just set us to point to next, and set firstPtr to us.
    A -> setNextPtr(getLinkedListElement(0));
    firstEntryPtr = A;
  }
  else
  {

    // If we are in the middle, set us to point to the next.
    A -> setNextPtr(getLinkedListElement(position));
    //we set the previous to connect to us.
    getLinkedListElement(position - 1) -> setNextPtr(A);

  }


	length = length+1;
}

template <typename T>
void LinkedList<T>::remove(int position) throw (std::runtime_error)
{
  if (length == 0)
  {
    //If there is nothing there...
    return;
  }
  else if (length == 1)
  {
    //This is the only element in the list. The list becomes empty.
    delete getLinkedListElement(0);
    firstEntryPtr = nullptr;
  }
  else
  {
    if (position == 0)
    {
      //If it is the first, set next to be firstEntryPtr
      LinkedListElement<T>* interimPtr = getLinkedListElement(0) -> getNextPtr(); //This will be the new first pointer.
      delete getLinkedListElement(0);
      firstEntryPtr = interimPtr;

    }
    else if (position == length-1)
    {
      //If it is the last, set the previous to point to nullptr
      delete getLinkedListElement(length-1);
      getLinkedListElement(length-2) -> setNextPtr(nullptr);


    }
    else
    {
      //If it is the middle, connect the previous to the next.
      getLinkedListElement(position-1) -> setNextPtr(getLinkedListElement(position+1));
      delete getLinkedListElement(position);
    }
  }

  length--;
}

template <typename T>
void LinkedList<T>::clear()
{
	while (true)
	{
		if (length == 0)
		{
			break;
		}
		else
		{
			remove(0);
		}
	}
}

template <typename T>
T LinkedList<T>::getEntry(int position) const throw (std::runtime_error)
{
  if (position < 0)
  {
    throw std::runtime_error("Error: Index out of Bounds"); // can't be less than 0.
  }
  else if (position > (length - 1))
  {
    throw std::runtime_error("Error: Index out of Bounds");
  }
  T toReturn = (getLinkedListElement(position) -> getElement());
  return toReturn;
}

template <typename T>
void LinkedList<T>::replace(int position, T newEntry) throw (std::runtime_error)
{
  //validation
  if (length == 0)
	{
		throw std::runtime_error("Error: Index out of Bounds");
	}
  if (position < 0)
  {
    throw std::runtime_error("Error: Index out of Bounds"); // can't be less than 0.
  }
  else if (position > length-1)  //Make sure we aren't out of bounds.
  {
    throw std::runtime_error("Error: Index out of Bounds");
  }

  printer();
	getLinkedListElement(position) -> setElement(newEntry);
}

template <typename T>
void LinkedList<T>::printer()
{
  std::cout << "Linked List of Length " << getLength() << std::endl;
  for (int i = 0; i < getLength(); i++)
  {
    std::cout << "-"<< getLinkedListElement(i) << " -> " << (getLinkedListElement(i) -> getNextPtr()) << " ("<< getEntry(i) <<")" <<std::endl;
   }
}
