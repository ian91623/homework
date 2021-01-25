#ifndef VECTOR_H
#define VECTOR_H

// vector class template definition
template< typename T >
class vector
{
   template< typename T >
   friend bool operator==( const vector< T > &lhs, const vector< T > &rhs );

   template< typename T >
   friend bool operator!=( const vector< T > &lhs, const vector< T > &rhs );
public:
   using iterator = T*;

   vector( unsigned int n = 0 ); // Constructor; Constructs a zero vector with size n

   // Copy constructor; Constructs a vector with a copy of each of the elements in x.
   vector( const vector &x );

   ~vector(); // Destroys the vector.

   const vector& operator=( const vector &x ); // assignment operator

   iterator begin() const; // Returns a pointer pointing to the first element in the vector.
                           // If the vector is empty, the returned pointer shall not be dereferenced.

   // Returns an pointer pointing to the past-the-end element in the vector.
   // The past-the-end element is the theoretical element that would follow the last element in the vector.
   // It does not point to any element, and thus shall not be dereferenced.
   iterator end() const;

   // Returns the number of elements in the vector.
   // This is the number of actual objects held in the vector,
   // which is not necessarily equal to its storage capacity.
   unsigned int size() const;

   // Returns the size of the storage space currently allocated for the vector,
   // expressed in terms of elements.
   unsigned int capacity() const;
   
   // Adds a new element at the end of the vector, after its current last element.
   // The content of val is copied to the new element.
   // This effectively increases the vector size by one,
   // which causes an automatic reallocation of the allocated storage space
   // if and only if the new vector size surpasses the current vector capacity.
   void push_back( const T val );

   // Removes the last element in the vector,
   // effectively reducing the container size by one.
   void pop_back();

   // Resizes the vector so that it contains n elements.
   // If n is smaller than the current vector size,
   // the content is reduced to its first n elements, removing those beyond.
   // If n is greater than the current vector size,
   // the content is expanded by inserting at the end as many elements as needed to reach a size of n.
   // The new elements are initialized as 0.
   // If n is also greater than the current vector capacity,
   // an automatic reallocation of the allocated storage space takes place.
   void resize( unsigned int n );

   T& operator[](size_t n);

   const T& operator[](size_t n)const;

private:
   T *myFirst = nullptr;
   T *myLast = nullptr;
   T *myEnd = nullptr;
}; // end class template vector


// constructor; constructs a zero vector with size n
template< typename T >
vector< T >::vector( unsigned int n )
   : myFirst( n == 0 ? nullptr : new T[ n ]() ),
     myLast( n == 0 ? nullptr : myFirst + n ),
     myEnd( n == 0 ? nullptr : myLast )
{
} // end vector default constructor

template< typename T >
vector< T >::vector( const vector< T > &x )
{  
   if(x.capacity() == 0)
      myFirst = myLast = myEnd = nullptr;
   else
   {
      myFirst = new T[x.capacity()]();
      myLast = myFirst + x.size();
      myEnd = myFirst + x.capacity();
      for(int i=0 ; i<x.size() ; i++)
         myFirst[i] = x.myFirst[i];
   }
}

// destructor; destroys the vector
template< typename T >
vector< T >::~vector()
{
   if( myFirst != nullptr )
      delete[] myFirst;
} // end destructor

template< typename T >
const vector<T>& vector< T >::operator=( const vector<T> &x )
{
   resize(x.size());
   for(int i=0 ; i<x.size() ; i++)
      myFirst[i] = x.myFirst[i];
   return *this;
}

template< typename T >
T* vector< T >::begin() const
{
   return myFirst;
}

template< typename T >
T* vector< T >::end() const
{
   return myLast;
}

template< typename T >
unsigned int vector< T >::size() const
{
   return ( myLast - myFirst );
}

template< typename T >
unsigned int vector< T >::capacity() const
{
   return ( myEnd - myFirst );
}

template< typename T >
void vector< T >::push_back( const T val )
{
   if(myEnd == myLast)
   {
      resize(capacity()+1);
      myLast--;
   }
   *myLast = val;
   myLast++;
}

template< typename T >
void vector< T >::pop_back()
{
   if( size() > 0 )
   {
      --myLast;
      *myLast = T();
   }
}

template< typename T >
void vector< T >::resize( unsigned int n )
{
   if(capacity() == 0)
   {
      myFirst = new T[n]();
      myEnd = myLast = myFirst + n;
   }
   else if(n > capacity())
   {
      T *tempPtr = new T[capacity()*3/2 > n ? capacity()*3/2 : n]();
      for(int i=0 ; i<size() ; i++)
         tempPtr[i] = myFirst[i];
      myLast = myEnd = tempPtr + n;
      delete [] myFirst;
      myFirst = tempPtr;
   }
   else
   {
      for(int i=size() ; i<n ; i++)
         myFirst[i] = T();
      myLast = myFirst + n;
   }
}

template< typename T >
T& vector< T >::operator[](size_t n)
{
   return myFirst[n];
}

template< typename T >
const T& vector< T >::operator[](size_t n) const
{
   return myFirst[n];
}

// inequality operator; returns opposite of == operator
template< typename T >
bool operator!=( const vector< T > &lhs, const vector< T > &rhs )
{
   return !( lhs == rhs ); // invokes vector::operator==
}

template< typename T >
bool operator==( const vector< T > &lhs, const vector< T > &rhs )
{
   if(lhs.size()!=rhs.size())
      return false;
   else
      for(int i=0 ; i<lhs.size() ; i++)
         if(lhs.myFirst[i] != rhs.myFirst[i])
            return false;
   return true;
}

#endif