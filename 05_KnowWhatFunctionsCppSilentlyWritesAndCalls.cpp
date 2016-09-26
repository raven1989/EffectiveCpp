#include<iostream>
using namespace std;

//如果没有自己写出来，那么编译器会代为声明：
//1.无参构造函数
//2.析构函数
//3.拷贝构造函数：仅单纯地将每一个来源的non-static成员变量拷贝到目标对象(
//包括const和reference，但不能修改const类型或更改reference类型，所以编译器会报错)
//4.赋值操作符重载函数

template<class T>
class NamedObject{
private:
  string& nameValue_;
  const T objectValue_;
public:
  NamedObject(string& name, const T& value);
};
template<class T>
NamedObject<T>::NamedObject(string& name, const T& value) 
  : nameValue_(name), 
  objectValue_(value) {
}

int main(){
  string sp("p");
  NamedObject<int> p(sp, 2);
  string ss("s");
  NamedObject<int> s(ss, 1);
  //试试这句，默认的赋值试图去修改const和更改reference
  p = s;
  //所以当有const和reference成员函数时，需要自己写赋值函数
  return 0;
}
