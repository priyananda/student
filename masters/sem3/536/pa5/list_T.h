#ifndef _LIST_GUARD
#define _LIST_GUARD

#include <cassert>
#include <fstream> // for definition of NULL

// **********************************************************************
// The List template implements an ordered list of items with a "current" item.
// To declare a list of items of type T use: List<T>, e.g., List<int> intlist;
// **********************************************************************
//
// Member functions
// ================
//
// constructors/destructor
// =======================
// List()               -- constructor: creates a list containing no items
// List(const List & L) -- copy constructor: creates a copy of L
// ~List()              -- destructor: cleans up as necessary
//
// mutators/modifiers
// ==================
// void AddToEnd(T k) -- add k to the end of the list
// void FreeList()    -- reinitialize the list to be empty, freeing storage
//
// other operations
// ================
// int Length()         -- length of list
// void Reset()         -- reset "current" item to be first item
// void Next()          -- advance current item
// bool AtEnd()         -- is current item past last item?
// T Current()          -- return current item (error if AtEnd)
// List & operator =    -- (assignment)
//
// Note: to iterate through a List L use code like this:
//      L.Reset();
//	while (!L.AtEnd()) {
//	  ...some code involving L.Current()...
//	  L.Next();
//	}
//                                               
// **********************************************************************

template <class T> class List
{

  public:
    List();                  // constructor (default)
    ~List();                 // destructor
    List(const List<T> & L); // copy constructor

    // mutator/modifier member functions

    void AddToEnd(T k);
    void FreeList();
        
    // other operations

    int Length() const;
    void Reset();
    void Next();
    bool AtEnd() const;
    T Current() const;
    List & operator = (const List<T> & dl); // assignment

  private:
   struct ListNode {
      T item;
      ListNode *next;
    };

    int mySize;                    // current length of the list
    ListNode * myItems;            // ptr to header node
    ListNode * myCurrent;          // ptr to "current" item
    ListNode * myLast;             // ptr to last node in list
    void Append(const List<T> & L);// private operation
};

// Implementation of List template using a linked list with a header node.

// **********************************************************************
// List constructor
//   initialize the list to be empty
// **********************************************************************
template<class T> List<T>::List():
    mySize(0),                 // contains no items, just a header node
    myItems(new ListNode),
    myCurrent(NULL),
    myLast(myItems)
{
  myItems->next = NULL;
}

// **********************************************************************
// List destructor
//   free storage
// **********************************************************************
template<class T> List<T>::~List()
{
  FreeList();
  delete myItems;
}

// **********************************************************************
// List copy constructor
// **********************************************************************
template<class T> List<T>::List(const List<T> & L):
  mySize(0),
  myItems(new ListNode),
  myCurrent(NULL),
  myLast(myItems)
// postcondition: list is a copy of L
{

  myItems->next = NULL;
  // add all items in list L to the end of this list
  Append(L);
}

// **********************************************************************
// List assignment
// **********************************************************************
template<class T> List<T> & List<T>::operator = (const List & L)
// postcondition: list is a copy of L
{
    if (this != & L)                      // watch aliasing
    {
      FreeList();
      Append(L);
    }
    return * this;
}

// **********************************************************************
// Freelist
//    reinitialize the list to be empty, freeing storage
// **********************************************************************
template<class T> void List<T>::FreeList()
{
ListNode *tmp1 = myItems->next;
ListNode *tmp2;

  while (tmp1 != NULL) {
    tmp2 = tmp1->next;
    delete tmp1;
    tmp1 = tmp2;
  }
  myItems->next = NULL;
  myCurrent = NULL;
  myLast = myItems;
  mySize = 0;
}

// **********************************************************************
// AddToEnd
//    Add the given item k to the end of the list
// **********************************************************************
template<class T> void List<T>::AddToEnd(T k)
{
ListNode *tmp;

    tmp = new ListNode;
    tmp->item = k;
    tmp->next = NULL;
    myLast->next = tmp;
    myLast = tmp;
    mySize++;
}

// **********************************************************************
// Length
//   return the length of the list
// **********************************************************************
template<class T> int List<T>::Length() const
{
  return(mySize);
}

// **********************************************************************
// Reset
//   reset the "current" item to be the first one
// **********************************************************************
template<class T> void List<T>::Reset()
{
  myCurrent = myItems->next;
}

// **********************************************************************
// Next
//   advance the "current" item
// **********************************************************************
template<class T> void List<T>::Next()
{
    if (myCurrent != NULL) myCurrent = myCurrent->next;
}

// **********************************************************************
// AtEnd
//   return true iff current item is past last item
// **********************************************************************
template<class T> bool List<T>::AtEnd() const
{
  return (NULL == myCurrent);
}

// **********************************************************************
// Current
//   return current item (error if AtEnd)
// **********************************************************************
template<class T> T List<T>::Current() const
{
    assert(myCurrent !=  NULL);
    return( myCurrent->item );
}

// **********************************************************************
// Append
//    Given: list L
//    Do:    add all items in L to the end of this list
// **********************************************************************
template<class T> void List<T>::Append(const List<T> & L)
{
ListNode *tmp = L.myItems->next;

  while (tmp != NULL) {
    AddToEnd(tmp->item);
    tmp = tmp->next;
  }
}

#endif
