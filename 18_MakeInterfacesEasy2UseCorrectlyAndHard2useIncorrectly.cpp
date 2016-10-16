#include<iostream>
using namespace std;

// 1. 创建新类型，阻止用户使用不是月份的数字，比如13
class Month{
public:
  static Month Jan(){ return Month(1); }
  static Month Feb(){ return Month(2); }
  static Month Mar(){ return Month(3); }
private:
  explicit Month(int m);
  int month_;
};
Month::Month(int m) : month_(m) {}

int main(){
  return 0;
}
