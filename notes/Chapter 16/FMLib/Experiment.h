#ifndef B4DB4031_F8F5_4253_8882_185493D590CF
#define B4DB4031_F8F5_4253_8882_185493D590CF

#include "iostream"

class Experiment {
    public:
        Experiment() {
            std::cout << "Default constructor is called" << std::endl;
        }

        ~Experiment() {
            std::cout << "Destructor is called" << std::endl;
        }

        Experiment& operator=(const Experiment& other) {
            std::cout << "Assignment operator is called" << std::endl;
            this->value = other.value;
            return *this;
        }

        Experiment(const Experiment& other) {
            std::cout << "Copy operator is called" << std::endl;
            this->value = other.value;
        }

        double value;
};

void testExperiment1(Experiment exp) {}

Experiment testExperiment2() {
    Experiment a;
    return a;
}

void testExperiment3(Experiment& exp) {
    exp.value = 3;
}

void testExperiment4() {
    Experiment a;
    Experiment b=a;
}

void testExperiment5() {
    Experiment a;
    Experiment b;
    b=a;
}

void testExperiments() {
    // 1
    std::cout << "Test 1" << std::endl;
    { Experiment a; }
    // 2
    std::cout << "Test 2" << std::endl;
    Experiment exp1;
    testExperiment1(exp1);
    // 3
    std::cout << "Test 3" << std::endl;
    testExperiment2();
    // 4
    std::cout << "Test 4" << std::endl;
    testExperiment3(exp1);
    // 5
    std::cout << "Test 5" << std::endl;
    testExperiment4();
    // 6
    std::cout << "Test 6" << std::endl;
    testExperiment5(); 
}

#endif /* B4DB4031_F8F5_4253_8882_185493D590CF */
