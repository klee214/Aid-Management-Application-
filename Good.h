#ifndef AID_GOOD_H
#define AID_GOOD_H

#include "Error.h"
#include "iGood.h"

namespace aid
{
	const int max_sku_length = 7;
	const int max_unit_length = 10;
	const int max_name_length = 75;
	const double tax_rate = 0.13;

	class Good : public iGood
	{
	private:
		char goodSku[max_sku_length + 1];
		char goodUnit[max_unit_length + 1];
		char* goodName;
		int quantityOnHand = 0;
		int quantityNeeded = 0;
		double priceBeforeTax = 0;
		bool taxStatus;
		Error errState;
	protected:
		char goodType;
		void name(const char*);
		const char* name() const;
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double itemPrice() const;
		double itemCost() const;
		void message(const char*);
		bool isClear() const;
	public:
		Good(char gType = 'N');
		Good(const char* sku, const char* name, const char* unit, int quantOnHand = 0, bool tStatus = true, double beforeTax = 0, int quantItemsNeeded = 0);
		Good(const Good&);
		Good& operator=(const Good&);
		~Good();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int);
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const char*) const;
		bool operator>(const iGood&) const;
		int operator+=(int);
	};

	//Helper Functions
	std::ostream& operator<<(std::ostream&, const iGood&);
	std::istream& operator>>(std::istream&, iGood&);
	double operator+=(double&, const iGood&);

}

#endif // !AID_GOOD_H

