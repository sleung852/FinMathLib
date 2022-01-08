#include "Cipher.h"

using namespace std;

void testCipher(Cipher& toTest) {
    string msg("Testing string");
    ASSERT( toTest.decode(toTest.encode(msg)) == msg);
}

