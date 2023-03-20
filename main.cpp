#include <iostream>
#include "Questions.hpp"
#include "Test.hpp"
#include "User.hpp"

int main() {
//    Quest q("weather", "storm");
//    q.add_answer_options("Havae");
//    q.add_answer_options("Havwofpe");
//    q.add_answer_options("storm");
//    q.add_answer_options("Havae;wojwgruq");
//    q.add_answer_options("Havaelqiwhyutjfk");
//    Quest q1("wather", "stor");
//    q1.add_answer_options("Hav");
//    q1.add_answer_options("Hav");
//    q1.add_answer_options("stor");
//    q1.add_answer_options("Havaeutjfk");
//    Quest q2("wether", "strm");
//    q2.add_answer_options("Havae");
//    q2.add_answer_options("Hwofpe");
//    q2.add_answer_options("strm");
//    q2.add_answer_options("Hawojwgruq");

    Test t;
//    t.add(q);
//    t.add(q1);
//    t.add(q2);
//    t.BeginTest();
//    std::cout << "Grade test: ";
//    std::cout << t.getgradeTest();

    t.load();
    for (auto i: t.getTest()) {
        i.printQuest();
    }
}
