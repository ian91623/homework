// HugeInteger class template definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

#include "List - 1061509 - hw8.h" // include definition of class template list

//#include <list> // include definition of class template list
//using std::list;

template< typename T >
class HugeInteger : public list< T >
{
	template< typename T >
	friend ostream &operator<<( ostream &output, const HugeInteger< T > &hugeInteger );
public:
	using iterator = typename list< T >::iterator;
	using reverse_iterator = typename list< T >::reverse_iterator;

	HugeInteger( unsigned int n = 0 ); // constructor; construct a zero HugeInteger with mySize n

	// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
	HugeInteger( const HugeInteger &integerToCopy );

	~HugeInteger(); // destructor; destroys the HugeInteger

	const HugeInteger &operator=( const HugeInteger &right ); // assignment operator
	const HugeInteger &operator=( const list< T > &right ); // assignment operator

	bool operator<(const HugeInteger &right )const;  // less than
	bool operator<=(const HugeInteger &right )const; // less than or equal to

	// addition operator; HugeInteger + HugeInteger
	const HugeInteger operator+(const HugeInteger &op2 )const;

	// subtraction operator; HugeInteger - HugeInteger provided that
	// the minuend is greater than or equal to the subtrahend
	const HugeInteger operator-(const HugeInteger &op2 )const;

	// multiplication operator; HugeInteger * HugeInteger
	const HugeInteger operator*(const HugeInteger &op2 )const;

	// division operator; HugeInteger / HugeInteger
	// provided that the divisor is not equal to 0
	const HugeInteger operator/(const HugeInteger &op2 )const;

	// modulus operator; HugeInteger % HugeInteger
	// provided that the divisor is not equal to 0
	const HugeInteger operator%(const HugeInteger &op2 )const;

	HugeInteger &operator++(); // prefix increment operator
	 
	HugeInteger operator++( int ); // postfix increment operator

	HugeInteger &operator--(); // prefix decrement operator

	HugeInteger operator--( int ); // postfix decrement operator

	bool isZero(); // return true if and only if all digits are zero

private:
	void divideByTen();   // divides a HugeInteger by 10
	void helpIncrement(); // increments a HugeInteger by 1
	void helpDecrement(); // decrements a HugeInteger by 1
}; // end class template HugeInteger

#endif

// constructor; construct a zero HugeInteger with mySize n
template< typename T >
HugeInteger< T >::HugeInteger( unsigned int n )
	: list< T >::list( ( n == 0 ) ? 1 : n )
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger( const HugeInteger< T > &integerToCopy )
	: list< T >::list( integerToCopy )
{
}

// destructor; destroys the HugeInteger
template< typename T >
HugeInteger< T >::~HugeInteger()
{
}

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
template< typename T >
const HugeInteger< T > &HugeInteger< T >::operator=( const HugeInteger< T > &right )
{
	if( &right != this ) // avoid self-assignment
	  list< T >::operator=( right );

	return *this; // enables x = y = z, for example
} // end function operator=

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
template< typename T >
const HugeInteger< T > &HugeInteger< T >::operator=( const list< T > &right )
{
	if( &right != this ) // avoid self-assignment
	  	list< T >::operator=( right );

	return *this; // enables x = y = z, for example
} // end function operator=

// function that tests if one HugeInteger< T > is less than another
template< typename T >//homework part
bool HugeInteger< T >::operator<(const HugeInteger< T > &right )const
{
	if(this->size() > right.size())
		return false;
	if(this->size() < right.size())
		return true;
	for(reverse_iterator it1 = this->rbegin() , it2 = right.rbegin(); !(it1 == this->rend()) ; ++it1 , ++it2)
	{
		if(*it1 > *it2)
			return false;
		if(*it1 < *it2)
			return true;
	}
	return false;
} // end function operator<

// function that tests if one HugeInteger< T > is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=(const HugeInteger< T > &right )const
{
	return ( *this == right || *this < right );
}

// addition operator; HugeInteger< T > + HugeInteger< T >
template< typename T >
const HugeInteger< T > HugeInteger< T >::operator+(const HugeInteger< T > &op2 )const
{
	unsigned int op1Size = this->size();
	unsigned int op2Size = op2.size();
	unsigned int sumSize = ( op1Size >= op2Size ) ? op1Size + 1 : op2Size + 1;

	HugeInteger< T > sum( sumSize );
	iterator it1 = this->begin();
	iterator it3 = sum.begin();
	for( ; it1 != this->end(); ++it1, ++it3 )
		*it3 = *it1;

	iterator it2 = op2.begin();
	it3 = sum.begin();
	for( ; it2 != op2.end(); ++it2, ++it3 )
		*it3 += *it2;

	it3 = sum.begin();
	iterator it4 = it3;
	for( ++it4; it4 != sum.end(); ++it3, ++it4 )
		if( *it3 > 9 )
		{
			( *it3 ) -= 10;
			( *it4 )++;
		}
	if( *it3 == 0 )
		sum.pop_back();

	return sum;
} // end function operator+

// subtraction operator; HugeInteger< T > - HugeInteger< T >
template< typename T >//homework part
const HugeInteger< T > HugeInteger< T >::operator-(const HugeInteger< T > &op2 )const
{
	HugeInteger< T > differ(*this);

	for(reverse_iterator it1 = differ.rbegin() , it2 = ++differ.rbegin(); it2 != differ.rend() ; ++it1 , ++it2)
	{
		--*it1;
		*it2 += 10;
	}

	for(iterator it1 = differ.begin() , it2 = op2.begin() ; it2 != op2.end() ; ++it1 , ++it2)
		*it1 -= *it2;

	for(iterator it1 = differ.begin() , it2 = ++differ.begin(); it2 != differ.end() ; ++it1 , ++it2)
		if(*it1 >= 10)
		{
			*it1 -= 10;
			++*it2;
		}
	
	for(reverse_iterator it = differ.rbegin() ; *it == 0 && it != --differ.rend() ; it = differ.rbegin())
		differ.pop_back();

	return differ;
} // end function operator-

// multiplication operator; HugeInteger< T > * HugeInteger< T >
template< typename T >//homework part
const HugeInteger< T > HugeInteger< T >::operator*(const HugeInteger< T > &op2 )const
{
	HugeInteger< T > product(this->size() + op2.size());

	for(iterator it1 = product.begin() , it3 = this->begin() ; it3 != this->end() ; ++it1 , ++it3)
		if(*it3 != 0)
			for(iterator it2 = it1 , it4 = op2.begin() ; !(it4 == op2.end()) ; ++it2 , ++it4)
				if(*it4 != 0)
					*it2 += *it3 * *it4;

	for(iterator it1 = product.begin() , it2 = ++product.begin() ; it2 != product.end() ; ++it1 , ++it2)
	if(*it1 > 9)
	{
		*it2 += *it1 / 10;
		*it1 %= 10;
	}

	for(reverse_iterator it = product.rbegin() ; *it == 0 && it != --product.rend() ; it = product.rbegin())
	  product.pop_back();

	return product;
} // end function operator*

// division operator; HugeInteger< T > / HugeInteger< T > provided that the divisor is not equal to 0
template< typename T >//homework part
const HugeInteger< T > HugeInteger< T >::operator/(const HugeInteger< T > &op2 )const
{
	if(*this < op2)
		return HugeInteger();

	HugeInteger< T > quotient(this->size() - op2.size() + 1);
	HugeInteger< T > tmpQuotient(quotient);
	HugeInteger< T > dividend(*this);

	for(reverse_iterator it1 = quotient.rbegin(), it2 = tmpQuotient.rbegin() ; it1 != quotient.rend() ; ++it1)
	{   
		*it2 = 1;
		for(HugeInteger< T > tmp = tmpQuotient*op2 ; tmp <= dividend; ++*it1 )
			dividend = dividend - tmp;
		tmpQuotient.pop_back();
		it2 = tmpQuotient.rbegin();
	}

	for(reverse_iterator it = quotient.rbegin() ; *it == 0 && it != --quotient.rend() ; it = quotient.rbegin())
		quotient.pop_back();
	
	return quotient;
} // end function operator/

// modulus operator; HugeInteger< T > % HugeInteger< T > provided that the divisor is not equal to 0
template< typename T >
const HugeInteger< T > HugeInteger< T >::operator%(const HugeInteger< T > &op2 )const
{
	HugeInteger quotient = ( *this ) / op2;
	HugeInteger remainder = ( *this ) - ( quotient * op2 );
	return remainder;
}

// overloaded prefix increment operator 
template< typename T >
HugeInteger< T > &HugeInteger< T >::operator++()
{
	helpIncrement(); // increment integer
	return *this; // reference return to create an lvalue
}

// overloaded postfix increment operator;
// note that the dummy integer parameter does not have a parameter name
template< typename T >
HugeInteger< T > HugeInteger< T >::operator++( int )
{
	HugeInteger< T > temp = *this; // hold current state of object
	helpIncrement();

	// return unincremented, saved, temporary object
	return temp; // value return; not a reference return
}

// overloaded prefix decrement operator 
template< typename T >
HugeInteger< T > &HugeInteger< T >::operator--()
{
	helpDecrement(); // increment integer
	return *this; // reference return to create an lvalue
}

// overloaded postfix decrement operator;
// note that the dummy integer parameter does not have a parameter name
template< typename T >
HugeInteger< T > HugeInteger< T >::operator--( int )
{
	HugeInteger temp = *this; // hold current state of object
	helpDecrement();

	// return unincremented, saved, temporary object
	return temp; // value return; not a reference return
}

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero()
{
	for( iterator it = this->begin(); it != this->end(); ++it )
		if( *it != 0 )
			return false;

	return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen()
{
	iterator it1 = begin();
	iterator it2 = it1;
	for( ++it2; it2 != end(); ++it1, ++it2 )
		*it1 = *it2;
	pop_back();
}

// function to help increment the integer
template< typename T >
void HugeInteger< T >::helpIncrement()
{
	iterator it = this->begin();
	( *it )++;
	iterator it2 = it;
	for( ++it2; it2 != this->end(); ++it, ++it2 )
		if( *it == 10 )
		{
			*it = 0;
			( *it2 )++;
		}

	if( ( *it ) == 10 )
	{
		*it = 0;
		this->resize(this->size() + 1 );
		it = this->end();
		--it;
		*it = 1;
	}
}

// function to help decrement the integer
template< typename T >//homework part
void HugeInteger< T >::helpDecrement()
{
	HugeInteger<T> tmp;
	*this = *this - ++tmp;
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream &operator<<( ostream &output, const HugeInteger< T > &hugeInteger )
{
	typename list< T >::reverse_iterator it = hugeInteger.rbegin();
	for( ; it != hugeInteger.rend(); ++it )
		if( *it < 10 )
			output << *it;

	return output; // enables cout << x << y;
}