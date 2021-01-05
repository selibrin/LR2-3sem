#pragma once
#include "IDictionary.hpp"
#include "Headers.hpp"
#include <string.h>


ListSequence<int>* current_lenght(ListSequence<string>* list) {
	ListSequence<int>* let_list = new ListSequence<int>();
	int cur_len = 0;

	for (int i = 1; i <= list->GetLength(); i++) {
		for (int k = 0; k < i; k++) {
			cur_len += list->Get(k).length();
		}
		cur_len += i - 1;
		let_list->Prepend(cur_len);
		cur_len = 0;
	}
	return let_list;
}



ListSequence<string>* WordList(string input, string delimiter, int& size) {
	string s = input;

	ListSequence<string>* list = new ListSequence<string>();

	size_t pos = 0;
	string token;

	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		list->Prepend(token);
		s.erase(0, pos + delimiter.length());
		++size;
	}
	list->Prepend(s);
	++size;
	return list;
}

IDictionary<string, int>* alphabetPtr(string input, int size, string type) {
	IDictionary<string, int>* output;
	int words = 0;

	string s = input;
	ListSequence<string>* list = WordList(s, " ", words);
	//list->Print();
	int wordscopy = words;

	output = new IDictionary<string, int>(words);

	if (type == "words") {
		int page = size;
		int first_page = (int)(page / 2);
		int tenth_page = (int)(page * 3 / 4);

		int num_pages = 0;
		int tenthpages = 0;

		wordscopy -= first_page;
		++num_pages;

		if (wordscopy > 0) {
			for (int i = wordscopy; i > 0; ) {
				if ((num_pages % 10) == 0) {
					i -= tenth_page;
				}
				else {
					i -= page;
				}
				++num_pages;
			}
		}


		for (int current_page = 1; (current_page <= num_pages); ++current_page) {
			if (current_page == 1) {
				for (int word = 0; (word < first_page) && (words > 0); ++word) {
					output->Add(list->Get(word), current_page);
					--words;
				}
			}
			else if ((current_page % 10) != 0) {
				for (int word = 0; (word < page) && (words > 0); ++word) {
					output->Add(list->Get(word + first_page + (current_page - 2 - tenthpages) * page + tenthpages * tenth_page), current_page);
					--words;
				}
			}
			else {
				for (int word = 0; (word < tenth_page) && (words > 0); ++word) {
					output->Add(list->Get(word + first_page + (current_page - 2 - tenthpages) * page + tenthpages * tenth_page), current_page);
					--words;
					++tenthpages;
				}
			}
		}
	}

	else if (type == "letters") {
		int len = input.length();
		int page = size;
		int first_page = (int)(page / 2);
		int tenth_page = (int)(page * 3 / 4);

		cout << list->GetLength() + 1 << " words" << endl;
		int added = 0;
		//cout << "first page: " << first_page << endl << "page: " << page << endl << "tenth_page: " << tenth_page;

		ListSequence<int>* let_list = current_lenght(list);
		//let_list->Print();
		for (int i = first_page, k = 0; i > 0; ) {
			if ((i - let_list->Get(k)) < 0) {
				//cout << "# words: " << k << endl << "curr_page: 1" << endl;
				for (int m = 0; m < k; m++) {
					output->Add(list->Get(m), 1);
				}
				i -= let_list->Get(k);
				for (int n = 0; n < k; n++) {
					list->RemoveAt(0);
				}
				added += k;
				len -= (let_list->Get(k - 1) + 1);
			}
			else {
				k++;
			}
		}
		//list->Print();
		//cout << len << endl;
		//let_list->Print();
		delete let_list;
		int current_page = 2;

		//cout << added << " words is used" << endl << len << endl << endl;

		while (len > 0) {
			ListSequence<int>* let_list = current_lenght(list);
			//let_list->Print();

			if ((current_page % 10) != 0) {
				if (let_list->Get(let_list->GetLength() - 1) > page) {
					for (int i = page, k = 0; i > 0; k++) {

						if ((i - let_list->Get(k)) < 0) {
							//cout << "# words: " << k << endl << "curr_page: " << current_page << endl;
							for (int m = 0; m < k; m++) {
								output->Add(list->Get(m), current_page);
							}
							i -= let_list->Get(k);
							for (int m = 0; m < k; m++) {
								list->RemoveAt(0);
							}
							added += k;
							len -= (let_list->Get(k - 1) + 1);
						}
					}
				}
				else {
					for (int i = 0; i < list->GetLength(); i++) {
						output->Add(list->Get(i), current_page);
						++added;
					}
					len -= let_list->Get(let_list->GetLength() - 1);
				}
				++current_page;
				//cout << added << " words is used" << endl << len << endl << endl;
			}
			else {
				if (let_list->Get(let_list->GetLength() - 1) > tenth_page) {
					for (int i = tenth_page, k = 0; i > 0; k++) {

						if ((i - let_list->Get(k)) < 0) {
							//cout << "# words: " << k << endl << "curr_page: " << current_page << endl;
							for (int m = 0; m < k; m++) {
								output->Add(list->Get(m), current_page);
							}
							i -= let_list->Get(k);
							for (int m = 0; m < k; m++) {
								list->RemoveAt(0);
							}
							added += k;
							len -= (let_list->Get(k - 1) + 1);
						}
					}
				}
				else {
					for (int i = 0; i < list->GetLength(); i++) {
						output->Add(list->Get(i), current_page);
						++added;
					}
					len -= let_list->Get(let_list->GetLength() - 1);
				}
				++current_page;
				//cout << added << " words is used" << endl << len << endl << endl;
			}
			delete let_list;
		}


	}

	return output;
}

void PrintAlphabetPtr(IDictionary< string, int >* Dict) {
	cout << "|============Alphabetical Index============|" << endl;
	Dict->Print("WORD", "PAGE");
}