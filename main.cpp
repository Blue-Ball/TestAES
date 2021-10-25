#include <iostream>
#include <sstream>
#include <string>
#include "include/aes.hpp"

using namespace std;

struct AES_ctx ctx;

// Convert HEX string to bytes array
void string2bytes(uint8_t target[], const string& str_val){
    stringstream converter;
    for(int i = 0; i < str_val.length(); i += 2) {
        converter << std::hex << str_val.substr(i,2);
        int byte;
        converter >> byte;
        target[i / 2] = byte & 0xFF;
        converter.str(std::string());
        converter.clear();
    }
}

void ascii2bytes(uint8_t target[], const string& str_val) {
    char* pTemp = (char *)str_val.c_str();
    for (int i = 0; i < str_val.length(); i ++) {
        target[i] = pTemp[i];
    }
}

int main(int argc, char* argv[]) {

    string str_key = "1234567890abcdef1234567890abcdef";
    uint8_t b_key[str_key.length() / 2];
    ascii2bytes(b_key, str_key);

    string str_iv = "e8b253d9da019dd1dbec3afbf792e5ea";
    uint8_t b_iv[str_iv.length() / 2];
    string2bytes(b_iv, str_iv);

    string encrypted = "c85a35d411122182235baa5923148b0e3c2a9a6f12eb7b56491e745ce9d41585";

    uint8_t enc_msg[encrypted.length() / 2];
    string2bytes(enc_msg, encrypted);

    AES_init_ctx_iv(&ctx, b_key, b_iv);

    AES_CBC_decrypt_buffer(&ctx, enc_msg, encrypted.length()/2);

    cout << enc_msg << endl;

    return 0;
}