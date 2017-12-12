//-----------------------------------------------------------------------------
// File: List.h
// Class: List
// Functions: 
//		list() -- construct the empty list
//      list(size_t n_elements, datatype datum) 
//      ~list() { release(); }
//      unsigned getSize()const  
//      iterator begin()const
//      iterator end()const 
//      datatype& front()const 
//      datatype& back()const 
//      bool empty()const 
//      list(const list& x)
//      list(iterator b, iterator e)
//      void push_front(datatype datum) 
//      datatype pop_front()
//      void push_back(datatype datum)
//      datatype pop_back() 
//      void release() 
//      list operator=(const list & rlist)
//      datatype& operator[](int index)
//      const datatype& operator[](int index)const
//      listelem(datatype c, listelem* p, listelem* n, listelem* p)
//      listelem* operator->() 
//      datatype& operator*() 
//      operator listelem*() 
//      iterator(listelem* p = nullptr) 
//      iterator operator++() 
//      iterator operator--() 
//      iterator operator++(int)
//      iterator operator--(int)
//		ostream& operator<<(ostream& sout, const CDLList<datatype>& x);
//-----------------------------------------------------------------------------
#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cassert>
#include <exception>
#include <cstdlib>
#include <string>
using namespace std;
//-----------------------------------------------------------------------------
//   Title: list Class
//   Description: This file contains the class definition for list, with a test driver
//
//   Programmer: 
//		Object Oriented Programming Using C++, Edition 2 By Ira Pohl,
//      modified by Paul Bladek
//		modified by Tabitha Roemish
// 
//   Date: original: Summer 1996
//   Version: 1.06
//
//   Environment: Intel Xeon PC
//     Software: Windows 10 Enterprise
//     Compiles under Microsoft Visual C++.Net 2015
//
//   class list:
//
//     Properties:
//       listelem *head -- front end of list
//       listelem *tail -- back end of list
//       unsigned m_size -- number of elements in the list
//
//     Methods:
// 
//       inline: 
//         list() -- construct the empty list
//         list(size_t n_elements, datatype datum) -- create a list of a specific size, all elements the same
//         ~list() { release(); } -- destructor
//         unsigned getSize()const  -- accessor, returns m_size
//         iterator begin()const -- returns address of first element
//         iterator end()const -- returns address of last element
//         datatype& front()const  -- returns first element data
//         datatype& back()const -- returns last element data
//         bool empty()const -- true if no elements
//
//       non-inline:
//         list(const list& x); -- copy constructor
//         list(iterator b, iterator e) -- constructor using iterators
//         void push_front(datatype datum) -- insert element at front of list
//         datatype pop_front(); -- removes front element and returns the data from that element
//         void push_back(datatype datum) -- insert element at back of list 
//         datatype pop_back() -- removes back element and returns the data from that element
//         void release() -- removes all items from list
//         list operator=(const list & rlist) -- returns a copy of rlist
//         datatype& operator[](int index) -- for l-value
//         const datatype& operator[](int index)const -- for r-value
//
//    Public Nested Structures:
//
//      struct listelem -- list cell
//
//        properties:
//          datatype data -- the actual datum
//          listelem *next -- forward link
//          listelem *prev -- backward link
//        constructor:
//          listelem(datatype c, listelem* p, listelem* n, listelem* p) -- struct constructor
//
//     class iterator
//        Public Methods
// 
//           inline: 
//            listelem* operator->() -- same as for pointer
//            datatype& operator*() -- same as for pointer
//            operator listelem*() -- conversion
//            iterator(listelem* p = nullptr) -- constructor
// 
//           non-inline: 
//            iterator operator++() -- pre-increment
//            iterator operator--() -- pre-decrement
//            iterator operator++(int) -- post-increment
//            iterator operator--(int) -- post-decrement
// 
//        Private Properties
//            listelem* ptr -- current listelem or NULL
//
//   History Log:
//     summer, 1996 original  IP completed version 1.0 
//     May 11, 2000,  PB  completed version 1.01 
//     March 8, 2002, PB  completed version 1.02 
//     April 10, 2003, PB  completed version 1.03 
//     April 30, 2003, PB  completed version 1.04 
//     May 10, 2005, PB  completed version 1.05 
//     April 15, 2008, PB  completed version 1.06
//     April 20, 2010, PB completed version 1.07 
//     April 15, 2011, PB completed version 1.09 
//	   May 3, 2017, TR completed version 1.10
//-----------------------------------------------------------------------------
namespace PB_ADT
{
	
	template<class datatype> class CDLList
	{
	public:
		struct listelem; // forward declarations
		class iterator;
		// constructors
		CDLList() : head(nullptr), tail(nullptr), m_size(0) {}
		CDLList(size_t n_elements, datatype datum);
		CDLList(const CDLList& x);
		CDLList(iterator b, iterator e);

		virtual ~CDLList() { release(); }
		virtual unsigned getSize() const { return m_size; }
		virtual iterator begin() const { return head; }
		virtual iterator end() const { return tail; }
		void push_front(datatype & datum);
		datatype pop_front();
		void push_back(datatype & datum);
		datatype pop_back();
		datatype& front() const { return head->data; }
		datatype& back() const { return tail->data; }
		virtual bool empty()const { return head == nullptr || tail == nullptr; }
		virtual void release();
		CDLList operator=(const CDLList & rlist);
		datatype& operator[](int index);
		const datatype& operator[](int index) const;
	private:
		listelem *head;
		listelem *tail;
		unsigned m_size; // number of elements in the list 
	public:
		struct listelem // list cell
		{
			datatype data;
			listelem *next;
			listelem *prev;
			listelem(datatype datum, listelem* p, listelem* n) : 
				data(datum), prev(p), next(n) {} // struct constructor
		};
		// scoped within class list !
		class iterator
		{
		public:
			iterator(listelem* p = nullptr) : ptr(p) {}
			iterator operator++();
			iterator operator--();
			iterator operator++(int);
			iterator operator--(int);
			listelem* operator->() const { return ptr; }
			datatype& operator*() const { return ptr->data; }
			operator listelem*() const { return ptr; }
		private:
			listelem* ptr;  //current listelem or nullptr
		};
	};

	template<class datatype>
	ostream& operator<<(ostream& sout, const CDLList<datatype>& x);


//-----------------------------------------------------------------------------
//            List Definitions:
//-----------------------------------------------------------------------------
//--------------------------------------------------
// Function: CDLList<datatype>::CDLList(size_t n_elements,
//		datatype datum)
//
// Description: 
// constructs a circular, doubly-linked list. 
//
// Programmer: Paul Bladek
//
// Date: April 15, 2011
// Version: 1.0
// Called by: main()
//
// Calls: push_front();
//
// Parameters: size_t n_elements, datatype datum
//
// History Log:
//    April 15, 2011 - PB final edits
//--------------------------------------------------
	template<class datatype>
	CDLList<datatype>::CDLList(size_t n_elements, datatype datum)
		:m_size(0), head(nullptr), tail(nullptr)
	{
		if (n_elements <= 0)
			throw out_of_range("Empty list");
		for (size_t i = 0; i < n_elements; ++i)
			push_front(datum);
	}

//--------------------------------------------------
// Function: CDLList<datatype>::CDLList(const CDLList& x)
//
// Description: copy constructor
//
// Programmer: Paul Bladek
//
// Date: April 15, 2011
// Version: 1.0
//
// Called by: main()
//
// Calls: push_front();
//
// Parameters: CDLList& x - list object to copy
//
// History Log:
//   April 15, 2011 - PB final edits
//--------------------------------------------------
	
	template<class datatype>
	CDLList<datatype>::CDLList(const CDLList& x)
		:m_size(0), head(nullptr), tail(nullptr)
	{
		CDLList<datatype>::iterator r_it = x.begin();
		push_front(*r_it);
		r_it++;
		while (r_it != x.begin())
			push_front(*r_it++);
	}
//--------------------------------------------------
// Function: CDLList<datatype>::CDLList(iterator b, iterator e)
//
// Description:constructor using iterators,
//		copies from b to one before e
//
// Programmer: Paul Bladek
//
// Date: April 15, 2011 
// Version: 1.0
//
// Called by: main()
//
// Calls: push_front();
//
// Parameters: iterator b, iterator e - iterator class objects
//
// History Log:
//   April 15, 2011 - PB final edits
//--------------------------------------------------

	template<class datatype>
	CDLList<datatype>::CDLList(iterator b, iterator e)
		:m_size(0), head(nullptr), tail(nullptr)
	{
		push_front(*b);
		iterator start = b;
		b++;
		while (b != start)
			push_front(*b++);
	}
//--------------------------------------------------
// Function: void CDLList<datatype>::CDLList::release()
//
// Description: empties the list 
//
// Programmer: Paul Bladek
//
// Date: April 15, 2011
// Version: 1.0
//
// Called by: main()
//
// Calls: pop_front();
//
// Parameters: none
//
// Returns:void
//
// History Log:
//   April 15, 2011 - PB final edits
//--------------------------------------------------

	template<class datatype> 
	void CDLList<datatype>::CDLList::release()
	{
		while (head != nullptr) 
			pop_front();
	}
//--------------------------------------------------
// Function: ostream& operator<<(ostream& sout, 
//		const CDLList<datatype>& x)
//
// Description: prints out a list 
//
// Programmer: Paul Bladek
//
// Date: April 15, 2011
// Version: 1.0
//
// input: none
//
// Output:  displays contents of list to ostream
//
// Called by: main()
//
// Calls: begin(), end();
//
// Parameters: ostream& sout, const CDLList<datatype>& x
//
// Returns: ostream reference
//
// History Log:
//   April 15, 2011 - PB final edits
//--------------------------------------------------

	template<class datatype>
	ostream& operator<<(ostream& sout, const CDLList<datatype>& x)
	{
		CDLList<datatype>::iterator p = x.begin(); // gets x.h
		if (p == nullptr)
			return sout << "()";
		else
		{
			sout << "(" << *p << ",";
			p++;
			while (p != x.end()->next)
			{
				sout << *p;
				if (p != x.end())
					sout << ",";
				++p; // advances iterator using next
			}
			sout << ")\n";
		}
		return sout;
	}
//--------------------------------------------------
// Function: void CDLList<datatype>::CDLList::
//			push_front(datatype datum)
//
// Description: insert element at front of list
//
// Programmer: Paul Bladek, modified by Tabitha Roemish
//
// Date: 5/13/2017 
// Version: 1.1
//
// Called by: main(), constructors
//
// Calls: none
//
// Parameters: datatype datum - item to add to list
//
// Returns: void
//
// History Log:
//	 April 15, 2011 - PB final edits 1.0
//   5/13/2017 TR completed version 1.1
//--------------------------------------------------

	template<class datatype>
	void CDLList<datatype>::CDLList::push_front(datatype & datum)
	{
		listelem* temp = new listelem(datum, nullptr, head);
		m_size++;
		if (!empty())
		{ 
			head->prev = temp;
			head = temp;
		}
		else
			head = tail = temp;

		//set circular
		tail->next = head;
		head->prev = tail;
	}
//--------------------------------------------------
// Function: void CDLList<datatype>::push_back(datatype datum)
//
// Description: insert element at end of list
//
// Programmer: Paul Bladek, modified by Tabitha Roemish
//
// Date: 5/13/2017 
// Version: 1.1
// Called by: main()
//
// Calls: listelem constructor
//
// Parameters: datatype datum - data to addd to back
//
// Returns: void
//
// History Log:
//	 April 15, 2011 - PB final edits 1.0
//   5/13/2017 TR completed version 1.1
//--------------------------------------------------

	template<class datatype>
	void CDLList<datatype>::push_back(datatype & datum)
	{
		listelem* temp = new listelem(datum, tail, nullptr);
		m_size++;
		if (!empty())
		{
			tail->next = temp;
			tail = temp;
		}
		else
			tail = head = temp;
		
		//set circular
		tail->next = head;
		head->prev = tail;
	}
//--------------------------------------------------
// Function: CDLList<datatype> CDLList<datatype>::
//		operator=(const CDLList & rlist)
// Description: returns a copy of rlist
//
// Programmer: Paul Bladek
//
// Date: April 15, 2011
// Version: 1.0
// Called by: main()
//
// Calls: push_front(), release(), begin();
//
// Parameters: & rlist - list to assign
//
// Returns: CDLList<datatype>
//
// History Log:
//   April 15, 2011 - PB final edits
//--------------------------------------------------
	
	template<class datatype>
	CDLList<datatype> CDLList<datatype>::operator=(const CDLList & rlist)
	{
		if (&rlist != this)
		{
			CDLList::iterator r_it = rlist.begin();
			release();
			push_front(*r_it);
			r_it++;
			while (r_it != rlist.begin())
				push_front(*r_it++);
		}
		return *this;
	}
//--------------------------------------------------
// Function: CDLList<datatype>::iterator CDLList<datatype>::
//		iterator::operator++()
//
// Description: pre-increment
//
// Programmer: Paul Bladek
//
// Date: April 15, 2011 
// Version: 1.0
//
// Called by: main()
//
// Parameters: none
//
// Returns: CDLList<datatype>::iterator
//
// History Log:
//    April 15, 2011 - PB final edits
//--------------------------------------------------

	template<class datatype>
	typename CDLList<datatype>::iterator CDLList<datatype>::iterator::operator++()
	{
		if (ptr == nullptr) 
			throw runtime_error("nullptr pointer");
		ptr = ptr->next;
		return *this;
	}
//--------------------------------------------------
// Function: CDLList<datatype>::CDLList(size_t n_elements,
//		datatype datum)
//
// Description: post-increment
//
// Programmer: Paul Bladek
//
// Date: April 15, 2011 
// Version: 1.0
//
// Called by: main()
// Parameters: none
//
// Returns: CDLList<datatype>::iterator
//
// History Log:
//  April 15, 2011 - PB final edits
//--------------------------------------------------

	template<class datatype>
	typename CDLList<datatype>::iterator CDLList<datatype>::iterator::operator++(int)
	{
		if (ptr == nullptr) 
			throw runtime_error("nullptr pointer");
		iterator temp = *this;
		ptr = ptr->next;
		return temp;
	}
//--------------------------------------------------
// Function: CDLList<datatype>::iterator
//		CDLList<datatype>::iterator::operator--()
//
// Description: pre-decrement
//
// Programmer: Tabitha Roemish
//
// Date: 5/13/2017 
// Version: 1.0
//
// Called by: main()
//
// Parameters: none
//
// Returns: CDLList<datatype>::iterator
//
// History Log:
//   5/17/2017 TR completed version 1.0
//--------------------------------------------------
	
	template<class datatype>
	typename CDLList<datatype>::iterator
		CDLList<datatype>::iterator::operator--()
	{
		if (ptr == nullptr) 
			throw runtime_error("nullptr pointer");
		ptr = ptr->prev;
		return *this;

	}
//--------------------------------------------------
// Function: CDLList<datatype>::iterator
//		CDLList<datatype>::iterator::operator--(int)
//
// Description:  post-decrement
//
// Programmer: Tabitha Roemish
//
// Date: 5/13/2017 
// Version: 1.0
//
// Called by: main()
//
// Parameters: none
//
// Returns: CDLList<datatype>::iterator
//
// History Log:
//   5/13/2017 TR completed version 1.0
//--------------------------------------------------

	template<class datatype>
	typename CDLList<datatype>::iterator
		CDLList<datatype>::iterator::operator--(int)
	{
		if (ptr == nullptr)
			throw runtime_error("nullptr pointer");
		iterator temp = *this;
		ptr = ptr->prev;
		return temp;
	}
//--------------------------------------------------
// Function: datatype CDLList<datatype>::pop_front()
//
// Description:  removes front element and returns 
//		the data from that element 
//
// Programmer: Paul Bladek, modified by Tabitha Roemish
//
// Date: 5/13/2017 
// Version: 1.1
//
// Called by: main()
//
// Calls: begin(), empty()
//
// Parameters: none
//
// Returns: datatype 
//
// History Log:
//	 April 15, 2011 - PB final edits 1.0
//   5/13/2017 TR completed version 1.1
//--------------------------------------------------
	template<class datatype>
	datatype CDLList<datatype>::pop_front()
	{
		if (head == nullptr)
			throw runtime_error("Empty list");
		
		datatype data = head->data;
		iterator temp = begin();
		temp++;
		if (m_size-- == 1)
			temp = nullptr;
		delete head;
		head = temp;
		if (!empty())
			head->prev = tail;
	
		return data;
	}
//--------------------------------------------------
// Function: datatype CDLList<datatype>::pop_back()
//
// Description: removes back element and returns 
//		the data from that element
//
// Programmer: Paul Bladek, modified by Tabitha Roemish
//
// Date: 5/13/2017 
// Version: 1.1
//
// Called by: main()
//
// Calls: empty(), end();
//
//Parameters: none
//
// Returns: datatype
//
// History Log:
//	 April 15, 2011 - PB final edits 1.0
//   5/13/2017 TR completed version 1.1
//--------------------------------------------------

	template<class datatype>
	datatype CDLList<datatype>::pop_back()
	{
		if (tail == nullptr)
			throw runtime_error("Empty List");
		
		datatype data = tail->data;
		iterator temp = end();
		temp--;
		if(m_size--==1)
			temp=nullptr;
		delete tail;
		tail = temp;
		if (!empty())
			tail->next= head;
	
		return data;
	}
//--------------------------------------------------
// Function: datatype& CDLList<datatype>::operator[](int index)
//
// Description: [] operator -- l-value
//
// Programmer:Paul Bladek, modified by Tabitha Roemish
//
// Date: April 15, 2011
// Version: 1.1
//
// Called by: main()
//
// Calls: begin(), end();
//
// Parameters: int index (index of list)
//
// Returns: datatype&
//
// History Log:
//	 April 15, 2011 - PB final edits 1.0
//   5/13/2017 TR completed version 1.1
//--------------------------------------------------

	template<class datatype>
	datatype& CDLList<datatype>::operator[](int index)
	{
		iterator it;
		if (index >= 0)
		{
			if (index >= static_cast<int>(getSize()))
				throw out_of_range("index out-of-range");
			it = begin();
			for (int i = 0; i < index; i++)
				it++;
		}
		else
		{
			if (index < -(static_cast<int>(getSize())))
				throw out_of_range("index out-of-range");
			it = end()->prev;
			for (int i = -1; i > index; i--)
				it--;
		}
		return *it;
	}
//--------------------------------------------------
// Function: CDLList<datatype>::CDLList(size_t n_elements,
//		datatype datum)
//
// Description: [] operator -- r-value 
//
// Programmer:Paul Bladek, modified by Tabitha Roemish
//
// Date: April 15, 2011
// Version: 1.1
//
// Called by: main()
//
// Calls: begin(), end()
//
// Parameters: int index, list index
//
// Returns: const datatype& 
//
// History Log:
//	 April 15, 2011 - PB final edits 1.0
//   5/13/2017 TR completed version 1.1
//--------------------------------------------------

	template<class datatype>
	const datatype& CDLList<datatype>::operator[](int index)const
	{
		iterator it;
		if (index >= 0)
		{
			if (index >= static_cast<int>(getSize()))
				throw out_of_range("index out-of-range");
			it = begin();
			for (int i = 0; i < index; i++)
				it++;
		}
		else
		{
			if (index < -(static_cast<int>(getSize())))
				throw out_of_range("index out-of-range");
			it = end()->prev;
			for (int i = -1; i > index; i--)
				it--;
		}
		return *it;
	}
}
#endif