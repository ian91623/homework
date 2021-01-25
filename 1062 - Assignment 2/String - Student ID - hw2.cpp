#include <iostream>
using std::cout;
using std::endl;
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
		for( unsigned int i = 0; i <= mySize; i++ )
			bx.buf[ i ] = str.bx.buf[ i ];
	else
	{
		bx.ptr = new char[ myRes + 1 ];
		for( unsigned int i = 0; i <= mySize; i++ )
			bx.ptr[ i ] = str.bx.ptr[ i ];
	}
}

string::string( const char *s, unsigned int n )
{
	assign(s, n);
}

string::~string()
{
	if( myRes > 15 )
		delete[] bx.ptr;
}

unsigned int string::size() const
{
	return mySize;
}

unsigned int string::capacity() const
{
	return myRes;
}

void string::resize( unsigned int n )
{
	char *tmpPtr = myRes == 15 ? bx.buf : bx.ptr;
	if(n > myRes)
	{
		int newRes = (n|15) > myRes*1.5 ? (n|15) : myRes*1.5;
		char* newArray = new char[newRes+1]();
		for(int i=0 ; i<mySize ; i++)
			newArray[i] = tmpPtr[i];
		myRes = newRes;
		if(tmpPtr == bx.ptr) delete [] tmpPtr;
		bx.ptr = newArray;	
	}
	else
		for(int i=mySize ; i<=n ; i++)
			tmpPtr[i] = char();
	mySize = n;
}

void string::clear()
{
	mySize = 0;
	if( myRes == 15 )
		bx.buf[ 0 ] = '\0';
	else
		bx.ptr[ 0 ] = '\0';
}

void string::push_back( char c )
{
	resize(mySize+1);
	char *tmpPtr = myRes == 15 ? bx.buf : bx.ptr;
	tmpPtr[mySize-1] = c;
}

void string::pop_back()
{
	if( mySize > 0 )
		--mySize;
}

string& string::assign( const char *s, unsigned int n )
{
	resize(n);
	char *tmpPtr = myRes == 15 ? bx.buf : bx.ptr;
	for(int i=0 ; i<n ; i++)
		tmpPtr[i] = s[i];
	return *this;
}

string& string::erase( unsigned int pos, unsigned int len )
{
	if(mySize<=pos);
	else if(len == npos || mySize<=len+pos)
		mySize = pos;
	else
	{
		char *tmpPtr = myRes == 15 ? bx.buf : bx.ptr;
		for(int i=pos ; i<=mySize-len ; i++)
			tmpPtr[i] = tmpPtr[i+len];
		mySize -= len;
	}
		return *this;
}

unsigned int string::find( char c, unsigned int pos ) const
{
	if( pos < mySize )
		if( myRes == 15 )
		{
			for( unsigned int i = pos; i < mySize; i++ )
				if( c == bx.buf[ i ] )
					return i;
		}
		else
		{
			for( unsigned int i = pos; i < mySize; i++ )
				if( c == bx.ptr[ i ] )
					return i;
		}

	return npos;
}

string string::substr( unsigned int pos, unsigned int len ) const
{
	string subString;
	if(pos > mySize);
	else
	{
		const char *tmpPtr = myRes == 15 ? bx.buf : bx.ptr;
		subString.assign( &tmpPtr[pos], (pos+len > mySize ? mySize-pos : len) );
	}
	return subString;
}

bool string::equal( std::string const &str )
{
	if( myRes != str.capacity() )
		return false;

	if( mySize != str.size() )
		return false;

	if( myRes == 15 )
	{
		for( unsigned int i = 0; i < mySize; i++ )
			if( bx.buf[ i ] != str[ i ] )
				return false;
	}
	else
	{
		for( unsigned int i = 0; i < mySize; i++ )
			if( bx.ptr[ i ] != str[ i ] )
				return false;
	}

	return true;
}