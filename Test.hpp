#ifndef TEST_H
#define TEST_H

#include"Questions.hpp"

class Test {
public:
	Test(string name) : name_(std::move(name)) {};

	~Test() = default;

	void add(Quest& quest) {
		test_.push_back(quest);
		idQewst_.push_back(quest.getIDQuest());
	}

	void ScoreCalculation() {
		int count = 1;
		double grade = 0;
		for (QuestUser i : test_) {
			grade += i.getgrade();
			std::cout << i.getgrade() << " ";
			count++;
		}
		gradeTest_ = (grade / count);
	}

	void BeginTest() {
		int number = -1;
		for (auto i = test_.begin(); i != test_.end(); i++) {
			// system("cls");
			if (i->getanswer_given()) {
				continue;
			}
			std::cout << "0. Test exit!!!!";
			i->printQuest();
			std::cout << "Enter an answer option:";
			std::cin >> number;
			if (number == 0) {
				std::cout << "You interrupted the test, you can resume at any time!!";
				break;
			}
			i->answer(number);
		}
		ScoreCalculation();
	}


	const double& getgradeTest() const {
		return gradeTest_;
	}

	const string& name() const {
		return name_;
	}

	const std::vector<QuestUser>& getTest() const {
		return test_;
	}

	void loadTest() {
		string s;
		std::fstream file("Test.txt", std::ios::in);
		if (file.is_open()) {
			name_ = s.substr(0, s.find(":::"));
			s.erase(0, s.find(":::") + 3);
			do {
				uint64_t id = std::stoi(s.substr(0, s.find(":::")));
				s.erase(0, s.find(":::") + 3);
				idQewst_.push_back(id);
			} while (s.empty());
		}
		file.close();
		for (auto i : idQewst_) {
			Quest q;
			q.loadQuest(i);
			test_.push_back(q);
		}
	}
	void saveTest() {
		std::fstream file("Test.txt", std::ios::app);
		if (file.is_open()) {
			file << name_;
			for (auto i : idQewst_) {
				file << ":::" << i;
			}
			file << "\n";
		}
		file.close();
	}

private:
	string name_;
	std::vector<uint64_t> idQewst_;
	std::vector<QuestUser> test_;
	double gradeTest_ = 0.0;
};


class Chapter {
public:
	void add_in_Chapter(Test& test) {
		int number;
		std::cout << "Choose a section: \n";
		std::cout << "1. Physics\n";
		std::cout << "2. Mathematics\n";
		std::cout << "3. Informatics\n";
		std::cout << "4. English\n";
		std::cin >> number;
		switch (number) {
		case '1':
			Fizika_.push_back(test);
			break;
		case '2':
			Mathematics_.push_back(test);
			break;
		case '3':
			Informatics_.push_back(test);
			break;
		case '4':
			Englisha_.push_back(test);
			break;
		default:
			std::cout << "no such section";
		}
	}

private:
	std::vector<Test> Fizika_;
	std::vector<Test> Mathematics_;
	std::vector<Test> Informatics_;
	std::vector<Test> Englisha_;
};

#endif // !TEST_H