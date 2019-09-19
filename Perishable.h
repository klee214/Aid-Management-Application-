#include"Good.h"
#include"Date.h"

namespace aid {
	class Perishable : public Good {
		Date expireDate;
	public:
		Perishable();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::ostream& write(std::ostream& os, bool linear) const;
		std::fstream& load(std::fstream& file);
		std::istream& read(std::istream& is);
		const Date& expiry() const;
	};

	iGood* CreateProduct(char);
}