#include <iostream>
#include <openssl/evp.h>
#include <fstream>


using namespace std;

char SALT[3] = "xx";

bool password_requirments_passed(string password) {
    if (password.length() > 12) {
        cout << "Illegal password inputted, please input another password!";
        return false;
    }
    if (password.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890") != std::string::npos) {
        cout << "Illegal password inputted, please input another password!" << endl;
        return false;
    }
    return true;
}
char* encrypt_password(string password) {

}

bool doesUserExist(fstream passwdFile) {

}

int main(int argc, char *argv[]) {
    srand(time(nullptr) );
    string user_account, password, user_credential_details;
    bool does_user_exists = false;
    int bad_password_counter = 0, group_id = 1005, maximum_password_attempts, user_id;
    user_id = rand() % 100 + 1000;

    if (argc != 2) {
        cout << "Incorrect number of arguments sent the program, please supply a maximum amount of password attempts argument";
        return 1;
    }
    maximum_password_attempts = atoi(argv[1]);
    if (maximum_password_attempts == 0) {
        cout << "Invalid max password attempts # inputted, please re-run the program with the correct argument supplied";
        return 1;
    }

    // Open passwd file, or create if does not exist
    char filename[] = "passwd";
    fstream appendFileToWorkWith;
    appendFileToWorkWith.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
    // If file does not exist, Create new file
    if (!appendFileToWorkWith) {
        cout << "passwd file doesnot exist yet, creating one now.";
        appendFileToWorkWith.open(filename,  fstream::in | fstream::out | fstream::trunc);
        //appendFileToWorkWith <<"\n";
    }

    cout << "Please input your user id" << endl;
    cin >> user_account;
    while (user_account.length() < 3 || user_account.length() > 32) {
        cout << "Illegal user name inputted, try again" << endl;
        cout << "Please input your user id" << endl;
        cin >> user_account;
    }

    //UserLookup
    //getline(appendFileToWorkWith, user_credential_details);
    //cout << user_credential_details << endl;

    if (does_user_exists) {
        cout << "Input your password " << endl;
        cin >> password;
        while (!password_requirments_passed(password)) {
            bad_password_counter++;
            if (bad_password_counter >= maximum_password_attempts) {
                cout << "Too many unsuccessful attempts, exiting program";
                return 1;
            }
            cout << "Input your password " << endl;
            cin >> password;
            // Do password lookup here
        }
        // Good password continue
    } else {
        //Create new user in the passwd file.
        cout << "No match found. Creating new profile" << endl;
        cout << "Please enter a password: " << endl;
        cin >> password;
        while (!password_requirments_passed(password)) {
            cout << "Please enter a password: " << endl;
            cin >> password;
        }
        appendFileToWorkWith << user_account << ":" << password << ":" << user_id << ":" << group_id << ":" << "CrptX user" << ":" << "/cryptx" << ":" << "/bin/bash" << endl;
        cout << "A new profile has been created for you." << endl;
    }

    cout << "Login Succesful" << endl;
    appendFileToWorkWith.close();
    return 0;
}