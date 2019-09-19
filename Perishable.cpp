#include<iostream>
#include"Perishable.h"

using namespace std;

namespace aid {
	Perishable::Perishable() : Good('P')
	{
		expireDate = Date();
	}

	std::fstream& Perishable::store(std::fstream& file, bool newLine) const
	{
		if (expireDate.errCode() != 0) {
			Good::store(file, newLine);
		}
		else {
			Good::store(file, false);
			expireDate.fwrite(file);

			if (newLine) {
				file << endl;
			}
		}

		return file;
	}

	std::fstream& Perishable::load(std::fstream& file)
	{
		Good::load(file);
		expireDate.read(file);

		return file;
	}

	std::ostream& Perishable::write(std::ostream& os, bool linear) const
	{
		Good::write(os, linear);

		if (Good::isClear() && expireDate.errCode() == 0) {
			if (!linear) {
				os << endl;
				os << " Expiry date: ";
				expireDate.write(os);
			}
			else {
				expireDate.write(os);
			}
		}

		return os;
	}

	std::istream& Perishable::read(std::istream& is)
	{
		Good::read(is);
		goodType = 'P';

		if (!is.fail()) {
			int y, m, d;
			char sep;

			cout << " Expiry date (YYYY/MM/DD): ";
			is >> y >> sep >> m >> sep >> d;

			Date tmp(y, m, d);

			if (tmp.errCode() == 1) {
				Good::message("Invalid Date Entry");
				is.setstate(std::ios::failbit);
			}
			else if (tmp.errCode() == 2) {
				Good::message("Invalid Day in Date Entry");
				is.setstate(std::ios::failbit);
			}
			else if (tmp.errCode() == 3) {
				Good::message("Invalid Month in Date Entry");
				is.setstate(std::ios::failbit);
			}
			else if (tmp.errCode() == 5) {
				Good::message("Invalid Expiry in Date Entry");
				is.setstate(std::ios::failbit);
			}
			else if (tmp.errCode() == 4) {
				Good::message("Invalid Year in Date Entry");
				is.setstate(std::ios::failbit);
			}

			if (!is.fail()) {
				expireDate = tmp;
			}

		}
		return is;
	}

	const Date& Perishable::expiry() const
	{
		return expireDate;
	}

	iGood* CreateProduct(char tag)
	{
		iGood* tmp = nullptr;
		if (tag == 'N' || tag == 'n') {

			tmp = new Good;
		}
		else if(tag == 'P' || tag == 'p'){
			tmp = new Perishable;
		}
		else {
			tmp = nullptr;
		}

		return tmp;
	}
}