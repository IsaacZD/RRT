#pragma once

template<typename T>
class DynArray
{
public:
	DynArray();
	DynArray(int);
	~DynArray();

	bool Append(T item);
	bool Truncate();
	void Clear() { nData = nullptr; }
	int Length() const { return nData; }
	bool Empty() const { return nData == 0; }
	const T& operator[](int i) const { return data[i]; }
	T& operator[](int i) { return data[i]; }

public:
	int nData;
	int arraySize;
	T *data;
};

template<typename T>
DynArray<T>::DynArray() : nData(0), arraySize(4), data(new T[arraySize])
{ }

template<typename T>
DynArray<T>::DynArray(int a) : nData(0), arraySize(a), data(new T[arraySize])
{ }

template<typename T>
DynArray<T>::~DynArray()
{
	nData = 0;
	delete[] data;
}

template<typename T>
bool DynArray<T>::Truncate()
{
	if (nData != arraySize)
	{
		T *temp = data;
		arraySize = nData;
		if (!(data = new T[arraySize])) return false;
		for (int i = 0; i < nData; i++) data[i] = temp[i];
		delete[] temp;
	}
	return true;
}

template<typename T>
bool DynArray<T>::Append(T item)
{
	if (nData == arraySize)
	{
		arraySize *= 2;
		T *temp = data;
		if (!(data = new T[arraySize])) return false;
		for (int i = 0; i < nData; i++)
			data[i] = temp[i];
		delete[] temp;
	}
	data[nData++] = item;
	return true;
}
