#include<iostream>
using namespace std;

/* 1. 当集成类对象由一个base指针被delete时，而该base class 带有一个non-virtual析构函数，其结果未定义：
 *    实际发生的结果是对象的derived成分没有被销毁 */
class TimeKeeper {
public:
  TimeKeeper();
  // 试试这一句，局部销毁
  // ~TimeKeeper();
  virtual ~TimeKeeper();
};
TimeKeeper::TimeKeeper(){
  cout << "Constructing TimeKeeper ..." << endl;
}
TimeKeeper::~TimeKeeper(){
  cout << "Destructing TimeKeeper ..." << endl;
}

class AtomicClock : public TimeKeeper {
public:
  AtomicClock();
  ~AtomicClock();
};
AtomicClock::AtomicClock(){
  cout << "Constructing AtomicClock ..." << endl;
}
AtomicClock::~AtomicClock(){
  cout << "Destructing AtomicClock ..." << endl;
}

/* 2. 当对象有一个virtual函数时，其对象的大小会增加：
 *    因为携带这部分信息的载体是一个叫做vptr(virtual table pointer)的指针，指向一个由函数指针构成的数组virtual table */
void checkSize(){
  cout << "Size of TimeKeeper : " << sizeof(TimeKeeper) << endl;
}

/* 3. 有时候需要一个抽象class，但没有一个可以作为纯虚函数的成员函数，这时候可以将析构函数声明为纯虚；但仍然要给出实现：
 *    因为子类的构造函数仍然需要调用它 */
class AWOV {
public:
  AWOV();
  virtual ~AWOV() = 0;
};
AWOV::AWOV(){
  cout << "Constructing AWOV ..." << endl;
}
AWOV::~AWOV(){
  cout << "Destructing AWOV ..." << endl;
}

int main(){
  TimeKeeper * clock = new AtomicClock;
  delete clock;

  checkSize();

  // 试试这句
  AWOV a;

  return 0;
}
