#include <iostream>
#include <memory>
#include <string>
using namespace std;


//工厂方法模式
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

//工厂方法
class Factory
{
public:
	virtual Car* createCar(string name) = 0;
};
//宝马工厂
class BMWFactory :public Factory
{
public:
	Car* createCar(string name)
	{
		return new Bmw(name);
	}
};

//奥迪工厂
class AudiFactory :public Factory
{
public:
	Car* createCar(string name)
	{
		return new Audi(name);
	}
};

int main()
{
	unique_ptr<Factory> bmwFactory(new BMWFactory());
	unique_ptr<Car> p1 (bmwFactory->createCar("X6"));
	unique_ptr<Factory> audiFactory(new AudiFactory());
	unique_ptr<Car> p2(audiFactory->createCar("A8"));

	p1->show();
	p2->show();
	return 0;
}
