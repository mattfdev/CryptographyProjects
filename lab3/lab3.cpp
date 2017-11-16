#include <iostream>
#include <iomanip>
#include <vector>
#include <bitset>


using namespace std;

long substitution_box_1[2][8] = {{5,2,1,6,3,4,7,0}, {1,4,6,2,0,7,5,3}};
long substitution_box_2[2][8] = {{4,0,6,5,7,1,3,2}, {5,3,0,7,6,2,1,4}};

// Convert a string comprising solely of binary numbers to a 12 bit long set.
vector<string> convert_to_binary(const string input) {
    // A vector to hold all the ASCII character values.
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

// Helper function to convert a binary number base 2 to base 10 decimal.
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

// Convert a vector comprising of strings(that are simply binary numbers) to their bitset equivalent. Also zero pads
// the strings appropriately to a length of 12 if required.
vector<bitset<12>> convert_binary_strings_to_blocks(vector<string> bit_strings) {
    vector<bitset<12>> encryption_blocks;
    int iterator = 0;
    while ((iterator + 2) < bit_strings.size()) {
        string bitstring_blk1 = bit_strings[iterator];
        string split_bit_string = bit_strings[++iterator];
        string bitstring_blk2 = bit_strings[++iterator];
        string first_half_block = split_bit_string.substr(0, 4);
        string second_half_block = split_bit_string.substr(4, 4);
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

// Get encryption key given master key, and round number.
bitset<8> get_encryption_round_key(bitset<9> ekey, int n) {
    bitset<8> roundKey;
    n = 10 - (n - 1) % 9;
    // Key returns the nth digit onwards
    for (int i = 0; i < 8 ; ++i ) {
        roundKey[i] = ekey[((n+i)%9)];
    }
    return roundKey;
}

// Get decryption key given master key, and round number.
bitset<8> get_decryption_round_key(bitset<9> ekey, int n) {
    bitset<8> roundKey;
    n = 10 - (n-1)%9;
    // Key returns the nth digit onwards
    for (int i = 0; i < 8 ; ++i ) {
        roundKey[i] = ekey[((n+i)%9)];
    }
    return roundKey;
}

// Expands a 6 bit long bitset to 8, using a hardcoded subsitution function.
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
    bitset<8> intermediary_block = expansion(bit_string);
    //cout << "Encryption round key is " << ekey.to_string() << endl;
    //cout << "Expanded block of " << bit_string.to_string() << " is : " << intermediary_block.to_string() << endl;
    intermediary_block = intermediary_block ^= ekey;
    //cout << "XORED block is " << intermediary_block.to_string() << endl;
    // Take the last 3 digits of the left and right sub-blocks, convert to decimal numbers to use as array indices to access.
    long left_block_array_number = convert_binary_decimal(std::strtoul(intermediary_block.to_string().substr(1,3).c_str(), NULL, 2));
    long left_block_row = convert_binary_decimal(std::strtoul(intermediary_block.to_string().substr(0,1).c_str(), NULL, 2));
    long left_block_substituted = substitution_box_1[left_block_row][left_block_array_number];
    bitset<3> left_bitset(left_block_substituted);
    //cout << "Array indeces of left bock s1 are " << left_block_row  << " and " << left_block_array_number << " the value subbed in is " << left_bitset.to_string() << endl;

    long right_block_array_number = convert_binary_decimal(std::strtoul(intermediary_block.to_string().substr(5,3).c_str(), NULL, 2));
    long right_block_row = convert_binary_decimal(std::strtoul(intermediary_block.to_string().substr(4,1).c_str(), NULL, 2));
    long right_block_substituted = substitution_box_2[right_block_row][right_block_array_number];
    bitset<3> right_bitset(right_block_substituted);
    //cout << "Array indeces of right bock s2 are " << right_block_row  << " and " << right_block_array_number << " the value subbed in is " << right_bitset.to_string() << endl;

    //cout << "the left block is " << left_block_substituted << " and the right block is " << right_block_substituted << endl;
    //unsigned long encrypted_binary = std::strtoul(to_string(left_block_substituted).append(to_string(right_block_substituted)).c_str(), NULL, 2);
    bitset<6> encrypted_block;
    encrypted_block[0] = right_bitset[0];
    encrypted_block[1] = right_bitset[1];
    encrypted_block[2] = right_bitset[2];
    encrypted_block[3] = left_bitset[0];
    encrypted_block[4] = left_bitset[1];
    encrypted_block[5] = left_bitset[2];
    //cout << "the encrypytped text binary is " << encrypted_block.to_string() << endl << endl;
    return encrypted_block;
}

// Helper function facilitating a single round of light-DES.
bitset<12> apply_des(bitset<12> input_block, bitset<8> ekey) {
    bitset<6> left_encryption_block;
    left_encryption_block[0] = input_block[6];
    left_encryption_block[1] = input_block[7];
    left_encryption_block[2] = input_block[8];
    left_encryption_block[3] = input_block[9];
    left_encryption_block[4] = input_block[10];
    left_encryption_block[5] = input_block[11];
    cout << "the input block is " << input_block.to_string() << endl;
    cout << "the left block is " << left_encryption_block.to_string() << endl;
    bitset<6> right_encryption_block;
    right_encryption_block[0] = input_block[0];
    right_encryption_block[1] = input_block[1];
    right_encryption_block[2] = input_block[2];
    right_encryption_block[3] = input_block[3];
    right_encryption_block[4] = input_block[4];
    right_encryption_block[5] = input_block[5];
    cout << "the right block before encrypt is " << right_encryption_block.to_string() << endl;

    bitset<6> encrypted_right_block = encrypt(right_encryption_block, ekey);
    cout << "the right block after encrypt is " << encrypted_right_block.to_string() << endl;

    encrypted_right_block = encrypted_right_block ^= left_encryption_block;
    cout << "the right block after XOR is " << encrypted_right_block.to_string() << endl;


    // Create bitset compirsed of unmodified right sub-block bits appended with modified left XOR encrypted right sub-block bits.
    bitset<12> final_encrypted_block;
    final_encrypted_block[0] = left_encryption_block[0];
    final_encrypted_block[1] = left_encryption_block[1];
    final_encrypted_block[2] = left_encryption_block[2];
    final_encrypted_block[3] = left_encryption_block[3];
    final_encrypted_block[4] = left_encryption_block[4];
    final_encrypted_block[5] = left_encryption_block[5];
    final_encrypted_block[6] = right_encryption_block[0];
    final_encrypted_block[7] = right_encryption_block[1];
    final_encrypted_block[8] = right_encryption_block[2];
    final_encrypted_block[9] = right_encryption_block[3];
    final_encrypted_block[10] = right_encryption_block[4];
    final_encrypted_block[11] = right_encryption_block[5];

    cout << "the final block is " << final_encrypted_block.to_string() << endl << endl;

    return final_encrypted_block;
}

int main(int argc, char *argv[]) {

    vector<string> bit_strings;
    vector<bitset<12>> encryption_blocks;


    if (argc != 4) {
        cout << "Incorrect number of arguments sent the program, please supply some plaintext and a key of length 9 for encryption(in binary format), and number of rounds of encryption to perform." << endl;
        return 1;
    }

    string plaintext =  argv[1];
    string key = argv[2];
    int encryption_rounds = atoi(argv[3]);
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
    bitset<12> IV("111000111000");


    encryption_blocks = convert_binary_strings_to_blocks(convert_to_binary(plaintext));

   cout << " pre-encryption blocks:\n";

   for (int j = 0; j < encryption_blocks.size(); j++) {
       cout << encryption_blocks[j] << endl;
   }
    cout << "round keys for encrypt:\n";
    // Encrypt the plaintext to ciphertext using the light DES algorithm.
    for (int i = 1; i <= encryption_rounds; i++) {
        bitset<8> round_key = get_encryption_round_key(encryption_key, i);
        cout << round_key << "\n";
        for (int j = 0; j < encryption_blocks.size(); j++) {
    //        cout << "round key for encryption" << round_key << "\n";
    //        cout << "pre-encrypted block" << j << ": " << encryption_blocks[j] << "\n";
            encryption_blocks[j] = apply_des(encryption_blocks[j], round_key);
    //        cout << "post-encrypted block" << j << ": " << encryption_blocks[j] << "\n";

        }
    }

    cout << " post-encryption blocks:\n";
    for (int j = 0; j < encryption_blocks.size(); j++) {
        cout << encryption_blocks[j] << endl;
    }

    for (int i = encryption_rounds; i > 0; i--) {
        bitset<8> round_key = get_encryption_round_key(encryption_key, i);
        cout << "decryption round key is " <<round_key << "\n";
        for (int j = 0; j < encryption_blocks.size(); j++) {
            //cout << "round key for decryption" << round_key << "\n";
            //cout << "pre-decrypted block" << j << ": " << encryption_blocks[j] << "\n";
            encryption_blocks[j] = apply_des(encryption_blocks[j], round_key);
            //cout << "post-decrypted block" << j << ": " << encryption_blocks[j] << "\n";
        }
    }
    cout << " post-decryption blocks:\n";
    for (int j = 0; j < encryption_blocks.size(); j++) {
        cout << encryption_blocks[j] << endl;
    }

    for (int i = 1; i <= encryption_rounds; i++) {
        bitset<8> round_key = get_encryption_round_key(encryption_key, i);
        for (int j = 0; j < encryption_blocks.size(); j++) {
            if (j == 0) { encryption_blocks[j] = encryption_blocks[j] ^= IV;}
            else{
                encryption_blocks[j] = encryption_blocks[j] ^= encryption_blocks[j-1]; }
            encryption_blocks[j] = apply_des(encryption_blocks[j], round_key);
        }
    }
    cout << "post-CBC-encryption blocks: \n";
    for (int j = 0; j < encryption_blocks.size(); j++) {
        cout << encryption_blocks[j] << endl;
    }

    for (int i = 1; i <= encryption_rounds; i++) {
        bitset<8> round_key = get_encryption_round_key(encryption_key, encryption_rounds - i + 1);
        for (int j = encryption_blocks.size() - 1; j >= 0 ; j--) {
            encryption_blocks[j] = apply_des(encryption_blocks[j], round_key);
            if (j == 0) { encryption_blocks[j] = encryption_blocks[j] ^= IV; }
            else {
                encryption_blocks[j] = encryption_blocks[j] ^= encryption_blocks[j - 1];
            }
            }
        }
    cout << "post-CBC-decryption blocks: \n";
    for (int j = 0; j < encryption_blocks.size(); j++) {
        cout << encryption_blocks[j] << endl;
    }
    }





