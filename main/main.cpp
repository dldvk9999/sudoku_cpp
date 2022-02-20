#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
using namespace std;
#include "testcase.h"

constexpr auto LENGTH		= 9;
constexpr auto TEST_MODE	= 1;	// 0 : OFF, 1 : Test case, 2 : Function Test

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
	map<string, int> list;
	for (int i = 0; i < LENGTH; i++) {
		list = {};
		for (int j = 0; j < LENGTH; j++) {
			if (list.find(arr[j][i]) == list.end()) list[arr[j][i]] = 1;
			else return false;
		}
	}
	return true;
}

bool Square_Check(vector<vector<string>> arr) {
	map<string, int> list1, list2, list3;
	for (int i = 0; i < LENGTH; i++) {
		if (i % (LENGTH / 3) == 0)
			list1 = {}, list2 = {}, list3 = {};

		for (int j = 0; j < LENGTH; j++) {
			if (j / (LENGTH / 3) == 0) {
				if (list1.find(arr[i][j]) == list1.end()) list1[arr[i][j]] = 1;
				else return false;
			}
			else if (j / (LENGTH / 3) == 1) {
				if (list2.find(arr[i][j]) == list2.end()) list2[arr[i][j]] = 1;
				else return false;
			}
			else {
				if (list3.find(arr[i][j]) == list3.end()) list3[arr[i][j]] = 1;
				else return false;
			}
		}
	}
	return true;
}

vector<vector<string>> calculate(vector<vector<string>> arr) {
	vector<vector<string>> result = arr;
	map<vector<int>, vector<string>> blank, number;

	// ���� ĭ�� ���� ĭ �з��Ͽ� map ���·� ����
	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			if (result[i][j] == "0")
				blank[{ i, j }] = { "1","2","3","4","5","6","7","8","9" };
			else
				number[{ i, j }] = { result[i][j] };
		}
	}

	// ���� ĭ ����Ʈ �� ���� ĭ ����Ʈ�� ���Ե� ���ڰ� ���� ��� ����
	for (const auto& num : number) {
		for (const auto& b : blank) {
			if (num.first[0] == b.first[0] || num.first[1] == b.first[1]) {
				auto index = find(b.second.begin(), b.second.end(), num.second[0]);
				if (index != b.second.end()) {
					vector<string> tmp = b.second;
					tmp.erase(remove(tmp.begin(), tmp.end(), num.second[0]), tmp.end());
					blank[{ b.first[0], b.first[1] }] = tmp;
				}
			}
		}
	}

	// ���� ĭ ����Ʈ�� value�� 0���̸� ���ְ�, 1���̸� result�� ���� �ְ� ����
	vector<vector<int>> rmlist;
	for (const auto& item : blank) {
		if (item.second.size() == 0)
			rmlist.push_back(item.first);
		else if (item.second.size() == 1) {
			result[item.first[0]][item.first[1]] = item.second[0];
			rmlist.push_back(item.first);
		}
	}
	for (const auto& item : rmlist) {
		blank.erase(item);
	}

	for (const auto& item : blank) {
		cout << "[" << item.first[0] << "," << item.first[1] << "]\t";
		for (const auto& list : item.second) {
			cout << list << ",";
		}
		cout << endl;
	}

	return result;
}

int main(void) {
	vector<vector<string>> numbers;

	if (TEST_MODE == 1) {
		bool result = false;
		for (int index = 0; index < TESTCASE_INPUT.size(); index++) {
			vector<vector<string>> input = calculate(TESTCASE_INPUT[index]);

			cout << "Input" << endl;
			for (int i = 0; i < LENGTH; i++) {
				for (int j = 0; j < LENGTH; j++) {
					cout << input[i][j] << " ";
					if ((j + 1) % 3 == 0) cout << "\t";
				}
				cout << endl;
				if ((i + 1) % 3 == 0) cout << endl;
			}

			cout << endl << "Output" << endl;
			for (int i = 0; i < LENGTH; i++) {
				for (int j = 0; j < LENGTH; j++) {
					cout << TESTCASE_OUTPUT[index][i][j] << " ";
					if ((j + 1) % 3 == 0) cout << "\t";
				}
				cout << endl;
				if ((i + 1) % 3 == 0) cout << endl;
			}

			if (input != TESTCASE_OUTPUT[index]) {
				result = true;
				break;
			}
		}
		string message = result ? "Fail" : "Success";
		cout << endl << message << endl;
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