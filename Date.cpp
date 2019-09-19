#include<iostream>
#include<fstream>
#include"Date.h"

using namespace std;

namespace aid {
	void Date::errCode(int errorCode)
	{
		if (errorCode > -1 && errorCode < 6)
			error = errorCode;
		else
			error = -1;
	}

	void Date::setInit()
	{
		errCode(-1);
		year = 0;
		month = 0;
		dayOfMonth = 0;
		compare = 0;
	}

	int Date::mdays(int year, int mon) const
	{
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;

		return days[month] + int((month == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	Date::Date()
	{
		setInit();
	}

	void Date::setVal(int c_year, int c_mon, int c_day)
	{

		compare = c_year * 372 + c_mon * 31 + c_day;
		if (c_year >= min_year && year <= max_year) {
			year = c_year;
		}
		else {
			setInit();
			errCode(4);
			return;
		}

		if (c_mon >= 1 && c_mon <= 12) {
			month = c_mon;
		}
		else {
			setInit();
			errCode(3);
			return;
		}

		if (c_day <= mdays(c_year, c_mon)) {
			dayOfMonth = c_day;
		}
		else {
			setInit();
			errCode(2);
			return;
		}

		if (compare >= min_date) {
			errCode(0);
		}
		else {
			setInit();
			errCode(5);
		}
	}

	Date::Date(int c_year, int c_mon, int c_day)
	{
		setVal(c_year, c_mon, c_day);
	}

	bool Date::operator == (const Date& d) const
	{
		if (d.compare == compare && d.dayOfMonth == dayOfMonth &&
			d.error == error && d.month == month && d.year == year) {
			return true;
		}
		else {
			return false;
		}
	}

	bool Date::operator != (const Date& d) const
	{
		if (compare == d.compare)
			return false;
		else
			return true;
	}

	bool Date::operator < (const Date& d) const
	{
		if (compare != d.compare)
			if (year < d.year)
				return true;
			else if (year == d.year)
				if (month < d.month)
					return true;
				else if (month == d.month)
					if (dayOfMonth < d.dayOfMonth)
						return true;
					else
						return false;
				else
					return false;
			else
				return false;
		else
			return false;
	}

	bool Date::operator >= (const Date& d) const
	{
		if (compare < d.compare)
			return false;
		else
			return true;
	}

	bool Date::operator > (const Date& d) const
	{
		if (compare != d.compare)
			if (year > d.year)
				return true;
			else if (year == d.year)
				if (month > d.month)
					return true;
				else if (month == d.month)
					if (dayOfMonth > d.dayOfMonth)
						return true;
					else
						return false;
				else
					return false;
			else
				return false;
		else
			return false;
	}

	bool Date::operator <= (const Date& d) const
	{
		if (compare > d.compare)
			return false;
		else
			return true;
	}

	int Date::errCode() const
	{
		return error;
	}

	bool Date::bad() const
	{
		if (error != 0)
			return true;
		else
			return false;
	}

	std::fstream& Date::read(std::fstream& istr)
	{
		char sep;
		int t_year = 0;
		int t_month = 0;
		int t_day = 0;

		istr >> t_year >> sep >> t_month >> sep >> t_day;
		if (istr.fail()) {
			errCode(1);
		}
		else {
			setVal(t_year, t_month, t_day);
		}

		return istr;
	}
	std::ostream& Date::write(std::ostream& ostr) const
	{
		ostr << year << "/";

		ostr.width(2);
		ostr.fill('0');
		ostr << month << "/";

		ostr.width(2);
		ostr.fill('0');
		ostr << dayOfMonth;

		return ostr;
	}

	std::fstream& Date::fwrite(std::fstream& ostr) const
	{
		ostr << "," << year << "/";

		ostr.width(2);
		ostr.fill('0');
		ostr << month << "/";

		ostr.width(2);
		ostr.fill('0');
		ostr << dayOfMonth;

		return ostr;
	}

	std::fstream& operator >> (std::fstream& istr, Date& d)
	{
		d.read(istr);
		return istr;
	}

	std::ostream& operator << (std::ostream& ostr, const Date& d)
	{
		d.write(ostr);
		return ostr;
	}
}
