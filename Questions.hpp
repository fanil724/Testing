#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <string>
#include <utility>
#include <vector>
#include <fstream>

using string = std::string;
uint64_t idQuest = 0;

class Quest {
public:
    void loadQuest();

    struct Res {
        string quest_;
        string answer_;
        std::vector<string> reply_;

        Res() = default;

        Res(string quest, string answer)
                : quest_(std::move(quest)), answer_(std::move(answer)) {};
    };

    Quest() = default;

    Quest(uint64_t id) {
        loadQuest(id);
    };

    Quest(string quest, string answer)
            : question(Res{std::move(quest), std::move(answer)}) {

        ID_ = idQuest;
        idQuest++;
    };

    Quest(int id, string quest, string answer)
            : question(Res{std::move(quest), std::move(answer)}), ID_(id) {};

    ~Quest() = default;


    void add_answer_options(const string &answer) {
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

    void printListQuest() {
        string s;
        std::fstream file("Quest.txt", std::ios::in);
        if (file.is_open()) {
            while (std::getline(file, s)) {
                int id = std::stoi(s.substr(0, s.find(":::")));
                s.erase(0, s.find(":::") + 3);
                std::cout << "ID:" << id;
                s.erase(0, s.find(":::") + 3);
                string quest = s.substr(0, s.find(":::"));
                s.erase(0, s.find(":::") + 3);
                std::cout << "Quewst: " << quest << "\n";
            }
        }
        file.close();
    }


    [[nodiscard]]  int getIDQuest() const {
        return ID_;
    }

    [[nodiscard]] const string &getQuest() const {
        return question.quest_;
    }

    [[nodiscard]] const string &getAnswer() const {
        return question.answer_;
    }

    [[nodiscard]] const std::vector<string> &getReply() const {
        return question.reply_;
    }

    void saveQuest() {
        std::fstream file("Quest.txt", std::ios::app);
        if (file.is_open()) {
            file << "\n" << ID_ << ":::" << question.answer_ << ":::" << question.quest_;
            for (const auto &i: question.reply_) {
                file << ":::" << i;
            }
            file << "\n";
        }
        file.close();
    }

    void loadQuest(uint64_t ID) {
        string s;
        std::fstream file("Quest.txt", std::ios::in);
        if (file.is_open()) {
            while (std::getline(file, s)) {
                uint64_t id = std::stoi(s.substr(0, s.find(":::")));
                if (id == ID) {
                    s.erase(0, s.find(":::") + 3);
                    string answer = s.substr(0, s.find(":::"));
                    s.erase(0, s.find(":::") + 3);
                    string quest = s.substr(0, s.find(":::"));
                    s.erase(0, s.find(":::") + 3);
                    Quest q(id, answer, quest);
                    while (!s.empty()) {
                        string option = s.substr(0, s.find(":::"));
                        q.add_answer_options(option);
                        if (s.find(":::") == -1) {
                            break;
                        }
                        s.erase(0, s.find(":::") + 3);
                    }
                }
            }
        }
        file.close();
    }

protected:
    uint64_t ID_;
    Res question;

};


class QuestUser : public Quest {
public:
    QuestUser(const Quest &quest) : Quest(quest.getIDQuest(), quest.getQuest(), quest.getAnswer()) {
        question.reply_ = quest.getReply();
    }

    QuestUser(int id, string quest, string answer, bool answer_given, int answers, double grade)
            : Quest(id, std::move(quest), std::move(answer)), answer_given_(answer_given), answer_(answers),
              grade_(grade) {};


    [[nodiscard]] const double &getgrade() const {
        return grade_;
    }

    [[nodiscard]] const int &getanswer() const {
        return answer_;
    }

    [[nodiscard]] const bool &getanswer_given() const {
        return answer_given_;
    }

    void setGrade(double grade) {
        grade_ = grade;
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

    void saveQuest() {
        std::fstream file("QuestUser.txt", std::ios::app);
        if (file.is_open()) {
            file << ID_ << ":::" << question.answer_ << ":::" << question.quest_ << ":::" << answer_given_ << ":::"
                 << answer_ << ":::" << grade_;
            for (auto i: question.reply_) {
                file << ":::" << i;
            }
            file << "\n";
        }
        file.close();
    }

    void loadQuest(uint64_t ID) {
        string s;
        std::fstream file("QuestUser.txt", std::ios::in);
        if (file.is_open()) {
            while (std::getline(file, s)) {
                uint64_t id = std::stoi(s.substr(0, s.find(":::")));
                if (id == ID) {
                    s.erase(0, s.find(":::") + 3);
                    string answer = s.substr(0, s.find(":::"));
                    s.erase(0, s.find(":::") + 3);
                    string quest = s.substr(0, s.find(":::"));
                    s.erase(0, s.find(":::") + 3);
                    bool answer_given;
                    string booling = s.substr(0, s.find(":::"));
                    if (booling == "1")
                        answer_given = true;
                    else if (booling == "0")
                        answer_given = false;

                    s.erase(0, s.find(":::") + 3);
                    int answers = std::stoi(s.substr(0, s.find(":::")));
                    s.erase(0, s.find(":::") + 3);
                    double grade = std::stod(s.substr(0, s.find(":::")));
                    s.erase(0, s.find(":::") + 3);
                    QuestUser qu(id, answer, quest, answer_given, answers, grade);
                    while (!s.empty()) {
                        string option = s.substr(0, s.find(":::"));
                        qu.add_answer_options(option);
                        if (s.find(":::") == -1) {
                            break;
                        }
                        s.erase(0, s.find(":::") + 3);
                    }
                }
            }
        }
        file.close();
    }

    void printQuestUser() {
        std::cout << "\n" << ID_ << "\n";
        std::cout << question.quest_ << "\n";
        std::cout << "\n" << question.reply_[answer_] << "\n";
        std::cout << "\nGrade: " << grade_ << "\n";


    }

private:
    bool answer_given_ = false;
    int answer_;
    double grade_ = 0.0;
};

#endif // !QUESTIONS_H