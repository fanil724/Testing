#ifndef USER_H
#define USER_H

#include "Test.hpp"

uint64_t iduser = 1;

class User {
public:
    User() = default;

    User(string login, string password, string name, string surname)
            : login_(std::move(login)), password_(std::move(password)), name_(std::move(name)),
              surname_(std::move(surname)) {
        id_ = iduser;
        iduser++;
    }

    User(uint64_t id, string login, string password, string name, string surname)
            : id_(id), login_(std::move(login)), password_(std::move(password)), name_(std::move(name)),
              surname_(std::move(surname)) {}

    User(const User &user) :
            User(user.id_, user.login_, user.password_, user.name_,
                 user.surname_) {}

    User &operator=(const User &user) noexcept {
        User user_copy(user);

        this->swap(user_copy);

        return *this;
    }

    void swap(User &another) noexcept {
        using std::swap;
        swap(another.id_, id_);
        swap(another.login_, login_);
        swap(another.password_, password_);
        swap(another.name_, name_);
        swap(another.surname_, surname_);
    }

    ~User() = default;

    void setLogin(string login) {
        login_ = std::move(login);
    }

    void setPassword(string password) {
        password_ = std::move(password);
    }

    void setName(string name) {
        name_ = std::move(name);
    }

    void setSurname(string surname) {
        surname_ = std::move(surname);
    }

    void setID(uint64_t id) {
        id_ = id;
    }

    void loadIDuser() {
        string s;
        std::fstream file("User.txt", std::ios::in);
        if (file.is_open()) {
            while (std::getline(file, s)) {
                uint64_t id = std::stoi(s.substr(0, s.find(":::")));
                iduser = id;
            }
        }
        file.close();
        iduser++;
    }

    void saveUser() {
        std::fstream file("User.txt", std::ios::app);
        if (file.is_open()) {
            file << id_ << ":::" << login_ << ":::" << password_ << ":::" << name_ << ":::" << surname_ << "\n";
            for (const auto &i: name_test_) {
                file << ":::" << i;
            }
            file << "\n";
        }
        file.close();
    }

    bool loadUser(const string &log, const string &pas) {
        string s;
        std::fstream file("User.txt", std::ios::in);
        if (file.is_open()) {
            while (std::getline(file, s)) {
                uint64_t id = std::stoi(s.substr(0, s.find(":::")));
                s.erase(0, s.find(":::") + 3);
                string login = s.substr(0, s.find(":::"));
                if (log.compare(login) == 0) {
                    s.erase(0, s.find(":::") + 3);
                    string password = s.substr(0, s.find(":::"));
                    if (pas.compare(password) == 0) {
                        s.erase(0, s.find(":::") + 3);
                        string name = s.substr(0, s.find(":::"));
                        s.erase(0, s.find(":::") + 3);
                        string surname = s.substr(0, s.find(":::"));
                        s.erase(0, s.find(":::") + 3);
                        id_ = id;
                        login_ = std::move(login);
                        password_ = std::move(password);
                        name_ = std::move(name);
                        surname_ = std::move(surname);
                        return true;
                    } else { return false; }
                }
            }
            file.close();
        }
        return false;
    };

    uint64_t &getID() {
        return id_;
    }

    string &getLogin() {
        return login_;
    }

    string &getPassword() {
        return password_;
    }

    string &getName() {
        return name_;
    }

    string &getSurName() {
        return surname_;
    }

    void add(const string &name) {
        name_test_.push_back(name);
        string s;
        std::fstream file("UserTest.txt", std::ios::out);
        if (file.is_open()) {
            file << id_ << ":::";
            for (auto i: name_test_) {
                file << i << ":::";
            }
        }
        file.close();
    }

    void loadNamTest() {
        string s;
        std::fstream file("User.txt", std::ios::in);
        if (file.is_open()) {
            std::getline(file, s);
            uint64_t id = std::stoi(s.substr(0, s.find(":::")));
            s.erase(0, s.find(":::") + 3);
            do {
                string name = s.substr(0, s.find(":::"));
                s.erase(0, s.find(":::") + 3);
                name_test_.push_back(name);
            } while (s.empty());
        }
        file.close();
    }

    std::vector<string> &getName_Test() {
        return name_test_;
    }

    TestUser &GetTest() {
        return usertest_;
    }

    void printUser() {
        std::cout << id_ << " - " << login_ << "\n" << name_ << " " << surname_ << "\n";
        int coutn = 1;
        std::cout << "List of passed tests: \n";
        for (auto i: name_test_) {
            std::cout << coutn << ". " << i << "\n";
            coutn++;
        }
    }

private:
    uint64_t id_;
    string login_;
    string password_;
    string name_;
    string surname_;
    Chapter testing_;
    std::vector<string> name_test_;
    TestUser usertest_;
};

class Admin {
public:
    Admin() = default;

    Admin(string login, string password, string name, string surname)
            : login_(std::move(login)), password_(std::move(password)), name_(std::move(name)),
              surname_(std::move(surname)) {}

    ~Admin() = default;

    void loadUser() {
        string s;
        std::fstream file("User.txt", std::ios::in);
        if (file.is_open()) {
            while (std::getline(file, s)) {
                uint64_t id = std::stol(s.substr(0, s.find(":::")));
                s.erase(0, s.find(":::") + 3);
                string login = s.substr(0, s.find(":::"));
                s.erase(0, s.find(":::") + 3);
                string password = s.substr(0, s.find(":::"));
                s.erase(0, s.find(":::") + 3);
                string name = s.substr(0, s.find(":::"));
                s.erase(0, s.find(":::") + 3);
                string surname = s.substr(0, s.find(":::"));
                s.erase(0, s.find(":::") + 3);
                User u(id, login, password, name, surname);
                users_.push_back(u);
            }
        }
        file.close();
    }

    void saveUser() {
        std::fstream file("User.txt", std::ios::out);
        if (file.is_open()) {
            for (User i: users_) {
                file << i.getID() << ":::" << i.getLogin() << ":::" << i.getPassword() << ":::" << i.getName()
                     << ":::"
                     << i.getSurName();
            }
        }
        file.close();
    }

    void setLogin(string login) {
        login_ = std::move(login);
    }

    void setPassword(string password) {
        password_ = std::move(password);
    }

    void setName(string name) {
        name_ = std::move(name);
    }

    void setSurname(string surname) {
        surname_ = std::move(surname);
    }

    void saveAdmin() {
        std::fstream file("Admin.txt", std::ios::out);
        if (file.is_open()) {
            file << id_ << ":::" << login_ << ":::" << password_ << ":::" << name_ << ":::" << surname_;
        }
        file.close();
    }

    bool loadAdmin(const string &log, const string &pas) {
        string s;
        std::fstream file("Admin.txt", std::ios::in);
        if (file.is_open()) {
            std::getline(file, s);
            uint64_t id = std::stol(s.substr(0, s.find(":::")));
            s.erase(0, s.find(":::") + 3);
            string login = s.substr(0, s.find(":::"));
            if (log.compare(login) == 0) {
                s.erase(0, s.find(":::") + 3);
                string password = s.substr(0, s.find(":::"));
                if (pas.compare(password) == 0) {
                    s.erase(0, s.find(":::") + 3);
                    string name = s.substr(0, s.find(":::"));
                    s.erase(0, s.find(":::") + 3);
                    string surname = s.substr(0, s.find(":::"));
                    s.erase(0, s.find(":::") + 3);
                    id_ = id;
                    login_ = std::move(login);
                    password_ = std::move(password);
                    name_ = std::move(name);
                    surname_ = std::move(surname);
                    return true;
                } else {
                    return false;
                }
            } else { return false; }

        }
        file.close();
        return false;
    }

    uint64_t &getID() {
        return id_;
    }

    string &getLogin() {
        return login_;
    }

    string &getPassword() {
        return password_;
    }

    string &getName() {
        return name_;
    }

    string &getSurName() {
        return surname_;
    }

    std::vector<User> &getUser() {
        return users_;
    }


    void printUsersList() {
        int coutn = 1;
        for (auto i: users_) {
            std::cout << coutn << "." << i.getName() << "\n";
            coutn++;
        }
    }

private:
    uint64_t id_ = 0;
    string login_;
    string password_;
    string name_;
    string surname_;
    Chapter testing_;
    std::vector<User> users_;
};

#endif // !USER_H
