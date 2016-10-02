#include<iostream>
using namespace std;

/* 1. 当自己实现base class的构造和copy assignment时，derived class的对应实现需要手动明确调用base；
 *    否则，会出现partial copy */

void log(const string& info){
	cout << info << endl;
}

class Customer{
public:
	Customer();
	Customer(const Customer& other);
	Customer& operator=(const Customer& other);
private:
	string name_;
};
Customer::Customer(){};
Customer::Customer(const Customer& other) : name_(other.name_){
	log("Customer copy constructor.");
}
Customer& Customer::operator=(const Customer& other){
	name_ = other.name_;
	log("Customer copy assignment operator.");
	return *this;
}

class PriorityCustomer : public Customer {
public:
	PriorityCustomer();
	PriorityCustomer(const PriorityCustomer& other);
	PriorityCustomer& operator=(const PriorityCustomer& other);
private:
	int priority_;
};
PriorityCustomer::PriorityCustomer(){};
PriorityCustomer::PriorityCustomer(const PriorityCustomer& other) : 
	// 试试没有这句，就去调用base的默认构造函数，而没有拷贝name_
	Customer(other), 
	priority_(other.priority_){
	log("PriorityCustomer copy constructor.");
}
PriorityCustomer& PriorityCustomer::operator=(const PriorityCustomer& other){
	priority_ = other.priority_;
	// 试试没有这句，就不会调用base的赋值，从而name_就没有更改
	Customer::operator=(other);
	log("PriorityCustomer copy assignment operator.");
	return *this;
} 

int main(){
	PriorityCustomer pc;
	PriorityCustomer other = pc;
	other = pc;
	return 0;
}
