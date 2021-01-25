// HugeInteger class template definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

#include "Vector - 1061509 - hw7.h" // include definition of class template vector
#include "List - 1061509 - hw7.h" // include definition of class template list

/*
#include <vector> // include definition of class template vector
#include <list> // include definition of class template list
using std::vector;
using std::list;
*/

template< typename T >
class HugeInteger
{
	template< typename T >
	friend ostream& operator<<( ostream &output, const HugeInteger< T > &hugeInteger );
public:
	// constructor; construct a zero HugeInteger with mySize n
	HugeInteger( unsigned int n = 0 );

	// copy constructor; constructs a HugeInteger with a copy
	// of each of the elements in integerToCopy
	HugeInteger( const HugeInteger &integerToCopy );

	~HugeInteger(); // destructor; destroys the HugeInteger

	const HugeInteger &operator=( const HugeInteger &right ); // assignment operator

	bool operator==(const HugeInteger &right ) const; // less than or equal to
	bool operator<(const HugeInteger &right ) const;  // less than
	bool operator<=(const HugeInteger &right ) const; // less than or equal to

	// addition operator; HugeInteger + HugeInteger
	HugeInteger operator+(const HugeInteger &op2 )const;

	// subtraction operator; HugeInteger - HugeInteger provided that
	// the minuend is greater than or equal to the subtrahend
	HugeInteger operator-(const HugeInteger &op2 )const;

	// multiplication operator; HugeInteger * HugeInteger
	HugeInteger operator*(const HugeInteger &op2 )const;

	// division operator; HugeInteger / HugeInteger
	// provided that the divisor is not equal to 0
	HugeInteger operator/(const HugeInteger &op2 )const;

	// modulus operator; HugeInteger % HugeInteger
	// provided that the divisor is not equal to 0
	HugeInteger operator%(const HugeInteger &op2 )const;

	HugeInteger &operator++();     // prefix increment operator
	  
	HugeInteger operator++( int ); // postfix increment operator

	HugeInteger &operator--();     // prefix decrement operator

	HugeInteger operator--( int ); // postfix decrement operator

	// convert a vector of decimal digits into a HugeInteger
	void convert( T &buffer );
	bool isZero(); // return true if and only if all digits are zero

private:
	T integer;

	void divideByTen();            // divides a HugeInteger by 10
	void helpIncrement();          // increments a HugeInteger by 1
	void helpDecrement();          // decrements a HugeInteger by 1
}; // end class template HugeInteger

#endif


// constructor; construct a zero HugeInteger with mySize n
template< typename T >
HugeInteger< T >::HugeInteger( unsigned int n )
	: integer( ( n == 0 ) ? 1 : n )
{
}

// copy constructor; constructs a HugeInteger with a copy
// of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger( const HugeInteger< T > &integerToCopy )
	: integer( integerToCopy.integer )
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
		integer = right.integer;

	return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger< T >::operator==(const HugeInteger< T > &right ) const
{
	return ( integer == right.integer );
} // end function operator==

// function that tests if one HugeInteger< T > is less than another
template< typename T >
bool HugeInteger< T >::operator<(const HugeInteger< T > &right ) const
{
	if(integer.size() > right.integer.size())
		return false;
	if(integer.size() < right.integer.size())
		return true;
	for(int i=integer.size()-1 ; i>=0 ; i--)
	{
		if(integer[i] > right.integer[i])
			return false;
		if(integer[i] < right.integer[i])
			return true;
	}
	return false;
} // end function operator<

// function that tests if one HugeInteger< T > is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=(const HugeInteger< T > &right ) const
{
	return ( *this == right || *this < right );
}

// addition operator; HugeInteger< T > + HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator+(const HugeInteger< T > &op2 )const
{
	unsigned int op1Size = integer.size();
	unsigned int op2Size = op2.integer.size();
	unsigned int sumSize = ( op1Size >= op2Size ) ? op1Size + 1 : op2Size + 1;

	HugeInteger< T > sum( sumSize );
	T::iterator it1 = integer.begin();
	T::iterator it3 = sum.integer.begin();
	for( ; it1 != integer.end(); ++it1, ++it3 )
		*it3 = *it1;

	T::iterator it2 = op2.integer.begin();
	it3 = sum.integer.begin();
	for( ; it2 != op2.integer.end(); ++it2, ++it3 )
		*it3 += *it2;

	it3 = sum.integer.begin();
	T::iterator it4 = it3;
	for( ++it4; it4 != sum.integer.end(); ++it3, ++it4 )
		if( *it3 > 9 )
		{
			( *it3 ) -= 10;
			( *it4 )++;
		}

	if( *it3 == 0 )
		sum.integer.pop_back();

	return sum;
} // end function operator+

// subtraction operator; HugeInteger< T > - HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator-(const HugeInteger< T > &op2 )const
{
	HugeInteger< T > differ(*this);

	for(int i=integer.size()-1 ; i>=1 ; i--)
	{
		differ.integer[i]--;
		differ.integer[i-1] += 10;
	}

	for(int i=0 ; i<op2.integer.size() ; i++)
		differ.integer[i] -= op2.integer[i];

	for(int i=0 ; i<differ.integer.size()-1 ; i++)
		if(differ.integer[i] >= 10)
		{
			differ.integer[i+1]++;
			differ.integer[i] -= 10;
		}

	while(differ.integer[differ.integer.size()-1] == 0 && differ.integer.size()-1 != 0)
		differ.integer.pop_back();

	return differ;
} // end function operator-

// multiplication operator; HugeInteger< T > * HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator*(const HugeInteger< T > &op2 )const
{
	HugeInteger< T > product(integer.size() + op2.integer.size());

	for(int i=0 ; i<integer.size() ; i++)
		for(int j=0 ; j<op2.integer.size() ; j++)
			if(integer[i]!=0 && op2.integer[j]!=0)
				product.integer[i+j] += integer[i] * op2.integer[j];

	for(int i=0 ; i<product.integer.size() ; i++)
		if(product.integer[i] > 9)
		{
			product.integer[i+1] += product.integer[i] / 10;
			product.integer[i] %= 10;
		}

	while(product.integer[product.integer.size()-1] == 0 && product.integer.size()-1 != 0)
		product.integer.pop_back();

	return product;
} // end function operator*

// division operator; HugeInteger< T > / HugeInteger< T > provided that
// the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator/(const HugeInteger< T > &op2 )const
{
	if(*this < op2)
		return HugeInteger();

	HugeInteger< T > quotient(integer.size() - op2.integer.size() + 1);
	HugeInteger< T > tmpQuotient(quotient);
	HugeInteger< T > dividend(*this);

	for(int i=quotient.integer.size()-1 ; i>=0 ; i--)
	{
		for(tmpQuotient.integer[i] = 1; !(dividend < (op2*tmpQuotient)); tmpQuotient.integer[i]++);
		quotient.integer[i] = --tmpQuotient.integer[i];
		dividend = dividend - op2*tmpQuotient;
		tmpQuotient.integer.pop_back();
	}
	if(quotient.integer[quotient.integer.size()-1] == 0 && quotient.integer.size()-1 != 0)
		quotient.integer.pop_back();
	return quotient;
} // end function operator/

// modulus operator; HugeInteger< T > % HugeInteger< T > provided that
// the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator%(const HugeInteger< T > &op2 )const
{
	HugeInteger quotient = ( *this ) / op2;
	HugeInteger remainder = ( *this ) - ( quotient * op2 );
	return remainder;
}

// overloaded prefix increment operator 
template< typename T >
HugeInteger< T > &HugeInteger< T >::operator++()
{
	helpIncrement();
	return *this;
}

// overloaded postfix increment operator;
// note that the dummy integer parameter does not have a parameter name
template< typename T >
HugeInteger< T > HugeInteger< T >::operator++( int )
{
	HugeInteger< T > tmp(*this);
	helpIncrement();
	return tmp;
}

// overloaded prefix decrement operator 
template< typename T >
HugeInteger< T > &HugeInteger< T >::operator--()
{
	helpDecrement();
	return *this;
}

// overloaded postfix decrement operator;
// note that the dummy integer parameter does not have a parameter name
template< typename T >
HugeInteger< T > HugeInteger< T >::operator--( int )
{
	HugeInteger< T > tmp(*this);
	helpDecrement();
	return tmp;
}

// convert a vector of decimal digits into a HugeInteger
template< typename T >
void HugeInteger< T >::convert( T &buffer )
{
	integer.resize( buffer.size() );
	T::reverse_iterator it1 = integer.rbegin();
	T::iterator it2 = buffer.begin();
	for( ; it2 != buffer.end(); ++it1, ++it2 )
		*it1 = *it2;
} // end function convert

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero()
{
	for( T::iterator it = integer.begin(); it != integer.end(); ++it )
		if( *it != 0 )
			return false;

	return true;
}

// function that divides a HugeInteger by 10;
// shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen()
{
	T::iterator it1 = integer.begin();
	T::iterator it2 = it1;
	for( ++it2; it2 != integer.end(); ++it1, ++it2 )
		*it1 = *it2;
	integer.pop_back();
}

// function to help increment the integer
template< typename T >
void HugeInteger< T >::helpIncrement()
{
	T::iterator it = integer.begin();
	( *it )++;
	T::iterator it2 = it;
	for( ++it2; it2 != integer.end(); ++it, ++it2 )
		if( *it == 10 )
		{
			*it = 0;
			( *it2 )++;
		}

	if( ( *it ) == 10 )
	{
		*it = 0;
		integer.resize( integer.size() + 1 );
		it = integer.end();
		--it;
		*it = 1;
	}
}

// function to help decrement the integer
template< typename T >
void HugeInteger< T >::helpDecrement()
{
	HugeInteger<T> tmp;
	*this = *this - ++tmp;
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<( ostream &output, const HugeInteger< T > &hugeInteger )
{
	typename T::reverse_iterator it = hugeInteger.integer.rbegin();
	for( ; it != hugeInteger.integer.rend(); ++it )
		if( *it < 10 )
			output << *it;

	return output; // enables cout << x << y;
}