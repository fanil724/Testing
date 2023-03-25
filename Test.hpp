#ifndef TEST_H
#define TEST_H

#include"Questions.hpp"

class Test {
public:
    Test() {};

    Test(string name) : name_(std::move(name)) {};

    ~Test() = default;

    void add(Quest &quest) {
        test_.push_back(quest);
        idQewst_.push_back(quest.getIDQuest());
    }

    [[nodiscard]] const string &getname() const {
        return name_;
    }

    [[nodiscard]] const std::vector<Quest> &getTest() const {
        return test_;
    }

    void loadTest(const string &nam) {
        string s;
        std::fstream file("Test.txt", std::ios::in);
        if (file.is_open()) {
            while (std::getline(file, s)) {
                name_ = s.substr(0, s.find(":::"));
                if (nam.compare(name_) == 0) {
                    s.erase(0, s.find(":::") + 3);
                    do {
                        uint64_t id = std::stoi(s.substr(0, s.find(":::")));
                        s.erase(0, s.find(":::") + 3);
                        idQewst_.push_back(id);
                    } while (s.empty());
                }
            }
        }
        file.close();
        for (auto i: idQewst_) {
            Quest q(i);
            test_.push_back(q);
        }
    }

    void saveTest() {
        std::fstream file("Test.txt", std::ios::app);
        if (file.is_open()) {
            file << name_;
            for (auto i: idQewst_) {
                file << ":::" << i;
            }
            file << "\n";
        }
        file.close();
    }

private:
    string name_;
    std::vector<uint64_t> idQewst_;
    std::vector<Quest> test_;

};

class TestUser {
public:
    TestUser() {};

    TestUser(string name) : name_(std::move(name)) {};

    ~TestUser() = default;

    void add(Quest &quest) {
        test_.push_back(quest);
        idQewst_.push_back(quest.getIDQuest());
    }

    void ScoreCalculation() {
        int count = 1;
        double grade = 0;
        for (QuestUser i: test_) {
            grade += i.getgrade();
            std::cout << i.getgrade() << " ";
            count++;
        }
        gradeTest_ = (grade / count);
    }

    void BeginTest() {
        int number = -1;
        for (auto i = test_.begin(); i != test_.end(); i++) {
            system("cls");
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
        endTest();
        std::cout << "Grade: " << gradeTest_ << "\n";
    }

    void endTest() {
        int count = 0;
        for (auto i: test_) {
            if (i.getgrade() == 5.0) {
                count++;
            }
        }
        std::cout << " Correct answers: " << count << "/" << test_.size() << "\n";
    }

    [[nodiscard]] const double &getgradeTest() const {
        return gradeTest_;
    }

    [[nodiscard]] const string &getname() const {
        return name_;
    }

    [[nodiscard]] const std::vector<QuestUser> &getTest() const {
        return test_;
    }

    void loadTest(const string &nam) {
        string s;
        std::fstream file("Test.txt", std::ios::in);
        if (file.is_open()) {
            while (std::getline(file, s)) {
                name_ = s.substr(0, s.find(":::"));
                if (nam.compare(name_) == 0) {
                    s.erase(0, s.find(":::") + 3);
                    do {
                        uint64_t id = std::stoi(s.substr(0, s.find(":::")));
                        s.erase(0, s.find(":::") + 3);
                        idQewst_.push_back(id);
                    } while (s.empty());
                }
            }
        }
        file.close();
        for (auto i: idQewst_) {
            Quest q(i);
            test_.push_back(q);
        }
    }

    void saveTest() {
        std::fstream file("Test.txt", std::ios::app);
        if (file.is_open()) {
            file << name_;
            for (auto i: idQewst_) {
                file << ":::" << i;
            }
            file << "\n";
        }
        file.close();
    }

    void printTest() {
        std::cout << "Name test: " << name_ << "\n";
        std::cout << "Grade: " << gradeTest_ << "\n";
        endTest();
    }

private:
    string name_;
    std::vector<uint64_t> idQewst_;
    std::vector<QuestUser> test_;
    double gradeTest_ = 0.0;
};

class Chapter {
public:
    Chapter() {}

    void add_in_Chapter(const string &name) {
        name_test_.push_back(name);
    }

    ~Chapter() = default;

    void printChapter() {
        int coutn = 1;
        std::cout << "Name test.\n";
        for (auto i: name_test_) {
            std::cout << coutn << "." << i << "\n";
            coutn++;
        }
    }

    string &getNameTest(int index) {
        return name_test_[index - 1];
    }

    void save() {
        std::fstream file("Chapter.txt", std::ios::out);
        if (file.is_open()) {
            for (auto i: name_test_) {
                file << i << ":::";
            }
            file << "\n";
        }
    }

    Test &getTest() {
        return testing_;
    }

    void LoadTest(const string &name) {
        testing_.loadTest(name);
    }

private:
    std::vector<string> name_test_;
    Test testing_;

};

#endif // !TEST_H