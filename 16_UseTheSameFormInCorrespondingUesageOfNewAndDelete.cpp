#include<iostream>
using namespace std;

/* 1. new 对 delete
 * 2. new[] 对 delete[] */

/* 单一对象和对象数组在内存中的布局是不一样的： */
// 对象数组有数组size这样的对象在内存中（一般编译器都会这样实现），以便以delete[]知道删除多少对象

// 一种容易引起误用的方式：
/* 使用这个类型new出来的需要特别指明其delete[] */
typedef string AddressLines[4];

int main(){
	string* pal = new AddressLines;
	// delete pal;
	delete[] pal;
	return 0;
}
