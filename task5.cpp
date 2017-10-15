#define _XOPEN_SOURCE

#include <iostream>
#include <openssl/evp.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <crypt.h>

using namespace std;

char SALT[3] = "xx"; //When running johnTester, this line is changed to: char SALT[10] = "xxxxxxxxx"
char passwd_file[] = "passwd";
string delim = ":";

// Validate if supplied password meets system minimum requirements.
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

//Encrypt supplied password and return hash.
char* encrypt_password(char* password) {
	return crypt(password, SALT);
}

// Check if user exists in passwd file.
string check_user_exists(string inputted_user) {
    ifstream user_lookupFile(passwd_file);
    string user_credential_details, user_name;
    while (getline(user_lookupFile, user_credential_details)) {
        //cout << "Line is " << user_credential_details << endl;
        user_name = user_credential_details.substr(0, user_credential_details.find(delim));
        //cout << "username = " << user_name << endl;
        if (user_name == inputted_user) {
            return user_credential_details;
        }
    }
    return "";
}

int main(int argc, char *argv[]) {
    srand(time(0) );
    string user_account, password, does_user_exist, database_password;
    int bad_password_counter = 0, group_id = 1005, maximum_password_attempts, user_id;
    user_id = rand() % 100 + 1000;

    if (argc != 2) {
        cout << "Incorrect number of arguments sent the program, please supply a maximum amount of password attempts argument" << endl;
        return 1;
    }
    maximum_password_attempts = atoi(argv[1]);
    if (maximum_password_attempts == 0) {
        cout << "Invalid max password attempts # inputted, please re-run the program with the correct argument supplied" << endl;
        return 1;
    }

    // Open passwd file, or create if does not exist
    fstream appendFileToWorkWith;
    appendFileToWorkWith.open(passwd_file, std::fstream::in | std::fstream::out | std::fstream::app);
    // If file does not exist, Create new file
    if (!appendFileToWorkWith) {
        cout << "passwd file doesnot exist yet, creating one now.";
        appendFileToWorkWith.open(passwd_file,  fstream::in | fstream::out | fstream::trunc);
    }
    appendFileToWorkWith.close();

    cout << "Please input your user id" << endl;
    cin >> user_account;
    while (user_account.length() < 3 || user_account.length() > 32) {
        cout << "Illegal user name inputted, try again" << endl;
        cout << "Please input your user id" << endl;
        cin >> user_account;
    }
    does_user_exist = check_user_exists(user_account);
    // If the user is found validate their password, or terminate the program if they donot authenticate before password limit exceeded.
    if (!does_user_exist.empty()) {
        cout << "Input your password " << endl;
        cin >> password;
        // Find the password of the user in the passwd file and save it for future comparison.
        does_user_exist.erase(0, does_user_exist.find(delim) + delim.length());
        database_password = does_user_exist.substr(0, does_user_exist.find(delim));

        while (!password_requirments_passed(password) || encrypt_password(strdup(password.c_str())) != database_password) {
            bad_password_counter++;
            if (bad_password_counter >= maximum_password_attempts) {
                cout << "Too many unsuccessful attempts, exiting program" << endl;
                return 1;
            }
            cout << "Incorrect password, input your password again: " << endl;
            cin >> password;
        }
    } else {
        //Create new user in the passwd file.
        appendFileToWorkWith.open(passwd_file, std::fstream::in | std::fstream::out | std::fstream::app);
        cout << "No match found. Creating new profile" << endl;
        cout << "Please enter a password: " << endl;
        cin >> password;
        while (!password_requirments_passed(password)) {
            cout << "Please enter a password: " << endl;
            cin >> password;
        }
	    char* user_pass = strdup(password.c_str());
        // Create a new user in  the passwd file with an the encrypted password. The user is asigned a userId at random
        // and a groupid and user description. After creation the user is told they are 'logged in' and the program exits.
        appendFileToWorkWith << user_account << ":" << encrypt_password(user_pass) << ":" << user_id << ":" << group_id << ":" << "CrptX user" << ":" << "/cryptx" << ":" << "/bin/bash" << "\n";
        cout << "A new profile has been created for you." << endl;
        appendFileToWorkWith.close();
    }

    cout << "Login Succesful" << endl;
    return 0;
}
