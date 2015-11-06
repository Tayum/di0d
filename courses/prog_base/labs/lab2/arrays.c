#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void fillRand3(int arr[], int size) {
	// srand(time(NULL)); this function should be in main(void)
	int i;
	for (i = 0; i < size; i++) {
		arr[i] = rand() % 2;
	}
}

int checkRand3(int arr[], int size) {
	int i;
	int check = 1;
	for (i = 0; i < size; i++) {
		if (arr[i] != 0 && arr[i] != 1) {
			check = 0;
		}
	}
	return check;
}

int maxValue(int arr[], int size) {
	int i;
	int max = arr[0];
	for (i = 1; i < size; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	return max;
}

int maxIndex(int arr[], int size) {
	int i;
	int max = arr[0];
	int index = 0;
	for (i = 1; i < size; i++) {
		if (arr[i] > max) {
			index = i;
			max = arr[i];
		}
	}
	return index;
}

int maxOccurance(int arr[], int size) {
	int i;
	int z=0;
	int o=0;
	int occurance = 0;
	for (i = 0; i < size; i++) {
		if (arr[i] == 0) {
			z++;
		}
		else {
			o++;
		}
	}
	if (o >= z) {
		occurance = 1;
	}
	else {
		occurance = 0;
	}
	return occurance;
}

int diff(int arr1[], int arr2[], int res[], int size) {
	int i;
	int diff = 1;
	for (i = 0; i < size; i++) {
		res[i] = arr1[i] - arr2[i];
		if (res[i] != 0) {
			diff = 0;
		}
	}
	return diff;
}

void sub(int arr1[], int arr2[], int res[], int size) {
	int i;
	for (i = 0; i < size; i++) {
		res[i] = arr1[i] - arr2[i];
	}
}

int eq(int arr1[], int arr2[], int size) {
	int i;
	int eq = 1;
	for (i = 0; i < size; i++) {
		if (arr1[i] != arr2[i]) {
			eq = 0;
		}
	}
	return eq;
}

void lor(int arr1[], int arr2[], int res[], int size) {
	int i;
	for (i = 0; i < size; i++) {
		if (arr1[i] == 0 && arr2[i] == 0) {
			res[i] = 0;
		}
		else {
			res[i] = 1;
		}
	}
}