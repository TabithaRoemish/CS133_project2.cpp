//--------------------------------------
// File: QueueClass.h
// Class Queue
// Functions:
////		queue() : CDLList() {};
//			queue(listelem* hd, listelem* tl, unsigned size) :
//				CDLLList(hd, tl, size) {};
//			queue(const queue& qu) : CDLList(qu) {};
//			queue(iterator b, iterator e) : CDLList(b, e) {};
//			virtual ~queue() { release(); };
//			unsigned getSize();
//			iterator begin();
//			iterator end();
//			bool empty();
//			void release();
//			void push(T& element);
//			T pop();
//			print(ostream& sout);
//---------------------------------------
#ifndef PUBLICQUEUE_H
#define PUBLICQUEUE_H

#include "CDLList.h"
#include <iostream>
#include <cassert>
#include <exception>
#include <cstdlib>

using namespace std;

//-----------------------------------------------------------------------------
//   Title: Queue Class Declaration and Definitions
//   Description: This file contains the class declarations and definitions for 
//					queue
//
//   Programmer: Tabitha Roemish
// 
//   Date: original: May 16, 2017
//   Version: 1.0
//
//   Environment: Intel Xeon PC
//     Software: Windows 10 Enterprise
//     Compiles under Microsoft Visual C++.Net 2015
//
//   class list:
//
//     Methods:
// 
//       inline: 
//			queue() : CDLList() {}; -- default constructor
//			queue(listelem* hd, listelem* tl, unsigned size) :
//				CDLLList(hd, tl, size) {}; -- constructor with two parameters
//			queue(const queue& qu) : CDLList(qu) {}; - constructor that copies a queue
//			Queue(const CDLList<T> & cl) : CDLList(cl) {}; -- constructor that takes CDLList
//			queue(iterator b, iterator e) : CDLList(b, e) {}; -- copy constructor with iterators
//			virtual ~queue() { release(); }; -- destructor for queue
//			unsigned getSize(); -- returns unsigned size of queue/CDLList
//			iterator begin(); -- returns iterator, beginning of queue/CDLList
//			iterator end();-- returns iterator, end of queue/CDLList
//			bool empty(); -- returns bool, false if list is not empty
//			void release(); -- returns non- releases and deletes list elements
//			void push(T& element);
//			T pop();
//			print(ostream& sout);
//
//   History Log:
//		5/16/2017 v1.0 completed by TR
//-----------------------------------------------------------------------------
namespace PB_ADT
{
	template<class T> class publicQueue : public CDLList<T>
	{
	public:
		publicQueue() : CDLList() {};
		publicQueue(size_t qsize, T data) : CDLList(qsize, data) {};
		publicQueue(const publicQueue<T>& qu) : CDLList(qu) {};
		publicQueue(const CDLList<T> & cl) : CDLList(cl) {};
		publicQueue(CDLList<T>::iterator b, CDLList<T>::iterator e) : CDLList(b, e) {};

		virtual  ~publicQueue() { release(); };
		virtual unsigned getSize() { return CDLList<T>::getSize(); };
		virtual iterator begin() { return CDLList<T>::begin(); };
		virtual iterator end() { return CDLList<T>::end(); };
		virtual bool empty() { return CDLList<T>::empty(); };
		virtual void release() { return CDLList<T>::release(); };
		virtual void push(T& element) { return CDLList<T>::push_back(element); };
		T pop() { return CDLList<T>::pop_front(); };
		void print(ostream& sout);


		void push_front(T & datum) { throw methodNotSupported(); };
		T pop_front() { throw methodNotSupported(); };
		void push_back(T & datum) { throw methodNotSupported(); };
		T pop_back() { throw methodNotSupported(); };
		T& front() const { throw methodNotSupported(); };
		T& back() const { throw methodNotSupported(); };

			};

	//--------------------------------------------------
	// Function: void Queue<T>::print(ostream& sout)
	//
	// Description: prints a queue
	//
	// Programmer: Tabitha Roemish
	//
	// Date: 5/19/2017
	// Version: 1.0
	// Called by: main()
	//
	// output: outputs queue to ostream reference
	//
	// Parameters: ostream& sout 
	//
	// History Log:
	//    5/19/2017 TR completed v1
	//--------------------------------------------------
	template<class T>
	void publicQueue<T>::print(ostream& sout)
	{
		sout << "(";
		iterator it = begin();
		while (it != end())
		{
			sout << *it << ", ";
			it++;
		}
		if (end() != nullptr)
			sout << *it;
		sout << ")";
	}
}
#endif
		