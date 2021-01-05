#pragma once
#include "Sequence.hpp"
#include "DynamicArray.hpp"
#include "Exception.hpp"
#include <string>
#include <iostream>


template <class T>
class ArraySequence : public Sequence<T>
{
private:
	DynamicArray<T>* items;

public:
	ArraySequence(T* items, int count) {
		try {
			this->items = new DynamicArray<T>(items, count);
		}
		catch (Exception & exception) {
			throw Exception("ConstructorError");
		}
	}

	ArraySequence() {
		try {
			this->items = new DynamicArray<T>();
		}
		catch (Exception& exception) {
			throw Exception("ConstructorError");
		}
	}

	ArraySequence(const ArraySequence<T>& items) {
		try {
			this->items = new DynamicArray<T>();
			for (int i = 0; i < items.GetLength(); i++) {
				this->Append(items.Get(i));
			}
		}
		catch (Exception& exception) {
			throw Exception("ConstructorError");
		}
	}

	virtual int GetLength() const override {
		return this->items->GetLength();
	}

	virtual T GetFirst() const override {
		try {
			return this->items->Get(0);
		}
		catch (Exception& exception) {
			throw Exception("GetFirstError");
		}
	}

	virtual T GetLast() const override {
		try {
			return this->items->Get(this->items->GetLength() - 1);
		}
		catch (Exception& exception) {
			throw Exception("GetLastError");
		}
	}

	virtual T Get(const int index) const override {
		try {
			return this->items->Get(index);
		}
		catch (Exception& exception) {
			throw Exception("GetError");
		}
	}

	virtual Sequence<T>* GetSubsequence(const int start, const int end) const override {
		ArraySequence<T>* temp = new ArraySequence<T>();
		for (int i = 0; i < temp->GetLength(); i++) {
			temp->Append(this->Get(start + i));
		}
		return temp;
	}

	virtual void Append(const T value) override {
		this->items->Resize(this->GetLength() + 1);
		this->items->Set(this->GetLength() - 1, value);
	}

	virtual void Prepend(const T value) override {
		this->items->Resize(this->GetLength() + 1);
		for (int i = this->GetLength() - 1; i > 0; i--) {
			this->items->Set(i, this->items->Get(i - 1));
		}
		this->items->Set(0, value);
	}

	virtual void InsertAt(const int index, const T value) override {
		try {
			this->items->InsertAt(value, index);
		}
		catch (Exception& exception) {
			throw Exception("InsertAtError");
		}
	}

	virtual void RemoveAt(const int index) override {
		try {
			this->items->RemoveAt(index);
		}
		catch (Exception& exception) {
			throw Exception("RemoveAt");
		}
	}

	virtual void Remove(const T value) override {
		this->items->Remove(value);
	}

	virtual void RemoveAll(const T value) override {
		this->items->RemoveAll(value);
	}

	virtual Sequence<T>* Concat(Sequence<T>* other) override {
		ArraySequence<T>* temp = new ArraySequence<T>();
		for (int i = 0; i < this->GetLength(); i++) {
			temp->Append(temp->Get(i));
		}
		for (int i = 0; i < other->GetLength(); i++) {
			temp->Append(other->Get(i));
		}
		return temp;
	}

	
	virtual void Set(const T item, int index) override
	{
		this->items->Set(index, item);
	}

	virtual void Swap(int index1, int index2) override
	{
		T temp = items->Get(index1);
		items->Set(index1, items->Get(index2));
		items->Set(index2, temp);
	}

	virtual ~ArraySequence()
	{
		Free();
	}

	virtual void Free() override
	{
		if (this->items != nullptr)
		{
			delete(this->items);
			this->items = nullptr;
		}
	}
};