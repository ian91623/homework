#include <iostream>
#include <vector>
#include <list>
#include <ctime>
#include <typeinfo>
#include <algorithm>

using namespace std;

template< typename T , typename U >
void mergeSortRecursive(T ptrBegin, T ptrMid, T ptrEnd, U fn);

template< typename T, typename U >
void mergeSort(T ptrBegin, T ptrEnd, U fn);

template< typename T, typename U >
void insertSort(T ptrBegin, T ptrEnd, U fn);

int main()
{
	srand(time(0));
	auto greater = [](auto a, auto b)->bool {return a > b;};
	auto less = [](auto a, auto b)->bool {return a < b;};
	
	int check = 10;
	const int num = 100000;
	
	vector<int> v;
	v.reserve(num);
	for (int i=0; i<10; i++)
	{
		v.resize(0);
		for(int j=0 ; j<num ; j++)
			v.push_back(rand());
		mergeSort(v.begin(), v.end(), greater);
		if(is_sorted(v.begin(), v.end(), greater))
			--check;
		cout << "vector " << i+1 << " complete" << endl;
	}
	cout << endl << check << " mistakes in vector" << endl << endl;

	check = 10;
	string s;
	s.reserve(num);
	for (int i = 0; i < 10; i++)
	{
		s.resize(0);
		for (int j = 0; j < num; j++)
			s.push_back(rand() % 95 + 33);
		mergeSort(s.begin(), s.end(), greater);
		if (is_sorted(s.begin(), s.end(), greater))
			--check;
		cout << "string " << i+1 << " complete" << endl;
	}
	cout << endl << check << " mistakes in string" << endl << endl;

	check = 10;
	int* arrayOfInt = new int [num];
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < num; j++)
			arrayOfInt[j] = rand();
		mergeSort(arrayOfInt, arrayOfInt + num, greater);
		if (is_sorted(arrayOfInt, arrayOfInt + num, greater))
			--check;
		cout << "arrayOfInt " << i+1 << " complete" << endl;
	}
	cout << endl << check << " mistakes in arrayOfInt" << endl << endl;
	delete [] arrayOfInt;

	check = 10;
	char* arrayOfChar = new char [num];
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < num; j++)
			arrayOfChar[j] = rand() % 95 + 33;
		mergeSort(arrayOfChar, arrayOfChar + num, greater);
		if (is_sorted(arrayOfChar, arrayOfChar + num, greater))
			--check;
		cout << "arrayOfChar " << i+1 << " complete" << endl;
	}
	cout << endl << check << " mistakes in arrayOfChar" << endl << endl;
	delete [] arrayOfChar;

	system("pause");
}

template< typename T, typename U >
void mergeSortRecursive(T ptrBegin, T ptrMid, T ptrEnd, U fn)
{
	if(ptrMid-ptrBegin > 15)
		mergeSort<T>(ptrBegin, ptrMid, fn);
	else if(ptrMid-ptrBegin > 1)
		insertSort(ptrBegin, ptrMid, fn);
		
	if (ptrEnd - ptrMid > 15)
		mergeSort<T>(ptrMid, ptrEnd, fn);
	else if (ptrEnd - ptrMid > 1)
		insertSort(ptrMid, ptrEnd, fn);

	vector< remove_reference_t<decltype(*ptrBegin)> > result;
	result.reserve(ptrEnd - ptrBegin);
	for(T it1 = ptrBegin, it2 = ptrMid; it1 != ptrMid || it2 != ptrEnd ; )
	{
		if(it1 == ptrMid)
			for(; it2 != ptrEnd ; ++it2)
				result.push_back(*it2);
		else if(it2 == ptrEnd)
			for(; it1 != ptrMid ; ++it1)
				result.push_back(*it1);
		else
		{
			if(!fn(*it1, *it2))
			{
				result.push_back(*it2);
				++it2;
			}
			else
			{
				result.push_back(*it1);
				++it1;
			}
		}
	}
	for(auto it1 = result.begin() ; it1 != result.end() ; ++it1, ++ptrBegin)
		*ptrBegin = *it1;
}

template< typename T , typename U>
void mergeSort(T ptrBegin, T ptrEnd, U fn)
{
	mergeSortRecursive<T>(ptrBegin, ptrBegin+(ptrEnd-ptrBegin)/2, ptrEnd, fn);
}

template< typename T, typename U >
void insertSort(T ptrBegin, T ptrEnd, U fn)
{
	for(auto ptrKey = ptrBegin + 1, locationForInsert = ptrBegin; ptrKey != ptrEnd ; locationForInsert = ptrKey++)
		for(; ; --locationForInsert)
			if(fn(*locationForInsert, *ptrKey) || locationForInsert == ptrBegin)
			{
				if(fn(*locationForInsert, *ptrKey))
					++locationForInsert;
				auto key = *ptrKey;
				auto tempPtr = ptrEnd - 1;
				for(; tempPtr > locationForInsert ; --tempPtr)
					*tempPtr = *(tempPtr - 1);
				*locationForInsert = key;
				break;
			}
}