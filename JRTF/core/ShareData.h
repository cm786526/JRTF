#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <typeinfo>
#include <limits.h>
#include <map>

typedef unsigned char BYTE;

#define TYPE_NONE 0
#define TYPE_INT 10
#define TYPE_UNSIGNED_INT 11
#define TYPE_LONG 20
#define TYPE_UNSIGNED_LONG 21
#define TYPE_FLOAT 30
#define TYPE_DOUBLE 40
#define TYPE_INT_ARRAY 50
#define TYPE_LONG_ARRAY 60
#define TYPE_FLOAT_ARRAY 70
#define TYPE_DOUBLE_ARRAY 80

class ShareData {
public:
	ShareData() {};
	ShareData(int type);
	ShareData(void* local, int type, unsigned int size);
	~ShareData();

	template<typename T>
	T* convert_data()
	{
		if (type == TYPE_INT || type == TYPE_FLOAT || type == TYPE_LONG || type == TYPE_DOUBLE)
		{
			return new T((T*)share);
		}
		else
		{
			return nullptr;
		}
	}

	template<typename T>
	T* convert_data_array()
	{
		if (type == TYPE_INT_ARRAY || type == TYPE_FLOAT_ARRAY || type == TYPE_LONG_ARRAY || type == TYPE_DOUBLE_ARRAY)
		{
			int number;
			switch (type)
			{
			case TYPE_INT_ARRAY:
				number = size / sizeof(int);
				return resolve_data_array<int, T>(number);
			case TYPE_FLOAT_ARRAY:
				number = size / sizeof(float);
				return resolve_data_array<float, T>(number);
			case TYPE_LONG_ARRAY:
				number = size / sizeof(long);
				return resolve_data_array<long, T>(number);
			case TYPE_DOUBLE_ARRAY:
				number = size / sizeof(double);
				return resolve_data_array<double, T>(number);
			}
		}
		else
		{
			return nullptr;
		}
	}

	template<typename T1, typename T2>
	T2* resolve_data_array(int number)
	{
		T2* dst_temp = new T2[number];
		T1* src_temp = (T1*)share;
		for (size_t i = 0; i < number; i++)
		{
			dst_temp[i] = (T2)src_temp[i];
		}
		return dst_temp;
	}

	void *share;
	int type;
	unsigned int size;

private:
	
};
