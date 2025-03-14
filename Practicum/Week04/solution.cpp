#include <iostream>
#include <sstream>
#include <fstream>
#pragma warning (disable: 4996)

namespace ex1 {
	const size_t NAME_LEN = 20;
	enum Subjects {
		MATH,
		BEL,
		PHYS,
		CHEM
	};
	class Teacher {
	private:
		char name[NAME_LEN];
		size_t age;
		double salary;

	public:
		Teacher(const char name[NAME_LEN], const size_t age, const double salary) {
			setName(name);
			setAge(age);
			setSalary(salary);
		}

		void setName(const char* name) {
			if (name == nullptr || strlen(name) != NAME_LEN) {
				std::cerr << "Invalid name!";
				return;
			}
			strcpy(this->name, name);
		}

		void setAge(const size_t age) {
			const size_t MIN_AGE = 18;
			const size_t MAX_AGE = 70;
			if (age < MIN_AGE || age > MAX_AGE) {
				std::cerr << "Invalid age!";
				return;
			}
			this->age = age;
		}

		void setSalary(const double salary) {
			const size_t MIN_SALARY = 500;
			if (salary < MIN_SALARY) {
				std::cerr << "Invalid salary";
			}
			this->salary = salary;
		}

		char* getName() const {
			char* result = new char[NAME_LEN + 1];
			for (size_t i = 0; i < NAME_LEN; i++) {
				result[i] = name[i];
			}
			result[NAME_LEN] = 0;
			return result;
		}

		size_t getAge() const {
			return age;
		}

		size_t getSalary() const {
			return salary;
		}
	};
}

namespace ex2 {
	const size_t COUNT_OF_PROBLEMS = 20;

	void errorAlert(const char* message) {
		std::cerr << message << std::endl;
	}

	class Problem {
	private:
		char* description;
		char answer;
		size_t points;
		char* pass;

		void setDescription(const char* descr) {
			if (descr == nullptr) {
				std::cerr << "Nullptr!";
			}
			if (descr == this->description) {
				return;
			}
			delete[] this->description;
			this->description = new char[strlen(descr) + 1];
			strcpy(this->description, descr);
		}

		void setPass(const char* pass) {
			if (pass == nullptr) {
				std::cerr << "Nullptr!";
			}
			if (pass == this->pass) {
				return;
			}
			delete[] this->pass;
			this->pass = new char[strlen(pass) + 1];
			strcpy(this->pass, pass);
		}

		void setAnswer(char answer) {
			this->answer = answer;
		}

		void setPoints(size_t points) {
			this->points = points;
		}

	public:
		Problem(const char* descr, char answer, const size_t points, const char* pass) {
			setDescription(descr);
			setAnswer(answer);
			setPass(pass);
		}

		~Problem() {
			delete[] description;
			delete[] pass;
		}

		char* getDescription() const {
			return this->description;
		}

		size_t getPoints() const {
			return this->points;
		}

		void setPoints(const char answer, const char* pass) {
			if (!strcmp(this->pass, pass))
				this->answer - answer;
			else errorAlert("Wrong Password!");
		}

		void setPoints(const size_t points, const char* pass) {
			if (!strcmp(this->pass, pass))
				this->points = points;
			else errorAlert("Wrong Password!");
		}

		char getAnswer(const char* pass) const{
			if (!strcmp(this->pass, pass))
				return answer;
			else errorAlert("Wrong Password!");
			return 0;
		}
	};

	class Exam {
	private:
		Problem* exercises[COUNT_OF_PROBLEMS];

	public:
		Exam(const char* fileName) {
			std::ifstream file(fileName, std::ios::binary);
			if (!file) {
				errorAlert("File not found!");
				return;
			}
			for (size_t i = 0; i < COUNT_OF_PROBLEMS; i++) {
				file.read((char*)exercises[i], sizeof(Problem));
			}
			file.close();
		}

		~Exam() {
			for (size_t i = 0; i < COUNT_OF_PROBLEMS; i++) {
				delete exercises[i];
			}
		}

		void save(const char* fileName) const{
			std::ofstream file(fileName, std::ios::binary);
			if (!file) {
				errorAlert("File can't be opened!");
				return;
			}
			for (size_t i = 0; i < COUNT_OF_PROBLEMS; i++) {
				file.write((const char*)exercises[i], sizeof(Problem));
			}
			file.close();
		}

		size_t maxPoints() const{
			size_t count = 0;
			for (size_t i = 0; i < COUNT_OF_PROBLEMS; i++) {
				if (exercises[i] == nullptr) {
					continue;
				}
				count += exercises[i]->getPoints();
			}
			return count;
		}
	};
}

namespace ex3 {
	const size_t MAX_TITLE_SIZE = 64;
	const size_t DEFAULT_CAPACITY = 10;

	void errorAlert(const char* message) {
		std::cerr << message << std::endl;
	}

	char* formatDouble(double num, int precision) {
		std::stringstream ss;
		ss.precision(precision);
		ss.setf(std::ios::fixed);
		ss << num;
		std::string temp = ss.str(); // for getting size
		char* result = new char[temp.size() + 1];
		for (size_t i = 0; i < temp.size(); i++) {
			result[i] = temp[i];
		}
		result[temp.size()] = '\0';
		return result;
	}

	struct Game {
		char title[MAX_TITLE_SIZE];
		double price;
		bool isAvailable;

		Game() : price(0.0), isAvailable(false) {
			title[0] = '\0';
		}

		Game(const char* _title, double _price, bool _isAvailable) : price(_price), isAvailable(_isAvailable) {
			strcpy(title, _title);
		}

		void print() const {
			char* formattedPrice = formatDouble(price, 2);
			std::cout << "Title: " << title << ", Price: " << formattedPrice
				<< ", Available: " << (isAvailable ? "YES" : "NO") << std::endl;
			delete[] formattedPrice;
		}

		bool isFree() const { return price == 0; }
	};

	class GamePlatform {
	private:
		Game* games;
		size_t numberOfGames;
		size_t capacity;

	public:
		GamePlatform(size_t _capacity = DEFAULT_CAPACITY)
			: numberOfGames(0), capacity(_capacity) {
			games = new Game[capacity];
		}

		GamePlatform(const Game* _games, size_t gamesCount, size_t _capacity = DEFAULT_CAPACITY)
			: numberOfGames(0), capacity(_capacity) {
			games = new Game[capacity];
			for (size_t i = 0; i < gamesCount && i < capacity; i++) {
				games[i] = _games[i];
				numberOfGames++;
			}
		}

		~GamePlatform() { delete[] games; }

		void addGame(const Game& game) {
			if (numberOfGames >= capacity) {
				errorAlert("No space to add more games!");
				return;
			}
			games[numberOfGames++] = game;
		}

		void removeGame(const Game& gameToRemove) {
			size_t index = 0;
			while (index < numberOfGames && strcmp(games[index].title, gameToRemove.title) != 0) index++;
			if (index == numberOfGames) {
				errorAlert("Game not found!");
				return;
			}
			for (size_t i = index; i < numberOfGames - 1; i++) games[i] = games[i + 1];
			numberOfGames--;
		}

		Game* getGameByIndex(size_t index) const {
			if (index >= numberOfGames) {
				errorAlert("Index out of bounds!");
				return nullptr;
			}
			return &games[index];
		}

		Game getCheapest() const {
			if (numberOfGames == 0) return Game();
			Game minGame = games[0];
			for (size_t i = 1; i < numberOfGames; i++) {
				if (games[i].price < minGame.price) minGame = games[i];
			}
			return minGame;
		}

		Game getMostExpensive() const {
			if (numberOfGames == 0) return Game();
			Game maxGame = games[0];
			for (size_t i = 1; i < numberOfGames; i++) {
				if (games[i].price > maxGame.price) maxGame = games[i];
			}
			return maxGame;
		}

		Game* getFreeGames(size_t& freeCount) const {
			freeCount = 0;
			for (size_t i = 0; i < numberOfGames; i++) {
				if (games[i].isFree()) freeCount++;
			}
			if (freeCount == 0) return nullptr;

			Game* freeGames = new Game[freeCount];
			size_t idx = 0;
			for (size_t i = 0; i < numberOfGames; i++) {
				if (games[i].isFree()) freeGames[idx++] = games[i];
			}
			return freeGames;
		}

		void save(const char* fileName, const char* padding = "   ") const {
			std::ofstream file(fileName);
			if (!file) {
				errorAlert("Cannot open file!");
				return;
			}
			file << "Capacity: " << capacity << "\n";
			file << "Number Of Games: " << numberOfGames << "\n";
			for (size_t i = 0; i < numberOfGames; i++) {
				char* formattedPrice = formatDouble(games[i].price, 2);
				file << padding << i + 1 << ") Title: " << games[i].title
					<< ", Price: " << formattedPrice
					<< ", Available: " << (games[i].isAvailable ? "YES" : "NO") << "\n";
				delete[] formattedPrice;
			}
		}
	};
}
