#ifndef AID_DATE_H
#define AID_DATE_H
#define NO_ERROR 0
#define CIN_FAILED 1  
#define DAY_ERROR 2  
#define MON_ERROR 3 
#define YEAR_ERROR 4 
#define PAST_ERROR 5  

namespace aid {
	const int min_year = 2018;
	const int max_year = 2038;
	const int min_date = 751098;

	class Date {
		int year;
		int month;
		int dayOfMonth;
		int compare;
		int error;
		void errCode(int errorCode);
		int mdays(int year, int month) const;
		void setInit();
		void setVal(int, int, int);
	public:
		Date();
		Date(int, int, int);
		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;
		int errCode() const;
		bool bad() const;
		std::fstream& read(std::fstream& istr);
		std::fstream& fwrite(std::fstream& ostr) const;
		std::ostream& write(std::ostream& ostr) const;
	};

	std::fstream& operator >> (std::fstream& is, Date& d);
	std::ostream& operator << (std::ostream& os, const Date& d);
}

#endif

