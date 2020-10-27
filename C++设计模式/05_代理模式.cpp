#include <iostream>
#include <memory>
using namespace std;

/*
结构型模式：
关注于类和对象的组合。继承的概念被用来组合接口和定义组合对象获得新功能的方式。

代理模式Proxy Pattern
装饰器模式Decorator Pattern
适配器模式Adapter Pattern
*/


/*
代理模式Proxy

代理Proxy模式 : 通过代理类，来控制实际对象的访问权限
客户     助理Proxy     老板 委托类

代理类和委托类之间是一个组合的关系
代理类用来控制委托类的访问权限问题
*/

class VideoSite // #1 抽象类
{
public:
	virtual void freeMovie() = 0; // 免费电影
	virtual void vipMovie() = 0; // vip电影
	virtual void ticketMovie() = 0; // 用券观看电影
};
class FixBugVideoSite :public VideoSite  //委托类
{
public:
	virtual void freeMovie() // 免费电影
	{
		cout << "观看免费电影" << endl;
	}
	virtual void vipMovie() // vip电影
	{
		cout << "观看VIP电影" << endl;
	}
	virtual void ticketMovie() // 用券观看电影
	{
		cout << "用券观看电影" << endl;
	}
private:
};


//代理类 代理FixBugVideoSite
class FreeVideoSiteProxy : public VideoSite
{
public:
	FreeVideoSiteProxy(){ pVideo = new FixBugVideoSite(); }
	~FreeVideoSiteProxy(){ delete pVideo; }
	virtual void freeMovie()  // 免费电影
	{
		pVideo->freeMovie();//通过代理对象的freeMovie，来访问真正委托类对象的freeMovie方法
	}
	virtual void vipMovie() // vip电影
	{
		cout << "您目前只是普通游客，需要升级为VIP，才能观看VIP电影" << endl;
	}
	virtual void ticketMovie() // 用券观看电影
	{
		cout << "你目前没有券，需要购买电影券，才能观看电影" << endl;
	}
private:
	VideoSite* pVideo;
};


class VipVideoSiteProxy : public VideoSite
{
public:
	VipVideoSiteProxy() { pVideo = new FixBugVideoSite(); }
	~VipVideoSiteProxy() { delete pVideo; }
	virtual void freeMovie()  // 免费电影
	{
		pVideo->freeMovie();//通过代理对象的freeMovie，来访问真正委托类对象的freeMovie方法
	}
	virtual void vipMovie() // vip电影
	{
		pVideo->vipMovie();
	}
	virtual void ticketMovie() // 用券观看电影
	{
		cout << "你目前没有券，需要购买电影券，才能观看电影" << endl;
	}
private:
	VideoSite* pVideo;
};

//这些都是通用的API接口，使用的都是基类的指针或者引用
void watchMovice(unique_ptr<VideoSite> &ptr)
{
	ptr->freeMovie();
	ptr->ticketMovie();
	ptr->vipMovie();
}

int main()
{
	//VideoSite* p1 = new FixBugVideoSite;
	//p1->freeMovie();
	//p1->ticketMovie();
	//p1->vipMovie();

	unique_ptr<VideoSite> freeVideo(new FreeVideoSiteProxy());// 客户直接访问代理对象
	unique_ptr<VideoSite> vipVideo(new VipVideoSiteProxy());
	cout << "游客身份：" << endl;
	watchMovice(freeVideo);

	cout << "VIP身份：" << endl;
	watchMovice(vipVideo);

	return 0;
}
