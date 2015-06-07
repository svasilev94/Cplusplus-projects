
#include<iostream>
using namespace std;

class BigNumbers{
    public:
    char* number;
    bool sign;
    BigNumbers(int, bool);
    BigNumbers();
    BigNumbers(char*, bool);
    BigNumbers(BigNumbers const&);
    ~BigNumbers();
    BigNumbers& operator=(const BigNumbers&);

    char* getNumber() const;
    bool getSign() const;

    void setNumber(char*);
    void setSign(bool);
	void change();
	void back();

    friend ostream& operator<<(ostream&, const BigNumbers&);
    friend istream& operator>>(istream&, const BigNumbers&);

    friend BigNumbers operator+ (BigNumbers const&, BigNumbers const&);
	friend BigNumbers operator+= (BigNumbers&, BigNumbers const&);
    friend BigNumbers operator- (BigNumbers const&, BigNumbers const&);
	friend BigNumbers operator-= (BigNumbers&, BigNumbers const&);

    friend BigNumbers operator* (BigNumbers const&, BigNumbers const&);
	friend BigNumbers operator*= (BigNumbers&, BigNumbers const&);
    friend BigNumbers operator/ (BigNumbers const&, BigNumbers const&);
	friend BigNumbers operator/= (BigNumbers&, BigNumbers const&);

	friend BigNumbers operator% (BigNumbers const&, BigNumbers const&);
	friend BigNumbers operator%= (BigNumbers&, BigNumbers const&);

    friend bool operator< (const BigNumbers&, const BigNumbers&);
    friend bool operator> (const BigNumbers&, const BigNumbers&);
    friend bool operator== (const BigNumbers&, const BigNumbers&);
    friend bool operator!= (const BigNumbers&, const BigNumbers&);
    friend bool operator<= (const BigNumbers&, const BigNumbers&);
    friend bool operator>= (const BigNumbers&, const BigNumbers&);

    int operator[](const int) const;


};



