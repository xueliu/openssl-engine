//
// Created by clock on 01/01/2023.
//
#include "string.h"

#include <bitset>
#include <array>
#include <iostream>
#include <openssl/sha.h>

#include <climits>

template<size_t numBytes>
std::bitset<numBytes * CHAR_BIT> bytesToBitset(uint8_t *data)
{
    std::bitset<numBytes * CHAR_BIT> b;

    for(int i = 0; i < numBytes; ++i)
    {
        uint8_t cur = data[i];
        int offset = i * CHAR_BIT;

        for(int bit = 0; bit < CHAR_BIT; ++bit)
        {
            b[offset] = cur & 1;
            ++offset;   // Move to next bit in b
            cur >>= 1;  // Move to next bit in array
        }
    }

    return b;
}

void sha1Test()
{
    // 1. init
    SHA_CTX ctx;
    SHA1_Init(&ctx);

    // 2. add data
    SHA1_Update(&ctx, "hello", strlen("hello"));
    SHA1_Update(&ctx, ", world", strlen(", world"));

    // 3. calculate hash
    std::array<unsigned char , SHA_DIGEST_LENGTH> md_array{};
    std::array<char , SHA_DIGEST_LENGTH * 2 + 1> md_array_hex{};

    std::array<std::bitset<8U>, SHA_DIGEST_LENGTH> md_bitset_array{};

    SHA1_Final(md_array.begin(), &ctx);
    SHA1_Final(reinterpret_cast<unsigned char *>(md_bitset_array.begin()), &ctx);

    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i)
    {
        sprintf(&md_array_hex[i * 2], "%02x", md_array[i]);
    }

    std::cout << "sha1: " << md_array_hex.data() << std::endl;

//    std::bitset<SHA_DIGEST_LENGTH * 8U> sha1_bits{ md };

//    for(const auto & bits : md)
//    {
//        std::cout << bits;
//    }

    std::cout << std::endl;
}

auto main() -> int {

    sha1Test();

    return 0;
}
