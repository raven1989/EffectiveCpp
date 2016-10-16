#include<iostream>
using namespace std;

class Rational{
public:
  Rational(int numerator=0, int denominator=1);
private:
  int numerator_;
  int denominator_;
  // 1. 在栈上建对象，如果在这里返回引用，那么将返回的是一个析构了的对象的引用，编译器会发出警告
  friend const Rational& operator*(const Rational& lhs, 
      const Rational& rhs);
  // 2. 在堆上建对象，谁来保证析构所有对象，比如连续调用: Rational d = a/b/c
  friend const Rational& operator/(const Rational& lhs, 
      const Rational& rhs);
};
Rational::Rational(int numerator, int denominator)
  : numerator_(numerator), denominator_(denominator) {
}
const Rational& operator*(const Rational& lhs, 
    const Rational& rhs){
  Rational res(lhs.numerator_*rhs.numerator_, lhs.denominator_*rhs.denominator_);
  return res;
}
const Rational& operator/(const Rational& lhs, 
    const Rational& rhs){
  return *(new Rational(lhs.numerator_*rhs.denominator_, lhs.denominator_*rhs.numerator_));
}

int main(){
  Rational a(1,2);
  Rational b(3,5);
  Rational c = a*b;

  Rational d = a/b/c;
  return 0;
}
