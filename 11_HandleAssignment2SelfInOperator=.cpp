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
		WidgetIII replica(other);
		swap(replica);
    // std 提供的swap出现了段错误，再琢磨下
    // std::swap(*this, replica);
		return *this;
	}
  const string getBitMapName() const{
    return pb_->getName();
  }
public:
	void swap(WidgetIII& other){
		// 交换*this和other的数据
    // 试试用memcpy来做
    WidgetIII tmp(*this);
    memcpy(this, static_cast<const WidgetIII*>(&other), sizeof(*this));
    memcpy(&other, static_cast<const WidgetIII*>(&tmp), sizeof(*this));
	}
public:
	BitMap* pb_;
};
WidgetIII::WidgetIII(BitMap& b) : pb_(&b){
}

int main(){
  BitMap bml("left");
  BitMap bmr("right");
  WidgetIII wl(bml);
  WidgetIII wr(bmr);
  cout << wl.getBitMapName() << " : " << wr.getBitMapName() << endl;
  swap(wl, wr);
  cout << wl.getBitMapName() << " : " << wr.getBitMapName() << endl;
  wl = wr;
  cout << wl.getBitMapName() << " : " << wr.getBitMapName() << endl;
	return 0;
}
