#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <string>
#include <vector>
#include <fstream>

using string = std::string;
uint64_t idQuest;

class Quest {
    struct Res {
        string quest_;
        string answer_;
        std::vector<string> reply_;

        Res(string quest, string answer)
                : quest_(std::move(quest)), answer_(std::move(answer)) {};
    };

public:
    Quest();

    Quest(string quest, string answer)
            : question(Res{quest, answer}) {
        ID_ = idQuest;
        idQuest++;
    };

    Quest(int id, string quest, string answer)
            : question(Res{quest, answer}), ID_(id) {};

    void add_answer_options(string answer) {
        question.reply_.push_back(answer);
    }

    void printQuest() {
        std::cout << "\n" << ID_ << "\n";
        std::cout << question.quest_ << "\n";
        std::cout << "Answer options: \n";
        int number = 1;
        for (string i: question.reply_) {
            std::cout << number++ << ". " << i << "\n";
        }
    }

    void answer(int options) {
        answer_ = options;
        answer_given_ = true;
        if ((question.answer_.compare(question.reply_[options - 1])) == 0) {
            setGrade(5.0);
        } else {
            setGrade(2.0);
        }
    }

    const double &getgrade() const {
        return grade_;
    }

    const int &getanswer() const {
        return answer_;
    }

    const bool &getanswer_given() const {
        return answer_given_;
    }

    void setGrade(double grade) {
        grade_ = grade;
    }

    void saveTest() {
        std::fstream file("Test.txt", std::ios::app);
        if (file.is_open()) {
            file << ID_ << ":::" << question.answer_ << ":::" << question.quest_;
            for (auto i: question.reply_) {
                file << ":::" << i;
            }
            file << "\n";
        }
        file.close();
    }

    static void loadTest(std::vector<Quest> &test) {
        string s;
        std::fstream file("Test.txt", std::ios::in);
        if (file.is_open()) {
            while (std::getline(file, s)) {
                int id = std::stoi(s.substr(0, s.find(":::")));
                s.erase(0,s.find(":::")+3);
                string answer = s.substr(0, s.find(":::"));
                s.erase(0,s.find(":::")+3);
                string quest = s.substr(0, s.find(":::"));
                s.erase(0,s.find(":::")+3);
                Quest q(id, answer, quest);
                while (!s.empty()) {
                    string option = s.substr(0, s.find(":::"));
                    q.add_answer_options(option);
                    if(s.find(":::")==-1){
                        break;
                    }
                    s.erase(0,s.find(":::")+3);
                }
                test.push_back(q);
            }
        }
        file.close();
    }

private:
    uint64_t ID_;
    Res question;
    bool answer_given_ = false;
    int answer_;
    double grade_ = 0.0;
};

#endif // !QUESTIONS_H