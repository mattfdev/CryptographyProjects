#include <iostream>
#include <iomanip>
#include <vector>
#include <bitset>
#include <stdlib.h>


using namespace std;

long substitution_box_1[2][8] = {{5,2,1,6,3,4,7,0}, {1,4,6,2,0,7,5,3}};
long substitution_box_2[2][8] = {{4,0,6,5,7,1,3,2}, {5,3,0,7,6,2,1,4}};

vector<string> convert_to_binary(const string input) {
    // Lets make a vector to hold all the ASCII character values.
    vector<string> block;

    // For each character, convert the ASCII chararcter to its binary
    // representation.
    for (int i = 0; i < input.size(); ++i) {
        // Make a temporary variable called B to store the 8 bit pattern
        // for the ASCII value.
        bitset<8> b(input.c_str()[i]);

        // Add that 8 bit pattern into the block.
        block.push_back(b.to_string());
    }
    return block;
}

long convert_binary_decimal(unsigned long bin_num) {
    unsigned long decimal = 0;
    int remainder=0, base = 1;

    while (bin_num > 0) {
        remainder = bin_num % 10;
        decimal = decimal + remainder * base;
        bin_num = bin_num / 10;
        base = base * 2;
    }
    return decimal;
}

vector<bitset<12>> convert_binary_strings_to_blocks(vector<string> bit_strings) {
    vector<bitset<12>> encryption_blocks;
    int iterator = 0;
    while ((iterator + 2) < bit_strings.size()) {
        string bitstring_blk1 = bit_strings[iterator];
        string split_bit_string = bit_strings[++iterator];
        string bitstring_blk2 = bit_strings[++iterator];
        string first_half_block = split_bit_string.substr(0, 4);
        //cout << first_half_block << endl;
        string second_half_block = split_bit_string.substr(4, 4);
        //cout << second_half_block << endl;
        bitset<12> block(bitstring_blk1.append(first_half_block));
        bitset<12> block2(second_half_block.append(bitstring_blk2));
        encryption_blocks.push_back(block);
        encryption_blocks.push_back(block2);
        iterator++;
    }
    cout << "iterator " << iterator << " and size " << bit_strings.size() << endl;
    // Need to account for last few bits in bit string block, and zero pad blocks as appropriate.
    if ((bit_strings.size() - iterator) == 2) {
        string bitstring_blk1 = bit_strings[iterator];
        string split_bit_string = bit_strings[++iterator];
        string first_half_block = split_bit_string.substr(0, 4);
        string second_half_block = split_bit_string.substr(4, 4);
        bitset<12> block(bitstring_blk1.append(first_half_block));
        bitset<12> block2(second_half_block.append("00000000"));
        encryption_blocks.push_back(block);
        encryption_blocks.push_back(block2);
    } else if ((bit_strings.size() - iterator) == 1) {
        string bitstring_blk1 = bit_strings[iterator];
        bitset<12> block(bitstring_blk1.append("0000"));
        encryption_blocks.push_back(block);
    }
    return encryption_blocks;
}

bitset<8> get_encryption_round_key(bitset<9> ekey, int n) {
    bitset<8> roundKey;
    n = 10 - (n-1)%9;
    // Key returns the nth digit onwards
    for (int i = 0; i < 8 ; ++i ) {
        roundKey[i] = ekey[((n+i)%9)];
    }
    return roundKey;
}

bitset<8> get_decryption_round_key(bitset<9> ekey, int n) {
    bitset<8> roundKey;
    n = 10 - (n-1)%9;
    // Key returns the nth digit onwards
    for (int i = 0; i < 8 ; ++i ) {
        roundKey[i] = ekey[((n+i)%9)];
    }
    return roundKey;
}

bitset<8> expansion(bitset<6> bit_strings) {
    bitset<8> output;
    output[0] = bit_strings[0];
    output[1] = bit_strings[1];
    output[2] = bit_strings[3];
    output[3] = bit_strings[2];
    output[4] = bit_strings[3];
    output[5] = bit_strings[2];
    output[6] = bit_strings[4];
    output[7] = bit_strings[5];
    return output;
}

// Incrementally build a Light-DES encryption block.
bitset<6> encrypt(bitset<6> bit_string, bitset<8> ekey) {
    cout << "encrypt fxn; intermediate block should be 00110111. it is:" << "\n";
    bitset<8> intermediary_block = expansion(bit_string);
    intermediary_block = intermediary_block ^= ekey;
    cout << intermediary_block << endl;
    // Take the last 3 digits of the left and right sub-blocks, convert to decimal numbers to use as array indices to access.
    long left_block_array_number = convert_binary_decimal(std::strtoul(intermediary_block.to_string().substr(1,3).c_str(), NULL, 2));
    long left_block_row = convert_binary_decimal(std::strtoul(intermediary_block.to_string().substr(0,1).c_str(), NULL, 2));
    long left_block_substituted = substitution_box_1[left_block_row][(left_block_array_number)];
    cout << "should see 3" << "\n";
    cout << left_block_array_number << endl;
    cout << "should see 0" << "\n";
    cout << left_block_row << endl;
    cout << "should see 6" << "\n";
    cout << left_block_substituted << endl;
    long right_block_array_number = convert_binary_decimal(std::strtoul(intermediary_block.to_string().substr(5,3).c_str(), NULL, 2));
    long right_block_row = convert_binary_decimal(std::strtoul(intermediary_block.to_string().substr(4,1).c_str(), NULL, 2));
    long right_block_substituted = substitution_box_2[right_block_row][(right_block_array_number)];
    cout << "should see 7" << "\n";
    cout << right_block_array_number<< endl;
    cout << "should see 0" << "\n";
    cout << right_block_row << endl;
    cout << "should see 2" << "\n";
    cout << right_block_substituted << endl;
    unsigned long encrypted_binary = std::strtoul(to_string(left_block_substituted).append(to_string(right_block_substituted)).c_str(), NULL, 2);
    bitset<6> encrypted_block (encrypted_binary);
    return encrypted_block;
}

int main(int argc, char *argv[]) {

    vector<string> bit_strings;
    vector<bitset<12>> encryption_blocks;


    if (argc != 3) {
        cout << "Incorrect number of arguments sent the program, please supply some plaintext and a key of length 9 for encryption" << endl;
        return 1;
    }

    string plaintext =  argv[1];
    string key = argv[2];
    if (key.find_first_not_of("01") != std::string::npos) {
        cout << "Illegal key inputted, please input another key, consisting wholly of binary digits" << endl;
        return false;
    }

    if (key.length() != 9) {
        cout << "Please enter a valid binary key of length 9" << endl;
        return 1;
    }
    bitset<9> encryption_key(key); // this is to test.
    bitset<6> teststring("111000");
    cout << "test string is:" << "\n";
    cout << teststring << endl;
    cout << "expansion of 111000 should be 11010100. expansion gives:" << "\n" ;
    cout << expansion(teststring) << endl;
    cout << "the key is:" << encryption_key << "\n";
    cout << "round key 1" << "\n" ;
    cout << get_encryption_round_key(encryption_key, 1) << endl;
    bitset<8> testxor = expansion(teststring);
    cout << "xor should give: 00110111. our test gives:" << "\n";
    testxor = get_encryption_round_key(encryption_key, 1) ^= testxor;
    cout << testxor << endl;
    cout << encrypt(teststring, get_encryption_round_key(encryption_key, 1)) << endl;
    cout << "round key 3" << "\n" ;
    cout << get_encryption_round_key(encryption_key, 3) << endl;
    cout << "round key 12" << "\n" ;
    cout << get_encryption_round_key(encryption_key, 12) << endl;
    cout << "round key 10" << "\n" ;
    cout << get_encryption_round_key(encryption_key, 10) << endl;

    cout << plaintext << endl;
    encryption_blocks = convert_binary_strings_to_blocks(convert_to_binary(plaintext));

    //cout << encryption_blocks[0] << " block 2: " << encryption_blocks[1];
    for(bitset<12> bits : encryption_blocks) {
        cout << bits;
    }
}