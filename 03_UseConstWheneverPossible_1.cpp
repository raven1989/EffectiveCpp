#include<iostream>
using namespace std;

class A{
public:
  A(int x) : a(x), c(x+1){};
  int& operator[](size_t p){
    return a;
  }
  //提供给const A对象调用使用，因为non-const函数对const对象不可见
  const int& operator[](size_t p) const {
    return c;
  }
  int geta(){
    return a;
  }
  int getc() const {
    return c;
  }
private:
  int a;
  const int c;  
};

class B{
public:
  B(int x) : a(x), c(x+1){};
  //为了去除代码重复，让non-const函数调用const函数
  int& operator[](size_t p){
    const_cast<int&>(                 //将结果去除const
        static_cast<const B&>(*this) //将this变成const B 类型
            [p]);                        //调用const operator[]
  }
  const int& operator[](size_t p) const {
    return c;
  }
  int geta(){
    return a;
  }
private:
  int a;
  const int c;  
};


int main(){
  A a0(0);
  cout << a0[0] << endl;
  //非const对象a0能看见const方法getc()
  cout << a0.getc() << endl;

  const A a1(0);
  cout << a1[0] << endl;
  //const对象a1看不见非const方法geta()
  //cout << a1.geta() << endl;
  
  B b0(2);
  cout << b0[2] << endl;

  const B b1(2);
  cout << b1[2] << endl;

  return 0;
}
