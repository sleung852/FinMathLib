#ifndef EBD072C4_2EC8_4B3D_889A_67FB9736E63C
#define EBD072C4_2EC8_4B3D_889A_67FB9736E63C

#include <random>
#include <memory>

class RandomNumberGenerator {
    public:

        RandomNumberGenerator();

        static void setSeed(int newSeed) {
            seed = newSeed;
        }

        int getSeed() {
            return seed;
        }

        double randomNumber() {
            return generator();
        }

        /* 
        Write a static function on the RandomNumberGenerator class called set-
        Default that sets the current default RandomNumberGenerator instance.
        Note that you should use a shared_ptr<RandomNumberGenerator> as the parameter to setDefault.
        */
        static void setDefault(std::shared_ptr<RandomNumberGenerator> numGen) {
            numGen->setSeed(1234);
        }

        void setAsDefault() {
            RandomNumberGenerator::setSeed(this->seed);
        }

        /*
        Write a static function randUniform on RandomNumberGenerator that allows the user
        to generate a uniformly distributed random number with- out needing to create a RandomNumberGenerator.
        */
        static double randUniform() {
            return generator();
        }

    private:
        static int seed;
        static std::mt19937 generator;
};

#endif /* EBD072C4_2EC8_4B3D_889A_67FB9736E63C */
