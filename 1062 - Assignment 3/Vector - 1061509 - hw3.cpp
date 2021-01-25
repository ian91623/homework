#include "Vector.h" // include definition of class vector

// constructor; constructs a zero vector with size n
vector::vector( unsigned int n )
   : myFirst( n == 0 ? nullptr : new int[ n ]() ),
      myLast( n == 0 ? nullptr : myFirst + n ),
       myEnd( n == 0 ? nullptr : myLast )
{
} // end vector default constructor

vector::vector( const vector &x )
{
    if(x.capacity() == 0)
    {
        myFirst = myLast = myEnd = nullptr;
    }
    else
    {
        myFirst = new int[x.capacity()]();
        myLast = myFirst + x.size();
        myEnd = myFirst + x.capacity();
        for(int i=0 ; i<x.size() ; i++)
        {
            *(myFirst + i) = *(x.myFirst + i);
        }
    }
}

// destructor; destroys the vector
vector::~vector()
{
   if( myFirst != nullptr )
      delete[] myFirst;
} // end destructor

const vector& vector::assign( const vector &x )
{
    resize(x.size());
    for(int i=0 ; i<x.size() ; i++)
        *(myFirst + i) = *(x.myFirst + i);
    return *this;
}

int* vector::begin() const
{
   return myFirst;
}

int* vector::end() const
{
   return myLast;
}

unsigned int vector::size() const
{
   return ( myLast - myFirst );
}

unsigned int vector::capacity() const
{
   return ( myEnd - myFirst );
}

void vector::push_back( const int val )
{
    if(myEnd == myLast)
    {
        resize(capacity()+1);
        myLast--;
    }
    *myLast = val;
    myLast++;
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

void vector::resize(unsigned int n)
{
    int a = capacity() * 1.5;
    int b = capacity();
    int c = size();
    if(b == 0)
    {
        myFirst = new int [n]();
        myLast = myEnd = myFirst+n;
    }
    else if(n >= a)
    {
        int *tempPtr;
        tempPtr = myFirst;
        myFirst = new int[n]();
        for(int i=0 ; i<c ; i++)
        {
            *(myFirst+i) = *(tempPtr+i);
        }
        myLast = myEnd = myFirst + n;
        delete [] tempPtr;
    }
    else if(n <= b)
    {

        myLast = myFirst + n;
        if(n > c)
            for(int i=0 ; myFirst+c+i<myLast ; i++)
            {
                *(myFirst+c+i) = 0;
            }
    }
    else
    {
        int *tempPtr;
        tempPtr = myFirst;
        myFirst = new int[a]();
        for(int i =0 ; i<c ; i++)
        {
            *(myFirst+i) = *(tempPtr+i);
        }
        myLast = myFirst + n;
        myEnd = myFirst + a;
        delete [] tempPtr;
    }
}
