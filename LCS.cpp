#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
using namespace std;
set<string> lcs(string, string, int, int, int**, int**);

int main() {
	//let user enter input file name
	cout << "enter file name\n";
	string filename;
	cin >> filename;
	//read file
	ifstream fin(filename);

	string s1;
	string s2;
	int counter = 1;
	//get the numbers of data sets as counter
	getline(fin, s1);
	counter = s1.at(0) - 48;
	while (!fin.eof() && counter > 0)
	{
		//get 2 lines every time
		getline(fin, s1);
		getline(fin, s2);
		string str1 = s1;
		string str2 = s2;
		//add 0 at the beginning of two strings, so it we can continue the following steps
		cout << s1 << "\n" << s2 << "\n";
		s1 = "0" + s1;
		s2 = "0" + s2;
		//create a 2D dynamic array
		int **length = new int*[(int)s1.length() + 1];
		int **record = new int*[s1.length() + 1];
		for (int i = 0; i <= (int)s1.length(); i++) {
			length[i] = new int[(int)s2.length() + 1];
			record[i] = new int[s2.length() + 1];
		}


		//record the way to find lcs and get the length of lcs
		//initialize length to 0 when either sub-sequence is 0
		for (int i = 0; i < s1.length(); i++) {
			length[i][0] = 0;
			record[i][0] = 0;
		}
		for (int i = 0; i < s2.length(); i++) {
			length[0][i] = 0;
			record[0][i] = 0;
		}
		//record 3 situations and find out the length of lcs
		for (int i = 1; i < s1.length(); i++) {
			for (int j = 1; j < s2.length(); j++) {
				if (s1.at(i) == s2.at(j)) {
					length[i][j] = length[i - 1][j - 1] + 1;
					record[i][j] = 1;
				}
				else if (length[i][j - 1] <= length[i - 1][j]) {
					length[i][j] = length[i - 1][j];
					record[i][j] = 2;
				}
				else {
					length[i][j] = length[i][j - 1];
					record[i][j] = 3;
				}
			}
		}
		//output lcs length
		cout << "lcs length:" << length[s1.length() - 1][s2.length() - 1] << "\n";

		//get common sub-sequences, and if there is any sub-sequence has the length as lcs, display it
		set<string> s = lcs(str1, str2, str1.length(), str2.length(), record, length);
		for (string str : s) {
			if (str.length() >= length[s1.length() - 1][s2.length() - 1]) {
				cout << str << endl;
			}
		}
		counter--;



		//delete 2D arrays
		for (int i = 0; i <= (int)s1.length(); i++) {
			delete[] length[i];
			delete[] record[i];
		}
		delete[] length;
		delete[] record;
	}



	system("pause");
	return 0;
}

//find sub-sequences
set<string> lcs(string s1, string s2, int m, int n, int**record, int**length) {
	set<string> s;
	//if either of the strings reaches the end, retrun a empty set
	if (m == 0 || n == 0)
	{
		s.insert("");
		return s;
	}
	//s1.at(i) == s2.at(j)
	if (record[m][n] == 1) {
		set<string> temp = lcs(s1, s2, m - 1, n - 1, record, length);
		for (string str : temp) {
			s.insert(str + s1[m - 1]);
		}
	}
	else {
		//length[i][j - 1] <= length[i - 1][j]
		if (record[m][n] == 2) {
			s = lcs(s1, s2, m - 1, n, record, length);
			set<string> temp = lcs(s1, s2, m, n - 1, record, length);
			s.insert(temp.begin(), temp.end());
		}
		//else
		if (record[m][n] == 3) {
			set<string> temp = lcs(s1, s2, m, n - 1, record, length);
			s.insert(temp.begin(), temp.end());
		}
	}

	return s;
}
