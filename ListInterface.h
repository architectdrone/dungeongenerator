
#ifndef LIST_INTERFACE_H
#define LIST_INTERFACE_H
#include <iostream>

template <typename T>
class ListInterface
{

     public:
     virtual ~ListInterface(){}


     virtual bool isEmpty() const = 0;
     virtual int getLength() const = 0;
     virtual void insert(int position, T entry) throw (std::runtime_error) = 0;
     virtual void remove(int position) throw (std::runtime_error) = 0;
     virtual void clear() = 0;
     virtual T getEntry(int position) const throw (std::runtime_error) = 0;

     /** Here's an example of a doxygen comment block. Do this for all methods
     * @pre The position is between 1 and the list's length
     * @post The entry at the given position is replaced with the new entry
     * @param position:  1<= position <= length
     * @param newEntry: A new entry to put in the list
     * @throw std::runtime_error if the position is invalid.
     **/
     virtual void replace(int position, T newEntry) throw (std::runtime_error) = 0;
};

#endif
