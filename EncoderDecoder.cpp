//
// Created by Grzegorz Olszewski on 27/05/2023.
//

#include "EncoderDecoder.h"

#include <utility>
#include "UserCommunicator.h"


string EncoderDecoder::encoder(const string& passwordForEncryption) {

    string encryptedPassword;
    string finalEncryption;

    if(passwordForEncryption.empty())
        return "";

    for(int i=0; i<passwordForEncryption.length(); i++){

        int currentChar = UserCommunicator::mainPassword[i%UserCommunicator::mainPassword.length()]+passwordForEncryption[i];
        if(currentChar>127)
            currentChar -= 127 ;
        encryptedPassword += (char)currentChar;
    }

    for(char &_char : encryptedPassword){
        auto last4Bits = _char & 15;
        auto first4Bits = _char & 240;
        first4Bits >>= 4;
        char firstChar = (char)(first4Bits + 65);
        char secondChar = (char)(last4Bits + 65);
        finalEncryption += firstChar;
        finalEncryption += secondChar;
    }

    return finalEncryption;
}

string EncoderDecoder::decoder(const string& charPasswordToDecode) {

    string passwordToDecode;

    for(int i=0; i<charPasswordToDecode.length(); i+=2){
        int first4bits = (charPasswordToDecode[i] - 65) << 4;
        int last4bits = (charPasswordToDecode[i+1] - 65);
        passwordToDecode += (char)(first4bits + last4bits);
    }

    string decodedPassword;

    for(int i=0; i<passwordToDecode.length(); i++){

        int currentChar = passwordToDecode[i] - UserCommunicator::mainPassword[i%UserCommunicator::mainPassword.length()];
        if(currentChar<0)
            currentChar += 127;
        decodedPassword += (char)currentChar;
    }

    return decodedPassword;
}

string EncoderDecoder::decoder(const string& password, const string& charPasswordToDecode) {

    string passwordToDecode;

    for(int i=0; i<charPasswordToDecode.length(); i+=2){
        int first4bits = (charPasswordToDecode[i] - 65) << 4;
        int last4bits = (charPasswordToDecode[i+1] - 65);
        passwordToDecode += (char)(first4bits + last4bits);
    }

    string decodedPassword;

    for(int i=0; i<passwordToDecode.length(); i++){

        int currentChar = passwordToDecode[i] - password[i%password.length()];
        if(currentChar<0)
            currentChar += 127;
        decodedPassword += (char)currentChar;
    }

    return decodedPassword;
}
