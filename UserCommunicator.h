//
// Created by Grzegorz Olszewski on 24/05/2023.
//

#ifndef UNTITLED4_USERCOMMUNICATOR_H
#define UNTITLED4_USERCOMMUNICATOR_H

#include "istream"
#include "PasswordManager.h"
#include "FileOperator.h"
#include "EncoderDecoder.h"
#include "vector"
#include "iostream"

using std::cout;
using std::cin;
using std::endl;
using std::vector;


class UserCommunicator {

private:

    string filePath;
    static string mainPassword;
    PasswordManager passwordManager{};
    FileOperator fileOperator;
    std::string pathChooser();
    bool authorization(const string& password);

public:
    UserCommunicator();
    int static userInputExceptionHandler();
    string static userEmptyStringExceptionHandler();
    int static userOneToFiveChoiceExceptionHandler();
    friend string EncoderDecoder::encoder(const string &forDecryption);
    friend string EncoderDecoder::decoder(const string &forDecryption);


};


#endif //UNTITLED4_USERCOMMUNICATOR_H
