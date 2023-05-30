//
// Created by Grzegorz Olszewski on 24/05/2023.
//

#ifndef UNTITLED4_PASSWORDMANAGER_H
#define UNTITLED4_PASSWORDMANAGER_H
#include "iostream"
#include "set"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::set;


class PasswordManager {

private:
    string currentPassword;
    double passwordScore();

public:
    PasswordManager();
    string passwordCreation();
    string passwordCreator();




};


#endif //UNTITLED4_PASSWORDMANAGER_H
