#include<iostream>
using namespace std;

class Font{
public:
	Font(){ cout << "Constructing Font" << endl;}
	~Font(){ cout << "Destructing Font" << endl;}
	Font(const Font&){ cout << "Copy Constructing Font" << endl; }
	void sample(){
		cout << "Font Sample" << endl;
	}
};

/* 提供对管理资源的访问途径
 * 1. 重载*和->
 * 2. 提供一个显示获取资源的方法 或 隐式方法 */

class FontPtr{
public:
	explicit FontPtr(Font* font);
	~FontPtr();
	Font& operator*() const;
	Font* operator->() const;
	// 显式获取
	Font& get() const;
	// 隐式获取
	operator Font&() const;
private:
	Font* font_;
};

FontPtr::FontPtr(Font* font) : font_(font) {
}
FontPtr::~FontPtr(){
	delete font_;
}
Font& FontPtr::operator*() const{
	return *font_;
}
Font* FontPtr::operator->() const{
	return font_;
}
Font& FontPtr::get() const{
	return *font_;
}
FontPtr::operator Font&() const{
	return *font_;
}

void implicitlyCall(Font& f){
	f.sample();
}

int main(){
	FontPtr font(new Font);
	(*font).sample();
	font->sample();
	font.get().sample();
	implicitlyCall(font);
	// 隐式获取容易被误用，一般使用显式获取
	// 比如：本意是复制一个FontPtr
	// FontPtr replica = font;
	// 但是写成了下面这个，仍然能通过
	Font* replica = new Font(font);
	return 0;
}
