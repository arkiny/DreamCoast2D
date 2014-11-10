#pragma once
#include <Windows.h>
#include <assert.h>
template <typename T> class Singleton
{
protected:
	static T* _instance;
	Singleton(void)
	{
		assert(!_instance && "Singleton : You can't create more"
			" object, because this object is SINGLETON.");

		_instance = static_cast< T* >(this);

	}

	~Singleton(void)
	{
		assert(_instance && "Singleton : This object may be "
			"destroyed by someone's memory control or other causes.");

		_instance = 0;
	}
public:
	static T& GetInstance(){

		return *_instance;
	}

	static T* GetInstancePtr(){
		return _instance;
	}

};

