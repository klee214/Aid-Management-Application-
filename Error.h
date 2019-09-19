#ifndef AID_ERROR_H
#define  AID_ERROR_H
#include<iostream>

namespace aid {
	class Error {
		char* messages;
	public:
		explicit Error(const char* mess = nullptr);
		~Error();
		void clear();
		bool isClear() const;
		void message(const char* str);
		const char* message() const;
	};
	std::ostream& operator << (std::ostream&, const Error&);
}
#endif // !AID_ERROR_H
