#pragma once

#include "Sequence.hpp"

template <class T>
class ISorter
{
public:
	virtual void Sorter(Sequence<T>* seq, bool (*cmp)(T, T)) = 0;
	// virtual void Sorter(Sequence<T>* seq, bool (*cmp)(T, T), int step) = 0;
};
