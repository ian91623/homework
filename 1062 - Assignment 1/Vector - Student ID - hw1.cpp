#include "Vector.h" // include definition of class vector 

// Constructs a zero vector with size n.
vector::vector( unsigned int n )
{
	if( n == 0 )
		myFirst = myLast = myEnd = nullptr;
	else
	{
		myFirst = new int[ n ]();
		myLast = myEnd = myFirst + n;
	}
} // end default constructor

// Destroys the vector.
vector::~vector()
{
	if( myFirst != nullptr )
		delete[] myFirst;
} // end destructor

unsigned int vector::size()
{
	return ( myLast - myFirst );
}

unsigned int vector::capacity()
{
	return ( myEnd - myFirst );
}

void vector::push_back( const int val )
{
	resize(size()+1);
	*(myLast-1) = val;
}

// Removes the last element in the vector,
// effectively reducing the container size by one.
void vector::pop_back()
{
	if( size() > 0 )
	{
		--myLast;
		*myLast = int();
	}
}

void vector::resize( unsigned int n )
{
	if(capacity() == 0)
	{
		myFirst = new int[n]();
		myEnd = myLast = myFirst + n;
	}
	else if(n > capacity())
	{
		int newCapacity = capacity()*3/2 > n ? capacity()*3/2 : n;
		int* tmpPtr = new int[newCapacity]();
		for(int i=0 ; i<size() ; i++)
			tmpPtr[i] = myFirst[i];
		myEnd = tmpPtr + newCapacity;
		myLast = tmpPtr + n;
		delete [] myFirst;
		myFirst = tmpPtr;
	}
	else
	{
		for(int i=size() ; i<n ; i++)
			myFirst[i] = int();
		myLast = myFirst + n;
	}
}

// Determines if two vectors are equal.
bool vector::equal( std::vector< int > &v )
{
	if( capacity() != v.capacity() )
		return false;

	if( size() != v.size() )
		return false;

	for( unsigned int i = 0; i < size(); i++ )
		if( myFirst[ i ] != v[ i ] )
			return false;

	return true;
}