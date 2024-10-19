#include <iostream>
#include <string>
using namespace std;



string encryptString(string input) {
    string encrypted;


    for (char c : input) {
        
        char encryptedChar = c + 5; 
        encrypted += encryptedChar;
    }

    return encrypted;
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