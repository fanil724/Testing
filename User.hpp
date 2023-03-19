#ifndef USER_H
#define USER_H

class User {
public:
    User() = default;

    ~User() = default;

    void run() {
        std::cout << "run";
    }

private:
    uint64_t id_;
    string login_;
    string password_;

};

#endif // !USER_H
