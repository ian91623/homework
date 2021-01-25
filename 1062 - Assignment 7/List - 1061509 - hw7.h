#ifndef LIST_H
#define LIST_H

// ListNode class template definition
template< typename T >
struct ListNode
{
	ListNode *next;
	T myVal;
	ListNode *prev;
}; // end class template ListNode


// ListIterator class template definition
template< typename T >
class ListIterator
{
public:
	ListIterator( ListNode< T > *p = nullptr ) // default constructor
		: ptr( p )
	{
	}

	ListIterator( const ListIterator &iteratorToCopy ) // copy constructor
		: ptr( iteratorToCopy.ptr )
	{
	}

	~ListIterator() // destructor
	{
	}

	// const return avoids: ( a1 = a2 ) = a3
	const ListIterator &operator=( const ListIterator &right )
	{
		if( &right != this ) // avoid self-assignment
			ptr = right.ptr;
		return *this; // enables x = y = z, for example
	}

	bool operator==( const ListIterator &right ) const // equal to
	{
		return ptr == right.ptr;
	}

	bool operator!=( const ListIterator &right ) const // not equal to
	{
		return ptr != right.ptr;
	}

	T& operator*() const // dereferencing operator
	{
		return ptr->myVal;
	}

	ListIterator& operator++() // prefix increment operator
	{
		ptr = ptr->next;
		return *this;
	}

	ListIterator& operator--() // prefix decrement operator
	{
		ptr = ptr->prev;
		return *this;
	}

private:
	ListNode< T > *ptr; // keep a pointer to list
}; // end class template ListIterator


// ReverseListIterator class template definition
template< typename T >
class ReverseListIterator
{
public:
	ReverseListIterator( ListNode< T > *p = nullptr ) // default constructor
		: ptr( p )
	{
	}

	ReverseListIterator( const ReverseListIterator &iteratorToCopy ) // copy constructor
		: ptr( iteratorToCopy.ptr )
	{
	}

	~ReverseListIterator() // destructor
	{
	}

	// const return avoids: ( a1 = a2 ) = a3
	const ReverseListIterator &operator=( const ReverseListIterator &right )
	{
		if( &right != this ) // avoid self-assignment
			ptr = right.ptr;
		return *this; // enables x = y = z, for example
	}

	bool operator==( const ReverseListIterator &right ) const // equal to
	{
		return ptr == right.ptr;
	}

	bool operator!=( const ReverseListIterator &right ) const // not equal to
	{
		return ptr != right.ptr;
	}

	T& operator*() const // dereferencing operator
	{
		return ptr->myVal;
	}

	ReverseListIterator& operator++() // prefix increment operator
	{
		ptr = ptr->prev;
		return *this;
	}

	ReverseListIterator& operator--() // prefix decrement operator
	{
		ptr = ptr->next;
		return *this;
	}

private:
	ListNode< T > *ptr; // keep a pointer to list
}; // end class template ReverseListIterator


// list class template definition
template< typename T >
class list
{
	template< typename T >
	friend bool operator==( const list< T > &lhs, const list< T > &rhs );

	template< typename T >
	friend bool operator!=( const list< T > &lhs, const list< T > &rhs );

public:
	using iterator = ListIterator< T >;
	using reverse_iterator = ReverseListIterator< T >;

	list( unsigned int n = 0 ); // Constructs an empty list container, with no elements.

	// Constructs a list container with a copy of each of the elements in x,
	// in the same order.
	list( const list &x );

	// Destroys all list elements,
	// and deallocates all the storage allocated by the list container.
	~list();

	// Copies all the elements from "right" into the list container 
	const list& operator=( const list &x );

	iterator begin() const; // Returns a pointer pointing to the first element in the list container.

	iterator end() const; // Returns an pointer referring to the past-the-end element in the list container.

	reverse_iterator rbegin() const; // Returns a pointer pointing to the last element in the list container
												// (i.e., its reverse beginning).

	reverse_iterator rend() const; // Returns a pointer pointing to the theoretical element preceding
											 // the first element in the list container (which is considered its reverse end).

	// Returns the number of elements in the list container.
	unsigned int size() const;

	// Resizes the list container so that it contains n elements.
	// If n is smaller than the current list container mySize,
	// the content is reduced to its first n elements, removing those beyond.
	// If n is greater than the current list container mySize,
	// the content is expanded by inserting at the end
	// as many elements as needed to reach a mySize of n.
	void resize( unsigned int n );

	// Adds a new element at the end of the list container,
	// after its current last element.
	// The content of val is copied to the new element.
	// This effectively increases the container size by one.
	void push_back( const T val );

	// Removes the last element in the list container,
	// effectively reducing the container size by one.
	void pop_back();

	// Removes all elements from the list container (which are destroyed).
	void clear();

	T& operator[]( size_t n );

	const T& operator[]( size_t n ) const;

private:
	unsigned int mySize = 0; // the number of elements in the list container

	// pointing to the past-the-end element in the list container
	ListNode< T > *myHead = nullptr;
}; // end class template list


// Constructs a list container with n elements.
template< typename T >
list< T >::list( unsigned int n )
{
	myHead = new ListNode< T >;
	myHead->myVal = T();
	myHead->prev = myHead->next = myHead;

	for( unsigned int i = 0; i < n; i++ )
		push_back( T() );
}

// Constructs a list container with a copy of each of the elements in x,
// in the same order.
template< typename T >
list< T >::list( const list< T > &x )
	: list( x.mySize )
{
	*this = x;
}

// Destroys all list container elements,
// and deallocates all the storage allocated by the list container.
template< typename T >
list< T >::~list()
{
	clear();
	delete myHead;
}

// Assigns new contents to the container, replacing its current contents,
// and modifying its size accordingly.
template< typename T >
const list< T >& list< T >::operator=( const list< T > &x )
{
	resize(x.size());
	for(iterator it = begin(),it2 = x.begin() ; it!=end() ; ++it , ++it2)
		*it = *it2;
	return *this;
} // end function operator=

template< typename T >
typename list< T >::iterator list< T >::begin() const
{
	return iterator( myHead->next );
}

template< typename T >
typename list< T >::iterator list< T >::end() const
{
	return iterator( myHead );
}

template< typename T >
typename list< T >::reverse_iterator list< T >::rbegin() const
{
	return reverse_iterator( myHead->prev );
}

template< typename T >
typename list< T >::reverse_iterator list< T >::rend() const
{
	return reverse_iterator( myHead );
}

template< typename T >
unsigned int list< T >::size() const
{
	return mySize;
}

template< typename T >
void list< T >::resize( unsigned int n )
{
	if( n > mySize )
	{
		unsigned int difference = n - mySize;
		for( unsigned int i = 0; i < difference; i++ ) // create n - mySize elements
			push_back( T() );
	}
	else if( n < mySize )
	{
		unsigned int difference = mySize - n;
		for( unsigned int i = 0; i < difference; i++ ) // erase mySize - n elements
			pop_back();
	}
}

template< typename T >
void list< T >::push_back( const T val )
{
	ListNode<T>* temp = myHead->prev;
	temp->next = new ListNode<T>;
	temp = temp->next;
	temp->myVal = val;
	temp->prev = myHead->prev;
	myHead->prev = temp;
	temp->next = myHead;
	mySize++;
}

template< typename T >
void list< T >::pop_back()
{
	ListNode<T>* temp = myHead->prev->prev;
	delete myHead->prev;
	temp->next = myHead;
	myHead->prev = temp;
	mySize--;
}

// Removes all elements from the list container (which are destroyed)
template< typename T >
void list< T >::clear()
{
	while( mySize > 0 )
		pop_back();
}


// determine if two lists are equal and rerturn true, otherwise return false
template< typename T >
bool operator==( const list< T > &lhs, const list< T > &rhs )
{
	if(lhs.size() != rhs.size())
		return false;
	else
		for(typename list<T>::iterator it1 = lhs.begin(),it2 = rhs.begin() ; it1 != lhs.end() ; ++it1 , ++it2)
			if(*it1 != *it2)
				return false;
	return true;
	// return (lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

// inequality operator; returns opposite of == operator
template< typename T >
bool operator!=( const list< T > &lhs, const list< T > &rhs )
{
	return !( lhs == rhs );
}

template< typename T >
T& list< T >::operator[]( size_t n )
{
	iterator tmpPtr = begin();
	for(int i=0 ; i<n ; i++, ++tmpPtr);
	return *tmpPtr;
}

template< typename T >
const T& list< T >::operator[]( size_t n )const
{
	iterator tmpPtr = begin();
	for(int i=0 ; i<n ; i++, ++tmpPtr);
	return *tmpPtr;
}


#endif