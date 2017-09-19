#include <iostream>
#include <openssl/evp.h>

int main() {
    EVP_MD_CTX *ctx;
    EVP_MD_CTX_init(ctx);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}