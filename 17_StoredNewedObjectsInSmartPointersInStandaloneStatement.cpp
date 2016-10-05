#include<iostream>
using namespace std;

class Widget{
public:
	Widget(){
		cout << "Constructing Widget" << endl;
	}
	~Widget(){
		cout << "Destructing Widget" << endl;
	}
};

int getPriority(){
	return 0;
}

void process(shared_ptr<Widget> pw, int priority){
	cout << "Unlikely 2 demonstrate" << endl;
}

int main(){
	/* 这句隐含的问题：
	 * 需要执行：1.new Widget; 2.构造shared_ptr; 3.getPriority; 4.process
	 * 对c++而言，编译器生成的代码中这几句的顺序并不完全确定（而java和c#则是确定的）：
	 * 2一定先于1，4一定是最后，3的位置无所谓
	 * 顺序：2, 3, 1, 4
	 * 这时候如果3发生问题，1的指针会丢失 */
	process(shared_ptr<Widget>(new Widget), getPriority());
	// 所以，应该使用独立的语句来填装资源
	shared_ptr<Widget> pw(new Widget);
	process(pw, getPriority());
	return 0;
}
