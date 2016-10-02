#include<iostream>
#include<exception>
#include<cstdlib>
using namespace std;

class DbCloseException : public exception {
};

class DbInstance {
public:
	DbInstance(const string& ip, const string& port);
	void close();
private:
	string ip_;
	string port_;
};
DbInstance::DbInstance(const string& ip, const string& port) : 
	ip_(ip), 
	port_(port) {
}
void DbInstance::close() {
	throw new DbCloseException;
}

/* 1. 析构函数绝对不要吐出异常：
 *    如果一个析构函数可能抛出异常，析构函数应该捕捉他们，然后吞下他们或者结束程序； */
class DbConn {
public:
	DbConn(const string& ip, const string& port);
	~DbConn();
/* 2. 如果客户需要对某个操作函数运行期间抛出的异常做出反应：
 *    那么class应该提供一个普通函数，而非在析构函数中，执行该操作 */
	void close();
private:
	DbInstance db_;
	bool closed_;
};
DbConn::DbConn(const string& ip, const string& port) : 
	db_(ip,port), 
	closed_(false) {
}
DbConn::~DbConn(){
	if(!closed_){
		try{
			db_.close();
		} catch (...){
			cout << "catch them all" << endl;
			abort();
		}
	}
}
void DbConn::close(){
	db_.close();
	closed_ = true;
}

int main(){
	DbConn conn("127.0.0.1", "6638");
	return 0;
}
