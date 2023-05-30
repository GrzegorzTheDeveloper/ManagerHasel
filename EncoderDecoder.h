//
// Created by Grzegorz Olszewski on 27/05/2023.
//

#ifndef UNTITLED4_ENCODERDECODER_H
#define UNTITLED4_ENCODERDECODER_H
#include "iostream"
#include "random"
#include "bitset"
#include "set"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::set;

class EncoderDecoder {

public:
    string static encoder(const string& forEncryption);
    string static decoder(const string& forDecryption);
    string static decoder(const string& password, const string& forDecryption);
};


#endif //UNTITLED4_ENCODERDECODER_H
