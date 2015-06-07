#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdio.h>

using namespace std;

#define MAX_COUNT 100
char me;
int N = 0, M = 0, br = 0;
bool c=false;
enum Accesslevel {Admin, Ordinary};

struct User {
    char userName[20];
    char Password[20];
    Accesslevel accesslevel;
} users[MAX_COUNT];

struct Book {
    string author = "";
    string title = "";
    string genre = "";
    string description = "";
    string keywords = "";
    int year;
    int rating;
    int number;
} books[MAX_COUNT];
Book rem[10000];

int mainreadusers () {
    string line;
    ifstream myfile ("/Users/Светлин/Desktop/Библиотека/users.txt");
    if (myfile.is_open()){
        N = 0;
        while ( getline (myfile,line) ){
            std::istringstream iss(line);
            int accesslevel;
            iss >> users[N].userName >> users[N].Password >> accesslevel;
            if(accesslevel == 0) {
                users[N].accesslevel = Admin;
            } else {
                users[N].accesslevel = Ordinary;
            }
            N++;
        }
        myfile.close();
    }
    else cout << "Unable to open file"<<endl;
    return 0;
}

int mainwriteusers () {
    ofstream myfile ("/Users/Светлин/Desktop/Библиотека/users.txt");
    int accesslevel;
    if (myfile.is_open()){
        for (int i = 0; i < N; i++) {
                if (users[i].accesslevel == Admin){
                    accesslevel = 0;
                }
                else{
                    accesslevel = 1;
                }
            myfile << users[i].userName << " " << users[i].Password << " " << accesslevel << endl;
        }
        myfile.close();
    }
    else cout << "Unable to open file"<<endl;
    return 0;
}

int mainwritebooks() {
    ofstream myfile ("/Users/Светлин/Desktop/Библиотека/books.txt");
    if (myfile.is_open()){
        for (int i = 0; i < M; i++) {
            myfile << books[i].author << "|" << books[i].title << "|" << books[i].genre << "|" << books[i].description << "|" << books[i].keywords
                   << "|" << books[i].year << " " << books[i].rating << " " << books[i].number<<endl;
        }
        myfile.close();
        }
    else cout << "Unable to open file"<<endl;
    return 0;
}

void login() {
    char userlog[20], passlog[20];
    if (c == false) {
        cout<< "Username: ";
        cin>> userlog;
        cout<< "Password: ";
        cin>> passlog;
        for (int i = 0; i < N; i++){
            if (strcmp(userlog, users[i].userName) == 0 && strcmp(passlog, users[i].Password) == 0 ) {
                cout<< "Welcome " << userlog <<endl;
                c = true;
                me = users[i].accesslevel;
                break;
            }
        }
        if(c == false) {cout<<"Wrong username ot password!"<<endl;}
    }
    else {cout<<"You are already login!"<<endl;}
}

void usersadd(){
    if(c == true){
        if (me == Admin){
                int accesslevel;
            cout<<"Username: ";
            cin>> users[N].userName;
            cout<<"Password: ";
            cin>>users[N].Password;
            cout<<"Access level (0 - Admin or 1 - Ordinary): ";
            cin>> accesslevel;
            if(accesslevel == 0) {
                users[N].accesslevel = Admin;
            }
            else {
                users[N].accesslevel = Ordinary;
            }
            N++;
        }
        else cout<<"You can't use this function!!!"<<endl;
    }
    else cout<<"You must be login to use this function."<<endl;
}

void usersremove(){
    if(c == true){
        if (me == Admin){
            string usrem;
            cout<<"Username: ";
            getline(cin, usrem);
            for (int i = 0; i < N; i++){
                if(usrem.compare(users[i].userName) == 0){
                    users[i] = users[N-1];
                    N--;
                    break;
                }
            }
        }
        else cout<<"You can't use this function!!!"<<endl;
    }
    else cout<<"You must be login to use this function."<<endl;
}

void help(){
    cout<<"login - Login."<<endl;
    cout<<"logout - Logout."<<endl;
    cout<<"exit - Exit of the system."<<endl;
    cout<<"books all - Show information for all books."<<endl;
    cout<<"books info - Show information for books by entring number."<<endl;
    cout<<"books find - Show information for books by entering author, title or ganre."<<endl;
    cout<<"books sort - Show information for books by entering year or rating."<<endl;
}

void logout(){
    if(c == true){
		c=false;
		cout<<"Goodbye!"<<endl;
    }
    else cout<<"You must be login to use this function."<<endl;
}

void exit(){
    mainwriteusers();
    mainwritebooks();
}

int mainreadbooks() {
    string line;
    ifstream myfile ("/Users/Светлин/Desktop/Библиотека/books.txt");
    if (myfile.is_open()){
        M = 0;
        while ( getline (myfile,line) ){
            std::istringstream iss(line);
            getline(iss, books[M].author, '|');
            getline(iss, books[M].title, '|');
            getline(iss, books[M].genre, '|');
            getline(iss, books[M].description, '|');
            getline(iss, books[M].keywords, '|');
            iss >> books[M].year >> books[M].rating >> books[M].number;
            M++;
        }
        myfile.close();
    }
    else cout << "Unable to open file"<<endl;
    return 0;
}



void booksall(){
    if(c == true){
		for(int i = 0 ; i < M; i++){
			cout<< "Number: " << books[i].number <<endl;
			cout<< "Title: " << books[i].title <<endl;
			cout<< "Author: " << books[i].author <<endl;
			cout<< "Genre: " << books[i].genre <<endl;
		}
    }
    else cout<<"You must be login to use this function."<<endl;
}

void booksinfo(){
    if(c == true){
        int num;
        cout<<"Enter Number: ";
        cin>>num;
        for(int i = 0; i < M; i++){
            if(num == books[i].number){
                cout<< "Number: " << books[i].number <<endl;
                cout<< "Title: " << books[i].title <<endl;
                cout<< "Author: " << books[i].author <<endl;
                cout<< "Genre: " << books[i].genre <<endl;
                cout<< "Year: " << books[i].year <<endl;
                cout<< "Description: " << books[i].description <<endl;
                cout<< "Key words: " << books[i].keywords <<endl;
                cout<< "Rating: " << books[i].rating <<endl;
            }
        }
    }
    else cout<<"You must be login to use this function."<<endl;
}

void booksfind(){
    if(c == true){
		char input;
		string p;
		cout<<"Enter Title(t), Author(a) or Genre(g): ";
		cin>>input;
		cin.ignore();
		getline(cin, p);
		switch(input){
			case 't':
			for (int i = 0; i < M; i++){
				if(p.compare(books[i].title) == 0){
					cout<< "Number: " << books[i].number <<endl;
					cout<< "Title: " << books[i].title <<endl;
					cout<< "Author: " << books[i].author <<endl;
					cout<< "Genre: " << books[i].genre <<endl;
					break;
				}
			}
			break;
			case 'a':
			for (int i = 0; i < M; i++){
				if(p.compare(books[i].author) == 0){
					cout<< "Number: " << books[i].number <<endl;
					cout<< "Title: " << books[i].title <<endl;
					cout<< "Author: " << books[i].author <<endl;
					cout<< "Genre: " << books[i].genre <<endl;
					break;
				}
			}
			break;
			case 'g':
			for (int i = 0; i < M; i++){
				if(p.compare(books[i].genre) == 0){
					cout<< "Number: " << books[i].number <<endl;
					cout<< "Title: " << books[i].title <<endl;
					cout<< "Author: " << books[i].author <<endl;
					cout<< "Genre: " << books[i].genre <<endl;
					break;
				}
			}
			break;
		}
    }
    else cout<<"You must be login to use this function."<<endl;
}

void bubbleSort1(Book array[], unsigned size){
	unsigned i, j;
	for (i = 1; i < size; i++){
		for (j = size-1; j >= i; j--){
			if (array[j-1].year < array[j].year) {
				Book temp = array[j-1];
				array[j-1] = array[j];
				array[j] = temp;
			}
		}
	}
	for(int v = 0 ; v < M; v++){
			cout << "Author: " << array[v].author <<endl;
			cout << "Title: " << array[v].title <<endl;
			cout << "Genre: " << array[v].genre <<endl;
	}
}


void bubbleSort2(Book array[], unsigned size){
	unsigned i, j;
	for (i = 1; i < size; i++){
		for (j = size-1; j >= i; j--){
			if (array[j-1].rating < array[j].rating) {
				Book temp = array[j-1];
				array[j-1] = array[j];
				array[j] = temp;
			}
		}
	}
	for(int v = 0 ; v < M; v++){
			cout << "Author: " << array[v].author <<endl;
			cout << "Title: " << array[v].title <<endl;
			cout << "Genre: " << array[v].genre <<endl;
	
}


void bookssort(){
    if(c == true){
		int a;
		char th;
		cout<<"Enter Year(y) or Rating(r): ";
		cin>>th;
		br = 0;
		switch(th){
			case 'y':
			bubbleSort1(books, M);
			break;
			case 'r':
			bubbleSort2(books, M);
			break;
		}
    }
    else cout<<"You must be login to use this function."<<endl;
}

void booksadd(){
    if(c == true){
        if (me == Admin){
            cout<< "Title: ";
            getline(cin, books[M].title);
            cout<< "Author: ";
            getline(cin, books[M].author);
            cout<< "Genre: ";
            getline(cin, books[M].genre);
            cout<< "Year: ";
            cin>> books[M].year;
            cin.ignore();
            cout<< "Description: ";
            getline(cin, books[M].description);
            cout<< "Key words: ";
            getline(cin, books[M].keywords);
            cout<< "Rating: ";
            cin>> books[M].rating;
            cin.ignore();
            cout<<"Number: ";
            cin>> books[M].number;
            cin.ignore();
            M++;
        }
        else cout<<"You can't use this function!!!"<<endl;
    }
    else cout<<"You must be login to use this function."<<endl;
}

void booksremove(){
    if(c == true){
        if (me == Admin){
            int nmb;
            cout<<"Enter Number: ";
            cin>> nmb;
            for (int i = 0; i <= M; i++){
                if(nmb == books[i].number){
                    books[i] = books[M-1];
                    M--;
                }
            }
        }
        else cout<<"You can't use this function!!!"<<endl;
    }
    else cout<<"You must be login to use this function."<<endl;
}

int main() {
    mainreadusers();
    mainreadbooks();
    char sth[15];
    while(strcmp(sth, "exit") != 0){
        cin>> sth;
        cin.ignore();
        if(strcmp(sth, "login") == 0){
            login();
        }
        else if(strcmp(sth, "logout") == 0){
            logout();
        }
        else if(strcmp(sth, "help") == 0){
            help();
        }
        else if(strcmp(sth, "usersadd") == 0){
            usersadd();
        }
        else if(strcmp(sth, "usersremove") == 0){
            usersremove();
        }
        else if(strcmp(sth, "booksadd") == 0){
            booksadd();
        }
        else if(strcmp(sth, "booksremove") == 0){
            booksremove();
        }
        else if(strcmp(sth, "booksall") == 0){
            booksall();
        }
        else if(strcmp(sth, "booksfind") == 0){
            booksfind();
        }
        else if(strcmp(sth, "booksinfo") == 0){
            booksinfo();
        }
        else if(strcmp(sth, "bookssort") == 0){
            bookssort();
        }
    }
    exit();
return 0;
}
