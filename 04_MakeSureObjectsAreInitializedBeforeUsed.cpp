#include<iostream>
#include<list>
using namespace std;

//1.不要混淆initialization和assignment
class PhoneNumber{};
//Adress Book Entry
class ABEntry{
public:
  ABEntry(const string& name, const string& adress,
      const list<PhoneNumber>& phones);
  ABEntry(const string& seq, const string& name, 
      const string& adress,
      const list<PhoneNumber>& phones);
  ABEntry();
private:
  string seq_; 
  string name_;
  string adress_;
  list<PhoneNumber> phones_;
  int numTimesConsulted_;
};
//1st这种实现是首先调用各个成员的default构造函数，这个阶段在进入下面的函数体之前，
//然后copy assignment
ABEntry::ABEntry(const string& name, const string& adress,
    const list<PhoneNumber>& phones){
  //这些都是被赋值
  seq_ = "1st";
  name_ = name;
  adress_ = adress;
  phones_ = phones;
  numTimesConsulted_ = 0;
}
//2nd是在初始化列表处直接调用copy构造，因此对于非内置类型，2nd的效率更高
ABEntry::ABEntry(const string& seq, const string& name, 
    const string& adress,
    const list<PhoneNumber>& phones) 
  : seq_("2nd"), 
  name_(name), 
  adress_(adress), 
  phones_(phones), 
  //对内置类型而言，1st和2nd两种其实是一样的
  numTimesConsulted_(0) {
}
//3rd，如果想要default构造一个成员变量时，也可以使用初始化列表，
//只要指定其他为空即可
ABEntry::ABEntry()
  : seq_(), 
  name_(),
  adress_(),
  phones_(),
  numTimesConsulted_(0) {
}
//4th，有些情况下，即使成员变量时内置类型，也必须只能是用初始化列表，
//而不能使用赋值，比如const reference
class ABEntryI{
public:
  ABEntryI(const string& name, const string& adress, 
      list<PhoneNumber>& phones);
private:
  //c++有固定的成员初始化顺序，与成员声明的顺序一致
  string seq_;
  const string name_;
  const string adress_;
  list<PhoneNumber>& phones_;
};
ABEntryI::ABEntryI(const string& name, const string& adress, 
    list<PhoneNumber>& phones) 
  : seq_("4th"), 
  name_(name), 
  adress_(adress), 
  phones_(phones){
}

//2. non-local static 对象 和 local static 对象 的初始化顺序
//local static 对象：在函数内的static对象称为local；
//non-local static 对象：函数外部的static对象，包括global, namespace, class和file内的static对象；
//static对象的生存期是从创建到程序结束，程序结束时会调用析构函数
//
//c++不保证non-local static对象的创建顺序
namespace os{
class FileSystem{
public:
  FileSystem();
  FileSystem(const size_t size);
  ~FileSystem();
  const size_t diskSize() const;
private:
  const size_t size_;
};
FileSystem::FileSystem(const size_t size) : size_(size){
  cout << "Constructing FileSystem by " << size_ << "..." << endl;
};
FileSystem::FileSystem() : size_(0){
  cout << "Constructing FileSystem by " << size_ << "..." << endl;
}
FileSystem::~FileSystem(){
  cout << "Deconstructing FileSystem ..." << endl;
}
const size_t FileSystem::diskSize() const{
  return size_;
}

extern FileSystem tfs;

}

class Directory{
public:
  Directory();
  Directory(const string& seq);
};
Directory::Directory(){
  //试试这一句，使用non-local static对象os::tfs，这个时候未必已经初始化了
  //size_t size = os::tfs.diskSize();
}

//所以尽量使用local static对象代替non-local static对象，
//local static对象在所在的函数被调用时才会创建
namespace os{
//为non-local static 对象创造一个仿真函数，用local static代替它
FileSystem& tfsAlways(){
  static FileSystem tfs_always(2048);
  return tfs_always;
}
}
Directory::Directory(const string& seq){
  size_t size = os::tfsAlways().diskSize();
}

int main(){
  //试试这句，如果不调用os::tfsAlways()，则不会生成local static对象tfs_always
  //这个特性被用在单例中
  Directory dir("make local static tfs_always");
  return 0;
}
