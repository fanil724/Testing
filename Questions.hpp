#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <string>
#include <vector>


using string = std::string;

class Quest {
    struct Res {
        string quest_;
        string answer_;
        std::vector<string> reply_;

        Res(string quest, string answer)
                : quest_(std::move(quest)), answer_(std::move(answer)) {};
    };

public:
    Quest(string quest, string answer)
            : question(Res{quest, answer}) {};

    void add_answer_options(string answer) {
        question.reply_.push_back(answer);
    }

    void printQuest() {
        std::cout << question.quest_ << "\n";
        std::cout << "Answer options: \n";
        for (string i: question.reply_) {
            std::cout << "1. " << i << "\n";
        }
    }

    void answer(int options) {
        answer_ = options;
        answer_given = true;
        if ((question.answer_.compare(question.reply_[options])) == 0) {
            grade_ = 5;
        } else {
            grade_ = 2;
        }
    }


private:
    Res question;
    bool answer_given = false;
    int answer_;
    double grade_;
};

#endif // !QUESTIONS_H