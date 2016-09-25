#include<iostream>

using namespace std;

class A{
public:
	//非static const 成员变量只能且必须在构造函数初始化列表初始化
	A(const int x, char* y) : b(x), p(y) {};
	// A(){ b = 2; }
	void set(int x){
		this->a = x;
	}
	void f() const{
		//const 成员函数不能修改任何成员变量，只能访问
		// a = 2;
		// 但可以修改static类型，它不是对象的成员
		ss = "B";
		// 也可以修改指针指向的对象
		*p = 'c';
		cout << a << " " << b << " " << ss << " " << *p << endl;
	}
	void ff(){
		a = 2;
		cout << a << " " << b <<endl;
	}
private:
	int a;
	const int b;
	char * p;
	//除了这几个类型，static都必须在外面初始化
	static const int i = 5;
	static const short si = 5;
	static const long l = 5;
	static const char c = 'c';
	// static const double d = 5.0;
	static const double d; 
	// static const char* chars = "A";
	static const char* chars;
	// static const string s = "A";
	static const string s;
	static string ss;
};

const double A::d = 5.0;
const char* A::chars = "A";
const string A::s = "A";
string A::ss = "AA";

int main(){
	char c = 'a';
	A a(1, &c);
	a.set(0);
	a.f();
	a.ff();
	return 0;
}
