#include <iostream>
#include <string>
using namespace std;



string encryptString(string input) {
    string encrypted;

    // Iterate through each character in the input string
    for (char c : input) {
        // Encrypt by adding 5 to the ASCII value of the character
        char encryptedChar = c + 5; // Add 5 to ASCII value
        encrypted += encryptedChar; // Append the encrypted character to the result
    }

    return encrypted; // Return the encrypted string
}


string decrypt(string input){
    string decrypted;
    for( char c:input){
        char decryptedChar = c - 5;
        decrypted += decryptedChar;
    }
    return decrypted;
}

int main() {
    string name = "alex-5";
    string encrypted = encryptString(name);
    cout<<encrypted;

    string decryptedt = decrypt(encrypted);
    cout<<decryptedt;
}