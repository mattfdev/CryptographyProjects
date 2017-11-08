#include <iostream>
#include <iomanip>
#include <fstream>
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

int main(int argc, char *argv[]) {

    vector<string> bit_strings;
    vector<bitset<12>> encryption_blocks;
    vector<bool> stringBits;

    if (argc != 2) {
        cout << "Incorrect number of arguments sent the program, please supply some plaintext for encryption" << endl;
        return 1;
    }

    string plaintext =  argv[1];
    bit_strings = convert_to_binary(plaintext);
    int iterator = 0;
    while (iterator < bit_strings.size()) {
        string bitstring = bit_strings[iterator];
        string split_bit_string = bit_strings[iterator++];
        string bitstring3 = bit_strings[iterator++];
        string first_half_block = split_bit_string.substr(0, 4);
        string second_half_block = split_bit_string.substr(0, 4);
        bitset<12> block(bitstring.append(first_half_block));
        bitset<12> block2(bitstring.append(second_half_block));

    }
}