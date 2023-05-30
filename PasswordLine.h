//
// Created by Grzegorz Olszewski on 29/05/2023.
//

#ifndef UNTITLED4_PASSWORDLINE_H
#define UNTITLED4_PASSWORDLINE_H
#include "iostream"
using std::string;


class PasswordLine {
private:
    string name, password, category, site, login;

    PasswordLine();

    PasswordLine(const string &name, const string &password, const string &category);

    PasswordLine(const string &name, const string &password, const string &category, const string &site);

    PasswordLine(const string &name, const string &password, const string &category, const string &site,
                 const string &login);

public:


    static PasswordLine fromLineToPasswordLine(const string& line);
    static string fromPasswordToEncodedLine(const PasswordLine& passwordLine);

    const string &getName() const;

    const string &getPassword() const;

    const string &getCategory() const;

    const string &getSite() const;

    const string &getLogin() const;

    operator string() const;
    bool operator == (const PasswordLine& passwordLine);

    void setName(const string &name);

    void setPassword(const string &password);

    void setCategory(const string &category);

    void setSite(const string &site);

    void setLogin(const string &login);

};


#endif //UNTITLED4_PASSWORDLINE_H
