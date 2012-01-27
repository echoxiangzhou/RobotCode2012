#ifndef SINGLETON_H
#define SINGLETON_H

template <class T>
class Singleton
{
public:
	static void CreateInstance()
	{
		instance = new T();
	}
	
	static void DestroyInstance()
	{
		delete instance;
	}
	
	static T& GetInstance()
	{
		if( !instance )
			CreateInstance();
		
		return *instance;
	}
	
private:
	Singleton();
	~Singleton();
	
	static T* instance;
};

template <class T>
T* Singleton::instance = 0;

#endif // SINGLETON_H
