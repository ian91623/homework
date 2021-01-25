#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

template< typename T, typename U >
void heapSort(T ptrBegin, T ptrEnd, U fn);

template< typename T, typename U >
void heapify(T ptrBegin, T ptrEnd, U fn);

template< typename T, typename U >
void shiftDown(T ptrBegin, T ptrEnd, U fn);

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
		heapSort(v.begin(), v.end(), greater);
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
		heapSort(s.begin(), s.end(), greater);
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
		heapSort(arrayOfInt, arrayOfInt + num, greater);
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
		heapSort(arrayOfChar, arrayOfChar + num, greater);
		if (is_sorted(arrayOfChar, arrayOfChar + num, greater))
			--check;
		cout << "arrayOfChar " << i+1 << " complete" << endl;
	}
	cout << endl << check << " mistakes in arrayOfChar" << endl << endl;
	delete [] arrayOfChar;

	system("pause");
}

template< typename T, typename U >
void heapSort(T ptrBegin, T ptrEnd, U fn)
{
	heapify(ptrBegin, ptrEnd, fn);
	for(; --ptrEnd != ptrBegin ;)
	{
		swap(*ptrBegin, *ptrEnd);
		shiftDown(ptrBegin, ptrEnd, 0, fn);
	}
}

template< typename T, typename U >
void heapify(T ptrBegin, T ptrEnd, U fn)
{
	for(int i = (ptrEnd-ptrBegin)/2-1 ; i>=0 ; i--)
		shiftDown(ptrBegin, ptrEnd, i, fn);
}

template< typename T, typename U >
void shiftDown(T ptrBegin, T ptrEnd, int locationForParent, U fn)
{
	for(int locationForChild = 2*locationForParent + 1 ; locationForChild < ptrEnd - ptrBegin ; locationForParent = locationForChild, locationForChild = 2*locationForParent + 1)
		{
			auto parent = ptrBegin + locationForParent, child1 = ptrBegin + locationForChild, child2 = child1 + 1;
			if(child2 < ptrEnd)
				if(fn(*child1, *child2))
				{
					swap(child1, child2);
					locationForChild++;
				}
			if (fn(*parent, *child1))
				swap(*child1, *parent);
			else
				return;
		}
}