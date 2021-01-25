// string class member-function definitions.

#include <iostream>
using std::cerr;

#include "String.h" // string class definition

string::string()
{
   bx.buf[ 0 ] = '\0';
}

string::string( const string &str )
   : mySize( str.mySize ),
     myRes( str.myRes )
{
   if( myRes == 15 )
      for( size_t i = 0; i <= mySize; i++ )
         bx.buf[ i ] = str.bx.buf[ i ];
   else
   {
      bx.ptr = new char[ myRes + 1 ];
      for( size_t i = 0; i <= mySize; i++ )
         bx.ptr[ i ] = str.bx.ptr[ i ];
   }
}

string::string( const char *s, size_t n )
{
    assign(s , n);
}
// destructor
string::~string()
{
   if( myRes > 15 )
      delete[] bx.ptr;
} // end destructor

string& string::operator=( const string &str )
{
    resize(str.size());
    for(int i=0 ; i<size() ; i++)
        (*this)[i] = str[i];
	return *this;
}

char* string::begin()
{
   if( myRes == 15 )
      return bx.buf;
   else
      return bx.ptr;
}

char* string::end()
{
   if( myRes == 15 )
      return bx.buf + mySize;
   else
      return bx.ptr + mySize;
}

size_t string::size() const
{
   return mySize;
}

void string::resize( size_t n )
{
	if (n > myRes)
	{
		int a = myRes * 3 / 2;
		int b = (n/16+1)*16-1;
		char* tempPtr = new char[a > b ? a+1 : b+1]();
		for(int i=0 ; i<mySize ; i++)
			tempPtr[i] = (*this)[i];
		if(&(*this)[0] == bx.ptr)
			delete [] bx.ptr;
        bx.ptr = tempPtr;
		myRes = a > b ? a : b;
	}
	else
		for(int i=mySize ; i<n ; i++)
			(*this)[i] = '\0';
	mySize = n;
}

char& string::operator[]( size_t pos )
{
    if(myRes == 15)
        return bx.buf[pos];
    else
        return bx.ptr[pos];
}

const char& string::operator[]( size_t pos ) const
{
    if(myRes == 15)
        return bx.buf[pos];
    else
        return bx.ptr[pos];
}

string& string::assign( const char *s, size_t n )
{
    resize(n);
    for(int i=0 ; i<n ; i++)
        (*this)[i] = s[i];
    return *this;
}

string& string::erase( size_t pos, size_t len )
{
    if(mySize<=pos);
    else
    {
        if(len == npos || mySize<=len+pos)
            resize(pos);
        else
        {
            for(int i=pos ; i<mySize-len ; i++)
                (*this)[i] = (*this)[len+i];
            resize(mySize-len);
        }
    }
    return *this;
}

size_t string::find( char c, size_t pos) const
{
    if( pos < mySize )
    {
        for( unsigned int i = pos; i < mySize; i++ )
            if( c == (*this)[i] )
                return i;
    }
    return npos;
}

string string::substr( size_t pos, size_t len) const
{
    if(pos>=mySize)
        return string();
    else
    {
        if(pos+len>mySize)
            return string(&(*this)[pos] , mySize-pos);
        else
            return string(&(*this)[pos] , len);
    }
}

int string::compare( const string& str ) const
{
    for(int i=0 ; i<( size()>str.size() ? str.size() : size()) ; i++)
    {
        if((*this)[i] > str[i])
            return 1;
        else if((*this)[i] < str[i])
            return -1;
    }
    if(size()==str.size())
        return 0;
    return size()>str.size() ? 1 : -1;
}

std::ostream &operator<<( std::ostream &output, string &str )
{
   if( str.myRes == 15 )
      for( size_t i = 0; i < str.mySize; i++ )
         output << str.bx.buf[ i ];
   else
      for( size_t i = 0; i < str.mySize; i++ )
         output << str.bx.ptr[ i ];

   return output; // enables cout << x << y;
}

bool operator==( const string &lhs, const string &rhs )
{
   return ( lhs.compare( rhs ) == 0 );
}

bool operator!=( const string &lhs, const string &rhs )
{
   return ( lhs.compare( rhs ) != 0 );
}
