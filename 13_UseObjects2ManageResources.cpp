#include<iostream>
#include<memory>
using namespace std;

class Investment{
public:
	Investment();
	~Investment();
};
Investment::Investment(){
	cout << "Constructing Investment ..." << endl;
}
Investment::~Investment(){
	cout << "Destructing Investment ..." << endl;
}

void f(){
	// 1. 将资源放在对象中管理
	auto_ptr<Investment> pInv(new Investment);
	// auto_ptr 的copy构造和copy assignment会移交资源；
	// 这个特性使得auto_ptr不支持STL容器
	auto_ptr<Investment> pInv1(pInv);
	auto_ptr<Investment> pInv2(NULL);
	pInv2 = pInv1;

	// 2. 引用计数的智能指针
	shared_ptr<Investment> sInv(new Investment);
	shared_ptr<Investment> sInv1 = sInv;
	shared_ptr<Investment> sInv2(NULL);
	sInv2 = sInv1;

	// 智能指针的析构函数调用的是delete，不是delete[]，所以不能用来管理数组资源
	// 试试这句，编译可以通过
	// shared_ptr<Investment> sArray(new Investment[2]);
}

int main(){
	f();
	return 0;
}
