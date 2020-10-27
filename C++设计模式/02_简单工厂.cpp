#include <iostream>
#include <string>
#include <memory>
using namespace std;



#if 1
/*
简单工厂 Simple Factory :
把对象的创建封装在一个接口函数里面，通过传入不同的标识，返回创建的对象
客户不用自己负责new对象，不用了解对象创建的详细过程

提供创建对象实例的接口函数不闭合，不能对修改关闭

工厂方法 Factory Method
Factory基类，提供了一个纯虚函数（创建产品），定义派生类（具体产品的工厂）负责创建对应的
产品，可以做到不同的产品，在不同的工厂里面创建，能够对现有工厂，以及产品的修改关闭

实际上，很多产品是有关联关系的，属于一个产品簇，不应该放在不同的工厂里面去创建，这样
一是不符合实际的产品对象创建逻辑，二是工厂类太多了，不好维护

抽象工厂 Abstract Factory
把有关联关系的，属于一个产品簇的所有产品创建的接口函数，放在一个抽象工厂里面AbstractFactory
，派生类（具体产品的工厂）应该负责创建该产品簇里面所有的产品

工厂模式：主要是封装了对象的创建
*/


//简单工厂
class Car
{
public:
	Car(string name) :_name(name) {}
	virtual void show() = 0;
protected:
	string _name;
};

class Bmw : public Car
{
public:
	Bmw(string name) :Car(name) {}
	void show()
	{
		cout << "获取了一辆宝马汽车:" << _name << endl;
	}
};
class Audi : public Car
{
public:
	Audi(string name) :Car(name) {}
	void show()
	{
		cout << "获取了一辆奥迪汽车:" << _name << endl;
	}
};

enum CarType
{
	BMW, AUDI
};

class SimpleFactory
{
public:
	Car* createCar(CarType ct)  //软件设计， 开闭原则
	{
		switch (ct)
		{
		case BMW:
			return new Bmw("X1");
		case AUDI:
			return new Audi("A6");
		default:
			cerr << "传入工厂的参数不正确" << ct << endl;
			break;
		}

		return nullptr;
	}
private:

};

int main()
{
	/*Car *p1 = new Bmw("X1");
	Car *p2 = new Audi("A6");
	p1->show();
	p2->show();*/


	//SimpleFactory* factory = new SimpleFactory();
	//Car* p1 = factory->createCar(BMW);
	//Car* p2 = factory->createCar(AUDI);
	//p1->show();
	//p2->show();

	//delete p1;
	//delete p2;
	//delete factory;
	//p1 = nullptr;
	//p2 = nullptr;
	//factory = nullptr;

	//智能指针
	unique_ptr<SimpleFactory> factory(new SimpleFactory());
	unique_ptr<Car> p1(factory->createCar(BMW));
	unique_ptr<Car> p2(factory->createCar(AUDI));
	p1->show();
	p2->show();


	return 0;
}


#endif