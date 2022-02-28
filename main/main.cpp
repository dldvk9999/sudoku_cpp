#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <cmath>
using namespace std;
#include "testcase.h"

constexpr auto LENGTH		= 9;	// Board Length (9, 16, 25 ...)
constexpr auto PRINT_BOARD	= 0;	// 0 : OFF, 1 : Print ON
auto		   TEST_MODE	= 1;	// 0 : OFF, 1 : Test case, 2 : Function Test

vector<string> split(string input, char delimiter) {
	vector<string> answer;
	stringstream ss(input);
	string temp;
	while (getline(ss, temp, delimiter))
		answer.push_back(temp);
	return answer;
}

bool Row_Check(vector<vector<string>> arr) {
	for (int i = 0; i < LENGTH; i++) {
		map<string, int> list;
		for (const auto& item : arr[i])
			if (item != "0") {
				if (list.find(item) == list.end()) list[item] = 1;
				else return false;
			}
	}
	return true;
}

bool Col_Check(vector<vector<string>> arr) {
	for (int i = 0; i < LENGTH; i++) {
		map<string, int> list;
		for (int j = 0; j < LENGTH; j++)
			if (arr[j][i] != "0") {
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

		for (int j = 0; j < LENGTH; j++)
			if (arr[i][j] != "0") {
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

bool Zero_Check(vector<vector<string>> arr) {
	for (const auto &row : arr)
		for (const auto& col : row)
			if (col == "0")
				return false;
	return true;
}

void Row_Col_Clear(map<vector<int>, vector<string>> &blank, map<vector<int>, string> &number) {
	for (const auto& num : number)
		for (const auto& b : blank)
			if (num.first[0] == b.first[0] || num.first[1] == b.first[1])
				if (find(b.second.begin(), b.second.end(), num.second) != b.second.end()) {
					vector<string> tmp = b.second;
					tmp.erase(remove(tmp.begin(), tmp.end(), num.second), tmp.end());
					blank[{ b.first[0], b.first[1] }] = tmp;
				}
}

void Square_Clear(vector<vector<string>> &result, map<vector<int>, vector<string>> &blank, map<vector<int>, string> &number) {
	for (int i = 0; i < LENGTH; i += 3)
		for (int j = 0; j < LENGTH; j += 3) {
			map<string, int> tmp;
			map<string, vector<int>> pos;
			int tmp_a = i / 3 * 3;
			int tmp_b = j / 3 * 3;
			for (int a = tmp_a; a < tmp_a + 3; a++)
				for (int b = tmp_b; b < tmp_b + 3; b++)
					if (result[a][b] == "0")
						for (const auto& item : blank[{a, b}]) {
							if (tmp.find(item) != tmp.end())
								tmp[item] += 1;
							else {
								tmp[item] = 1;
								pos[item] = { a, b };
							}
						}
			for (const auto& item : tmp)
				if (item.second == 1) {
					bool flag = true;
					int tmp_a = pos[item.first][0] / 3 * 3;
					int tmp_b = pos[item.first][1] / 3 * 3;
					for (int a = tmp_a; a < tmp_a + 3; a++)
						for (int b = tmp_b; b < tmp_b + 3; b++)
							if (result[a][b] == item.first) {
								flag = false;
								break;
							}
					if (flag) {
						result[pos[item.first][0]][pos[item.first][1]] = item.first;
						number[{pos[item.first][0], pos[item.first][1]}] = item.first;
						blank.erase({ pos[item.first][0], pos[item.first][1] });
					}
				}
		}
}

void Square_Clear_2(vector<vector<string>>& result, map<vector<int>, vector<string>>& blank, map<vector<int>, string>& number) {
	for (int i = 0; i < LENGTH; i += 3)
		for (int j = 0; j < LENGTH; j += 3) {
			vector<string> tmp;
			int tmp_a = i / 3 * 3;
			int tmp_b = j / 3 * 3;
			for (int a = tmp_a; a < tmp_a + 3; a++)
				for (int b = tmp_b; b < tmp_b + 3; b++)
					if (result[a][b] != "0")
						tmp.push_back(result[a][b]);
			for (int a = tmp_a; a < tmp_a + 3; a++)
				for (int b = tmp_b; b < tmp_b + 3; b++)
					if (result[a][b] == "0") {
						vector<string> newtmp;
						for (const auto& item : blank[{a, b}])
							if (find(tmp.begin(), tmp.end(), item) == tmp.end())
								newtmp.push_back(item);
						blank[{a, b}] = newtmp;
					}
		}
}

void Blank_Clear(vector<vector<string>> &result, map<vector<int>, vector<string>> &blank) {
	vector<vector<int>> rmlist;
	for (const auto& item : blank) {
		if (item.second.size() == 0)
			rmlist.push_back(item.first);
		else if (item.second.size() == 1) {
			result[item.first[0]][item.first[1]] = item.second[0];
			rmlist.push_back(item.first);
		}
	}
	for (const auto& item : rmlist)
		blank.erase(item);
}

void Row_Blank_Clear(vector<vector<string>>& result, map<vector<int>, vector<string>>& blank, map<vector<int>, string>& number) {
	vector<vector<string>> square;
	for (int i = 0; i < LENGTH; i += 3)
		for (int j = 0; j < LENGTH; j += 3) {
			vector<string> tmp;
			int tmp_a = i / 3 * 3;
			int tmp_b = j / 3 * 3;
			for (int a = tmp_a; a < tmp_a + 3; a++)
				for (int b = tmp_b; b < tmp_b + 3; b++)
					if (result[a][b] != "0")
						tmp.push_back(result[a][b]);
			square.push_back(tmp);
		}

	for (int i = 0; i < LENGTH; i++)
		for (int j = 0; j < LENGTH; j++)
			if (result[i][j] == "0") {
				vector<string> tmp;
				vector<string> sq = square[(i / 3 * 3) + (j / 3)];
				for (const auto& item : blank[{i,j}])
					if (find(sq.begin(), sq.end(), item) == sq.end())
						tmp.push_back(item);
				if (tmp.size() == 1) {
					result[i][j] = tmp[0];
					number[{i, j}] = tmp[0];
					blank.erase({ i, j });
				}
			}
}

vector<vector<string>> Input_Value(vector<vector<string>> arr, map<vector<int>, vector<string>> blank) {
	vector<vector<string>> result = arr;
	map<vector<int>, vector<string>> b = blank;
	vector<int> firstIt = b.begin()->first;
	vector<string> secondIt = b.begin()->second;
	b.erase(b.begin());

	for (const auto& item : secondIt) {
		result[firstIt[0]][firstIt[1]] = item;

		if (!Row_Check(result) || !Col_Check(result) || !Square_Check(result))
			continue;

		if (b.size() != 0) {
			vector<vector<string>> tmp = Input_Value(result, b);
			if (!Row_Check(tmp) || !Col_Check(tmp) || !Square_Check(tmp) || !Zero_Check(tmp))
				continue;
			else if (Row_Check(tmp) && Col_Check(tmp) && Square_Check(tmp)) 
				return tmp;
			else
				result = tmp;
		}
		else
			return result;
	}
	return result;
}

void Print_Board(vector<vector<string>> arr) {
	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			cout << arr[i][j] << " ";
			if ((j + 1) % 3 == 0) cout << "\t";
		}
		cout << endl;
		if ((i + 1) % 3 == 0) cout << endl;
	}
}

vector<vector<string>> calculate(vector<vector<string>> arr) {
	vector<vector<string>> result = arr;
	map<vector<int>, vector<string>> blank;
	map<vector<int>, string> number;

	// 공백 칸과 숫자 칸 분류하여 map 형태로 저장
	for (int i = 0; i < LENGTH; i++)
		for (int j = 0; j < LENGTH; j++) {
			if (result[i][j] == "0") blank[{ i, j }] = { "1","2","3","4","5","6","7","8","9" };
			else number[{ i, j }] = { result[i][j] };
		}

	// 공백 칸 리스트 중 숫자 칸 리스트에 포함된 숫자가 있을 경우 제거
	Row_Col_Clear(blank, number);

	vector<vector<string>> before_result;
	while (before_result != result) {
		before_result = result;

		// 각 구역의 공백칸(nx3)을 모두 합쳐서 중복된 모든 요소를 제거하고 남은 수가 1개면 result에 값 넣고 없앰
		Square_Clear(result, blank, number);

		// 각 구역의 숫자 칸을 공백 칸의 리스트에서 지움
		Square_Clear_2(result, blank, number);

		// 공백 칸 리스트 중 숫자 칸 리스트에 포함된 숫자가 있을 경우 제거
		Row_Col_Clear(blank, number);

		// 각 행의 공백 칸 중 어쩔 수 없이 어떤 숫자가 들어가는 칸을 찾아 적용
		Row_Blank_Clear(result, blank, number);

		// 공백 칸 리스트의 value가 0개이면 없애고, 1개이면 result에 값을 넣고 없앰
		Blank_Clear(result, blank);
	}

	// 공백 칸에 들어갈 수 있는 숫자 모두 넣어보기
	result = Input_Value(result, blank);

	return result;
}

bool IsSquare(unsigned int num) {
	unsigned int temp;
	switch (num & 0x0f) {
	case 0:
	case 1:
	case 4:
	case 9:
		temp = (unsigned int)(sqrt((double)num) + 0.5);
		return temp * temp == num;
	default:
		return false;
	}
}

int main(void) {
	if (!IsSquare(LENGTH)) {
		cout << "Please check LENGTH ..." << endl;
		return 0;
	}
	else {
		cout << "==== Please enter TEST MODE ==== " << endl;
		cout << "1. Test Case Running" << endl;
		cout << "2. Row, Col, Square check (you will input board)" << endl;
		cout << "3. Input board and calculate" << endl;
		cout << "default : "<< TEST_MODE << endl;
		cout << ">> ";
		cin >> TEST_MODE;
	}

	vector<vector<string>> numbers;

	if (TEST_MODE == 1) {
		cout << "Test Case Running ..." << endl;

		bool result = false;
		for (int index = 0; index < TESTCASE_INPUT.size(); index++) {
			vector<vector<string>> input = calculate(TESTCASE_INPUT[index]);

			if (PRINT_BOARD) {
				cout << "Input" << endl;
				Print_Board(input);
				cout << endl << "Output" << endl;
				Print_Board(TESTCASE_OUTPUT[index]);
			}

			if (input != TESTCASE_OUTPUT[index])
				result = true;

			string message = result ? "Fail" : "Success";
			cout << endl << "Test Case " << index + 1 << " : " << message << endl;
		}
	}
	else if (TEST_MODE == 2) {
		cout << "Check board ..." << endl;

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
		cout << "==== Input numbers ====" << endl;
		cout << "ex. line 1 >> 1 2 3 4 5 6 7 8 9" << endl;

		for (int i = 0; i < LENGTH; i++) {
			cout << "line " << i + 1 << " >> " << endl;
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