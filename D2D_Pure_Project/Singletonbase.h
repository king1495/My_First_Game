#pragma once
//	하나의 객체를 단 하나만 만들고 싶을때 쓰는 디자인 패턴
template <typename T>
class SingletonBase {
protected:
	static T* Instance;

	SingletonBase() {};
	~SingletonBase() {};

public:
	static T* GetInstance(void);
	void ReleaseSingleton(void);
};

template <typename T>
T* SingletonBase<T>::Instance = nullptr;

template <typename T>
T* SingletonBase<T>::GetInstance(void) {
	if (!Instance) Instance = new T;
	return Instance;
}

template <typename T>
void SingletonBase<T>::ReleaseSingleton(void) {
	if (Instance) {
		delete Instance;
		Instance = nullptr;
	}
}
