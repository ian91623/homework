// SourceLine class member-function definitions.

#include <iostream>
using std::cout;
using std::endl;

#include "SourceLine.h" // SourceLine class definition

// default/conversion constructor
SourceLine::SourceLine() : sourceLine()
{
}

void SourceLine::assign( const char *s, size_t n )
{
   sourceLine.assign( s, n );
}

void SourceLine::delComments()
{
    for(int i=0 ; i<sourceLine.size()-1 ; i++)
        if(sourceLine[i] == sourceLine[i+1] && sourceLine[i] == '/')
        {
            sourceLine.erase(i , -1);
            break;
        }
}

void SourceLine::delStrConst()
{
    for(int start = sourceLine.find('"' , 0) ; start !=npos ; start = sourceLine.find('"' , 0))
    {
        int end = sourceLine.find('"' , start+1);
        sourceLine.erase(start , end-start+1);
    }
}

void SourceLine::delCharConst()
{
    for(int start = sourceLine.find('\'' , 0) ; start !=npos ; start = sourceLine.find('\'' , 0))
    {
        int end = sourceLine.find('\'' , start+1);
        sourceLine.erase(start , end-start+1);
    }
}

string SourceLine::delFirstIdentifier()
{
    for(int i=0 ; i<sourceLine.size() ; i++)
        if(sourceLine[i] >= 'A' && sourceLine[i] <= 'Z' || sourceLine[i] >= 'a' && sourceLine[i] <= 'z' || sourceLine[i] == '_')
            for(int j=i+1 ; j<sourceLine.size() ; j++)
                if(sourceLine[j] < '0' || sourceLine[j] > '9' && sourceLine[j] < 'A' || sourceLine[j] > 'Z' && sourceLine[j] < 'a' && sourceLine[j] != '_' || sourceLine[j] > 'z')
                {
                    string temp( &sourceLine[i] , j-i);
                    sourceLine.erase(0 , j+1);
                    return temp;
                }
    return string();
}
