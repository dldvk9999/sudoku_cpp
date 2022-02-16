#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
using namespace std;
#include "testcase.h"

constexpr auto LENGTH		= 9;
constexpr auto TEST_MODE	= 2;	// 0 : OFF, 1 : Test case, 2 : Function Test

vector<string> split(string input, char delimiter) {
	vector<string> answer;
	stringstream ss(input);
	string temp;
	while (getline(ss, temp, delimiter))
		answer.push_back(temp);
	return answer;
}

bool Row_Check(vector<vector<string>> arr) {
	map<string, int> list;
	for (int i = 0; i < LENGTH; i++) {
		list = {};
		for (const auto& item : arr[i]) {
			if (list.find(item) == list.end()) list[item] = 1;
			else return false;
		}
	}
	return true;
}

bool Col_Check(vector<vector<string>> arr) {
	// Input this function ...
	return true;
}

bool Square_Check(vector<vector<string>> arr) {
	// Input this function ...
	return true;
}

vector<vector<string>> calculate(vector<vector<string>> arr) {
	vector<vector<string>> result = arr;
	// Input this function ...
	return result;
}

int main(void) {
	vector<vector<string>> numbers;

	if (TEST_MODE == 1) {
		bool result = false;
		for (int i = 0; i < TESTCASE_INPUT.size(); i++)
			if (calculate(TESTCASE_INPUT[i]) != TESTCASE_OUTPUT[i]) {
				result = true;
				break;
			}
		string message = result ? "Fail" : "Success";
		cout << message << endl;
	}
	else if (TEST_MODE == 2) {
		for (int i = 0; i < LENGTH; i++) {
			string num = "";
			getline(cin, num);
			numbers.push_back(split(num, ' '));
		}

		string message = Row_Check(numbers) ? "No duplicates" : "duplicate existence";
		cout << "Rows : " << message << endl;
		message = Col_Check(numbers) ? "No duplicates" : "duplicate existence";
		cout << "Cols : " << message << endl;
		message = Square_Check(numbers) ? "No duplicates" : "duplicate existence";
		cout << "Squares : " << message << endl;
	}
	else {
		for (int i = 0; i < LENGTH; i++) {
			string num = "";
			getline(cin, num);
			numbers.push_back(split(num, ' '));
		}

		numbers = calculate(numbers);

		for (int i = 0; i < LENGTH; i++) {
			for (int j = 0; j < LENGTH; j++) {
				cout << numbers[i][j] << " ";
				if ((j + 1) % 3 == 0) cout << "\t";
			}
			cout << endl;
			if ((i + 1) % 3 == 0) cout << endl;
		}
	}

	return 0;
}