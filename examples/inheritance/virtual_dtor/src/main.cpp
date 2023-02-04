#include <iostream>
#include <string>

using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;

#include <fmt/core.h>

constexpr std::string_view separatorStr = "---------------------------------------------------------------------------"sv;
constexpr std::string_view separatorStr2 = "==========================================================================="sv;
constexpr std::string_view separatorStr3 = "--------------X--------------X------------X--------------X-----------------"sv;

class CorrectA {
    std::string _name;

public:
    CorrectA(std::string_view name) : _name{name} {
        fmt::print("{}; CorrectA::CorrectA()\n", _name);
    }
    virtual ~CorrectA() {
        fmt::print("{}; CorrectA::~CorrectA()\n", _name);
    }
};

class CorrectB : public CorrectA {
    std::string _name;

public:
    CorrectB(std::string_view name) : CorrectA{name}, _name{name} {
        fmt::print("{}; CorrectB::CorrectB()\n", _name);
    }
    ~CorrectB() override {
        fmt::print("{}; CorrectB::~CorrectB\n", _name);
    }
    virtual void f() {}
};

class CorrectC : public CorrectA {
    std::string _name;

public:
    CorrectC(std::string_view name) : CorrectA{name}, _name{name} {
        fmt::print("{}; CorrectC::CorrectC()\n", _name);
    }
    ~CorrectC() override {
        fmt::print("{}; CorrectC::~CorrectC()\n", _name);
    }
};

class IncorrectA {
    std::string _name;

public:
    IncorrectA(std::string_view name) : _name{name} {
        fmt::print("{}; IncorrectA::IncorrectA()\n", _name);
    }
    ~IncorrectA() {
        fmt::print("{}; IncorrectA::~IncorrectA()\n", _name);
    }
};

class IncorrectB : public IncorrectA {
    std::string _name;

public:
    IncorrectB(std::string_view name) : IncorrectA{name}, _name{name} {
        fmt::print("{}; IncorrectB::IncorrectB()\n", _name);
    }
    ~IncorrectB() {
        fmt::print("{}; IncorrectB::~IncorrectB()\n", _name);
    }
};

class IncorrectC : public IncorrectA {
    std::string _name;

public:
    IncorrectC(std::string_view name) : IncorrectA{name}, _name{name} {
        fmt::print("{}; IncorrectC::IncorrectC()\n", _name);
    }
    ~IncorrectC() {
        fmt::print("{}; IncorrectC::~IncorrectC()\n", _name);
    }
};

int main() {
    fmt::print("{}\n", separatorStr);
    fmt::print("| Virtual Destructor\n");
    fmt::print("{}\n", separatorStr);

    fmt::print("Demonstrating an example of virtual destructor. Why it is required.\n"
               "What is its use and how to use it.\n"
               "There are 2 sets of class A, B & C respectively Correct & Incorrect.\n");

    fmt::print("{}\n", separatorStr2);

    {
        fmt::print("Example of correct versions of class A, B & C\n");
        CorrectA *ptrA = new CorrectA{"ptrA"};
        CorrectB *ptrB = new CorrectB{"ptrB"};
        CorrectC *ptrC = new CorrectC{"ptrC"};
        CorrectA *ptrBtoA = new CorrectB{"ptrBtoA"};
        CorrectA *ptrCtoA = new CorrectC{"ptrCtoA"};

        fmt::print("\n");

        fmt::print("Going out of scope...\n");
        fmt::print("{}\n", separatorStr2);

        delete ptrCtoA;
        delete ptrBtoA;
        delete ptrC;
        delete ptrB;
        delete ptrA;
    }
    fmt::print("{}\n", separatorStr3);

    fmt::print("\n");

    {
        fmt::print("Example of incorrect versions of class A, B & C\n");
        IncorrectA *ptrA = new IncorrectA("ptrA");
        IncorrectB *ptrB = new IncorrectB("ptrB");
        IncorrectC *ptrC = new IncorrectC("ptrC");
        IncorrectA *ptrBtoA = new IncorrectB{"ptrBtoA"};
        IncorrectA *ptrCtoA = new IncorrectC{"ptrCtoA"};

        fmt::print("\n");

        fmt::print("Going out of scope...\n");
        fmt::print("{}\n", separatorStr2);

        delete ptrCtoA;
        delete ptrBtoA;
        delete ptrC;
        delete ptrB;
        delete ptrA;
    }
    fmt::print("{}\n", separatorStr3);


    return 0;
}
