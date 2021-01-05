#pragma once
#include "ISorter.hpp"
#include "compare.hpp"
#include "DynamicArray.hpp"
#include "ArraySequence.hpp"
#include "LinkedList.hpp"
#include "ListSequence.hpp"
#include "compare.hpp"
#include "Sequence.hpp"
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;


template <class T>
class BubbleSorter : public ISorter<T>
{
public:
	virtual void Sorter(Sequence<T>* seq, bool (*cmp)(T, T)) override
	{
		int length = seq->GetLength();
		
		for (int i = 1; i < length; i++)
		{
			for (int j = 0; j < length - i; j++)
			{
				if (!cmp(seq->Get(j), seq->Get(j + 1))) 
					seq->Swap(j + 1, j);
			}
		}
	}
};


template <class T>
class ShellSort : public ISorter<T>
{
public:
	virtual void Sorter(Sequence<T>* seq, bool (*cmp)(T, T)) override
	{
		int n = seq->GetLength();
		int i, j, step;
		T temp;
		for (step = n / 2; step > 0; step /= 2)
			for (i = step; i < n; i++)
			{
				temp = seq->Get(i);
				for (j = i; j >= step; j -= step)
				{
					if (temp < seq->Get(j - step))
						seq->Set(seq->Get(j - step), j);
					else
						break;
				}
				seq->Set(temp, j);
			}
	}
};


template <class T>
class ShellSortCustomStep : public ISorter<T>
{
public:
	void Sorter(Sequence<T>* seq, bool (*cmp)(T, T)) 
	{
		int step;
		cin >> step;
		int n = seq->GetLength();
		int i, j;
		T temp;
		for (step; step > 0; step /= 2)
			for (i = step; i < n; i++)
			{
				temp = seq->Get(i);
				for (j = i; j >= step; j -= step)
				{
					if (temp < seq->Get(j - step))
						seq->Set(seq->Get(j - step), j);
					else
						break;
				}
				seq->Set(temp, j);
			}
	}
};


template <class T>
class InsertionSorter : public ISorter<T>
{
public:
	virtual void Sorter(Sequence<T>* seq, bool (*cmp)(T, T)) override
	{
		for (int i = 1; i < seq->GetLength(); i++)
			for (int j = i; j > 0 && (!cmp(seq->Get(j - 1), seq->Get(j))); j--)
				seq->Swap(j - 1, j);
	}
};


/*

template <class T>
class CountSorter : public ISorter<T>
{
public:
	virtual void Sorter(Sequence<T>* seq, bool (*cmp)(T, T)) override
	{
		а что делать когда range не определен? 
	}

private:
	virtual void Sorter(Sequence<T>* seq, bool (*cmp)(T, T), int left, int right) override { };// = 0
};

*/