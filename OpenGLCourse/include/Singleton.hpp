#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__

namespace OpenGL {


template<typename T>
class Singleton
{
public:
	static T* GetInstance();
	static void destroy();

private:
	Singleton(const Singleton&) = delete;
	auto	operator = (const Singleton&)->Singleton& = delete;

protected:
	static T* _instance;

	Singleton() { _instance = static_cast <T*> (this); };
	~Singleton() = default;
};

template<typename T>
typename T* Singleton<T>::_instance = 0;

template<typename T>
T* Singleton<T>::GetInstance()
{
	if (!_instance)
	{
		Singleton<T>::_instance = new T();
	}

	return _instance;
}

template<typename T>
void Singleton<T>::destroy()
{
	delete Singleton<T>::_instance;
	Singleton<T>::_instance = 0;
}


} // OpenGL

#endif /*__SINGLETON_HPP__*/