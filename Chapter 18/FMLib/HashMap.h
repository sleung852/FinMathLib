#ifndef D49E5F28_F17D_459B_B97B_A7455043B936
#define D49E5F28_F17D_459B_B97B_A7455043B936

#include "stdafx.h"

class HashMap {
    public:
        void store(std::string key, std::string value) {
            int hashKey = computeHashKey(key);
            int targetKeyInd = getHashKeyId(hashKey, key);

            if (targetKeyInd == -1) {
                std::pair<std::string, std::string > dataPoint(key, value);
                keyHashValues[hashKey].push_back(dataPoint);
            } else {
                keyHashValues[hashKey][targetKeyInd].second = value;
            }
        }

        std::string get(std::string key) {
            int hashKey = computeHashKey(key);
            int targetKeyInd = getHashKeyId(hashKey, key);

            if (targetKeyInd == -1) {
                throw("Key does not exist!");
            } 
            return keyHashValues[hashKey][targetKeyInd].second;

        }

        HashMap() {
            for (int i=0; i<100; i++) {
                keyHashValues.push_back(std::vector<std::pair<std::string, std::string > >()); 
            }
        }

    private:
        std::vector<std::vector<std::pair<std::string, std::string > > > keyHashValues;

        int getHashKeyId(int hashKey, std::string queryKey) {
            // iterator within the targetted hashKey bin
            auto itKey = keyHashValues[hashKey].begin();
            int ind = 0;
            while (itKey != keyHashValues[hashKey].end()) {
                if (itKey->first == queryKey) return ind;
                ind++;
                itKey += ind;
            }
            return -1;
        }

        int computeHashKey (std::string key) {
            int hash = 0;
            auto iC = key.c_str();
            auto stopC = iC+key.size();
            while (iC != stopC) {
                hash += static_cast<int>(*iC) % 100;
                iC++;
            }
            return hash%100;
        }
};

void testHashMapSimple() {
    HashMap hashMap;
    hashMap.store("apple", "red");
    hashMap.store("orange", "orange");
    hashMap.store("pineapple", "yellow");
    hashMap.store("grape", "purple");
    hashMap.store("coconut", "white");

    std::cout << "Get apple: " << hashMap.get("apple") << std::endl;
    std::cout << "Get coconut: " << hashMap.get("coconut") << std::endl;
    // std::cout << "Get banana: " << hashMap.get("banana") << std::endl; // expect error
}

void testHashMap() {
    TEST(testHashMapSimple);
}

#endif /* D49E5F28_F17D_459B_B97B_A7455043B936 */
