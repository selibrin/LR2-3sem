#pragma once 
#include "Exception.hpp"
#include <cstdlib>
#include <ctime>
#include <stdlib.h>  
using namespace std;



template <class T>
class LinkedList
{
private:
	struct node
	{
		T data;
		int index;
		node* next;
	};

	node* head;
public:
	LinkedList()
	{
		head = NULL;
	}

	LinkedList(T* items, int count)
	{

		for (int i = 0; i < count; ++i)
		{
			this->addNode(items[i]);
		}

	}

	LinkedList(LinkedList <T>& other)
	{

		node* current = other.head;
		while (current->next != NULL)
		{
			this->addNode(current->data);
			current = current->next;
		}
		this->addNode(current->data);
	}

	void addNode(T d)
	{
		node* nd = new node;
		nd->data = d;
		nd->index = 0;
		nd->next = NULL;

		if (head == NULL)
			head = nd;
		else
		{
			node* current = head;
			while (current->next != NULL)
				current = current->next;
			nd->index = current->index + 1;
			current->next = nd;
		}
	}


	T GetFirst()
	{
		return head->data;
	}
	T GetLast()
	{
		if (head == NULL) throw Exception("IndexOutOfRange");
		else
		{
			node* current = head;
			while (current->next != NULL)
			{

				current = current->next;
			}
			return current->data;
		}
	}
	T Get(int ind)
	{
		node* current = head;
		while (current != NULL)
		{
			if (current->index == ind)
				return current->data;
			current = current->next;
		}
	}
	int GetLength()
	{
		int size = 0;
		node* current = head;
		while (current != NULL)
		{
			//current = current->next;
			size = current->index + 1;
			current = current->next;
		}
		return size;
	}
	LinkedList<T>* GetSubList(int startindex, int endindex)
	{
		node* current = head;
		while (current->index != startindex)
			current = current->next;

		LinkedList<T>* ll = new LinkedList<T>();

		while (current->index != endindex)
		{
			ll->addNode(current->data);
			current = current->next;
		}
		ll->addNode(current->data);

		return ll;

	}

	void Put(T item, int count)
	{
		int size = 0;
		node* current = this->head;
		while (current != NULL)
		{
			size = current->index + 1;
			current = current->next;
		}
		current = this->head;
		if (count<size && count>-1)
		{
			while (current->index != count)
				current = current->next;
			current->data = item;
		}
		else throw Exception("IndexOutOfRange");
	}

	void InsertAt(T items, int index)
	{
		T temp, a;
		int size = 0;
		node* current = this->head;
		while (current != NULL)
		{
			size = current->index + 1;
			current = current->next;
		}
		current = this->head;
		if (index<size && index>-1)
		{
			while (current->index != index)
				current = current->next;
			temp = current->data;
			current->data = items;
			
			while (current->next != NULL)
			{
				a = current->data;
				current->data = temp;
				temp = a;
				current = current->next;
			}
			node* nd = new node;

			a = current->data;
			current->data = temp;
			temp = a;

			nd->data = temp;
			nd->index = size;
			nd->next = NULL;
			current->next = nd;


		}
		else throw Exception("IndexOutOfRange");
	}

	
	void RemoveAt(const int index)
	{
		if (index < 0 || index >= this->GetLength())
			throw Exception("IndexOutOfRange");
		if (index == 0)
		{
			node* temp = this->head;
			this->head = this->head->next;

			delete temp;

			node* last = this->head;

			while (last->next != NULL)
			{
				last->index--;
				last = last->next;
			}
		}
		else
		{
			node* last = this->head;

			for (int i = 0; i < index - 1; i++)
			{
				last = last->next;
			}
			node* ToDelete = last->next;
			last->next = ToDelete->next;

			delete ToDelete;
			while (last->next != NULL)
			{
				last->index--;
				last = last->next;
			}
		}
    }
	
	~LinkedList()
	{
		Free();
	}

	void Free()
	{
		node* temp;
		if (this->head != NULL)
		{
			while (this->head->next != NULL)
			{
				temp = this->head->next;
				delete this->head;
				this->head = temp;
				
			}
		}
	}
};
 