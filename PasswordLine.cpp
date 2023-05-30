//
// Created by Grzegorz Olszewski on 29/05/2023.
//

#include <sstream>
#include "PasswordLine.h"
#include "EncoderDecoder.h"

PasswordLine::PasswordLine() {};
PasswordLine::PasswordLine(const string &name, const string &password, const string &category) : name(name),
                                                                                                 password(password),
                                                                                                 category(category){}

PasswordLine::PasswordLine(const string &name, const string &password, const string &category, const string &site)
        : name(name), password(password), category(category), site(site) {}

PasswordLine::PasswordLine(const string &name, const string &password, const string &category, const string &site,
                           const string &login) : name(name), password(password), category(category), site(site),
                                                  login(login) {}

PasswordLine PasswordLine::fromLineToPasswordLine(const string& line) {


    if(line.size()<3)
        return PasswordLine();
    std::stringstream ss(line);
    std::vector<string> decodedLine;
    string word;
    while(ss >> word){
        decodedLine.push_back(EncoderDecoder::decoder(word));
    }

    if(decodedLine.size()==3) {
        PasswordLine passwordLine{decodedLine[0], decodedLine[1], decodedLine[2]};
        return passwordLine;
    }
    else if(decodedLine.size() == 4) {
        PasswordLine passwordLine{decodedLine[0], decodedLine[1], decodedLine[2], decodedLine[3]};
        return passwordLine;
    }else {
        PasswordLine passwordLine{decodedLine[0], decodedLine[1], decodedLine[2], decodedLine[3], decodedLine[4]};
        return passwordLine;
    }
}

const string &PasswordLine::getName() const {
    return name;
}

const string &PasswordLine::getPassword() const {
    return password;
}

const string &PasswordLine::getCategory() const {
    return category;
}

const string &PasswordLine::getSite() const {
    return site;
}

const string &PasswordLine::getLogin() const {
    return login;
}

PasswordLine::operator string() const {
    string result;

    if(name.empty() || password.empty() || category.empty())
        return "Bledne dane w pliku wejsciowym!";


    result += "Nazwa hasla: " + name + ", haslo: " + password + ", kategoria: " + category;
    if(!site.empty())
        result += ", strona: " + site;
    if(!login.empty())
        result += ", login: " + login;

    return result;

}

string PasswordLine::fromPasswordToEncodedLine(const PasswordLine &passwordLine) {

    string line;
    line += EncoderDecoder::encoder(passwordLine.name) + " "
    + EncoderDecoder::encoder(passwordLine.password) + " "
    + EncoderDecoder::encoder(passwordLine.category);
    if(!passwordLine.site.empty())
        line += " " + EncoderDecoder::encoder(passwordLine.site);
    if(!passwordLine.login.empty())
        line += " " + EncoderDecoder::encoder(passwordLine.login);
    return line;
}

bool PasswordLine::operator==(const PasswordLine &passwordLine) {
    if(name == passwordLine.name)
        if(password == passwordLine.password)
            if(category == passwordLine.category)
                if (site == passwordLine.site)
                    if(login == passwordLine.login)
                        return true;
                    else
                        return false;
                else
                    return false;
            else
                return false;
        else
            return false;
    else
        return false;
}

void PasswordLine::setName(const string &name) {
    PasswordLine::name = name;
}

void PasswordLine::setPassword(const string &password) {
    PasswordLine::password = password;
}

void PasswordLine::setCategory(const string &category) {
    PasswordLine::category = category;
}

void PasswordLine::setSite(const string &site) {
    PasswordLine::site = site;
}

void PasswordLine::setLogin(const string &login) {
    PasswordLine::login = login;
}



