#ifndef TEST_H
#define TEST_H

#include"Questions.hpp"

class Test {
public:
    void add(Quest &quest) {
        test_.push_back(quest);
    }

    void BeginTest() {
        int number;
        for (Quest i: test_) {
            i.printQuest();
            std::cout << "Enter an answer option:";
            std::cin >> number;
            i.answer(number);
        }
    }


private:
    std::vector<Quest> test_;

};

#endif // !TEST_H