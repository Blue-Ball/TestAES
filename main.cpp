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
    uint8_t b_key[str_key.length()];
    ascii2bytes(b_key, str_key);

    string str_iv = "7faa71dbb2c24faca6753e4291e72c0b";
    uint8_t b_iv[str_iv.length() / 2];
    string2bytes(b_iv, str_iv);

    string encrypted = "44a31baf1e2fc5bbaf04ba21586fcb24";

    uint8_t enc_msg[encrypted.length() / 2];
    string2bytes(enc_msg, encrypted);

    AES_init_ctx_iv(&ctx, b_key, b_iv);

    AES_CBC_decrypt_buffer(&ctx, enc_msg, encrypted.length()/2);

    // FIXME: This should output "Hello"
    cout << enc_msg << endl;

    return 0;
}