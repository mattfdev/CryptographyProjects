#include <iostream>
#include <openssl/evp.h>
#include <cstring>

using namespace std;
static int RANDOM_STRING_LENGTH = 30;

// Generate random 30 char long string.
char* generate_random_string(int length) {
    char* random_string = (char*) malloc (31);
    if (random_string == NULL) exit (1);

    for(int i = 0;i < length;i++) {
        random_string[i] = rand() % 26 + 'a';
    }
    random_string[31] = '\0';
    return random_string;
}

int main(int argc, char *argv[]) {
    EVP_MD_CTX ctx, ctx2;
    EVP_MD_CTX_init(&ctx);
    EVP_MD_CTX_init(&ctx2);
    const EVP_MD *md, *md2;
    unsigned char md_value[EVP_MAX_MD_SIZE], md_value2[EVP_MAX_MD_SIZE];
    unsigned int md_len, md_len2;
    int create_collision_count = 0, one_way_property_count = 0;
    srand(time(NULL) );

    // Rudimentary Hash argument checking.
    if (argc != 2) {
        cout << "6 hex long hash argument not supplied, exiting program.\n";
        return 1;
    }
    char* hash_to_find = argv[1];
    cout << "Looking for hash: " << hash_to_find << endl;
    if (strlen(hash_to_find) != 6) {
        cout << "Hash argument supplied is incorrect length, please supply a 6 hex letter long hash";
        return 1;
    }
    for (int j = 0; j < 6; j++) {
        if (hash_to_find[j] > 'f') {
            cout << "Invalid hash character supplied, please supply letters for hash that are lower than or equal to the hex letter F";
            return 1;
        } else if (isdigit(hash_to_find[j])) {
            cout << "Invalid hash character supplied, don't supply numbers in the hex to find, as specified in the lab requirements.";
            return 1;
        }

    }

    char* initialString = generate_random_string(RANDOM_STRING_LENGTH);
    md = EVP_sha1();
    md2 = EVP_sha1();
    cout << "====Testing Collision free property====" << endl;
    cout << "Finding a collision can take a while, please be patient." << endl;
    cout << "Initial random string " << initialString << endl;
    EVP_DigestInit_ex(&ctx, md, NULL);
    EVP_DigestUpdate(&ctx, initialString, strlen(initialString));
    EVP_DigestFinal(&ctx, md_value, &md_len);
    cout << "SHA1 hash for initial string −−> ";
    // Print 24 bit hash of original string
    for (int i = 0; i < 3; i++) {
        printf("%x", md_value[i]);
    }
    // Search for a string that hashes to a value with the matching leading 24 bits as the hashed initial string above.
    while(true) {
        bool foundMatch = false;
        // Initialize hashing function
        EVP_DigestInit_ex(&ctx2, md2, NULL);
        char* second_string = generate_random_string(RANDOM_STRING_LENGTH);
        EVP_DigestUpdate(&ctx2, second_string, strlen(second_string));
        EVP_DigestFinal(&ctx2, md_value2, &md_len2);

        // Search through both hashes for a non matching value, and if found break out of loop, and hash next random string.
        for (int i = 0; i < 3; i++) {
            if (md_value[i] != md_value2[i]) {
                foundMatch = false;
                break;
            }
            foundMatch = true;
        }
        // If all 24 bits of the two random strings hashes' match, then print success message and continue to part 2.
        if (foundMatch) {
            cout << endl << "Found string with matching hash: " << second_string << " : ";
            for (int i = 0; i < 3; i++) {
                printf("%x", md_value2[i]);
            }
            break;
        }
        create_collision_count++;
    }
    cout << endl << "Number of trials to find a hash collision: " << create_collision_count << endl;

    //Part 2
    cout << endl << "====Testing one way property====" << endl;
    // Search for a random string, that when hashed, will have the same leading 24 bits as the user inputted into the program to find.
    while(true) {
        bool foundMatch = false;
        // Initialize hashing function
        EVP_DigestInit_ex(&ctx2, md2, NULL);
        char* second_string = generate_random_string(RANDOM_STRING_LENGTH);
        EVP_DigestUpdate(&ctx2, second_string, strlen(second_string));
        EVP_DigestFinal(&ctx2, md_value2, &md_len2);

        char hash_charecter_storage[EVP_MAX_MD_SIZE];
        string hash_string_representation;
        // Workaround for OpenSSL returning an array of Hex pairs, instead of one long hex value. Reads in the hex value
        // to a char array, and then makes use of C++ string to collect all the individual char arrays representing a hex pair
        // into one contiguous string for easy comparison.
        for(int i =0; i < 6; i++) {
            sprintf(hash_charecter_storage,"%x", md_value2[i]);
            hash_string_representation.append(hash_charecter_storage);
        }
        // Similar to part 1 above, iterate through the user supplied 24 bit hash, and compare it to the random string's
        // hash representation (conveniently packaged into a C++ string). If a character differs between the two, break,
        // and generate a new random string to hash and test for collision.
        for (int i = 0; i < 6; i++) {
            if ( hash_string_representation[i] != hash_to_find[i]) {
                foundMatch = false;
                break;
            }
            foundMatch = true;
        }
        if (foundMatch) {
            cout << endl << "Found plain text with matching hash: " << second_string << " : ";
            for (int i = 0; i < 3; i++) {
                printf("%x", md_value2[i]);
            }
            break;
        }
        one_way_property_count++;
    }
    cout << endl << "Number of trials to find a hash collision: " << one_way_property_count << endl;

    return 0;
}
