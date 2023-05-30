//
// Created by Grzegorz Olszewski on 24/05/2023.
//

#ifndef UNTITLED4_FILEOPERATOR_H
#define UNTITLED4_FILEOPERATOR_H
#include "EncoderDecoder.h"
#include "iostream"
#include "map"
#include "fstream"
#include "vector"
#include "PasswordLine.h"
#include "EncoderDecoder.h"
using std::string;
using std::ofstream;
using std::vector;

class FileOperator {

private:
string filePath;
set<string> categories;
vector<PasswordLine> passwordLines;

public:
    explicit FileOperator(const string& filePath);
    string fileChooser();
    void addPassword(string const& password);
    void editPassword();
    void addCategory(const string &category);
    void sortPasswords();
    void deletePassword();
    void deleteCategory();
    vector<PasswordLine> searchPassword();

    void wypiszHasla();
    ~FileOperator();

};


#endif //UNTITLED4_FILEOPERATOR_H
