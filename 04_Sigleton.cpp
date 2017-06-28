#include<iostream>
using namespace std;

/* 
 * 比较一下，就会发现利用local-static做的单例的优势在于析构的时候是自动的，
 * 所以如果有一些善后工作那么放到析构函数中就不用担心了
 *                 local-static                 triditional
 * 内存位置：栈上，所以析构函数会自动调用           堆上
 * 生存期：  首次调用函数-进程结束              new - delete
 *  */

class Sigleton{
public:
  static Sigleton* instance_;
  static Sigleton& getInstance(){
    if(instance_==NULL){
      instance_ = &(Sigleton::instanceImpl());
    }
    return *instance_;
  }
  string monologue(){
    return "Sigleton";
  }
private:
  Sigleton(){};
  // 这个不可以，因为声明后c++编译器不会自动再去生成一个，所以就没有实现的构造函数了
  // Sigleton();
  Sigleton(const Sigleton&);
  Sigleton& operator=(const Sigleton&);

  inline static Sigleton& instanceImpl(){
    static Sigleton ins;
    return ins;
  }
};
//static 除了integer, char, bool 都要在外面初始化
Sigleton* Sigleton::instance_ = NULL;

class TriditionalSigleton{
public:
  static TriditionalSigleton* instance_;
  static TriditionalSigleton&  getInstance(){
    if(instance_==NULL){
      instance_ = new TriditionalSigleton;
    }
    return *instance_;
  }
  string monologue(){
    return "Tridtional Sigleton";
  }
private:
  TriditionalSigleton(){};
  TriditionalSigleton(const TriditionalSigleton&);
  TriditionalSigleton& operator=(const TriditionalSigleton&);
};
TriditionalSigleton* TriditionalSigleton::instance_ = NULL;


int main(int argc, char* argv[]){
  cout << Sigleton::getInstance().monologue() << endl;
  // static可以是private的，所以调不了
  // Sigleton& ins = Sigleton::instanceImpl();
  cout << TriditionalSigleton::getInstance().monologue() << endl;
  return 0;
}
