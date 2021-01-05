#pragma once
#include <iostream>
#include "Sorter.hpp"
#include <thread>
#include "PrintSimulation.hpp"
#include <string>
using namespace std;

void SorterTests() {
	{
		int arr[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
		int size = sizeof(arr) / sizeof(int);

		ArraySequence<int>* A = new ArraySequence<int>(arr, size);
		BubbleSorter<int> s;
		s.Sorter(A, compare);

		int check = 0;
		for (int i = 0; i < size - 1; i++)  {
			if (A->Get(i) > A->Get(i + 1)) check++;		
		}

		A->~ArraySequence();
		
		char str[] = "BubbleSort test on an int_array succeeded.";
		if (check == 0)
			PrintSimulationEndLine(str);
		else
			cout << "BubbleSort test on an int_array failed. Amount of errors is " << check << endl;
	}

	{
		
		double arr[] = { 9.5, 8.8, 7.8, 6.4, 5.9, 4.1, 3.5, 2,547, 1.1002 };
		int size = sizeof(arr) / sizeof(double);

		ArraySequence<double>* A = new ArraySequence<double>(arr, size);
		BubbleSorter<double> s;
		s.Sorter(A, compare);

		int check = 0;
		for (int i = 0; i < size - 1; i++) {
			if (A->Get(i) > A->Get(i + 1)) check++;
		}

		A->~ArraySequence();
	
		char str[] = "BubbleSort test on a double_array succeeded.";
		if (check == 0)
			PrintSimulationEndLine(str);
		else
			cout << "BubbleSort test on a double_array failed. Amount of errors is " << check << endl;
		
	}
	
	{
		int arr[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 10};
		int size = sizeof(arr) / sizeof(int);

		ListSequence<int>* L = new ListSequence<int>(arr, size);
		BubbleSorter<int> s;
		s.Sorter(L, compare);
	

		int check = 0;
		for (int i = 0; i < L->GetLength()-1; i++) {
			if (L->Get(i) > L->Get(i + 1)) 
				check++; 
		}

		L->~ListSequence();
		
		char str[] = "BubbleSort test on an int_list succeeded.";
		if (check == 0)
			PrintSimulationEndLine(str);
		else
			cout << "BubbleSort test on an int_list failed. Amount of errors is " << check << endl;
	}
	
	{

		double arr[] = { 9.457, 8.662, 7.991, 6.454, 5.005, 4.4474, 3.228, 2.463, 1.337 };
		int size = sizeof(arr) / sizeof(double);

		ListSequence<double>* L = new ListSequence<double>(arr, size);
		BubbleSorter<double> s;
		s.Sorter(L, compare);
		
		int check = 0;
		for (int i = 0; i < L->GetLength()-1; i++) {
			if (L->Get(i) > L->Get(i + 1)) check++; 		
		}

		L->~ListSequence();
		
		char str[] = "BubbleSort test on a double_list succeeded.";
		if (check == 0)
			PrintSimulationEndLine(str);
		else
			cout << "BubbleSort test on a double_list  failed. Amount of errors is " << check << endl;

	}

	{
		int arr[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
		int size = sizeof(arr) / sizeof(int);

		ArraySequence<int>* A = new ArraySequence<int>(arr, size);
		ShellSort<int> s;
		s.Sorter(A, compare);

		int check = 0;
		for (int i = 0; i < size - 1; i++) {
			if (A->Get(i) > A->Get(i + 1)) check++;
		}

		A->~ArraySequence();
		
		char str[] = "ShellSort test on an int_array succeeded.";
		if (check == 0)
			PrintSimulationEndLine(str);
		else
			cout << "ShellSort test on an int_array failed. Amount of errors is " << check << endl;
	}
	
	{
		double arr[] = { 9.457, 8.662, 7.991, 6.454, 5.005, 4.4474, 3.228, 2.463, 1.337 };
		int size = sizeof(arr) / sizeof(double);

		ArraySequence<double>* A = new ArraySequence<double>(arr, size);
		ShellSort<double> s;
		s.Sorter(A, compare);

		int check = 0;
		for (int i = 0; i < size - 1; i++) {
			if (A->Get(i) > A->Get(i + 1)) check++;
		}

		A->~ArraySequence();
		
		char str[] = "ShellSort test on a double_array succeeded.";
		if (check == 0)
			PrintSimulationEndLine(str);
		else
			cout << "ShellSort test on a double_array failed. Amount of errors is " << check << endl;
	}

	{
		int arr[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 10 };
		int size = sizeof(arr) / sizeof(int);

		ListSequence<int>* L = new ListSequence<int>(arr, size);
		ShellSort<int> s;
		s.Sorter(L, compare);


		int check = 0;
		for (int i = 0; i < L->GetLength() - 1; i++) {
			if (L->Get(i) > L->Get(i + 1))
				check++;
		}


		L->~ListSequence();
		
		char str[] = "ShellSort test on an int_list succeeded.";
		if (check == 0)
			PrintSimulationEndLine(str);
		else
			cout << "ShellSort test on an int_list failed. Amount of errors is " << check << endl;
	}
	
	{

		double arr[] = { 9.457, 8.662, 7.991, 6.454, 5.005, 4.4474, 3.228, 2.463, 1.337 };
		int size = sizeof(arr) / sizeof(double);

		ListSequence<double>* L = new ListSequence<double>(arr, size);
		ShellSort<double> s;
		s.Sorter(L, compare);

		int check = 0;
		for (int i = 0; i < L->GetLength() - 1; i++) {
			if (L->Get(i) > L->Get(i + 1)) check++;
		}


		L->~ListSequence();

		char str[] = "ShellSort test on a double_list succeeded.";
		if (check == 0)
			PrintSimulationEndLine(str);
		else
			cout << "ShellSort test on a double_list failed. Amount of errors is " << check << endl;

	}
	
	{
		int arr[] = { 125, 1, 16, 22, 4, 3, 555, 65, 14, 12, 122, 333, 6544, 14};
		int size = sizeof(arr) / sizeof(int);
		
		ArraySequence<int>* A = new ArraySequence<int>(arr, size);
		InsertionSorter<int> s;
		s.Sorter(A, compare);

		int check = 0;
		for (int i = 0; i < size - 1; i++) {
			if (A->Get(i) > A->Get(i + 1))	check++;
		}


		A->~ArraySequence();

		char str[] = "InsertionSorter test on an int_array succeeded.";
		if (check == 0)
			PrintSimulationEndLine(str);
		else
			cout << "InsertionSorter test on an int_array failed. Amount of errors is " << check << endl;
	}


	{

		double arr[] = { 9.5, 8.8, 7.8, 6.4, 5.9, 4.1, 3.5, 2,547, 1.1002 };
		int size = sizeof(arr) / sizeof(double);

		ArraySequence<double>* A = new ArraySequence<double>(arr, size);
		BubbleSorter<double> s;
		s.Sorter(A, compare);

		int check = 0;
		for (int i = 0; i < size - 1; i++) {
			if (A->Get(i) > A->Get(i + 1)) check++;
		}

		A->~ArraySequence();

		char str[] = "InsertionSorter test on a int_list succeeded.";
		if (check == 0)
			PrintSimulationEndLine(str);
		else
			cout << "InsertionSorter test on a double_array failed. Amount of errors is " << check << endl;

	}

	{
		int arr[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 10 };
		int size = sizeof(arr) / sizeof(int);

		ListSequence<int>* L = new ListSequence<int>(arr, size);
		BubbleSorter<int> s;
		s.Sorter(L, compare);


		int check = 0;
		for (int i = 0; i < L->GetLength() - 1; i++) {
			if (L->Get(i) > L->Get(i + 1))
				check++;
		}

		L->~ListSequence();

		char str[] = "InsertionSorter test on a int_list succeeded.";
		if (check == 0)
			PrintSimulationEndLine(str);
		else
			cout << "InsertionSorter test on an int_list failed. Amount of errors is " << check << endl;
	}

	{

		double arr[] = { 9.457, 8.662, 7.991, 6.454, 5.005, 4.4474, 3.228, 2.463, 1.337 };
		int size = sizeof(arr) / sizeof(double);

		ListSequence<double>* L = new ListSequence<double>(arr, size);
		BubbleSorter<double> s;
		s.Sorter(L, compare);

		int check = 0;
		for (int i = 0; i < L->GetLength() - 1; i++) {
			if (L->Get(i) > L->Get(i + 1)) check++;
		}

		L->~ListSequence();

		char str[] = "InsertionSorter test on a double_list succeeded.";
		if (check == 0)
			PrintSimulationEndLine(str);
		else
			cout << "InsertionSorter test on a double_list  failed. Amount of errors is " << check << endl;

	}
}