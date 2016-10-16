#include<iostream>
using namespace std;

// 1. 效率问题
// 2. 对象切割问题

class Window{
public:
  string name() const;
  virtual void display() const;
};
string Window::name() const{
  return "Window";
}
void Window::display() const{
  cout << "Display a window." << endl;
}

class WindowWithScrollBar : public Window {
public:
  virtual void display() const;
};
void WindowWithScrollBar::display() const{
  cout << "Display a scroll-bared window." << endl;
}

// 值传递的copy构造调用的window类型的，所以切割了对象
void display(Window w){
  w.display();
}

void displayByRef(const Window& w){
  w.display();
}


int main(){
  WindowWithScrollBar w;
  display(w);
  displayByRef(w);
  return 0;
}
