#pragma once 
#include"Sequence.hpp"
#include "LinkedList.hpp"
#include "Exception.hpp"


template <class T>
class ListSequence : public Sequence<T>
{
private:
	LinkedList<T>* items;

public:
	ListSequence()
	{
		this->items = new LinkedList<T>();
	}

	ListSequence(T* items, int count) 
	{
		this->items = new LinkedList<T>(items, count);
	}

	ListSequence(ListSequence<T>& other)
	{
		this->items = new LinkedList<T>();
		for (int i = 0; i < other.GetLength(); i++)
		{
			this->items->addNode(other.Get(i));
		}
	}

	virtual T GetFirst() const override
	{

		return this->items->GetFirst();
	}
	virtual T GetLast() const override
	{
		return this->items->GetLast();
	}
	virtual T Get(int i) const override
	{
		return this->items->Get(i);
	}
	virtual int GetLength() const override
	{
		return this->items->GetLength();
	}
	virtual Sequence<T>* GetSubsequence(int startindex, int endindex) const override
	{
		Sequence<T>* ll = new ListSequence<T>();
		for (int i = startindex; i <= endindex; i++)
		{
			ll->Prepend(this->items->Get(i));
		}
		return ll;

	}



	virtual void Append(T items) override
	{
		LinkedList<T>* newlist = new LinkedList<T>();
		newlist->addNode(items);
		for (int i = 0; i < this->items->GetLength(); i++)
		{
			newlist->addNode(this->items->Get(i));
		}
		delete this->items;
		this->items = newlist;


	}
	virtual void Prepend(T items) override
	{
		this->items->addNode(items);
	}

	virtual void InsertAt(int index, T value) override
	{
		this->items->InsertAt(value, index);
	}

	virtual Sequence<T>* Concat(Sequence<T>* newmas) override
	{
		Sequence<T>* ll = new ListSequence<T>();
		for (int i = 0; i < this->items->GetLength(); i++)
		{
			ll->Prepend(this->items->Get(i));
		}

		for (int i = 0; i < newmas->GetLength(); i++)
		{
			ll->Prepend(newmas->Get(i));
		}
		return ll;
	}

	virtual void Set(T value, int index) override
	{
		this->items->Put(value, index);
	}

	virtual void Remove(const T value)  override
	{
		int size = this->GetLength();
		for (size_t i = 0; i < size; i++)
		{
			if (this->items->Get(i) == value)
			{
				this->items->RemoveAt(i);
				break;
			}
		}
	}

	virtual void RemoveAt(const int index)  override
	{
		this->items->RemoveAt(index);
	}

	virtual void RemoveAll(T value)  override
	{
		int size = this->GetLength();
		int count = 0;
		size_t j = 0;
	    for (j; j < size; j++)
		{
			if (this->items->Get(j) == value) count++;
		}

		for (size_t i = 0; i < count; i++)
		{
			for (j = 0; j < size; j++)
			{
				if (this->items->Get(j) == value) this->items->RemoveAt(j);
			}
			if (i == count) break;
		}
	}

	virtual void Swap(int indexA, int indexB) override
	{
		T temp = items->Get(indexA);	
		items->Put(items->Get(indexB), indexA);
		items->Put(temp, indexB);
	}

	 ~ListSequence()
	{
		Free();
	}

	virtual void Free() override
	{
		this->items->Free();
	}
};



