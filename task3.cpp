#include <iostream>
#include <openssl/evp.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    EVP_MD_CTX *ctx;
    EVP_MD_CTX_init(ctx);

    ifstream inFile;
    string unhashed_file;
    string line;
    string filename;

    if (argc != 2) {
       cout << "Incorrect number of arguments sent the program, try adding a file name?";
        return 1;
    }


    filename = argv[1];
    cout << "Filename given: " + filename << "\n";

    inFile.open(filename);
    if (inFile.fail()) {
        cout << "Unable to open file";
    }

    while (getline(inFile, line)) {
        unhashed_file.append(line);
    }


    inFile.close();

    //cout << "Hello, World!" << std::endl;
    return 0;
}