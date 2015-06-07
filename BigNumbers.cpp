#include <iostream>
#include <cstring>
#include<cmath>
#include "BigNumbers.h"

using namespace std;

BigNumbers::BigNumbers() : number(""), sign(true){
}

BigNumbers::BigNumbers(char* _number, bool _sign) : sign(_sign){
    number = new char[strlen(_number) + 1];
    for(int i = 0; i <= strlen(_number); i++){
        number[i] = _number[i];
    }
}

BigNumbers::BigNumbers(int x, bool _sign) : sign(_sign){
    number = new char[x + 1];
}

BigNumbers::BigNumbers(BigNumbers const& s) : sign(s.sign){
    number = new char[strlen(s.number) + 1];
	strcpy(number, s.number);
}

BigNumbers::~BigNumbers(){
delete[] number;
}

BigNumbers& BigNumbers::operator=(const BigNumbers& cop){
    sign = cop.sign;
    number = new char[strlen(cop.number) + 1];
    strcpy(number, cop.number);
	return *this;
}


char* BigNumbers::getNumber() const{
    return number;
}

bool BigNumbers::getSign() const{
    return sign;
}

void BigNumbers::setNumber(char* _number){
    if (number != _number){
        delete[] number;
    }
    number = new char[strlen(_number) + 1];
    strcpy(number, _number);
}

void BigNumbers::setSign(bool _sign){
    sign = _sign;
}


ostream& operator<<(ostream& os, const BigNumbers& z){
    if (z.sign == true)
		os << "+" << z.number;
	if (z.sign == false)
		os << "-" << z.number;
    return os;
}

istream& operator>>(istream& is, const BigNumbers& t){
    if (t.sign == true){

        is >> t.number;
    }
    else {
        cout << "+";
        is >> t.number;
    }
    return is;
}


BigNumbers operator+ (BigNumbers const& a, BigNumbers const& b){
    BigNumbers c;
    int x = strlen(a.number) - 1;
    int y = strlen(b.number) - 1;
    if (a.sign == true && b.sign == true){
        if (x < y){
			c = b;
			int rem = 0, vpn = 0;
			while (y >= 0){
				vpn = ((a[x] + b[y]) - 96);
				if (x >= 0){
					c.number[y] = '0' + vpn % 10 + rem / 10;
					if (vpn % 10 + rem / 10 == 10){
						c.number[y] = c.number[y] - 10;
					}
					rem = ((a[x] + b[y] + rem/10) - 96);
				}
				if (x < 0){
					vpn = '0' + b[y] + rem / 10 - 96;
					c.number[y] = (b.number[y] + rem / 10);
					if (vpn == 10){
						c.number[y] = c.number[y] - 10;
					}
					rem = '0' + b[y] + rem / 10 - 96;
				}
				x--;
				y--;
			}
			if (vpn >= 10){
				char* oop = c.number;
				c.number = new char[strlen(oop) + 1];
				for (int i = strlen(oop); i >= 0; i--){
					c.number[i + 1] = oop[i];
				}
				delete[] oop;
				c.number[0] = '1';
			}
        }
        if (x > y){
            c = a;
            int rem = 0, vpn = 0;
            while(x >= 0){
                vpn = ((a[x] + b[y]) - 96);
                if (y >= 0){
                    c.number[x] = '0' + vpn%10 + rem/10;
					if (vpn % 10 + rem / 10 == 10){
						c.number[x] = c.number[x] - 10;
					}
					rem = ((a[x] + b[y] + rem/10) - 96);
                }
                if (y < 0){
					vpn ='0' + a[x] + rem/10 - 96;
                    c.number[x] =(a.number[x] + rem/10);
					if (vpn == 10){
						c.number[x] = c.number[x] - 10;
					}
					rem ='0' + a[x] + rem/10 - 96;
                }
				x--;
				y--;
            }
			if (vpn >= 10){
				char* oop = c.number;
				c.number = new char[strlen(oop) + 1];
				for (int i = strlen(oop); i >= 0; i--){
					c.number[i + 1] = oop[i];
				}
				delete[] oop;
				c.number[0] = '1';
			}
        }
        if (x == y){
			c = a;
			int rem = 0, vpn = 0;
			while (x >= 0){
				vpn = ((a[x] + b[y]) - 96);
				c.number[x] = '0' + vpn % 10 + rem / 10;
				rem = ((a[x] + b[y]) - 96);
				x--;
				y--;
            }
			if (vpn >= 10){
				char* oop = c.number;
				c.number = new char[strlen(oop) + 1];
				for (int i = strlen(oop); i >= 0; i--){
					c.number[i + 1] = oop[i];
				}
				delete[] oop;
				c.number[0] ='0' + rem/10;
            }
        }
    }
    else if(a.sign == true && b.sign == false){
		BigNumbers u;
		u = b;
		u.sign = true;
        return a - u;
    }
    else if(a.sign == false && b.sign == true){
		BigNumbers u;
		u = a;
		u.sign = true;
        return b - u;
    }
    else if(a.sign == false && b.sign == false){
		BigNumbers u, v;
		u = a;
		v = b;
		u.sign = true;
		v.sign = true;
		c = u + v;
        c.sign = false;
    }
    return c;
}

BigNumbers operator+= (BigNumbers& a, BigNumbers const& b){
	BigNumbers c;
	c = a + b;
	a = c;
	return a;
}

BigNumbers operator- (BigNumbers const& a, BigNumbers const& b){
    BigNumbers c;
    int x = strlen(a.number) - 1;
    int y = strlen(b.number) - 1;
    if (a.sign == true && b.sign == true){
        if (x > y){
            c = a;
			int vpn = 0, rem = 0;
            while (x >= 0){
				vpn = '0' + (a[x] - b[y]) - 48;
				if (vpn < 0){
					vpn = '0' + a[x] + 10 - b[y] - 48;
				}
                if(y >= 0){
					if (vpn == 0 && rem == 1){
						vpn = 10;
					}
                    c.number[x] = '0' + vpn - rem;
					rem = '0' + (a[x] - b[y] - rem) - 48;
                }
                if(y < 0){
					vpn = (a.number[x]) - 48;
					if (vpn == 0 && rem == 1){
						vpn = 10;
					}
					c.number[x] = '0' + vpn - rem;
					rem = a.number[x] - rem - 48;
				}
				if (rem < 0){
					rem = 1;
				}
				else rem = 0;
				x--;
				y--;
			}
		}
        if (x < y){
			c = b;
			int vpn = 0, rem = 0;
			while (y >= 0){
				vpn = '0' + (b[y] - a[x]) - 48;
				if (vpn < 0){
					vpn = '0' + b[y] + 10 - a[x] - 48;
				}
				if (x >= 0){
					if (vpn == 10 && rem == 1){
						vpn = 10;
					}
					c.number[y] = '0' + vpn - rem;
					rem = '0' + (b[y] - a[x] - rem) - 48;
				}
				if (x < 0){
					vpn = (b.number[y]) - 48;
					if (vpn == 0 && rem == 1){
						vpn = 10;
					}
					c.number[y] = '0' + vpn - rem;
					rem = b.number[y] - rem - 48;
				}
				if (rem < 0){
					rem = 1;
				}
				else rem = 0;
				x--;
				y--;
			}
        }
        if (x == y){
			if (a < b){
				c = b;
				c.sign = false;
				int vpn = 0, rem = 0;
				while (y >= 0){
					vpn = '0' + (b[y] - a[x]) - 48;
					if (vpn < 0){
						vpn = '0' + b[y] + 10 - a[x] - 48;
					}
					c.number[y] = '0' + vpn - rem;
					rem = '0' + (b[y] - a[x]) - 48;
					if (rem < 0){
						rem = 1;
					}
					else rem = 0;
					x--;
					y--;
				}
			}
            if (a > b){
				c = a;
				int vpn = 0, rem = 0;
				while (x >= 0){
					vpn = '0' + (a[x] - b[y]) - 48;
					if (vpn < 0){
						vpn = '0' + a[x] + 10 - b[y] - 48;
					}
						c.number[x] = '0' + vpn - rem;
						rem = '0' + (a[x] - b[y]) - 48;
					if (rem < 0){
						rem = 1;
					}
					else rem = 0;
					x--;
					y--;
				}
            }
            if (a == b) {
                c = a;
                for (int i = 0; i <= x; i++){
					c.number[i] = '0';
                }
            }
        }
    }
    else if(a.sign == true && b.sign == false){
		BigNumbers u;
		u = b;
		u.sign = true;
        return a + u;
    }
    else if(a.sign == false && b.sign == true){
		BigNumbers u;
		u = a;
		u.sign = true;
		c = u + b;
		c.sign = false;
		return c;
    }
    else if(a.sign == false && b.sign == false){
		BigNumbers u, v;
		u = a;
		v = b;
		u.sign = true;
		v.sign = true;
        return v - u;
    }
	while (c.number[0] == '0' && strlen(c.number) > 1){
		char* oop = c.number;
		c.number = new char[strlen(oop)];
		for (int i = 0; i < strlen(oop); i++){
			c.number[i] = oop[i + 1];
		}
		delete[] oop;
	}
    return c;
}

BigNumbers operator-= (BigNumbers& a, BigNumbers const& b){
	BigNumbers c;
	c = a - b;
	a = c;
	return a;
}

BigNumbers operator* (BigNumbers const& a, BigNumbers const& b){
    BigNumbers c("0", true), w("0", true), v("1", true);
	if (a.sign == true && b.sign == true){
		while (w < a){
			w = w + v;
			c = c + b;
		}
	}
		if (a.sign == true && b.sign == false){
			BigNumbers u;
			u = b;
			u.sign = true;
			c = a * u;
			c.sign = false;
		}
		if (a.sign == false && b.sign == true){
			BigNumbers u;
			u = a;
			u.sign = true;
			c = u * b;
			c.sign = false;
		}
		if (a.sign == false && b.sign == false){
			BigNumbers p, q;
			p = a;
			q = b;
			p.sign = true;
			q.sign = true;
			c = q * p;
			c.sign = true;
		}
    return c;
}

BigNumbers operator*= (BigNumbers& a, BigNumbers const& b){
	BigNumbers c;
	c = a * b;
	a = c;
	return a;
}

BigNumbers operator/ (BigNumbers const& a, BigNumbers const& b){
	BigNumbers c, w("0", true), v("1", true);
	if (a.sign == true && b.sign == true){
		c = a;
		while (c >= b){
			c = c - b;
			w = w + v;
		}
	}
	if (a.sign == true && b.sign == false){
		BigNumbers p;
		p = b;
		p.sign = true;
		w = a / p;
		w.sign = false;
	}
	if (a.sign == false && b.sign == true){
		BigNumbers p;
		p = a;
		p.sign = true;
		w = p / b;
		w.sign = false;
	}
	if (a.sign == false && b.sign == false){
		BigNumbers p, q;
		q = a;
		p = b;
		p.sign = true;
		w = q / p;
		w.sign = true;
	}
	return w;
}

BigNumbers operator/= (BigNumbers& a, BigNumbers const& b){
	BigNumbers c;
	c = a / b;
	a = c;
	return a;
}

BigNumbers operator% (BigNumbers const& a, BigNumbers const& b){
	if (a < b && a.sign == true || a > b && a.sign == false){
		BigNumbers w("1", true);
		return a;
	}
	if (a == b){
		BigNumbers w("0", true);
		return w;
	}
	BigNumbers ac = a, bc = b, p, q, c, v("", true);
	ac.sign = true;
	bc.sign = true;
	q = ac / bc;
	p = q * bc;
	c = ac - p;
	return c;
}

BigNumbers operator%= (BigNumbers& a, BigNumbers const& b){
	BigNumbers c;
	c = a % b;
	a = c;
	return a;
}


bool operator<(const BigNumbers& a, const BigNumbers& b){
    int x = strlen(a.number);
    int y = strlen(b.number);
    if (a.sign == true && b.sign == true){
        if (x > y) return false;
        else if (x < y) return true;
        else if (x == y){
            for (int i = 0; i < x; i++){
                if (a.number[i] < b.number[i]) return true;
                else if (a.number[i] > b.number[i]) return false;
                else if (i == x-1) return false;
            }
        }
    }
    else if (a.sign == true && b.sign == false) return false;
    else if (a.sign == false && b.sign == true) return true;
    else if (a.sign == false && b.sign == false){
        if (x < y) return false;
        else if (x > y) return true;
        else if (x == y){
            for (int i = 0; i < x; i++){
                if (a.number[i] > b.number[i]) return true;
                if (a.number[i] < b.number[i]) return false;
                if (i == x-1) return false;
            }
        }
    }
}

bool operator==(const BigNumbers& a, const BigNumbers& b){
    int x = strlen(a.number);
    int y = strlen(b.number);
    if (a.sign == true && b.sign == true){
        if (x > y) return false;
        else if (x < y) return false;
        else if (x == y){
            for (int i = 0; i < x; i++){
                if (a.number[i] > b.number[i]) return false;
                if (a.number[i] < b.number[i]) return false;
                if (i == x-1) return true;
            }
        }
    }
    else if (a.sign == true && b.sign == false) return false;
    else if (a.sign == false && b.sign == true) return false;
    else if (a.sign == false && b.sign == false){
        if (x > y) return false;
        else if (x < y) return false;
        else if (x == y){
            for (int i = 0; i < x; i++){
                if (a.number[i] > b.number[i]) return false;
                if (a.number[i] < b.number[i]) return false;
                if (i == x-1) return true;
            }
        }
    }
}

bool operator>(const BigNumbers& a, const BigNumbers& b){
    if (a < b) return false;
    else if (a == b) return false;
    else return true;
}

bool operator<=(const BigNumbers& a, const BigNumbers& b){
    if (a < b) return true;
    else if (a == b) return true;
    else return false;
}

bool operator>=(const BigNumbers& a, const BigNumbers& b){
    if (a > b) return true;
    else if (a == b) return true;
    else return false;
}

bool operator!=(const BigNumbers& a, const BigNumbers& b){
    if (a == b) return false;
    else return true;
}

int BigNumbers::operator[] (const int a) const{
    return (int)number[a];
}




int main(){
    BigNumbers a("33", true);
    BigNumbers b("42", true);
    cout<<a<<endl;
    cout<<b<<endl;
	a.change();
	BigNumbers c = a + b;
	cout << c << endl;
	cout << a << endl;
	a.back();
	cout << a << endl;
	return 0;
}

void BigNumbers::change(){
	if (this->number[1] == 'x'){
		BigNumbers c("0", true);
		int w = 0;
		int co = 0, j = 0;
		co = strlen(this->number);
		j = co - 3;
		for (int i = 2; i < co; i++){
			if (this->number[i] == 'A'){
				this->number[i] = '0';
				w = w + ((this->number[i] - 48 + 10) * pow(16, j));
			}
			else if (this->number[i] == 'B'){
				this->number[i] = '1';
				w = w + ((this->number[i] - 48 + 10) * pow(16, j));
			}
			else if (this->number[i] == 'C'){
				this->number[i] = '2';
				w = w + ((this->number[i] - 48 + 10) * pow(16, j));
			}
			else if (this->number[i] == 'D'){
				this->number[i] = '3';
				w = w + ((this->number[i] - 48 + 10) * pow(16, j));
			}
			else if (this->number[i] == 'E'){
				this->number[i] = '4';
				w = w + ((this->number[i] - 48 + 10) * pow(16, j));
			}
			else if (this->number[i] == 'F'){
				this->number[i] = '5';
				w = w + ((this->number[i] - 48 + 10) * pow(16, j));
			}
			else{
				w = w + ((this->number[i] - 48) * pow(16, j));
			}
			j--;
		}
		int l = 0, ne = co;
		while (w != 0){
			l++;
			int f = w % 10;
			this->number[ne - 1] = f + 48;
			ne--;
			w /= 10;
		}
		char* oop = this->number;
		this->number = new char[l];
			for (int i = l - 1; i >= 0; i--){
				this->number[i] = oop[co - 1];
				co--;
			}
			this->number[l] = '\0';
			delete[] oop;
	}
}

void BigNumbers::back(){
	BigNumbers a("16", true), b = *this, w("0", true), h;
	for (int i = 0; i < strlen(this->number); i++){
		this->number[i] = '0';
	}
	int j = strlen(this->number) - 1;
	while (b > w){
		h = b % a;
		if (h.number[0] == '1' && h.number[1] == '0'){
			this->number[j] = 'A';
		}
		else if (h.number[0] == '1' && h.number[1] == '1'){
			this->number[j] = 'B';
		}
		else if (h.number[0] == '1' && h.number[1] == '2'){
			this->number[j] = 'C';
		}
		else if (h.number[0] == '1' && h.number[1] == '3'){
			this->number[j] = 'D';
		}
		else if (h.number[0] == '1' && h.number[1] == '4'){
			this->number[j] = 'E';
		}
		else if (h.number[0] == '1' && h.number[1] == '5'){
			this->number[j] = 'F';
		}
		else{
			this->number[j] = h.number[0];
		}
		b /= a;
		j--;
	}
	int co = strlen(this->number);
	char* oop = this->number;
	this->number = new char[strlen(oop) + 2];
	for (int i = strlen(oop); i >= 0; i--){
		this->number[i] = oop[co - 1];
		co--;
	}
	this->number[0] = '0';
	this->number[1] = 'x';
	this->number[strlen(oop) + 1] = '\0';
	delete[] oop;
}
