// HugeInteger class definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

#include "Vector - 1061509 - hw5.h" // include definition of class vector 

template< typename T >
class HugeInteger
{
   template< typename T >
   friend ostream& operator<<( ostream &output, HugeInteger< T > const &hugeInteger );
public:
   HugeInteger(); // default constructor; construct a HugeInteger with size 0

   // copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
   HugeInteger( const HugeInteger &integerToCopy );

   ~HugeInteger(); // destructor; destroys the HugeInteger

   const HugeInteger& operator=( const HugeInteger &right ); // assignment operator

   bool operator==( const HugeInteger &right ) const; // less than or equal to

   bool operator<( const HugeInteger &right ) const;  // less than

   bool operator<=( const HugeInteger &right ) const; // less than or equal to

   bool operator>( const HugeInteger &right ) const; // addition, greater than

   // addition operator; HugeInteger + HugeInteger
   HugeInteger operator+( const HugeInteger &op2 ) const;

   // subtraction operator; HugeInteger - HugeInteger provided that
   // the minuend is greater than or equal to the subtrahend
   HugeInteger operator-( const HugeInteger &op2 ) const;

   // multiplication operator; HugeInteger * HugeInteger
   HugeInteger operator*( const  HugeInteger &op2 ) const;

   // division operator; HugeInteger / HugeInteger
   // provided that the divisor is not equal to 0
   HugeInteger operator/( const HugeInteger &op2 ) const;

   // modulus operator; HugeInteger % HugeInteger
   // provided that the divisor is not equal to 0
   HugeInteger operator%( const HugeInteger &op2 ) const;
     
   HugeInteger& operator++(); // prefix increment operator
     
   HugeInteger operator++( int ); // postfix increment operator

   HugeInteger& operator--(); // prefix decrement operator

   HugeInteger operator--( int ); // postfix decrement operator

   void convert( vector< T > v ); // convert a vector of decimal digits into a HugeInteger
   bool isZero() const;           // return true if and only if all digits are zero
private:
   vector< T > integer;

   HugeInteger( unsigned int n ); // constructor; construct a zero HugeInteger with size n
   void divideByTen();            // divides a HugeInteger by 10
   void helpIncrement();          // increments a HugeInteger by 1
   void helpDecrement();          // decrements a HugeInteger by 1
}; // end class HugeInteger


// default constructor; construct a HugeInteger with size 0
template< typename T >
HugeInteger< T >::HugeInteger()
   : integer( 1 )
{
}

// constructor; construct a zero HugeInteger with size n
template< typename T >
HugeInteger< T >::HugeInteger( unsigned int n )
   : integer( ( n > 0 ) ? n : 1 )
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
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
const HugeInteger< T >& HugeInteger< T >::operator=( const HugeInteger< T > &right )
{
   if( &right != this ) // avoid self-assignment
      integer = right.integer;

   return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger< T >::operator==( const HugeInteger< T > &right ) const
{
   return ( integer == right.integer );
} // end function operator==

// function that tests if one HugeInteger< T > is less than or equal to another

template< typename T >
bool HugeInteger< T >::operator<( const HugeInteger< T > &right ) const
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
}

template< typename T >
bool HugeInteger< T >::operator<=( const HugeInteger< T > &right ) const
{
   return ( *this == right || *this < right );
}

template< typename T >
bool HugeInteger< T >::operator>( const HugeInteger< T > &right ) const
{
   return !(*this <= right);
}

// addition operator; HugeInteger< T > + HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator+( const HugeInteger< T > &op2 ) const
{
   unsigned int op1Size = integer.size();
   unsigned int op2Size = op2.integer.size();
   unsigned int sumSize = ( op1Size >= op2Size ) ? op1Size + 1 : op2Size + 1;

   HugeInteger sum( sumSize );

   vector< T >::iterator it1 = integer.begin();
   vector< T >::iterator it3 = sum.integer.begin();
   for( ; it1 != integer.end(); ++it1, ++it3 )
      *it3 = *it1;

   vector< T >::iterator it2 = op2.integer.begin();
   for( it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3 )
      *it3 += *it2;

   for( it3 = sum.integer.begin(); it3 != sum.integer.end() - 1; ++it3 )
      if( *it3 > 9 )
      {
         *it3 -= 10;
         ( *( it3 + 1 ) )++;
      }

   if( *it3 == 0 )
      sum.integer.pop_back();

   return sum;
} // end function operator+

template< typename T >
HugeInteger< T > HugeInteger< T >::operator-( const HugeInteger &op2 ) const
{
   HugeInteger differ(*this);

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
}

template< typename T >
HugeInteger< T > HugeInteger< T >::operator*( const  HugeInteger &op2 ) const
{
   HugeInteger product(integer.size() + op2.integer.size());

   for(int i=0 ; i<integer.size() ; i++)
      for(int j=0 ; j<op2.integer.size() ; j++)
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
}

template< typename T >
HugeInteger< T > HugeInteger< T >::operator/( const HugeInteger &op2 ) const
{
   if(*this < op2)
      return HugeInteger();

   HugeInteger quotient(integer.size() - op2.integer.size() + 1);
   for(int i=quotient.integer.size()-1 ; i>=0 ; i--)
   {
      for(quotient.integer[i] = 1 ; !(*this<(op2*quotient)) ; quotient.integer[i]++);
      quotient.integer[i]--;
   }
   if(quotient.integer[quotient.integer.size()-1] == 0 && quotient.integer.size()-1 != 0)
      quotient.integer.pop_back();
   return quotient;
}

// modulus operator; HugeInteger< T > % HugeInteger< T > provided that the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator%( const HugeInteger< T > &op2 ) const
{
   HugeInteger quotient = ( *this ) / op2;
   HugeInteger remainder = ( *this ) - ( quotient * op2 );
   return remainder;
}

template< typename T >
HugeInteger< T >& HugeInteger< T >::operator++()
{
   helpIncrement();
   return *this;
}

template< typename T >     
HugeInteger< T > HugeInteger< T >::operator++( int )
{
   HugeInteger<T> tmp(*this);
   helpIncrement();
   return tmp;
}

template< typename T >
HugeInteger< T >& HugeInteger< T >::operator--()
{
   helpDecrement();
   return *this;
}

template< typename T >
HugeInteger< T > HugeInteger< T >::operator--( int )
{
   HugeInteger<T> tmp(*this);
   helpDecrement();
   return tmp;
}

// convert a vector of decimal digits into a HugeInteger
template< typename T >
void HugeInteger< T >::convert( vector< T > v )
{
   integer.resize( v.size() );
   vector< T >::iterator it1 = integer.end() - 1;
   vector< T >::iterator it2 = v.begin();
   for( ; it2 != v.end(); --it1, ++it2 )
      *it1 = *it2;
} // end function convert

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero() const
{
   vector< T >::iterator it = integer.begin();
   for( ; it != integer.end(); ++it )
      if( *it != 0 )
         return false;
         
   return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen()
{
   vector< T >::iterator it = integer.begin() + 1;
   for( ; it != integer.end(); ++it )
      *( it - 1 ) = *it;
   integer.pop_back();
}

// function to help increment the integer
template< typename T >
void HugeInteger< T >::helpIncrement()
{
   vector< T >::iterator it = integer.begin();
   ( *it )++;
   vector< T >::iterator it2 = it;
   for( ++it2; it2 != integer.end(); ++it, ++it2 )
      if( *it == 10 )
      {
         *it = 0;
         ( *it2 )++;
      }

   if( ( *it ) == 10 )
   {
      *( it ) = 0;
      integer.resize( integer.size() + 1 );
      it = integer.end();
      --it;
      *it = 1;
   }
}

template< typename T >
void HugeInteger< T >::helpDecrement()
{
   HugeInteger<T> tmp;
   *this = *this - ++tmp;
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<( ostream &output, HugeInteger< T > const&hugeInteger )
{
   typename vector< T >::iterator it = hugeInteger.integer.end() - 1;
   for( ; it != hugeInteger.integer.begin() - 1; --it )
      if( *it < 10 )
         output << *it;

   return output; // enables cout << x << y;
}

#endif