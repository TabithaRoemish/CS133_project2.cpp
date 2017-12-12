#include "CDLList.h"
#include "PublicQueue.h"
#include <exception>
#include <iostream>


using namespace std;
class methodNotSupported : public exception
{
	virtual const char* what() const throw()
	{
		return "This method is not supported by publicQueue";
	}
};

using namespace PB_ADT;
int main(void)
{
	try
	{
		CDLList<int> test(5, 5);
		CDLList<int> * ptr = &test;
		cout << "CDLList<int> * ptr: (*ptr) " << *ptr;

		publicQueue<int> pqtest(5, 4);
		
		publicQueue<int> * pqptr = &pqtest;
		cout << "publicQueue<int> * pqptr: (*pqptr) " << *pqptr;
		cout << endl;

		ptr = &pqtest;
		
		cout << "CDLList<int> * ptr = &pqtest" << endl;
		
		cout << "ptr->print(cout): ";
		ptr->print(cout);
		cout << endl;

		cout << "pqtest->pop_front(): (should throw error)" <<endl;
		pqptr->pop_front();


		
		

		
	}
	catch (exception & e)
	{
		cerr << e.what();
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}