#include<iostream>

class Waffle {
	char* brand;
	double weigth;
	double largePrice;
	double normalPrice;

public:
	Waffle(char* brand, double weight, double largePrice, double normalPrice) {
		setBrand(brand);
		setWeigth(weight);
		setLargePrice(largePrice);
		setNormalPrice(normalPrice);
	}

	void setBrand(char* brand) {
		if (brand == nullptr || brand == this->brand) {
			return;
		}
		delete[] this->brand;
		this->brand = new char[strlen(brand)];
		strcpy(this->brand, brand);
	}

	void setWeigth(double weigth) {
		if (weigth < 0) {
			std::cerr << "Inlavid weigth";
			return;
		}
		this->weigth = weigth;
	}

	void setLargePrice(double price) {
		if (price < 0) {
			std::cerr << "Ïnvalid price";
			return;
		}
		this->largePrice = price;
	}

	void setNormalPrice(double price) {
		if (price < 0) {
			std::cerr << "Ïnvalid price";
			return;
		}
		this->normalPrice = price;
	}

	char* getBrand() {
		return brand;
	}

	double getNormalPrice() {
		return normalPrice;
	}

	double getLargePrice() {
		return largePrice;
	}

	double getWeigth() {
		return weigth;
	}
};

class Shop {
private:
	Waffle** waffles;
	size_t maxCount;
	size_t currentCount;
	double totalIncome;
	double totalExpense;

	const size_t defaultCount = 1;

public:
	Shop() {
		waffles = new Waffle*[defaultCount];
		currentCount = 0;
		maxCount = defaultCount;
		totalIncome = 0;
		totalExpense = 0;
	}

	Shop(Waffle** waffles, size_t wafflesCount, size_t maxCount) {
		setWaffles(waffles, wafflesCount);
		setmaxCount(maxCount);
		totalIncome = 0;
		totalExpense = 0;
	}

	void setWaffles(Waffle** waffles, size_t wafflesCount) {
		if (waffles == nullptr || waffles == this->waffles) {
			return;
		}
		delete this->waffles;
		this->waffles = new Waffle* [wafflesCount];
		for (size_t i = 0; i < wafflesCount; i++) {
			this->waffles[i] = waffles[i];
			totalExpense += waffles[i]->getLargePrice();
		}
	}

	void setmaxCount(size_t maxCount) {
		if (maxCount < 0) {
			std::cerr << "Invalid count";
			return;
		}
		this->maxCount = maxCount;
	}

	void buyWaffle(const char* brand) {
		Waffle* waffle = findByBrand(brand);
		if (waffle == nullptr) {
			std::cerr << "Can find this brand";
			return;
		}
		this->totalIncome += waffle->getNormalPrice();
		removeFromStore(waffle);
		delete waffle;
	}

	void buyWaffles(size_t count, const char* brand) {
		size_t counter = 0;
		for (size_t i = 0; i < currentCount; i++) {
			if (currentCount == count) {
				return;
			}
			Waffle* waffle = findByBrand(brand, i);
			if (waffle != nullptr) {
				i--;
				removeFromStore(waffle);
				delete waffle;
				counter++;
				currentCount--;
			}
			else {
				return;
			}
		}
	}

	Waffle* findByBrand(const char* brand, size_t& startIndex) {
		for (size_t i = startIndex; i < currentCount; i++) {
			if (waffles[i]->getBrand() == brand) {
				return waffles[i];
			}
		}
		return nullptr;
	}

	Waffle* findByBrand(const char* brand) {
		size_t useless = 0;
		return findByBrand(brand, useless);
	}

	void removeFromStore(Waffle* waffle) {
		size_t index = 0;
		for (; index < currentCount; index++) {
			if (waffle == waffles[index]) break;
		}
		for (; index < currentCount - 1; index++) {
			waffles[index] = waffles[index + 1];
		}
		currentCount--;
	}

	size_t getCount(char* brand){
		size_t counter = 0;
		for (size_t i = 0; i < currentCount; i++) {
			if (waffles[i]->getBrand() == brand) {
				counter++;
			}
		}
		return counter;
	}

	double getProfit() {
		return totalIncome - totalExpense;
	}
};
