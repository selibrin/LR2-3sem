#pragma once

template <class T>
class Sequence
{
public:
	virtual int GetLength() const = 0;
	virtual T GetFirst() const = 0;
	virtual T GetLast() const = 0;
	virtual T Get(const int i) const = 0;
	virtual Sequence<T>* GetSubsequence(const int start, const int end) const = 0;
public:
	virtual void Append(const T value) = 0;
	virtual void Prepend(const T value) = 0;
	virtual void InsertAt(const int index, const T value) = 0;
	virtual void Set(const T item, int index) = 0;
	virtual void RemoveAt(const int index) = 0;
	virtual void Remove(const T value) = 0;
	virtual void RemoveAll(const T value) = 0;
	virtual void Swap(int index1,int index2) = 0;
	virtual Sequence<T>* Concat(Sequence<T>* other) = 0;
public:
	virtual void Free() = 0;
};
