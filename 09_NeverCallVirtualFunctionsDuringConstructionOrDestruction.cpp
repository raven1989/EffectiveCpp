#include<iostream>
#include<time.h>
using namespace std;

class Transaction{
public:
	Transaction();
	virtual void logTransaction() const = 0;
	void init();
};
Transaction::Transaction(){
	// 试试这句
	// 调用的是base class的纯虚函数
	// init();
}
void Transaction::init(){
	logTransaction();
}

class BuyTransaction : public Transaction {
public:
	virtual void logTransaction() const;
};
void BuyTransaction::logTransaction() const {
	time_t now;
	time(&now);
	char* now_str = ctime(&now);
	now_str[strlen(now_str)-2] = 0;
	cout << now_str << " BuyTransaction." << endl;
}

int main(){
	BuyTransaction buy;
	// 解决的办法是将调用virtual函数的逻辑提出构造和析构函数，在外面手动调用：
	// 此时，各个对象都已经构造完成，virtual会按照预期进行
	buy.init();
	return 0;
}
