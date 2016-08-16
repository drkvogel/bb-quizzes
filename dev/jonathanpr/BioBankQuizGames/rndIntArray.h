//---------------------------------------------------------------------------
#ifndef rndIntArrayH
#define rndIntArrayH
//---------------------------------------------------------------------------
#include <exception>
#include <stdlib.h>  //srand
#include <time.h> //ctime
#include <new>  //bad_alloc

class Exception_rndIntArray_Empty : public std::exception {
public:
	virtual const char* what() const {
		return "pop on empty";
	}
};


class rndIntArray {
public:
	rndIntArray(int size = 18) {
		srand(time(NULL));
		m_size = size;
		m_used = 0;
		m_data = NULL; // int *m_data;
	}

	~rndIntArray() {
		if (m_data)
			delete []m_data;
	}

	void push(int newInt) {
		checkGrow();							// check if the size of the array needs to grow
		m_data[m_used] = newInt;				// push the value onto the stack
		m_used++;
	}

	int pop() {
		if (isEmpty()) 
			throw Exception_rndIntArray_Empty();

		int index = 0;
		if (m_used > 1)
			index = (rand() % (m_used-1));		// pick a random element from the list
		int result = m_data[index];				// that's your popped result

		for (int i=index;i<m_used-1;i++)
			m_data[i] = m_data[i+1];			// shuffle the others left to fill gap
		m_used--;								// number of elements is one less
		return result;
	}

	bool isEmpty() {
		return (m_used==0);
	}

private:
	void checkGrow() {
		if (m_data == NULL) {					// no data yet, initialise at m_size
			m_data = new int[m_size];
		} else if (m_used == m_size) {
			int *m_biggerData = new int[m_size*2]; // create new twice as big
			if (m_biggerData == NULL) 
				throw std::bad_alloc();			// if it fails
			for (int i=0;i<m_size;i++) 
				m_biggerData[i] = m_data[i];	// copy old to new
			delete []m_data;					// delete old
			m_data = m_biggerData;				// swap
			m_size *=2;							// size is double
		}
	}

	int *m_data;
	int m_size;
	int m_used;
};

#endif
