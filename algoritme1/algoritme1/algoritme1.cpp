// algoritme1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Implement a (sorting) algorithm of choice in C++. Measure the execution time of the algorithm using different input sizes and perform a regression analysis.

//On blackboard you’ll find a document describing how to do a regression analysis in Excel, 
//but you’re free to use other tools, such as R or SPSS.
//Do the results of your analysis match what Wikipedia says about the order of the algorithm ?

#include "pch.h"
#include <iostream>
#include <ctime>
#include <chrono>

//swap bubble sort
void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

//function to print an array 
void printArray(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", arr[i]);
	printf("n");
}

// A function to implement bubble sort , should be O(n^2)
void bubbleSort(int arr[], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)

		// Last i elements are already in place    
		for (j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1])
				swap(&arr[j], &arr[j + 1]);
}


int main()
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed_seconds; //time
	int arr[] = { 64, 34, 25, 12, 22, 11, 90 };
	int n = sizeof(arr) / sizeof(arr[0]);
	bubbleSort(arr, n);
	printf("Sorted array: \n");
	printArray(arr, n);
	std::cout << elapsed_seconds.count() << std::endl; //print elapsed time
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
