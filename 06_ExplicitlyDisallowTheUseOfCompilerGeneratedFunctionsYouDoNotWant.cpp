#include<iostream>
using namespace std;

//有时候我们不希望某个类被拷贝：
//这时候只要将拷贝构造和赋值函数声明为private的，并且不实现它们
//1.声明为private，可以防止外部调用；
//2.不实现可以防止内部成员函数或者friend调用，这时候ld会报错
class HomeForSale{
private:
  HomeForSale(const HomeForSale&);
  HomeForSale& operator=(const HomeForSale&);
public:
  HomeForSale(){};
  void callCopy();
};
void HomeForSale::callCopy(){
  //试试这句，ld会报错
  //HomeForSale replica(*this);
}

//那么能不能将成员函数和friend的调用报错，提前到编译阶段呢？
//当然可以，使用base class，将拷贝构造和赋值声明为私有且不实现；
//这些私有的base class中的函数在derived class中就不可见了
//利用derived class会尝试调用base class的对应的这几类函数的特点；
//事实上，Boost就有提供这样的类，叫做 noncopyable
class Uncopyable{
private:
  Uncopyable(const Uncopyable&);
  Uncopyable& operator=(const Uncopyable&);
};

class HomeForSaleI : public Uncopyable {
public:
  void callCopy(){
    //试试这句，编译报错
    //HomeForSaleI replica(*this);
  }
};

int main(){
  HomeForSale uniq0;
  HomeForSale uniq1;
  //试试这两句，编译不通过
  //HomeForSale uniq2(uniq0);
  //uniq0 = uniq1;

  return 0;
}
