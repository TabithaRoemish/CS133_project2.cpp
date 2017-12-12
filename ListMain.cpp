//-----------------------------------------------------------------------------
// File ListMain.cpp
// Functions: main()
//-----------------------------------------------------------------------------

#include "List.h"
#include"QueueClass.h"

//--------------------------------------------------
// Functions: main() 
//
// Title: Circular Doubly-Linked List
//
// Description: 
//  Using a circular, doubly linked list
//
// Programmer: Tabitha Roemish
//
// Date: 5/13/2017 
//
// Version: 1.0 
//
// Environment: // Hardware: Intel core i5
//   Software: Windows 10
//   Compiles under Microsoft Visual Studio 2015
//
// Output:  list display
//
// Parameters: void 
//
// Returns: EXIT_SUCCESS 
//
// History Log:
//   5/13/2017 TR completed version 1.0
//--------------------------------------------------
using namespace PB_ADT;
using namespace std;

int main(void)
{
	try
	{ 
	// test CDLList

	CDLList<int> dconstructor;
	CDLList<int> twoParConstruct(5, 6);
	CDLList<int> copyConstruct(twoParConstruct);
	CDLList<int>::iterator it = twoParConstruct.begin();
	CDLList<int> itConstruct(it, twoParConstruct.end());
	
		// test constructors
	cout << "CDLList Testing" << endl;
	cout << endl;
	cout << "dconstructor: " << dconstructor;
	cout << "twoParConstruct: " << twoParConstruct;
	cout << "copyConstruct (copy twoParConstruct): " << copyConstruct;
	cout << "itConstruct: " << itConstruct;
	 
		// test methods
	int push = 5;
	copyConstruct.push_front(push);
	cout << "copyConstruct.push_front(5): " << copyConstruct;
	copyConstruct.push_back(push);
	cout << "copyConstruct.push_back(5): " << copyConstruct << endl;
		
		//assignment operator test
	itConstruct = copyConstruct;
	cout << "itConstruct = copyConstruct: (itConstruct) " << itConstruct;
	cout << endl;
		
		// pop and push
	copyConstruct.pop_front();
	cout << "copyConstruct.pop_front(): " << copyConstruct;
	copyConstruct.pop_back();
	cout << "copyConstruct.pop_back(): " << copyConstruct << endl;
	
		//test [] operator
	for (unsigned i = 0; i < copyConstruct.getSize(); i++)
		copyConstruct[i] = 2 * i;
	cout << "Fill copyConstruct with multiples of 2 using []: " << copyConstruct << endl;
		
		// test iterator methods
	CDLList<int>::iterator start = copyConstruct.begin();
	cout << "copyConstruct.begin(): " << *start << endl;

	CDLList<int>::iterator end = copyConstruct.end();
	cout << "copyConstruct.end(): " << *end << endl;

	start++;
	cout << "copyConstruct.begin()++: " << *start << endl;

	end--;
	cout << "copyConstruct.end()--: " << *end << endl;
	cout << endl;

		//test pointer and target operators
	CDLList<int> * cdllptr = &itConstruct;
	cout << "cdllptr = &itConstruct: " << itConstruct;
	cout << "cdllptr->front(): " << cdllptr->front() << endl;
	cout << "*cdllptr: " << *cdllptr;

	// test queue
	cout << "Queue testing" << endl;
	cout << endl;
	CDLList<string> copyTest(6, "x");
	Queue<string> qDefault;
	Queue<string> q2ParConstruct(5, "Test String");
	Queue<string> qcopyConstruct(q2ParConstruct);
	Queue<string> qcopyCDLLConstruct(copyTest);
	Queue<string> qitConstruct(qcopyCDLLConstruct.begin(), qcopyCDLLConstruct.end());
	 
		// test constructors
	cout << "qDefault: ";
	qDefault.print(cout);
	cout << endl;
	
	cout << "q2ParConstruct(5, ""Test String""): ";
	q2ParConstruct.print(cout);
	cout << endl;
	
	cout << "qcopyConstruct(q2ParConstruct): ";
	qcopyConstruct.print(cout);
	cout << endl;

	cout << "CDLL copy Test: " << copyTest;
	cout << "qcopyCDLLConstruct(copyTest): ";
	qcopyCDLLConstruct.print(cout);
	cout << endl;

	cout << "qitConstruct(qcopyCDLLConstruct.begin(), qcopyCDLLConstruct.end()): ";
	qitConstruct.print(cout); 
	cout << endl;
	cout << endl;
	 
		// test methods
	string spush = "New";
	qitConstruct.push(spush);
	cout << "qitConstruct.push(""new""): ";
	qitConstruct.print(cout);
	cout << endl;

	qitConstruct.pop();
	cout << "qitConstruct.pop(): ";
	qitConstruct.print(cout);
	cout << endl;

		//test pointers and target method with queue
	Queue<string> * qptr = &qitConstruct;
	cout << "qptr->print: ";
	qptr->print(cout);
	
	}
	catch (out_of_range & oa)
	{
		cout << oa.what();
		return EXIT_FAILURE;
	}
	catch (bad_alloc & ba)
	{
		cout << ba.what();
		return EXIT_FAILURE;
	}
	catch (exception & e)
	{
		cout << e.what();
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}