#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

// The objects from this structure contains the information for the obstacles in the room!
struct Obstacle{
	int X1 = 0;
	int Y1 = 0;
	int X2 = 0;
	int Y2 = 0;

	void Print(Obstacle o){
		cout << o.X1 << " " << o.Y1 << " " << o.X2 << " " << o.Y2 << endl;
	}

public:
	Obstacle();
	Obstacle(int _X1, int _Y1, int _X2, int _Y2) : X1(_X1), Y1(_Y1), X2(_X2), Y2(_Y2){}
};

struct Turns{
	int* x_array;
	int* y_array;
	int turns = 0;
	int size = 0;

	Turns();
	Turns(int* _x_array, int* _y_array, int _size) : size(_size){
		x_array = new int[_size+1];
		y_array = new int[_size+1];

		for (int i = 0; i < _size+1; i++){
			x_array[i] = _x_array[i];
			y_array[i] = _y_array[i];
		}

		turns = TurnsCounter(*this);
	}

	int TurnsCounter(Turns t){
		t.turns = 0;

		for (int i = 0; i + 2 <= t.size; i++){

			if (t.x_array[i] != t.x_array[i + 2] && t.y_array[i] != t.y_array[i + 2]){
				t.turns++;
			}

		}

		return t.turns;
	}

	void Print2(Turns t){

		for (int i = 0; i <= t.size; i++){
			cout << "(" << t.x_array[i] << "," << t.y_array[i] << ")" << " ";
		}

		cout << t.size << " - " << t.turns << endl;
	}
	
};

// This function reverse the room according to the rules of the condition
void ReverseRoom(ofstream& TJF2, vector<Obstacle> q, char **Room, char **reverse_room, int Rx, int Ry, int Tx, int Ty, int Jx, int Jy){

	for (int i = 0; i <= Ry; i++){
		for (int j = 0; j <= Rx; j++){
			reverse_room[i][j] = Room[Ry - i][j];
		}
	}

	for (int i = 0; i <= Ry; i++){
		for (int j = 0; j <= Rx; j++){
			TJF2 << reverse_room[i][j] << " ";
		}

		TJF2 << endl;
	}

}

// This function put the positions of Tom, Jerry and obstacles in two-dimensional array
void DrawMap(vector<Obstacle> q, char **Room,char **reverse_room, int Rx, int Ry, int Tx, int Ty, int Jx, int Jy){

	reverse_room[Ty][Tx] = 'T';
	reverse_room[Jy][Jx] = 'J';
	int Ox = 0;
	int Oy = 0;

	for (int i = 0; i < q.size(); i++){
		Ox = q[i].X2 - q[i].X1;
		Oy = q[i].Y2 - q[i].Y1;

		for (int col = 0; col <= Oy; col++){
			for (int row = 0; row <= Ox; row++){
				reverse_room[q[i].Y1 + col][q[i].X1 + row] = '*';
			}
		}

	}

	for (int i = 0; i <= Ry; i++){
		for (int j = 0; j <= Rx; j++){
			Room[i][j] = reverse_room[i][j];
		}
	}

}

// This function reads the file and put obstacles in vector
void ReadFile(vector<Obstacle>& q, ifstream& TJF,string& line, int& Rx, int& Ry, int& Tx, int& Ty, int& Jx, int& Jy){

	if (TJF.is_open()){
		Rx = line[0] - 48;
		Ry = line[1] - 48;
		getline(TJF, line);
		Tx = line[0] - 48;
		Ty = line[1] - 48;
		Jx = line[2] - 48;
		Jy = line[3] - 48;
		getline(TJF, line);

		while (line != "-1"){
			q.push_back(Obstacle(line[0] - 48, line[1] - 48, line[2] - 48, line[3] - 48));
			getline(TJF, line);
		}

	}
}

bool SearchingTheRoom(vector<Turns>& p, char **Room, int *x_array, int *y_array, int Rx, int Ry, int Tx, int Ty, int Jx, int Jy, bool **visit, int x, int y, int k, bool& c){

	if (x == Jx && y == Jy){
		c = true;
		x_array[k] = x;
		y_array[k] = y;
		p.push_back(Turns(x_array, y_array, k));
		k = 0;
		return true;
	}

	if (x >= 0 && x <= Rx && y >= 0 && y <= Ry){

		if (Room[y][x] != '*' && visit[y][x] == false){
			visit[y][x] = true;
			x_array[k] = x;
			y_array[k] = y;
			k++;
			SearchingTheRoom(p, Room, x_array, y_array, Rx, Ry, Tx, Ty, Jx, Jy, visit, x + 1, y, k, c);
			SearchingTheRoom(p, Room, x_array, y_array, Rx, Ry, Tx, Ty, Jx, Jy, visit, x, y + 1, k, c);
			SearchingTheRoom(p, Room, x_array, y_array, Rx, Ry, Tx, Ty, Jx, Jy, visit, x - 1, y, k, c);
			SearchingTheRoom(p, Room, x_array, y_array, Rx, Ry, Tx, Ty, Jx, Jy, visit, x, y - 1, k, c);
			visit[y][x] = false;
		}

	}

	return false;
}

int main(){
	int Tx = 0;
	int Ty = 0;
	int Jx = 0;
	int Jy = 0;
	int Rx = 0;
	int Ry = 0;
	int k = 0;
	int x = 0;
	int y = 0;
	int helper = 100;
	int element = 0;
	bool c = false;

	vector<Obstacle> q;
	vector<Turns> p;
	ifstream TJF("InTJ.txt");
	string line;
	ofstream TJF2("OutTJ.txt");

	while (getline(TJF, line)){
		while (!q.empty()){
			q.pop_back();
		}

		while (!p.empty()){
			p.pop_back();
		}

		helper = 100;
		c = false;
		ReadFile(q, TJF, line, Rx, Ry, Tx, Ty, Jx, Jy);

		x = Tx;
		y = Ty;

		char ** Room = new char*[Ry + 1];
		for (int i = 0; i < Ry + 1; i++){
			Room[i] = new char[Rx + 1];
		}

		char ** reverse_room = new char*[Ry + 1];
		for (int i = 0; i < Ry + 1; i++){
			reverse_room[i] = new char[Rx + 1];
		}

		for (int i = 0; i <= Ry; i++){
			for (int j = 0; j <= Rx; j++){
				reverse_room[i][j] = '0';
			}
		}

		bool ** visit = new bool*[Ry + 1];
		for (int i = 0; i < Ry + 1; i++){
			visit[i] = new bool[Rx + 1];
		}

		for (int i = 0; i <= Ry; i++){
			for (int j = 0; j <= Rx; j++){
				visit[i][j] = false;
			}
		}

		int *x_array = new int[(Rx * Ry) + 1];
		int *y_array = new int[(Rx * Ry) + 1];
		for (int i = 0; i < (Rx * Ry) + 1; i++){
			x_array[i] = 0;
			y_array[i] = 0;
		}

		DrawMap(q, Room, reverse_room, Rx, Ry, Tx, Ty, Jx, Jy);

		SearchingTheRoom(p, Room, x_array, y_array, Rx, Ry, Tx, Ty, Jx, Jy, visit, x, y, k, c);

		if (c == false){
			TJF2 << "Impossible" << endl;
			ReverseRoom(TJF2, q, Room, reverse_room, Rx, Ry, Tx, Ty, Jx, Jy);
		}

		else{
			
			for (int i = 0; i < p.size(); i++){
				if (helper > p[i].TurnsCounter(p[i])){
					helper = p[i].TurnsCounter(p[i]);
					element = i;
				}
			}

			for (int j = 1; j < p[element].size; j++){
				Room[p[element].y_array[j]][p[element].x_array[j]] = '+';
			}

			TJF2 << helper << endl;
			ReverseRoom(TJF2, q, Room, reverse_room, Rx, Ry, Tx, Ty, Jx, Jy);

		}
		
		if (Room != NULL || visit != NULL || reverse_room != NULL){
			for (int i = 0; i < Ry + 1; i++){
				delete[] Room[i];
				delete[] visit[i];
				delete[] reverse_room[i];
			}

			delete[] Room;
			delete[] visit;
			delete[] reverse_room;

		}

	}

	system("Pause");

	return 0;
}