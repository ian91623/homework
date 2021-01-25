#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

template <typename T, typename U>
void quickSort(T ptrBegin, T ptrEnd, U fn);

template< typename T, typename U >
void insertSort(T ptrBegin, T ptrEnd, U fn);

int main()
{
	srand(time(0));
	auto greater = [](auto a, auto b)->bool {return a > b;};
	auto less = [](auto a, auto b)->bool {return a < b;};
	
	int check = 10;
	const int num = 1000000;
	
	vector<int> v;
	v.reserve(num);
	for (int i=0; i<10; i++)
	{
		v.resize(0);
		for(int j=0 ; j<num ; j++)
			v.push_back(rand());
		quickSort(v.begin(), v.end(), greater);
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
		quickSort(s.begin(), s.end(), greater);
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
		quickSort(arrayOfInt, arrayOfInt + num, greater);
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
		quickSort(arrayOfChar, arrayOfChar + num, greater);
		if (is_sorted(arrayOfChar, arrayOfChar + num, greater))
			--check;
		cout << "arrayOfChar " << i+1 << " complete" << endl;
	}
	cout << endl << check << " mistakes in arrayOfChar" << endl << endl;
	delete [] arrayOfChar;

	system("pause");
}

template <typename T, typename U>
void quickSort(T ptrBegin, T ptrEnd, U fn)
{
	if(ptrEnd - ptrBegin > 15)
	{
		int len = ptrEnd - ptrBegin;
		auto pivot = ptrBegin + rand() % len;
		swap(*pivot, *(ptrEnd - 1));
		pivot = ptrEnd - 1;
		auto locationForPivot = ptrBegin;
		for(auto it = ptrBegin ; it != pivot ; ++it)
			if(fn(*it, *pivot))
			{
				swap(*locationForPivot, *it);
				++locationForPivot;
			}
		swap(*locationForPivot, *pivot);
		quickSort(ptrBegin, locationForPivot, fn);
		quickSort(locationForPivot + 1, ptrEnd, fn);
	}
	else if(ptrEnd - ptrBegin > 1)
		insertSort(ptrBegin, ptrEnd, fn);
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