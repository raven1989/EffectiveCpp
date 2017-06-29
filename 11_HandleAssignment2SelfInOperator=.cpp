#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

// 1. 自我赋值会引发一些错误
class BitMap{
public:
  BitMap(const string& name);
  const string getName() const;
	void heartBeat();
private:
  string name_;
};
BitMap::BitMap(const string& name):name_(name){};
const string BitMap::getName() const{
  return name_;
}
void BitMap::heartBeat(){
	cout << "I'm ok." << endl;
}

class Widget{
public:
	Widget(BitMap& b);
	// 如果是自我赋值，这里就有问题
	Widget& operator=(const Widget& other){
		delete pb_;
		pb_ = new BitMap(*other.pb_);
		return *this;
	}
public:
	BitMap* pb_;
};
Widget::Widget(BitMap& b) : pb_(&b){
}

// 2. 使用 证同测试 identity test
class WidgetI{
public:
	WidgetI(BitMap& b);
	// identity test
	WidgetI& operator=(const WidgetI& other){
		if(this == &other) return *this;
		delete pb_;
		pb_ = new BitMap(*other.pb_);
		return *this;
	}
public:
	BitMap* pb_;
};
WidgetI::WidgetI(BitMap& b) : pb_(&b){
}

// 3. 使用良好的顺序
class WidgetII{
public:
	WidgetII(BitMap& b);
	WidgetII& operator=(const WidgetII& other){
		BitMap * origin = pb_;
		pb_ = new BitMap(*other.pb_);
		delete origin;
		return *this;
	}
public:
	BitMap* pb_;
};
WidgetII::WidgetII(BitMap& b) : pb_(&b){
}

// 4. 一个比较好的代替方案是copy and swap
class WidgetIII{
public:
	WidgetIII(BitMap& b);
	WidgetIII& operator=(const WidgetIII& other){
    if(!(this==&other)){
      WidgetIII replica(other);
      swap(replica);
      // std 提供的swap出现了段错误，再琢磨下
      // std::swap又调了operator=，循环调用了
      // std::swap(*this, replica);
    }
		return *this;
	}
  const string getBitMapName() const{
    return pb_->getName();
  }
private:
	void swap(WidgetIII& other){
		// 交换*this和other的数据
    // 试试用memcpy来做
    WidgetIII tmp(*this);
    memcpy(this, reinterpret_cast<const void*>(&other), sizeof(*this));
    memcpy(&other, reinterpret_cast<const void*>(&tmp), sizeof(*this));
    // stl的swap：如果Alocator相同，就用赋值操作交换控制信息，其实和memcpy效果一样
    // memcpy的效率显然更高
	}
public:
	BitMap* pb_;
};
WidgetIII::WidgetIII(BitMap& b) : pb_(&b){
}

// 5. 上面在operator=中调用std::swap出错是因为std::swap调用了operator=，循环调用了
class WidgetIV{
public:
  WidgetIV(BitMap& b);
  WidgetIV& operator=(const WidgetIV& other){
    cout << "operator= called by " << this->getBitMapName() << endl;
    return *this;
  }
  void swap(WidgetIV& other){
    ::std::swap(*this, other);
  }
  const string getBitMapName() const{
    return pb_->getName();
  }
private:
  BitMap* pb_;
};
WidgetIV::WidgetIV(BitMap& b) : pb_(&b){
}

int main(){
  BitMap bml("left");
  BitMap bmr("right");
  WidgetIII wl(bml);
  WidgetIII wr(bmr);
  cout << wl.getBitMapName() << " : " << wr.getBitMapName() << endl;
  // std::swap
  swap(wl, wr);
  cout << wl.getBitMapName() << " : " << wr.getBitMapName() << endl;
  wl = wr;
  cout << wl.getBitMapName() << " : " << wr.getBitMapName() << endl;

  BitMap bmivl("IV_left");
  BitMap bmivr("IV_right");
  WidgetIV ivl(bmivl);
  WidgetIV ivr(bmivr);
  cout << ivl.getBitMapName() << " : " << ivr.getBitMapName() << endl;
  ivl.swap(ivr);
  cout << ivl.getBitMapName() << " : " << ivr.getBitMapName() << endl;
	return 0;
}
