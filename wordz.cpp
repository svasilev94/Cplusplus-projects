#include<iostream>
#include<string>
#include<fstream>
#include<queue>
using namespace std;

//reads words from the file and put them in queue
void readWord(queue<string>& q, int n, ifstream& myf){

	string line;

	if (myf.is_open()){

		for (int i = 0; i < n; i++){
			(getline(myf, line));
		}

		while (getline(myf, line)){
			q.push(line);
		}

	}

}

//reads table of letters from the file and puts them in two-dimensional array
void readLettering(char **letter_array, int n){

	ifstream myf("wordz.txt");

	if (myf.is_open()){

		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				myf >> letter_array[i][j];
			}
		}

	}

	else{
		cout << "Unable to open the file!";
	}

}

bool SearchingMatrix(char **letter_array, queue<string>& q, int n, int col, int row, int k, int *row_array, int *col_array, bool **visit){

	while (!q.empty()){

		//searching the first letter of the word in the table
		if (k == 0){

			bool c = false;

			for (int i = 0; i < n; i++){
				for (int j = 0; j < n; j++){
					if (letter_array[i][j] == q.front()[0] && visit[i][j] == false){
						row = i;
						col = j;
						row_array[k] = row;
						col_array[k] = col;
						c = true;
						break;
					}
				}
				if (c == true) break;
			}

			if (c == false){
				for (int i = 0; i < n; i++){
					for (int j = 0; j < n; j++){
						visit[i][j] = false;
					}
				}

				q.pop();
				SearchingMatrix(letter_array, q, n, col, row, k, row_array, col_array, visit);

				if (q.empty()){
					return true;
				}
			}

		}

		//condition for the end of the recursion
		if (row >= 0 && row < n && col >= 0 && col < n && letter_array[row][col] == q.front()[q.front().length() - 1] && k == q.front().length() - 1 && visit[row][col] == false){
			row_array[k] = row;
			col_array[k] = col;
			k = 0;

			for (int i = 0; i < n; i++){
				for (int j = 0; j < n; j++){
					visit[i][j] = false;
				}
			}

			cout << q.front();

			for (int i = 0; i < q.front().length(); i++){
				cout << " (" << col_array[i] << "," << row_array[i] << ")";
			}

			cout << endl;
			q.pop();
			SearchingMatrix(letter_array, q, n, col, row , k, row_array, col_array, visit);

			if (q.empty()){
				return true;
			}
		}

		//recursively scanning the table
		if (col >= 0 && col < n && row >= 0 && row < n && letter_array[row][col] == q.front()[k] && visit[row][col] == false){
			visit[row][col] = true;
			row_array[k] = row;
			col_array[k] = col;
			SearchingMatrix(letter_array, q, n, col, row + 1, k + 1, row_array, col_array, visit);
			SearchingMatrix(letter_array, q, n, col + 1, row + 1, k + 1, row_array, col_array, visit);
			SearchingMatrix(letter_array, q, n, col + 1, row, k + 1, row_array, col_array, visit);
			SearchingMatrix(letter_array, q, n, col + 1, row - 1, k + 1, row_array, col_array, visit);
			SearchingMatrix(letter_array, q, n, col, row - 1, k + 1, row_array, col_array, visit);
			SearchingMatrix(letter_array, q, n, col - 1, row - 1, k + 1, row_array, col_array, visit);
			SearchingMatrix(letter_array, q, n, col - 1, row, k + 1, row_array, col_array, visit);
			SearchingMatrix(letter_array, q, n, col - 1, row + 1, k + 1, row_array, col_array, visit);

			if (!q.empty() && k == 0){
				SearchingMatrix(letter_array, q, n, col, row, 0, row_array, col_array, visit);
			}

			visit[row][col] = false;
		}

		return false;
	}

}

int main(){

	int row = 0;
	int col = 0;
	queue<string> q;
	ifstream myf("wordz.txt");
	int n = 0;
	cout << " vuvedete n:";
	cin >> n;

	char ** letter_array = new char*[n];
	for (int i = 0; i < n; i++){
		letter_array[i] = new char[n];
	}

	bool ** visit = new bool*[n];
	for (int i = 0; i < n; i++){
		visit[i] = new bool[n];
	}

	int row_array[64];
	int col_array[64];

	for (int i = 0; i < 64; i++){
		col_array[i] = 0;
		row_array[i] = 0;
	}

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			visit[i][j] = false;
		}
	}

	readLettering(letter_array, n);
	readWord(q, n, myf);
	SearchingMatrix(letter_array, q, n, 0, 0, 0, row_array, col_array, visit);
	myf.close();

	system("Pause");
	return 0;
}