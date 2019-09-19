#define _CRT_SECURE_NO_WARNINGS
#include "Good.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>

using namespace std;

namespace aid
{

	void Good::name(const char* n)
	{
		delete[] goodName;
		goodName = nullptr;

		goodName = new char[max_name_length + 1];
		strncpy(goodName, n, max_name_length);
		goodName[max_name_length] = '\0';
	}

	const char* Good::name() const
	{
		return goodName == nullptr ? nullptr : goodName; //if i checked element 0 of goodName, it would cause a read access violation because the name was not input yet
	}

	const char* Good::sku() const
	{
		return goodSku;
	}

	const char* Good::unit() const
	{
		return goodUnit;
	}

	bool Good::taxed() const
	{
		return taxStatus;
	}

	//single item price without tax
	double Good::itemPrice() const
	{
		return priceBeforeTax;
	}

	//single item price plus tax
	double Good::itemCost() const
	{
		return taxStatus ? (itemPrice() + (itemPrice() * tax_rate)) : itemPrice();
	}

	void Good::message(const char* err)
	{
		errState.message(err);
	}

	bool Good::isClear() const
	{
		return errState.isClear() ? true : false;
	}

	Good::Good(char gType)
	{
		goodType = gType;
		goodSku[0] = '\0';
		goodUnit[0] = '\0';
		goodName = nullptr;
		goodName = new char[max_name_length + 1];
		quantityOnHand = 0;
		quantityNeeded = 0;
		priceBeforeTax = 0;
		taxStatus = true;
	}

	Good::Good(const char* sku, const char* n, const char* unit, int quantOnHand, bool tStatus, double beforeTax, int quantNeeded)
	{
		goodType = 'N';
		goodName = nullptr;
		name(n);
		strncpy(goodSku, sku, max_sku_length);
		goodSku[max_sku_length] = '\0';
		strncpy(goodUnit, unit, max_unit_length);
		goodUnit[max_unit_length] = '\0';
		quantityOnHand = quantOnHand;
		quantityNeeded = quantNeeded;
		priceBeforeTax = beforeTax;
		taxStatus = tStatus;
	}

	Good::Good(const Good& obj)
	{
		if (!obj.isEmpty())
		{
			goodName = nullptr;
			*this = obj;
		}
	}

	Good& Good::operator=(const Good& obj)
	{
		if (this != &obj)
		{
			goodType = obj.goodType;

			strncpy(goodSku, obj.goodSku, max_sku_length);
			goodSku[max_sku_length] = '\0';

			strncpy(goodUnit, obj.goodUnit, max_unit_length);
			goodUnit[max_unit_length] = '\0';

			quantityOnHand = obj.quantityOnHand;
			quantityNeeded = obj.quantityNeeded;
			priceBeforeTax = obj.priceBeforeTax;
			taxStatus = obj.taxStatus;

			delete[] goodName;
			goodName = nullptr;

			if (obj.goodName != nullptr)
			{
				name(obj.goodName);
			}

		}
		return *this;
	}

	Good::~Good()
	{
		delete[] goodName;
		goodName = nullptr;
	}

	std::fstream& Good::store(std::fstream& file, bool newLine) const
	{
		if (file.is_open())
		{
			file << goodType << "," << goodSku << "," << goodName << "," << goodUnit << "," <<
				taxStatus << "," << priceBeforeTax << "," << quantityOnHand << "," << quantityNeeded;
		}
		if (newLine)
		{
			file << std::endl;
		}
		return file;
	}

	std::fstream& Good::load(std::fstream& file)
	{
		Good temp;

		if (file.is_open())
		{
			file.getline(temp.goodSku, max_sku_length + 1, ',');
			file.getline(temp.goodName, max_name_length + 1, ',');
			file.getline(temp.goodUnit, max_unit_length + 1, ',');
			file >> temp.taxStatus;
			file.ignore();
			file >> temp.priceBeforeTax;
			file.ignore();
			file >> temp.quantityOnHand;
			file.ignore();
			file >> temp.quantityNeeded;
			file.ignore();

			*this = temp;
		}

		return file;
	}

	std::ostream& Good::write(std::ostream& os, bool linear) const
	{
		if (!errState.isClear())
		{
			os << errState;
		}
		else
		{
			if (!isEmpty())
			{
				if (linear)
				{
					os.fill(' ');
					os << std::setw(max_sku_length) << std::left << sku() << '|'
						<< std::setw(20) << std::left << name() << '|'
						<< std::setw(7) << std::setprecision(2) << std::fixed << std::right << itemCost() << '|'
						<< std::setw(4) << std::right << quantity() << '|'
						<< std::setw(10) << std::left << unit() << '|'
						<< std::setw(4) << std::right << qtyNeeded() << '|';
				}
				else
				{
					os << " Sku: " << sku() << std::endl << " Name (no spaces): " << name() << std::endl << " Price: " << itemPrice() << std::endl
						<< " Price after tax: ";
					if (taxStatus) {
						os << itemCost() << std::endl;
					}
					else {
						os << " N/A" << std::endl;
					}

					os << " Quantity on Hand: " << quantity() << " " << unit() << std::endl
						<< " Quantity needed: " << qtyNeeded();
				}
			}
		}
		return os;
	}

	std::istream& Good::read(std::istream& is)
	{
		char sku_[max_sku_length + 1];
		char* name = new char[max_name_length + 1];
		char unit[max_unit_length + 1];
		int	quantity = 0, qtyNeeded = 0;
		double price_ = 0;
		char choice = '\0';
		bool taxed_ = false;

		Error error;
		Good temp;

		std::cout << " Sku: ";
		is >> sku_;

		std::cout << " Name (no spaces): ";
		is >> name;

		std::cout << " Unit: ";
		is >> unit;

		if (!is.fail())
		{
			std::cout << " Taxed? (y/n): ";
			is >> choice;

			//had to check if y or n or the values in output were off and output for tax was always 1 in final output line
			if (choice == 'y' || choice == 'Y')
			{
				taxed_ = true;
			}
			else if (choice == 'N' || choice == 'n')
			{
				taxed_ = false;
			}
			else {
				is.setstate(std::ios::failbit);
				error.message("Only (Y)es or (N)o are acceptable");
			}
		}

		if (!is.fail())
		{
			std::cout << " Price: ";
			is >> price_;
			if (is.fail())
				error.message("Invalid Price Entry");
		}

		if (!is.fail())
		{
			std::cout << " Quantity on hand: ";
			is >> quantity;
			if (is.fail())
				error.message("Invalid Quantity Entry");
		}

		if (!is.fail())
		{
			std::cout << " Quantity needed: ";
			is >> qtyNeeded;
			if (is.fail())
				error.message("Invalid Quantity Needed Entry");
		}

		if (!is.fail())
		{
			temp = Good(sku_, name, unit, quantity, taxed_, price_, qtyNeeded);
			*this = temp;
		}

		errState.message(error.message());

		delete[] name;
		name = nullptr;

		return is;
	}

	bool Good::operator==(const char* sku) const
	{
		return strcmp(goodSku, sku);
	}

	double Good::total_cost() const
	{
		return itemCost() * quantityOnHand;
	}

	void Good::quantity(int units)
	{
		if (units > 0)
		{
			quantityOnHand = units;
		}
	}

	bool Good::isEmpty() const
	{
		return (goodSku[0] == '\0');

	}

	int Good::qtyNeeded() const
	{
		return quantityNeeded;
	}

	int Good::quantity() const
	{
		return quantityOnHand;
	}

	bool Good::operator>(const char* sku) const
	{
		return strcmp(goodSku, sku) > 0 ? true : false;
	}

	bool Good::operator>(const iGood& obj) const
	{
		return strcmp(name(), obj.name()) > 0 ? true : false;
	}

	int Good::operator+=(int units)
	{
		return units > 0 ? quantityOnHand += units : quantityOnHand;
	}

	//Helper Functions
	std::ostream& operator<<(std::ostream& os, const iGood& obj)
	{
		obj.write(os, true);
		return os;
	}

	std::istream& operator>>(std::istream& is, iGood& obj)
	{
		obj.read(is);
		return is;
	}

	double operator+=(double& cost, const iGood& obj)
	{
		return cost + obj.total_cost();
	}
}