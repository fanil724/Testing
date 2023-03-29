#ifndef RUNTESTING_H
#define RUNTESTING_H

#include <iostream>
#include "Questions.hpp"
#include "Test.hpp"
#include "User.hpp"

class RunTesting {
public:
    RunTesting() = default;

    bool is_empty(std::ifstream &pFile) {
        return pFile.peek() == std::ifstream::traits_type::eof();
    }

    void workAdmin() {
        int number = -1;
        string stest, squest, ansew, quest;
        do {
            size_t size = 1;
            int ask = -1;
            int num = -1, choice = -1;
            string login, password;
            //system("cls");
            std::cout << "1. Change administrator username and password.\n";
            std::cout << "2. Test management.\n";
            std::cout << "3. User statistics.\n";
            std::cout << "4. Sign out.\n";
            std::cout << "Select an action:\n";
            std::cin >> number;
            switch (number) {
                case 1:
                    std::cout << "Enter login:\n";
                    std::getline(std::cin, login);
                    admin_.setLogin(login);
                    std::cout << "Enter password:\n";
                    std::getline(std::cin, password);
                    admin_.setPassword(password);
                    break;
                case 2:
                    std::cout << "1. Add test.\n";
                    std::cout << "2. Greate questions for tests.\n";
                    std::cout << "Select an action:\n";
                    std::cin >> choice;
                    switch (choice) {
                        case 1:
                            test_.load();
                            std::cout << "1. Add test.\n2. Add quest in test.\n";
                            std::cin >> num;
                            switch (num) {
                                case 1: {
                                    std::cout << "Enter test name: ";
                                    std::cin >> stest;
                                    Test t(stest);
                                    test_.save(stest);
                                    break;
                                }
                                case 2:
                                    if (test_.getTestName().empty()) {
                                        std::cout << "You don't have tests!!!\n";
                                        break;
                                    }

                                    test_.printChapter();
                                    std::cout << "Select the name of the test to which you want to add questions\n";
                                    std::cin >> num;
                                    Test t(test_.getNameTest(num));
                                    Quest q(0);
                                    do {
                                        q.printListQuest();
                                        std::cout << "Select number ID questa: \n";
                                        std::cin >> num;
                                        q.loadQuest(num);
                                        t.add(q);
                                        std::cout << "I want to add another question(0-no,1-yes):\n";
                                        std::cin >> ask;
                                    } while (ask != 0);
                                    t.saveTest();
                                    break;
                            }
                            break;
                        case 2:
                            std::cout << "Enter the answer to your question: \n";
                            std::getline(std::cin, ansew);
                            std::cout << "Enter the  quest: \n";
                            std::getline(std::cin, quest);
                            Quest q(quest, ansew);
                            q.loadIDQuest();
                            q.setID(idQuest);
                            std::cout << "How many answers will be in your question?: \n";
                            std::cin >> size;
                            for (int i = 0; i < size; i++) {
                                std::cout << "Enter answer options: \n";
                                std::getline(std::cin, squest);
                                q.add_answer_options(squest);
                            }
                            q.saveQuest();
                            std::cout << "You have created a question ID of your question:" << q.getIDQuest() << "\n";
                            break;
                    }
                    break;

                case 3:
                    admin_.loadUser();
                    admin_.printUsersList();
                    std::cout << "Select user";
                    std::cin >> num;
                    admin_.getUser()[num - 1].printUser();
                    break;

                case 4:
                    return;
            }
        } while (true);
    }

    void testingUser() {
        int number = -1;
        int num = 0;
        int nimberi = 1;
        do {
            //   system("cls");
            std::cout << "1. See your previous results.\n";
            std::cout << "2. Take a new test.\n";
            std::cout << "3. Sign out.\n";
            std::cin >> number;
            switch (number) {
                case 1:
                    if (!user_.getName_Test().empty()) {
                        for (auto i: user_.getName_Test()) {
                            std::cout << nimberi << ". " << i << "\n";
                            nimberi++;
                        }
                        std::cout << "Choose test name:\n";
                        std::cin >> num;
                        user_.GetTest().loadTest(user_.getName_Test()[num - 1]);
                        user_.GetTest().printTest();
                    } else {
                        std::cout << "You have not passed the tests\n";
                    }
                    break;
                case 2:
                    test_.load();
                    test_.printChapter();
                    std::cout << "Choose test name:\n";
                    std::cin >> num;
                    test_.LoadTest(test_.getNameTest(num - 1));
                    user_.add(test_.getTest().getname());
                    user_.GetTest().loadTest(test_.getNameTest(num - 1));
                    user_.GetTest().BeginTest();
                    break;
            }
        } while (true);

    }

    void authorization() {
        int num;
        string login, password, name, surname;
        std::ifstream file("Admin.txt");
        if (is_empty(file)) {
            system("cls");
            std::cout << "You are the first user to register as an administrator!\n";
            std::cout << "Enter login:";
            std::cin >> login;
            std::cout << "Enter password:";
            std::cin >> password;
            std::cout << "Enter name:";
            std::cin >> name;
            std::cout << "Enter surname:";
            std::cin >> surname;
            admin_.setLogin(login);
            admin_.setPassword(password);
            admin_.setName(name);
            admin_.setSurname(surname);
            admin_.saveAdmin();
            workAdmin();
        } else {
            do {
                system("cls");
                std::cout << "1. To come in\n" << "2. Registration!\n" << "3. Exit!!!\n";
                std::cin >> num;
                switch (num) {
                    case 1:
                        system("cls");
                        std::cout << "Enter login:";
                        std::cin >> login;
                        std::cout << "Enter password: ";
                        std::cin >> password;
                        if (admin_.loadAdmin(login, password)) {
                            workAdmin();
                        } else if (user_.loadUser(login, password)) {
                            testingUser();
                        } else {
                            std::cout << "Login and password entered incorrectly!!!\n";
                        }
                        break;
                    case 2:
                        system("cls");
                        std::cout << "Enter login:";
                        std::cin >> login;
                        std::cout << "Enter password: ";
                        std::cin >> password;
                        if (!user_.loadUser(login, password)) {
                            std::cout << "Enter name:";
                            std::cin >> name;
                            std::cout << "Enter surname: ";
                            std::cin >> surname;
                            User u(login, password, name, surname);
                            u.loadIDuser();
                            u.setID(iduser);
                            u.saveUser();
                            user_ = u;
                            testingUser();
                        }
                        break;
                    case 3:
                        return;
                }
            } while (true);
            std::cout << "Congratulations, you have entered.\n";
        }
    }

private:
    User user_;
    Admin admin_;
    Chapter test_;
};

#endif // !RUNTESTING_H