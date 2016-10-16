#include<iostream>
using namespace std;

// 隐式转换：
// 1. 在结果类型中写一个non-explicit-one-argument的构造函数
// 2. 在源类型中声明一个operator To函数

class To{};

class From{
public:
  operator To();
};
From::operator To(){
  To res;
  return res;
}

void convert(To from){
}

int main(){
  From from;
  convert(from);
  return 0;
}
