#pragma once
#include <string.h>
#include <thread>

void PrintSimulationEndLine(const char arr[]) {
	int length = strlen(arr);
	this_thread::sleep_for(chrono::milliseconds(10));
	for (int i = 0; i < length; i++) {
		std::cout << arr[i];
		this_thread::sleep_for(chrono::milliseconds(7));
	}
	std::cout << endl;
}

void PrintSimulationEndLine(const char arr[], int duration) { // [duration] = ms
	int length = strlen(arr);
	this_thread::sleep_for(chrono::milliseconds(duration));
	for (int i = 0; i < length; i++) {
		std::cout << arr[i];
		this_thread::sleep_for(chrono::milliseconds(duration));
	}
	std::cout << endl;
}

void PrintSimulation(const char arr[]) {
	int length = strlen(arr);
	this_thread::sleep_for(chrono::milliseconds(10));
	for (int i = 0; i < length; i++) {
		std::cout << arr[i];
		this_thread::sleep_for(chrono::milliseconds(7));
	}
	std::cout << ' ';
}

void PrintSimulation(const char arr[], int duration) { // [duration] = ms
	int length = strlen(arr);
	this_thread::sleep_for(chrono::milliseconds(duration));
	for (int i = 0; i < length; i++) {
		std::cout << arr[i];
		this_thread::sleep_for(chrono::milliseconds(duration));
	}
	std::cout << ' ';
}