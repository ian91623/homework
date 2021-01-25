// Member-function definitions for class HugeInteger
#include <iostream>
using namespace std;
#include "HugeInteger.h" // include definition of class HugeInteger

// default constructor; construct a zero HugeInteger with size 1
HugeInteger::HugeInteger()
   : integer( 1 )
{
}

// constructor; construct a zero HugeInteger with size n
HugeInteger::HugeInteger( unsigned int n )
   : integer( ( n > 0 ) ? n : 1 )
{
} // end HugeInteger constructor

// copy constructor
// constructs a HugeInteger with a copy of each of the elements in integerToCopy
HugeInteger::HugeInteger( const HugeInteger &integerToCopy )
   : integer( integerToCopy.integer )
{
} // end HugeInteger copy constructor

// destructor; destroys the HugeInteger
HugeInteger::~HugeInteger()
{

} // end HugeInteger destructor

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
const HugeInteger &HugeInteger::assign( const HugeInteger &right )
{
   if( &right != this ) // avoid self-assignment
      integer.assign( right.integer );

   return *this; // enables x = y = z, for example
}

bool HugeInteger::equal( const HugeInteger &right ) const
{
    if(integer.size() != right.integer.size())
        return false;
    for(int i=0 ; i<integer.size() ; i++)
        if(integer.begin()[i] != right.integer.begin()[i])
            return false;
    return true;
}

bool HugeInteger::less( const HugeInteger &right ) const
{
    if(integer.size() > right.integer.size())
        return false;
    if(integer.size() < right.integer.size())
        return true;
    for(int i=integer.size()-1 ; i>=0 ; i--)
    {
        if(integer.begin()[i] > right.integer.begin()[i])
            return false;
        if(integer.begin()[i] < right.integer.begin()[i])
            return true;
    }
    return false;
}
// function that tests if one HugeInteger is less than or equal to another
bool HugeInteger::lessEqual( const HugeInteger &right ) const
{
   return ( less( right ) || equal( right ) );
} // end function lessEqual

// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::add( const HugeInteger &op2 ) const
{
   unsigned int op1Size = integer.size();
   unsigned int op2Size = op2.integer.size();
   unsigned int sumSize = ( op1Size >= op2Size ) ? op1Size + 1 : op2Size + 1;

   HugeInteger sum( sumSize );

   vector::iterator it1 = integer.begin();
   vector::iterator it3 = sum.integer.begin();
   for( ; it1 != integer.end(); ++it1, ++it3 )
      *it3 = *it1;

   vector::iterator it2 = op2.integer.begin();
   for( it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3 )
      *it3 += *it2;

   for( it3 = sum.integer.begin(); it3 != sum.integer.end() - 1; ++it3 )
      if( *it3 > 9 )
      {
         ( *it3 ) -= 10;
         ( *( it3 + 1 ) )++;
      }

   if( *it3 == 0 )
      sum.integer.pop_back();

   return sum;
} // end function add

HugeInteger HugeInteger::subtract( const HugeInteger &op2 ) const
{
    HugeInteger differ(*this);

    for(int i=0 ; i<op2.integer.size() ; i++)
        differ.integer.begin()[i] -= op2.integer.begin()[i];

    for(int i=0 ; i<differ.integer.size()-1 ; i++)
        if(differ.integer.begin()[i] < 0)
        {
            differ.integer.begin()[i+1]--;
            differ.integer.begin()[i] += 10;
        }

    while(*(differ.integer.end()-1) == 0 && differ.integer.end()-1 != differ.integer.begin())
        differ.integer.pop_back();

    return differ;
}

HugeInteger HugeInteger::multiply( const  HugeInteger &op2 ) const
{
    HugeInteger product(integer.size() + op2.integer.size());

    for(int i=0 ; i<integer.size() ; i++)
        for(int j=0 ; j<op2.integer.size() ; j++)
            product.integer.begin()[i+j] += integer.begin()[i] * op2.integer.begin()[j];

    for(int i=0 ; i<product.integer.size() ; i++)
        if(product.integer.begin()[i] > 9)
        {
            product.integer.begin()[i+1] += product.integer.begin()[i] / 10;
            product.integer.begin()[i] %= 10;
        }

    while(*(product.integer.end()-1) == 0 && product.integer.end()-1 != product.integer.begin())
        product.integer.pop_back();

    return product;
}

HugeInteger HugeInteger::divide( const HugeInteger &op2 ) const
{
    if(integer.size() < op2.integer.size())
        return HugeInteger();

    HugeInteger quotient(integer.size() - op2.integer.size() + 1);
    for(int i=quotient.integer.size()-1 ; i>=0 ; i--)
    {
        for(quotient.integer.begin()[i] = 1 ; !less(op2.multiply(quotient)) ; quotient.integer.begin()[i]++);
        quotient.integer.begin()[i]--;
    }
    if(*(quotient.integer.end()-1) == 0 && quotient.integer.end()-1 != quotient.integer.begin())
        quotient.integer.pop_back();
    return quotient;
}

// modulus operator; HugeInteger % HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::modulus( const HugeInteger &op2 ) const
{
   HugeInteger quotient = divide( op2 );
   HugeInteger product = quotient.multiply( op2 );
   HugeInteger remainder = subtract( product );
   return remainder;
}

// convert a vector of decimal digits into a HugeInteger
void HugeInteger::convert( vector v )
{
   integer.resize( v.size() );
   vector::iterator it1 = integer.end() - 1;
   vector::iterator it2 = v.begin();
   for( ; it2 != v.end(); --it1, ++it2 )
      *it1 = *it2;
} // end function convert

// function that tests if a HugeInteger is zero
bool HugeInteger::isZero() const
{
   for( vector::iterator it = integer.begin(); it != integer.end(); ++it )
      if ( *it != 0 )
         return false;

   return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
void HugeInteger::divideByTen()
{
   vector::iterator it = integer.begin();
   vector::iterator it2 = it;
   for( ++it2; it2 != integer.end(); ++it, ++it2 )
      *it = *it2;
   integer.pop_back();
}

// overloaded output operator
void HugeInteger::output( ostream &outFile )
{
   vector::iterator it = integer.end() - 1;
   for( ; it != integer.begin() - 1; --it )
      if( *it < 10 )
         outFile << *it;
   outFile << endl;
} // end function output
