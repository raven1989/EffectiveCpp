#include<iostream>
#include<mutex>
using namespace std;

/* 1. 有些资源的复制并不合理，这时候容器对象禁止拷贝，比如Lock
 * 2. 有些资源只要一份，但需要在最后一个使用使用后释放，这时候用引用计数容器对象
 * 3. 有些资源复制时，需要复制资源本身，这时候重写出深度copy构造，比如string
 * 4. 有些资源复制时，需要移交，这时使用auto_ptr */

class Lock{
public:
	explicit Lock(mutex* pm) : mutexPtr_(pm){
		if(mutexPtr_->try_lock()){
			cout << "Locked" << endl;
		}else{
			cout << "Locking Failed" << endl;
		}
	}
	~Lock(){
		mutexPtr_->unlock();
		cout << "Unlocked" << endl;
	}
private:
	mutex * mutexPtr_;
};

void doSomething(){
	mutex m;
	Lock lock(&m);

	//copy构造：
	//没有什么意义，只是将其复制一份；
	//默认的copy构造函数也没有执行加锁操作
	Lock lock1(lock);
}

int main(){
	doSomething();
	return 0;
}
