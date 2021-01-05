#pragma once
#include <string>
#include "Exception.hpp"
#include <cstdlib>
#include <ctime>
#include <stdlib.h>  

template <class T> class DynamicArray
{
private:
	T* items;
	bool* itemsCheck;
	int size;
public:
	DynamicArray(T* items, int size) {
		if (size < 0)
			throw Exception("NegativeSize");
		this->size = size;
		this->items = new T[size];
		this->itemsCheck = new bool[size];
		for (int i = 0; i < size; i++) {
			this->itemsCheck[i] = true;
			this->items[i] = items[i];
		}
	}
	DynamicArray(const int size=0)
	{
		if (size < 0)
			throw Exception("NegativeSize");
		this->items = new T[size];
		this->itemsCheck = new bool[size];
		for (int i = 0; i < size; i++)
			this->itemsCheck[i] = false;
		this->size = size;
	}
	DynamicArray(const DynamicArray<T>& array) {
		this->size = array.GetLength();
		this->items = new T[this->size];
		this->itemsCheck = new bool[this->size];
		for (int i = 0; i < this->size; i++) {
			if (array.GetitemsCheck(i)) {
				this->items[i] = array.Get(i);
				this->itemsCheck[i] = true;
			}
			else
				this->itemsCheck[i] = false;
		}
	}
	int GetLength() const {
		return this->size; 
	}
	bool GetitemsCheck(int index) const { 
		if (index < 0 || index >= this->size)
			throw Exception("IndexOutOfRange");
		return this->itemsCheck[index];
	}
	T Get(const int index) const {
		if (index < 0 || index >= this->size || !this->itemsCheck[index])
			throw Exception("IndexOutOfRange ");
		return this->items[index];
	}
	bool HasValue(const int index) const {
		if (index < 0 || index >= this->size || !this->itemsCheck[index])
			throw Exception("IndexOutOfRange");
		return this->itemsCheck[index];
	}
	void Set(const int index, const T value)
	{
		if (index < 0 || index >= this->size)
			throw Exception("IndexOutOfRange");
		this->items[index] = value;
		this->itemsCheck[index] = true;
	}
	void Resize(int newSize) {
		if (newSize < this->size) {
			this->size = newSize;
			T* temp = new T[newSize];
			bool* newitemsCheck = new bool[newSize];
			for (int i = 0; i < newSize; i++) {
				if (this->itemsCheck[i]) {
					temp[i] = this->items[i];
					newitemsCheck[i] = true;
				}
				else {
					newitemsCheck[i] = false;
				}
			}
			delete[] this->items;
			delete[] this->itemsCheck;
			this->items = temp;
			this->itemsCheck = newitemsCheck;
		}
		else if (newSize > this->size) {
			this->size = newSize;
			T* temp = new T[newSize];
			bool* newitemsCheck = new bool[newSize];
			for (int i = 0; i < this->size; i++) {
				if (this->itemsCheck[i]) {
					temp[i] = this->items[i];
					newitemsCheck[i] = true;
				}
				else {
					newitemsCheck[i] = false;
				}
			}
			for (int i = this->size; i < newSize; i++) 
				newitemsCheck[i] = false;
			delete[] this->items;
			delete[] this->itemsCheck;
			this->items = temp;
			this->itemsCheck = newitemsCheck;
		}
	}
	

	void InsertAt(T value, int index) {
		if (index < 0 || index > this->size - 1)
			throw Exception("IndexOutOfRange");
		T* temp = new T[this->size + 1];
		for (int i = 0; i < index; i++) {
			temp[i] = this->items[i];
		}
		temp[index] = value;
		for (int i = index + 1; i < this->size + 1; i++) {
			temp[i] = this->items[i - 1];
		}
	}
	void RemoveAt(const int index) {
		if (index < 0 || index > this->size - 1)
			throw Exception("IndexOutOfRange");
		T* newItems = new T[size - 1];
		bool* newItemsCheck = new bool[size - 1];
		for (int i = 0; i < index; i++) {
			newItems[i] = this->Get(i);
			newItemsCheck[i] = this->itemsCheck[i];
		}
		for (int i = index + 1; i < size; i++) {
			newItems[i - 1] = this->Get(i);
			newItemsCheck[i - 1] = this->itemsCheck[i];
		}
		delete[] this->items;
		delete[] this->itemsCheck;
		this->items = newItems;
		this->itemsCheck = newItemsCheck;
		this->size--;
	}
	void Remove(T value) {
		int i = 0;
		while ((i < this->size) && (this->items[i] != value)) {
			i++;
		}
		if (i != this->size) {
			if (this->items[i] == value) {
				this->RemoveAt(i);
			}
		}
	}
	void RemoveAll(T value) {
		int k = 0;
		for (int i = 0; i < this->size; i++) {
			if (this->items[i] == value) {
				k++;
			}
		}
		for (int i = 0; i < k; i ++) {
			this->Remove(value);
		}
	}
	~DynamicArray()
	{
		Free();
	}

	void Free()
	{
		if (items != nullptr)
		{
			delete[] items;
			items = nullptr;
		}

		if (itemsCheck != nullptr)
		{
			delete[] itemsCheck;
			itemsCheck = nullptr;
		}
	}
};