#include <iostream>
#include <openssl/evp.h>
using namespace std;

// Generate random 30 char long string.
char* generate_random_string() {
    auto random_string = (char*) malloc (31);
    if (random_string == nullptr) exit (1);

    for(int i = 0;i < 30;i++) {
        random_string[i] = rand() % 26 + 'a';
    }
    random_string[31] = '\0';
    return random_string;
}

int main() {
    EVP_MD_CTX ctx, ctx2;
    EVP_MD_CTX_init(&ctx);
    EVP_MD_CTX_init(&ctx2);
    const EVP_MD *md, *md2;
    unsigned char md_value[EVP_MAX_MD_SIZE], md_value2[EVP_MAX_MD_SIZE];
    unsigned int md_len, md_len2;
    int count = 0;
    srand(time(nullptr) );

    char* initialString = generate_random_string();
    md = EVP_sha1();
    md2 = EVP_sha1();
    cout << "====Testing Collision free property====" << endl;
    cout << "Initial random string " << initialString << endl;
    EVP_DigestInit_ex(&ctx, md, nullptr);
    EVP_DigestUpdate(&ctx, initialString, strlen(initialString));
    EVP_DigestFinal(&ctx, md_value, &md_len);
    cout << "SHA1 hash for initial string −−> ";
    // Print 24 bit hash of original string
    for (int i = 0; i < 3; i++) {
        printf("%x", md_value[i]);
    }
    // Search for a string that hashes to a value with the matching leading 24 bits as the hashed inital string above.
    while(true) {
        bool foundMatch = false;
        EVP_DigestInit_ex(&ctx2, md2, nullptr);
        char* second_string = generate_random_string();
        EVP_DigestUpdate(&ctx2, second_string, strlen(second_string));
        EVP_DigestFinal(&ctx2, md_value2, &md_len2);
        for (int i = 0; i < 3; i++) {
            if (md_value[i] != md_value2[i]) {
                foundMatch = false;
                break;
            }
            foundMatch = true;
        }
        if (foundMatch) {
            cout << endl << "Found string with matching hash: " << second_string << endl;
            for (int i = 0; i < 3; i++) {
                printf("%x", md_value2[i]);
            }
            break;
        }
        count++;
    }
    cout << endl << "Number of trials to find a hash collion: " << count << endl;

    return 0;
}