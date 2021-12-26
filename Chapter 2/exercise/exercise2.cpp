#include <iostream>
#include <cmath>

using namespace std;

// 2.5.5
char convert_to_capitial(char inputChar) {
    int inputCharInInt = static_cast<int>(inputChar);
    if (inputCharInInt >= 97 && inputCharInInt <= 122) {
        return static_cast<char>(inputCharInInt-32);
    }
    else if (inputCharInInt >= 65 && inputCharInInt <=90) {
        return inputChar;
    }
    return '?'; // <- debug
}

// 2.5.6
int round_float(float inputFloat) {
    if (static_cast<int>(inputFloat * 10)%10 >=5) {
        return static_cast<int>(inputFloat) + 1;
    }
    else {
        return static_cast<int>(inputFloat);
    }
}

int main() {
    // 2.5.1
    cout << "Exercise 2.5.1\n";
    cout << "true || false: " << (true || false) << endl; // 1
    cout << "(true && false) || true: " << ((true && false) || true) << endl; // 0
    cout << "true && (false || true): " << (true && (false || true)) << endl; // 1
    cout << "true && false || true: " << (true || false) << endl; // 0
    cout << "3*5==15 && (7*8==21 || true!=false): " << (3*5==15 && (7*8==21 || true!=false)) << endl; // 1?
    // moral of the story is to use brackets!
    cout << endl;

    // 2.5.2
    cout << "Exercise 2.5.2\n";
    cout << "sizeof bool: " << sizeof(bool) << endl;
    cout << "sizeof size_t: " << sizeof(size_t) << endl;
    cout << "sizeof char: " << sizeof(char) << endl;
    cout << "sizeof int: " << sizeof(int) << endl;
    cout << "sizeof unsigned int: " << sizeof(unsigned int) << endl;
    cout << "sizeof long: " << sizeof(long) << endl;
    cout << "sizeof long long: " << sizeof(long long) << endl;
    cout << "sizeof float: " << sizeof(float) << endl;
    cout << "sizeof double: " << sizeof(double) << endl;
    cout << endl;

    // 2.5.3
    cout << "Exercise 2.5.3\n";
    cout << "int value of 'a': " << static_cast<int>('a') << endl;
    cout << "int value of 'z': " << static_cast<int>('z') << endl;
    cout << "int value of 'A': " << static_cast<int>('A') << endl;
    cout << "int value of 'Z': " << static_cast<int>('Z') << endl;
    cout << "int value of '0': " << static_cast<int>('0') << endl;
    cout << "int value of '9': " << static_cast<int>('9') << endl;
    cout << "int value of '\\n': " << static_cast<int>('\n') << endl;
    cout << "int value of '\\t': " << static_cast<int>('\t') << endl;
    cout << "int value of '\\r': " << static_cast<int>('\r') << endl;
    cout << endl;

    //2.5.4
    cout << "Exercise 2.5.4\n";
    unsigned int a = 5; // 
    unsigned int b = 3; // binary: 011
    cout << "unsigned difference: 5 - 3 = " << a-b << endl; // binary 
    /*
    bin(5) = 101
    bin(3) = 011
    (-)---------
    bin(2) = 010
    */
   cout << "unsigned difference: 3 - 5 = " << b-a << endl; // binary
    /*
    bin(3) = 0000....011
    bin(5) = 0000....101
    (-)-----------------
    bin(2) = 1000....010
    which is why the value is large!!
    */

    cout << endl;

    // 2.5.5
    cout << "Exercise 2.5.5\n";
    // see above for function definition
    cout << "Converting 'b': " << convert_to_capitial('b') << endl;
    cout << "Converting 'y': " << convert_to_capitial('y') << endl;
    cout << "Converting 'K': " << convert_to_capitial('K') << endl;
    cout << "Converting 'L': " << convert_to_capitial('L') << endl;
    cout << endl;

    // 2.5.6
    cout << "Exercise 2.5.6\n";
    float x = 4.32;
    float y = 4.78;
    cout << "Using custom functions:\n";
    cout << "Rounding " << x << ": " << round_float(x) << endl;
    cout << "Rounding " << y << ": " << round_float(y) << endl;
    cout << "Using cmath functions:\n";
    cout << "Rounding " << x << ": " << round(x) << endl;
    cout << "Rounding " << y << ": " << round(y) << endl;
    cout << endl;

    // 2.5.7
    /*
    (a)
    line 9 and line 11 needs static_cast<int>(*)
    (b)
    fixing line 12 (player1=player2)
    with (player1==player2)
    */

    // 2.5.8
    cout << "Exercise 2.5.8\n";
    int x1 = -1;
    unsigned int x2 =0;
    cout << "Is int(-1) less than unsigned int(0): " << (x1 < x2) << endl;
    /*
    In short because unsigned int(0) starts at 0 of 2^n where as int(-1) starts at 2^n / 2 - 1
    Therefore, int(-1) is greater than int(0)
    */
    cout << endl;

    // 2.5.9
    cout << "Exercise 2.5.8\n";
    cout << "Printing bell char" << endl;
    cout << '\a' << endl; // only works in terminal but not in VS code
}