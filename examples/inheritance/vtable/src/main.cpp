#include <iostream>
#include <string>

using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;

#include <fmt/core.h>

constexpr std::string_view separatorStr = "---------------------------------------------------------------------------"sv;
constexpr std::string_view separatorStr2 = "==========================================================================="sv;
constexpr std::string_view separatorStr3 = "--------------X--------------X------------X--------------X-----------------"sv;

class CorrectA {
    std::string _inheritedBy;

public:
    CorrectA(std::string_view inheritedBy = "None"sv) : _inheritedBy{inheritedBy} {
        fmt::print("A::A(); inherited by {}\n", _inheritedBy);
    }

    ~CorrectA() {
        fmt::print("A::~A(); inherited by {}\n", _inheritedBy);
    }

    virtual void sayA() {
        fmt::print("A::sayA()\n");
    }

    virtual void sayB() {
        fmt::print("A::sayB()\n");
    }
    virtual void sayC() {
        fmt::print("A::sayC()\n");
    }
};

class CorrectB : public CorrectA {
    std::string _inheritedBy;

public:
    CorrectB(std::string_view inheritedBy = "None"sv) : CorrectA{"B"sv}, _inheritedBy{inheritedBy} {
        fmt::print("B::B(); inherited by {}\n", _inheritedBy);
    }

    ~CorrectB() {
        fmt::print("B::~B; inherited by {}\n", _inheritedBy);
    }

    void sayA() override {
        fmt::print("B::sayA()\n");
    }
    void sayC() override {
        fmt::print("B::sayC()\n");
    }
};

class CorrectC : public CorrectA {
    std::string _inheritedBy;

public:
    CorrectC(std::string_view inheritedBy = "None"sv) : CorrectA{"C"sv}, _inheritedBy{inheritedBy} {
        fmt::print("C::C(); inherited by {}\n", _inheritedBy);
    }

    ~CorrectC() {
        fmt::print("C::~C() ; inherited by {}\n", _inheritedBy);
    }

    void sayA() override {
        fmt::print("C::sayA()\n");
    }

    void sayB() override {
        fmt::print("C::sayB()\n");
    }
};


int main() {
    fmt::print("{}\n", separatorStr);
    fmt::print("| Inheritance VTable\n");
    fmt::print("{}\n", separatorStr);

    // Stack
    {
        fmt::print("Example 1 : Allocation on stack.\n");
        fmt::print("{}\n", separatorStr2);
        fmt::print("Creating instance of class A on stack\n");
        CorrectA instA;
        fmt::print("Creating instance of class B on stack\n");
        CorrectB instB;
        fmt::print("Creating instance of class C on stack\n");
        CorrectC instC;

        fmt::print("\n");

        fmt::print("Calling  A::sayA\n");
        instA.sayA();
        fmt::print("Calling  A::sayB\n");
        instA.sayB();
        fmt::print("Calling  A::sayC\n");
        instA.sayC();

        fmt::print("\n");

        fmt::print("Calling  B::sayA\n");
        instB.sayA();
        fmt::print("Calling  B::sayB\n");
        instB.sayB();
        fmt::print("Calling  B::sayC\n");
        instB.sayC();

        fmt::print("\n");

        fmt::print("Calling  C::sayA\n");
        instC.sayA();
        fmt::print("Calling  C::sayB\n");
        instC.sayB();
        fmt::print("Calling  C::sayC\n");
        instC.sayC();

        fmt::print("Example 1 end...\n");
        fmt::print("{}\n", separatorStr2);
    }
    fmt::print("{}\n", separatorStr3);

    // Heap with shared pointer
    {
        fmt::print("Example 2 : Allocation on heap(shared_pointer).\n");
        fmt::print("{}\n", separatorStr2);
        fmt::print("Creating instance of class A on heap(shared_pointer)\n");
        std::shared_ptr<CorrectA> ptrA = std::make_shared<CorrectA>();
        fmt::print("Creating instance of class B on heap(shared_pointer)\n");
        std::shared_ptr<CorrectB> ptrB = std::make_shared<CorrectB>();
        fmt::print("Creating instance of class C on heap\n");
        std::shared_ptr<CorrectC> ptrC = std::make_shared<CorrectC>();
        fmt::print("Casting B pointer to pointer A\n");
        std::shared_ptr<CorrectA> ptrBtoA = std::dynamic_pointer_cast<CorrectA>(ptrB);
        fmt::print("Casting C pointer to pointer A\n");
        std::shared_ptr<CorrectA> ptrCtoA = std::dynamic_pointer_cast<CorrectA>(ptrC);

        fmt::print("\n");

        fmt::print("Calling all methods of ptrA one by one.\n");
        fmt::print("Calling  A::sayA\n");
        ptrA->sayA();
        fmt::print("Calling  A::sayB\n");
        ptrA->sayB();
        fmt::print("Calling  A::sayC\n");
        ptrA->sayC();

        fmt::print("\n");

        fmt::print("Calling all methods of ptrB one by one.\n");
        fmt::print("Calling  B::sayA\n");
        ptrB->sayA();
        fmt::print("Calling  B::sayB\n");
        ptrB->sayB();
        fmt::print("Calling  B::sayC\n");
        ptrB->sayC();

        fmt::print("\n");

        fmt::print("Calling all methods of ptrC one by one.\n");
        fmt::print("Calling  C::sayA\n");
        ptrC->sayA();
        fmt::print("Calling  C::sayB\n");
        ptrC->sayB();
        fmt::print("Calling  C::sayC\n");
        ptrC->sayC();

        fmt::print("\n");

        fmt::print("Calling all methods of ptrBtoA one by one.\n");
        fmt::print("Calling  B::sayA\n");
        ptrBtoA->sayA();
        fmt::print("Calling  B::sayB\n");
        ptrBtoA->sayB();
        fmt::print("Calling  B::sayC\n");
        ptrBtoA->sayC();

        fmt::print("\n");

        fmt::print("Calling all methods of ptrCtoA one by one.\n");
        fmt::print("Calling  C::sayA\n");
        ptrCtoA->sayA();
        fmt::print("Calling  C::sayB\n");
        ptrCtoA->sayB();
        fmt::print("Calling  C::sayC\n");
        ptrCtoA->sayC();

        fmt::print("Example 2 end...\n");
        fmt::print("{}\n", separatorStr2);
    }
    fmt::print("{}\n", separatorStr3);

    std::getchar();
    return 0;
}
