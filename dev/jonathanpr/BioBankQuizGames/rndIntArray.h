//---------------------------------------------------------------------------

#ifndef rndIntArrayH
#define rndIntArrayH
//---------------------------------------------------------------------------
#include <exception>
#include <stdlib.h>  //srand
#include <time.h> //ctime
#include <new>  //bad_alloc

class Exception_rndIntArray_Empty : public std::exception
{
public:
	virtual const char* what() const
	{
		return "pop on empty";
	}
};


class rndIntArray
{
public:
	rndIntArray(int size = 18)
	{
		srand(time(NULL));
		m_size = size;
		m_used = 0;
		m_data = NULL;
	}

	~rndIntArray()
	{
		if (m_data)
			delete []m_data;
	}

	void push(int newInt)
	{
		checkGrow();
		m_data[m_used] = newInt;
		m_used++;
	}

	int pop()
	{
		if (isEmpty())
			throw Exception_rndIntArray_Empty();

		int index = 0;
		if (m_used > 1)
			index = (rand() % (m_used-1));
		int result = m_data[index];

		for (int i=index;i<m_used-1;i++)
			m_data[i] = m_data[i+1];
		m_used--;
		return result;
	}

	bool isEmpty()
	{
		return (m_used==0);
	}

private:
	void checkGrow()
	{
		if (m_data == NULL)
		{
			m_data = new int[m_size];
		}
		else if (m_used == m_size)
		{
			int *m_biggerData = new int[m_size*2];
			if (m_biggerData == NULL)
				throw std::bad_alloc();

			for (int i=0;i<m_size;i++)
				m_biggerData[i] = m_data[i];
			delete []m_data;
			m_data = m_biggerData;
			m_size *=2;
		}
	}

	int *m_data;
	int m_size;
	int m_used;
};

#endif
