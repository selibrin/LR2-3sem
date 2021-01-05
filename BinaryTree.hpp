#pragma once
#include "Headers.hpp"
#include <stdio.h>
#include <Windows.h>

std::ostream& operator << (std::ostream& os, const pair<int, int>& p) {
	return os << "(" << p.first << ", " << p.second << ")";
}

bool operator< (string s1, string s2) {
	for (int i = 0; i < min(s1.length(), s2.length()); ++i) {
		if (s1[i] > s2[i]) return false;
		else if (s1[i] < s2[i]) return true;
	}
	if (s1[min(s1.length(), s2.length())]) return false;
	else if (s2[min(s1.length(), s2.length())]) return true;
	else return false;
}

bool operator> (string s1, string s2) {
	for (int i = 0; i < min(s1.length(), s2.length()); ++i) {
		if (s1[i] > s2[i]) return true;
		else if (s1[i] < s2[i]) return false;
	}
	if (s1[min(s1.length(), s2.length())]) return true;
	else if (s2[min(s1.length(), s2.length())]) return false;
	else return false;
}

template <class TKey, class TItem>
class BinaryTree {
public:
	struct Node {
		TKey key;
		TItem item;
		Node* left;
		Node* right;

		Node(TKey key, TItem item) {
			this->key = key;
			this->item = item;
			this->left = nullptr;
			this->right = nullptr;
		}

		pair<TKey, TItem> Get() {
			pair<TKey, TItem> p;
			p.first = key;
			p.second = item;
			return p;
		}
	};

public:
	Node* root;

public:
	//----------Конструкторы----------//
	BinaryTree(TKey key, TItem item) {
		this->root = new Node(key, item);
	};

	BinaryTree(Node* root) {
		this->root = root;
	};

	BinaryTree() {
		this->root = nullptr;
	};

	//-------------Методы--------------//

	Node* getRoot() {
		return this->root;
	};

	// Проверка на наличие элемента в дереве
	bool toCheck(TKey key) {
		Node* temp;
		temp = this->root;

		while (temp != nullptr) {
			if (temp->Get().first > key) {
				temp = temp->left;
			}
			else if (temp->Get().first < key) {
				temp = temp->right;
			}
			else {
				return true;
			}
		}

		if (temp == nullptr) {
			return false;
		}
	};

	// Поиск узла по ключу с заданного узла
	Node* findNode(Node* Node, TKey key) {
		if (this->root == nullptr) {
			throw std::exception("ERROR: Tree is EMPTY");
		}

		if (Node->key == key) {
			return Node;
		}
		else {
			if (Node->key < key) {
				return findNode(Node->right, key);
			}
			else {
				return findNode(Node->left, key);
			}
		}
		return nullptr;
	};

	// Поиск узла с заданным ключом во всём дереве
	Node* findNode(TKey key) {
		return findNode(this->root, key);
	};

	// map для поддерева, начиная с заданного узла
	void map(Node* Node, TItem(*foo)(TItem)) {
		Node->item = foo(Node->item);

		if (Node->right != nullptr) {
			map(Node->right, foo);
		}
		if (Node->left != nullptr) {
			map(Node->left, foo);
		}
	};

	// map для всего деева
	void map(TItem(*foo)(TItem)) {
		if (this->root == nullptr) {
			std::cout << "Tree is EMPTY" << std::endl;;
		}
		else {
			map(this->root, foo);
		}
	};

	// "Высота" поддерева, длина самой длинной ветви начиная с заданного узла
	static int getHeight(Node* Node)
	{
		int L = 0;
		int R = 0;
		if (Node->left == nullptr && Node->right == nullptr) {
			return 0;
		}
		else {
			if (Node->right != nullptr) {
				R = getHeight(Node->right) + 1;
			}
			else {
				R = 0;
			}

			if (Node->left != nullptr) {
				L = getHeight(Node->left) + 1;
			}
			else {
				L = 0;
			}
		}

		if (L > R) {
			return L;
		}
		else {
			return R;
		}
	};

	// "Высота" всего дерева
	int getHeight() {
		if (this->root == nullptr) {
			throw std::exception("ERROR: Tree is EMPTY");
		}

		return (getHeight(this->root));
	};

	// Получение поддерева по элементу
	BinaryTree<TKey, TItem>* getSubTree(TKey key) {
		Node* temp = this->findNode(key);
		BinaryTree<TKey, TItem>* subTree = new BinaryTree<TKey, TItem>(temp);

		return subTree;
	};

	// Проверка деревьев на равенство
	bool isEqual(BinaryTree<TKey, TItem>* Tree) {
		if ((this->getRoot() == nullptr && Tree->getRoot() != nullptr) ||
			(this->getRoot() != nullptr && Tree->getRoot() == nullptr)) {
			return false;
		}

		if (this->getRoot() == nullptr && Tree->getRoot()) {
			return true;
		}

		Node* Right = this->root->right;
		Node* Left = this->root->left;
		Node* treeRight = Tree->getRoot()->right;
		Node* treeLeft = Tree->getRoot()->left;
		bool out = true;

		if (Left != nullptr && treeLeft != nullptr) {
			out = out && this->getSubTree(Left->key)->isEqual(Tree->getSubTree(treeLeft->key));
		}

		if (Left == nullptr && treeLeft == nullptr) {
			out = true;
		}
		else {
			out = false;
		}

		if (Right != nullptr && treeRight != nullptr) {
			out = out && this->getSubTree(Right->key)->isEqual(Tree->getSubTree(treeRight->key));
		}

		if (Right == nullptr && treeRight == nullptr) {
			out = true;
		}
		else {
			out = false;
		}
		return out;
	};

	// Проверка на вхождение поддерева в исходной дерево
	bool toCheckSubtree(BinaryTree<TKey, TItem>* subTree) {
		if (subTree->getRoot() == nullptr && this->getRoot() != nullptr) {
			return false;
		}
		if (subTree->getRoot() == this->getRoot()) {
			return true;
		}
		if (this->toCheck(subTree->getRoot()->key)) {
			return this->getSubTree(subTree->getRoot()->key)->isEqual(subTree);
		}
		else {
			return false;
		}
	};

	// (НЕТ) Прошивка с заданного узла
	static Sequence<Node*>* Chain(Node* node, std::string order) {
		Sequence<Node*>* list = nullptr;

		for (size_t i = 0; i < order.length(); i++) {
			switch (order[i]) {

			case 'N':
				if (list == nullptr) {
					list = new ListSequence<Node*>();
					list->Prepend(node);
				}
				else {
					Sequence<Node*>* list1 = nullptr;
					list1 = new ListSequence<Node*>();
					list1->Prepend(node);

					list = list->Concat(list1);
				}
				break;

			case 'R':
				if (node->right != nullptr) {
					if (list == nullptr) {
						list = Chain(node->right, order);
					}
					else {
						list = list->Concat(Chain(node->right, order));
					}
				}
				break;

			case 'L':
				if (node->left != nullptr) {
					if (list == nullptr) {
						list = Chain(node->left, order);
					}
					else {
						list = list->Concat(Chain(node->left, order));
					}
				}
				break;
			}
		}
		return list;
	};

	// (НЕТ) Прошивка всего дерева
	Sequence<Node*>* Chain(std::string order) {
		return this->Chain(this->root, order);
	};


	// Восстановление дерева из списка узлов
	Node* deChain(Sequence<Node*>* Chain) {
		Sequence<Node*>* listLR = new ListSequence<Node*>();
		Sequence<Node*>* listN = Chain;
		ArraySequence<bool>* listCheck = new ArraySequence<bool>(listN->GetSize());

		for (int i = 0; i < listN->GetSize(); i++) {
			if (listN->Get(i)->left != nullptr) {
				listLR->Prepend(listN->Get(i)->left);
			}

			if (listN->Get(i)->right != nullptr) {
				listLR->Prepend(listN->Get(i)->right);
			}

			listCheck->Set(i, false);
		}

		for (int i = 0; i < listN->GetSize(); i++) {
			for (int k = 0; k < listLR->GetSize(); k++) {
				if (listLR->Get(k) == listN->Get(i)) {
					listCheck->Set(i, true);
				}
			}
		}

		for (int i = 0; i < listCheck->GetSize(); i++) {
			if (listCheck->Get(i) == false) {
				return listN->Get(i);
			}
		}

		return nullptr;
	};


	//---------------------------БЛОК-БАЛАНСИРОВКИ------------------------------------
	// Балансировка Day–Stout–Warren
	void DSW() {
		if (nullptr != root) {
			createBackbone();
			createBalancedBT();
		}
	};

	void createBackbone() {
		Node* grandParent = nullptr;
		Node* parent = root;
		Node* leftChild;

		while (nullptr != parent) {
			leftChild = parent->left;
			if (nullptr != leftChild) {
				grandParent = rotateRight(grandParent, parent, leftChild);
				parent = leftChild;
			}
			else {
				grandParent = parent;
				parent = parent->right;
			}
		}
	};

	Node* rotateRight(Node* grandParent, Node* parent, Node* leftChild) {
		if (nullptr != grandParent) {
			grandParent->right = leftChild;
		}
		else {
			root = leftChild;
		}
		parent->left = leftChild->right;
		leftChild->right = parent;
		return grandParent;
	};

	void createBalancedBT() {
		int n = 0;
		for (Node* tmp = root; tmp != nullptr; tmp = tmp->right) {
			n++;
		}

		int m = greatestPowerOf2LessThanN(n + 1) - 1;
		makeRotations(n - m);

		while (m > 1) {
			makeRotations(m /= 2);
		}
	};

	int greatestPowerOf2LessThanN(int n) {
		int x = MSB(n);
		return (1 << x);
	};

	int MSB(int n) {
		int ndx = 0;
		while (1 < n) {
			n = (n >> 1);
			ndx++;
		}
		return ndx;
	};

	void makeRotations(int bound) {
		Node* grandParent = nullptr;
		Node* parent = root;
		Node* child = root->right;
		for (; bound > 0; bound--) {
			if (child != nullptr && child->right != nullptr) {
				rotateLeft(grandParent, parent, child);
				grandParent = child;
				parent = grandParent->right;
				child = parent->right;
			}
			else {
				break;
			}
		}
	};

	void rotateLeft(Node* grandParent, Node* parent, Node* rightChild) {
		if (nullptr != grandParent) {
			grandParent->right = rightChild;
		}
		else {
			root = rightChild;
		}
		parent->right = rightChild->left;
		rightChild->left = parent;
	};
	//---------------------------------------------------------------------------

	// Вставка элемента
	void toInsert(TKey key, TItem item) {
		if (this->toCheck(key)) {
			return;
		}

		Node* toInsert = new Node(key, item);
		Node* p = this->root;
		Node* p1 = nullptr;

		while (p != nullptr) {
			p1 = p;
			if (key < p->Get().first) {
				p = p->left;
			}
			else {
				p = p->right;
			}
		}

		if (p1 == nullptr) {
			this->root = toInsert;
		}
		else {
			if (key < p1->Get().first) {
				p1->left = toInsert;
			}
			else {
				p1->right = toInsert;
			}
		}

		DSW();
	};



	Node* removeNode(Node* tree, TKey key) {
		if (tree == nullptr) {
			return tree;
		}

		if (key > tree->key) {
			tree->right = removeNode(tree->right, key);
			return tree;

		}
		else if (tree->key > key) {
			tree->left = removeNode(tree->left, key);
			return tree;
		}

		if (tree->left == nullptr) {
			Node* temp = tree->right;
			delete tree;
			return temp;

		}
		else if (tree->right == nullptr) {
			Node* temp = tree->left;
			delete root;
			return temp;

		}
		else {
			Node* succParent = tree;
			Node* succ = tree->right;

			while (succ->left != nullptr) {
				succParent = succ;
				succ = succ->left;
			}

			if (succParent != tree) {
				succParent->left = succ->right;

			}
			else {
				succParent->right = succ->right;
			}

			tree->key = succ->key;

			delete succ;
			return tree;
		}
	}

	/*
	Node* CopyTree(BinaryTree<TKey, TItem>* NewTree) {
		auto List = this->Chain("LNR");
		for (int i = 0; i < List->GetSize(); i++) {
			NewTree->toInsert(List->Get(i)->key, List->Get(i)->item);
		}
		delete List;
		return NewTree->root;
	}
	*/

	// Удаление узла по элементу
	Node* removeNode(TKey key) {
		return removeNode(this->root, key);
	};

	// Сохранение дерева по обходу в строку

	std::string toString(std::string order) {
		std::string res;
		Sequence<Node*>* chainTree = this->Chain(order);
		if (this->root == nullptr) {
			throw std::exception("ERROR: Tree is EMPTY");
		}

		for (int i = 0; i < chainTree->GetSize(); i++) {
			if (i == 0) {
				string strkey = (chainTree->Get(i)->key);
				string stritem = std::to_string(chainTree->Get(i)->item);

				res += strkey + ": " + stritem + " ";
			}
			else {
				string strkey = (chainTree->Get(i)->key);
				string stritem = std::to_string(chainTree->Get(i)->item);

				res += "-> " + strkey + ": " + stritem + " ";
			}
		}
		return res;
	};

	Sequence<pair<TKey, TItem>>* first_n(std::string order, int n) {

		Sequence<Node*>* chainTree = this->Chain(order);
		if (this->root == nullptr) {
			throw std::exception("ERROR: Tree is EMPTY");
		}
		pair<TKey, TItem> p;
		ArraySequence<pair<TKey, TItem>>* newlist = new ArraySequence<pair<TKey, TItem>>(n);
		for (int i = 0; i < n; i++) {
			p.first = chainTree->Get(i)->key;
			p.second = chainTree->Get(i)->item;
			newlist->Append(p);
		}
		return newlist;
	};

	// reduce
	/*
	T reduce(T(*foo)(T, T), T startItem, std::string order) {
		if (this->root == nullptr) {
			throw std::exception("ERROR: Tree is EMPTY");
		}
		T out = { 0 };
		Sequence<Node<T>*>* ChainTree = this->Chain(order);

		for (int i = 0; i < ChainTree->GetSize(); i++) {
			if (i == 0) {
				out = foo(ChainTree->Get(i)->Get(), startItem);
			}
			else {
				out = foo(ChainTree->Get(i)->Get(), out);
			}
		}
		delete ChainTree;
		return out;
	};
	*/

	// where
	/*
	Sequence<Node<T>*>* Where(bool(*foo)(T), std::string order) {
		if (this->getRoot() == nullptr) {
			throw std::exception("ERROR: Tree is EMPTY");
		}
		Sequence<Node<T>*>* list = this->Chain(order);
		Sequence<Node<T>*>* out = new ListSequence<Node<T>*>();
		for (int i = 0; i < list->GetSize(); i++) {
			if (foo(list->Get(i)->Get()) == true) {
				out->Prepend(list->Get(i));
			}
		}
		delete list;
		return out;
	};
	*/


	// Вывод дерева

	void printTree(Node* node, int level)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if (node)
		{
			printTree(node->left, level + 1);
			for (int i = 0; i < level - this->getHeight(); i++) cout << "          ";
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
			std::cout << "lvl" << level - this->getHeight() << ": ";
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
			std::cout << node->Get().first << ": " << node->Get().second << std::endl;
			printTree(node->right, level + 1);
		}
	};

	void printTree() {
		this->printTree(this->getRoot(), this->getHeight());
	};

};
