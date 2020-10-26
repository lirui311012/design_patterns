#include <iostream>
#include <mutex>
using namespace std;


/*
单例模式：一个类不管创建多少次对象，永远只能得到该类型一个对象的实例
A *p1 = new A();
A *p2 = new A();
A *p3 = new A();

常用到的，比如日志模块，数据库模块


单例模式：
饿汉式单例模式：还没有获取实例对象，实例对象就已经产生了，本身就是线程安全
懒汉式单例模式：唯一的实例对象，直到第一次获取它的时候，才产生(更加受欢迎)，需要考虑线程安全
*/


#if 1

// 线程安全的懒汉式单例模式  //简单实用
class Singleton
{
public:
	static Singleton* getInstance() // #3 获取类的唯一实例对象的接口方法
	{
		// linux下调试一下g++ -o run 单例模式.cpp -g   gdb run
		// 结论：函数静态局部变量的初始化，在汇编指令上已经自动添加线程互斥指令了
		//所以说静态局部变量的初始化本身就是线程安全的操作，不必担心
		static Singleton instance; // #2 定义一个唯一的类的实例对象
		return &instance;
	}
private:
	Singleton() // #1 构造函数私有化
	{
		// 很多初始化的代码
	}
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
};

int main()
{
	Singleton* p1 = Singleton::getInstance();
	Singleton* p2 = Singleton::getInstance();
	Singleton* p3 = Singleton::getInstance();
	cout << "===========" << endl;
	return 0;
}

#endif





//////////////////////////////////////////////////////////////////////////////

#if 0
//线程安全的懒汉式单例模式  懒汉单例+互斥锁+双重判断
std::mutex mtx;

// 懒汉式单例模式 => 是不是线程安全的呢？   => 线程安全的懒汉式单例模式
//懒汉模式单例将单例对象的实例化，延迟到了第一次获取该对象的时候再进行构造实例化
class Singleton
{
public:
	// 是不是可重入函数呢？   锁+双重判断
	static Singleton* getInstance() // #3 获取类的唯一实例对象的接口方法
	{
		//lock_guard<std::mutex> guard(mtx); // 锁的粒度太大了
		if (instance == nullptr)
		{
			lock_guard<std::mutex> guard(mtx);
			if (instance == nullptr)
			{
				/*
				开辟内存
				构造对象-->A
				给instance赋值-------->B  //翻译成汇编指令A和B顺序可能混乱,使用volatile关键字
				*/
				instance = new Singleton();
			}
		}
		return instance;
	}
private:
	static Singleton* volatile instance; // #2 定义一个唯一的类的实例对象
	Singleton() // #1 构造函数私有化
	{

	}
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
};
Singleton* volatile Singleton::instance = nullptr;

int main()
{
	Singleton* p1 = Singleton::getInstance();
	Singleton* p2 = Singleton::getInstance();
	Singleton* p3 = Singleton::getInstance();

	return 0;
}

#endif

//////////////////////////////////////////////////////////////////////////////

#if 0

// 饿汉式单例模式 一定是线程安全的
class Singleton
{
public:
	static Singleton* getInstance() // #3 获取类的唯一实例对象的接口方法
	{
		return &instance;
	}
private:
	static Singleton instance; // #2 定义一个唯一的类的实例对象
	Singleton() // #1 构造函数私有化
	{

	}
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
};
Singleton Singleton::instance;  //在进程虚拟内存的数据段

int main()
{
	Singleton *p1 = Singleton::getInstance();
	Singleton *p2 = Singleton::getInstance();
	Singleton *p3 = Singleton::getInstance();

	return 0;
}
//饿汉式存在的问题是：
//初始化信息都是放在构造函数里面进行初始化的，那在程序运行刚刚开始就花大量时间去
//初始化这个单例对象，但是你还没有用到。所以单例对象应该在第一次调用的时候去初始化
//但是可以发现，饿汉模式的单例天生就是线程安全的。
//////////////////////////////////////////////////////////////////////////////

#endif 