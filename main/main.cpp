#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <fstream>
using namespace std;
#include "testcase.h"

int LENGTH			= 9;
int PRINT_BOARD		= 0;
int TEST_MODE		= 1;

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
			if (item != "0")
				if (list.find(item) == list.end()) list[item] = 1;
				else return false;
	}
	return true;
}

bool Col_Check(vector<vector<string>> arr) {
	for (int i = 0; i < LENGTH; i++) {
		map<string, int> list;
		for (int j = 0; j < LENGTH; j++)
			if (arr[j][i] != "0")
				if (list.find(arr[j][i]) == list.end()) list[arr[j][i]] = 1;
				else return false;
	}
	return true;
}

bool Square_Check(vector<vector<string>> arr) {
	vector< map<string, int>> list(3);
	for (int i = 0; i < LENGTH; i++) {
		if (i % (LENGTH / 3) == 0) list = { {}, {}, {} };

		for (int j = 0; j < LENGTH; j++)
			if (arr[i][j] != "0")
				if		(j / (LENGTH / 3) == 0)
					if (list[0].find(arr[i][j]) == list[0].end()) list[0][arr[i][j]] = 1;
					else return false;
				else if (j / (LENGTH / 3) == 1)
					if (list[1].find(arr[i][j]) == list[1].end()) list[1][arr[i][j]] = 1;
					else return false;
				else
					if (list[2].find(arr[i][j]) == list[2].end()) list[2][arr[i][j]] = 1;
					else return false;
	}
	return true;
}

bool Zero_Check(vector<vector<string>> arr) {
	for (const auto &row : arr)
		for (const auto& col : row)
			if (col == "0") return false;
	return true;
}

bool Row_Col_Square_Check(vector<vector<string>> arr) {
	vector<map<string, int>> col(LENGTH);
	vector<map<string, int>> square(LENGTH / 3);
	for (int i = 0; i < LENGTH; i++) {
		map<string, int> row;
		if (i % 3 == 0) square = { {}, {}, {} };
		for (int j = 0; j < LENGTH; j++)
			if (arr[i][j] != "0") {
				if (row.find(arr[i][j]) == row.end()) row[arr[i][j]] = 1;
				else return false;
				if (col[j].find(arr[i][j]) == col[j].end()) col[j][arr[i][j]] = 1;
				else return false;
				if (square[j / 3].find(arr[i][j]) == square[j / 3].end()) square[j / 3][arr[i][j]] = 1;
				else return false;
			}
	}
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
			for (int a = i / 3 * 3; a < i / 3 * 3 + 3; a++)
				for (int b = j / 3 * 3; b < j / 3 * 3 + 3; b++)
					if (result[a][b] == "0")
						for (const auto& item : blank[{a, b}])
							if (tmp.find(item) != tmp.end()) tmp[item] += 1;
							else {
								tmp[item] = 1;
								pos[item] = { a, b };
							}
			for (const auto& item : tmp)
				if (item.second == 1) {
					bool flag = true;
					for (int a = pos[item.first][0] / 3 * 3; a < pos[item.first][0] / 3 * 3 + 3; a++) {
						for (int b = pos[item.first][1] / 3 * 3; b < pos[item.first][1] / 3 * 3 + 3; b++)
							if (result[a][b] == item.first) {
								flag = false;
								break;
							}
						if (!flag) break;
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
			for (int a = i / 3 * 3; a < i / 3 * 3 + 3; a++)
				for (int b = j / 3 * 3; b < j / 3 * 3 + 3; b++)
					if (result[a][b] != "0") tmp.push_back(result[a][b]);
			for (int a = i / 3 * 3; a < i / 3 * 3 + 3; a++)
				for (int b = j / 3 * 3; b < j / 3 * 3 + 3; b++)
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
	map<vector<int>, vector<string>> tmp;
	for (const auto& item : blank)
		if		(item.second.size() >  1) tmp[item.first] = item.second;
		else if (item.second.size() == 1) result[item.first[0]][item.first[1]] = item.second[0];
	blank = tmp;
}

void Row_Blank_Clear(vector<vector<string>>& result, map<vector<int>, vector<string>>& blank, map<vector<int>, string>& number) {
	vector<vector<string>> square;
	for (int i = 0; i < LENGTH; i += 3)
		for (int j = 0; j < LENGTH; j += 3) {
			vector<string> tmp;
			for (int a = i / 3 * 3; a < i / 3 * 3 + 3; a++)
				for (int b = j / 3 * 3; b < j / 3 * 3 + 3; b++)
					if (result[a][b] != "0") tmp.push_back(result[a][b]);
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
	vector<vector<string>>			 result		= arr;
	map<vector<int>, vector<string>> b			= blank;
	vector<int>						 firstIt	= b.begin()->first;
	vector<string>					 secondIt	= b.begin()->second;
	b.erase(b.begin());

	for (const auto& item : secondIt) {
		result[firstIt[0]][firstIt[1]] = item;

		if (!Row_Col_Square_Check(result)) continue;

		if (b.size() != 0) {
			vector<vector<string>> tmp = Input_Value(result, b);
			if (!Zero_Check(tmp)) continue;
			else return tmp;
		}
		else return result;
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
	vector<vector<string>>			 result = arr;
	map<vector<int>, vector<string>> blank;
	map<vector<int>, string>		 number;

	// 공백 칸과 숫자 칸 분류하여 map 형태로 저장
	for (int i = 0; i < LENGTH; i++)
		for (int j = 0; j < LENGTH; j++)
			if (result[i][j] == "0") blank[{ i, j }] = { "1","2","3","4","5","6","7","8","9" };
			else number[{ i, j }] = { result[i][j] };

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

void Test_Mode_1() {
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

		if (input != TESTCASE_OUTPUT[index]) result = true;

		string message = result ? "Fail" : "Success";
		cout << endl << "Test Case " << index + 1 << " : " << message << endl;
	}
}

void Test_Mode_2(vector<vector<string>> numbers) {
	cout << "Check board ..." << endl;

	for (int i = 0; i < LENGTH; i++) {
		string num = "";
		cout << "Input line " << i + 1 << " >> ";
		getline(cin, num);
		vector<string> spt = split(num, ' ');
		if (spt.size() != LENGTH) {
			cout << "Please check your input!" << endl;
			i--;
		}
		else numbers.push_back(spt);
	}

	string message = Row_Check(numbers) ? "No duplicates" : "duplicate existence";
	cout << "Rows : " << message << endl;
	message = Col_Check(numbers) ? "No duplicates" : "duplicate existence";
	cout << "Cols : " << message << endl;
	message = Square_Check(numbers) ? "No duplicates" : "duplicate existence";
	cout << "Squares : " << message << endl;
}

void Test_Mode_3(vector<vector<string>> numbers) {
	cout << "==== Input numbers ====" << endl;
	cout << "ex. line 1 >> 1 2 3 4 5 6 7 8 9" << endl;

	for (int i = 0; i < LENGTH; i++) {
		cout << "line " << i + 1 << " >> ";
		string num = "";
		getline(cin, num);
		numbers.push_back(split(num, ' '));
	}

	cout << endl << "Calculating ...";
	numbers = calculate(numbers);
	cout << "\r======= result =======" << endl;
	Print_Board(numbers);
}

int Read_Config() {
	ifstream Config("sudoku.conf", ios::in | ios::binary);
	if (Config.is_open()) {
		for (int i = 0; i < 3; i++) {
			string s;
			Config >> s;
			vector<string> tmp = split(s, '=');

			bool isStringNumber = true;
			for (int i = 0; i < tmp[1].length(); i++)
				if (isdigit(tmp[1][i]) == 0) {
					isStringNumber = false;
					break;
				}

			if (isStringNumber) {
				int c = stoi(tmp[1]);
				if (i == 0 && !IsSquare(c)) {
					cout << "Please check Config ..." << endl;
					return 0;
				}
				if		(i == 0) LENGTH		 = c;
				else if (i == 1) PRINT_BOARD = c;
				else			 TEST_MODE	 = c;
			}
			else {
				cout << "Please check Config ..." << endl;
				return 0;
			}
		}
		Config.close();
	}
	else {
		ofstream Config("sudoku.conf", ios::out);
		Config << "LENGTH=" << LENGTH << endl;
		Config << "PRINT_BOARD=" << PRINT_BOARD << endl;
		Config << "TEST_MODE=" << TEST_MODE << endl << endl;
		Config << "# LENGTH : Board Length(ex. 9, 16, 25 ...)" << endl;
		Config << "# PRINT_BOARD : 0 - OFF, 1 - Print ON" << endl;
		Config << "# TEST_MODE : 0 - OFF, 1 - Test case, 2 - Function Test" << endl;
		Config.close();
	}
	return 1;
}

void Print_UI() {
	cout << "==== Please enter TEST MODE ==== " << endl;
	cout << "1. Test Case Running" << endl;
	cout << "2. Row, Col, Square check (You have to enter the board.)" << endl;
	cout << "3. Input board and calculate" << endl;
	cout << "4. Exit" << endl;
	cout << "default : " << TEST_MODE << endl;
	cout << ">> ";
	cin >> TEST_MODE;
	cin.get();
}

int main(void) {
	if (!Read_Config()) return 0;

	Print_UI();

	vector<vector<string>> numbers;
	switch (TEST_MODE) {
	case 1:
		Test_Mode_1(); break;
	case 2:
		Test_Mode_2(numbers); break;
	case 3:
		Test_Mode_3(numbers); break;
	case 4:
		return 0;
	default:
		Test_Mode_3(numbers); break;
	}
}