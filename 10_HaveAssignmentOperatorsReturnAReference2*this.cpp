#include<iostream>
using namespace std;

// 1. 为了遵循连续赋值x=y=z=15，你的operator=应该返回一个指向*this的引用:
// 这个 规范 适用于所有赋值相关运算 += -= etc.
class Widget{
public:
	Widget& operator=(const Widget& other);
};
Widget& Widget::operator=(const Widget& other){
	return *this;
}

int main(){
	Widget x, y, z;
	x = y = z;
	return 0;
}
