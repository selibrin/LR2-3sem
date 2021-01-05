#pragma once
#include "BinaryTree.hpp"

template <class TKey, class TItem>
class IDictionary {
private:
	//BinaryTree<TKey, TItem>* Tree;
	int Capacity;
	int Count;

public:
	BinaryTree<TKey, TItem>* Tree;

	IDictionary(int capacity = 100) {
		this->Capacity = capacity;
		this->Count = 0;
		this->Tree = new BinaryTree<TKey, TItem>();
	}

	int GetCapacity() {
		return this->Capacity;
	}
	int GetCount() {
		return this->Count;
	}

	TItem Get(TKey key) {
		auto node = this->Tree->findNode(key);
		if (node != nullptr) {
			return node->item;
		}
		else return NULL;
	}

	bool ContainsKey(TKey key) {
		return this->Tree->toCheck(key);
	}

	void Add(TKey key, TItem item) {
		this->Tree->toInsert(key, item);
		++this->Count;
	}

	// Для типов, совместимых с std::cout 
	void Print(string maintag = "", string tag = "") {
		auto list = this->Tree->Chain("LNR");

		cout << "|    ";
		cout.width(20);
		cout.setf(ios::left);
		cout << maintag;

		cout << "    |     ";
		cout.width(6);
		cout << tag;
		cout << "  |" << endl;
		cout << "|============================" << "|" << "=============" << "|" << endl;
		for (int i = 0; i < list->GetLength(); ++i) {
			cout << "|    ";
			cout.width(20);
			cout.setf(ios::left);
			cout << list->Get(i)->key << "    |      ";
			cout.width(6);
			cout << list->Get(i)->item << " |" << endl;
			cout << "|----------------------------" << "|" << "-------------" << "|" << endl;
		}
		delete list;
	}

	IDictionary<TKey, TItem>* CopyDict(IDictionary<TKey, TItem>* NewDict) {
		auto list = this->Tree->Chain("NLR");
		for (int i = 0; i < this->Count; i++) {
			NewDict->Add(list->Get(i)->key, list->Get(i)->item);
		}

		delete list;


		return NewDict;
	}

	void Remove(TKey key) {
		this->Tree->removeNode(key);
		return;
	}
};