#include<iostream>
using namespace std;

// 1. 自我赋值会引发一些错误
class BitMap{
public:
	void heartBeat();
};
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
		return *this;
	}
private:
	void swap(WidgetIII& other){
		// 交换*this和other的数据
	}
public:
	BitMap* pb_;
};
WidgetIII::WidgetIII(BitMap& b) : pb_(&b){
}

int main(){
	return 0;
}
