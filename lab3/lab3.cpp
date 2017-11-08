#include <iostream>
#include <iomanip>
#include <vector>


using namespace std;

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

int main(int argc, char *argv[]) {

    vector<string> bit_strings;
    vector<bitset<12>> encryption_blocks;

    if (argc != 2) {
        cout << "Incorrect number of arguments sent the program, please supply some plaintext for encryption" << endl;
        return 1;
    }

    string plaintext =  argv[1];

    cout << plaintext << endl;
    bit_strings = convert_to_binary(plaintext);
    encryption_blocks = convert_binary_strings_to_blocks(bit_strings);

    //cout << encryption_blocks[0] << " block 2: " << encryption_blocks[1];
    for(bitset<12> bits : encryption_blocks) {
        cout << bits;
    }
}