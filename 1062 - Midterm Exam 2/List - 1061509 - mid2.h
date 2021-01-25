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


//template< typename T > class list;

// ListIterator class template definition
template< typename T >
class ListIterator
{
	template< typename U > friend class list;
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
	const ListIterator& operator=( const ListIterator &right )
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

	// overloaded class member access operator
	T* operator->() const
	{
		return &( ptr->myVal );
	}

	ListIterator& operator++() // prefix increment operator
	{
		ptr = ptr->next;
		return *this;
	}

private:
	ListNode< T > *ptr = nullptr; // keep a pointer to list
}; // end class template ListIterator


// list class template definition
template< typename T >
class list
{
public:
	using iterator = ListIterator< T >;

	list(); // Default constructor; Constructs an empty list container, with no elements.

	// Copy constructor; Constructs a list container with a copy of each of the elements in x.
	list( const list &x );

	// Destructor; Destroys all linked list elements, and deallocates all the storage allocated by the list container.
	~list();

	iterator begin() const; // Returns a pointer pointing to the first element in the list container.

	iterator end() const; // Returns an pointer referring to the past-the-end element in the list container.

	bool empty() const; // Returns a bool value indicating whether the linked list is empty.

	// The list container is extended by inserting a new element before the element at the specified position.
	// This effectively increases the list size by one.
	iterator insert( iterator position, const T val );

	// Removes from the list container the element at the specified position.
	// This effectively reduces the list size by one.
	iterator erase( iterator position );

	void clear(); // Removes all elements from the list container (which are destroyed).

private:
	unsigned int mySize = 0;   // the number of elements in the list container
	ListNode< T > *myHead = nullptr; // pointing to the header node in the list container
}; // end class template list


// Default constructor; Constructs an empty list container, with no elements.
template< typename T >
list< T >::list()
	: mySize( 0 ),
	  myHead( new ListNode< T > )
{
	myHead->myVal = T();
	myHead->prev = myHead->next = myHead;
}

// Copy constructor; Constructs a list container with a copy of each of the elements in x.
template< typename T >
list< T >::list( const list< T > &x )
	: mySize( x.mySize )//這句基本上就是個沒有任何卵用的垃圾
{
	myHead = new ListNode< T >;
	mySize = 0;
	for(auto it = x.begin(); it != x.end(); ++it)
		insert(end(), *it);
}

// Destructor; Destroys all list container elements, and deallocates all the storage allocated by the list container.
template< typename T >
list< T >::~list()
{
	clear();
	delete myHead;
}

// Returns a pointer pointing to the first element in the list container.
template< typename T >
typename list< T >::iterator list< T >::begin() const
{
	return iterator( myHead->next );
}

// Returns an pointer referring to the past-the-end element in the list container.
template< typename T >
typename list< T >::iterator list< T >::end() const
{
	return iterator( myHead );
}

// Returns a bool value indicating whether the linked list is empty.
template< typename T >
bool list< T >::empty() const
{
	return ( mySize == 0 );
}

// The list container is extended by inserting a new element before the element at the specified position.
template< typename T >
ListIterator< T > list< T >::insert( iterator position, const T val )
{
	if (mySize == 0)
	{
		myHead->next = new ListNode< T >;
		myHead->next->next = myHead;
		myHead->next->prev = myHead;
		myHead->prev = myHead->next;
		myHead->next->myVal = val;
	}
	
	else
	{
		ListNode< T >* tmp = new ListNode< T >, *it = myHead->next;
		for (iterator it2 = begin(); it2 != position; ++it2, it = it->next);
		it->prev->next = tmp;
		tmp->next = it;
		tmp->prev = it->prev;
		it->prev = tmp;
		tmp->myVal = val;
	}
	
	mySize++;
	return position;
}

// Removes from the list container the element at the specified position.
template< typename T >
ListIterator< T > list< T >::erase( iterator position )
{
	ListNode< T >* it = myHead->next;
	for (iterator it2 = begin(); it2 != position; ++it2, it = it->next);
	it->next->prev = it->prev;
	it->prev->next = it->next;
	delete it;
	mySize--;
	return position;
}

// Removes all elements from the list container (which are destroyed)
template< typename T >
void list< T >::clear()
{
	if( mySize != 0 ) // the list is not empty
	{
		while( myHead->next != myHead )
		{
			myHead->next = myHead->next->next;
			delete myHead->next->prev;
		}

		myHead->prev = myHead;
		mySize = 0;
	}
}

#endif