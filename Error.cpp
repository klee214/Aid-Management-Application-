#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include"Error.h"

using namespace std;

namespace aid {
	Error::Error(const char* mess)
	{
		if (mess == nullptr || mess[0] == '\0') {
			messages = nullptr;
		}
		else {
			int length = strlen(mess);
			
			messages = new char[length + 1];
			strncpy(messages, mess, length + 1);
		}
	}

		Error::~Error(){
		delete[] messages;
	}

	void Error::clear()
	{
		if (messages != nullptr) {
			delete[] messages;
			messages = nullptr;
		}
	}

	bool Error::isClear() const
	{
		if (messages == nullptr)
			return true;
		else
			return false;
	}

	void Error::message(const char* str)
	{
		if (!isClear())
			delete[] messages;

		if (str != nullptr && str[0] != '\0') {
			int length = strlen(str);
			
			messages = new char[length + 1];
			strncpy(messages, str, length + 1);
		}
		else {
			messages = nullptr;
		}
	}

	const char* Error::message() const
	{
		if (isClear())
			return nullptr;
		else
			return messages;
	}

	std::ostream& operator << (std::ostream& ost, const Error& mes)
	{
		if (!mes.isClear()) {
			ost << mes.message();
		}

		return ost;
	}
}