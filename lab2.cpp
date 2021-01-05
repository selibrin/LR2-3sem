#pragma once
#include "Alphabet.hpp"
#include "TicTacToe.hpp"

int main() {
	/*
	string input;
	string type;
	int size;

	cout << "Enter your String:  ";
	getline(cin, input );
	cout << endl;

	cout << "Enter your the Type of pagination: ('words' or 'letters')  ";
	getline(cin, type);
	cout << endl;

	cout << "Enter the number of elements on one page:  ";
	cin >> size;
	cout << endl;

	IDictionary<string, int>* Dict = alphabetPtr(input, size, type);

	PrintAlphabetPtr(Dict);
	*/


	TicTacToe* Game = new TicTacToe("PVE");
	Game->Play();

	return 0;
}
