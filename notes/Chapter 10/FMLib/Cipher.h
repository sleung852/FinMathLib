#ifndef AA456024_CB09_4C52_8358_B2AC87A24936
#define AA456024_CB09_4C52_8358_B2AC87A24936

#include "stdafx.h"

class Cipher{
    public:
        virtual ~Cipher();
        virtual std::string encode(std::string msg) = 0;
        virtual std::string decode(std::string encodedMsg) = 0;
};

void testCipher(Cipher& toTest);

#endif /* AA456024_CB09_4C52_8358_B2AC87A24936 */
