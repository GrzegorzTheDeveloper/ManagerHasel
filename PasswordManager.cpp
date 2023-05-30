//
// Created by Grzegorz Olszewski on 24/05/2023.
//
#include "UserCommunicator.h"
#include "PasswordManager.h"
#include "iostream"
#include "random"
#include "bitset"
#include "set"


PasswordManager::PasswordManager() {};

string PasswordManager::passwordCreation() {
    int usersChoice;
    bool accepted = false;
    cout<<"Podaj haslo, ktore ma zostac dopisane do pliku (1) lub wygeneruj haslo (2). "
          "Wybierz jedna z opcji wpisujac 1 lub 2."<<endl;

    switch (UserCommunicator::userInputExceptionHandler()) {
        case 1:
            while(!accepted) {
                cout << "Teraz prosze podac haslo(haslo nie moze zawierac: [,],\\,space):" << endl; //bugfix na spacje
                std::getline(cin, currentPassword);
                cout << "Sila wybranego przez ciebie hasla (w skali do 100) to: " << passwordScore()<<endl;
                if(passwordScore()==0) {
                    cout << "Niestety twoje haslo zawiera jednek z zakazanych znakow, prosze podac nowe haslo" << endl;
                    accepted = false;
                }else {
                    cout << "Jezeli ci to odpowiada wpisz 1, "
                            "jezeli chcesz zmienic haslo wpisz 2" << endl;
                    cin >> usersChoice; //jezeli bedzie blad szukaj tu
                    if (usersChoice == 1)
                        accepted = true;
                }
            }
            break;
        case 2:
            currentPassword = passwordCreator();
            break;

    }

    return currentPassword;

}
string PasswordManager::passwordCreator() {
    string password = "";
    int numberOfChars;
    bool normalAndCapital = false;
    bool specialSymbols = false;
    bool correctAnswer = false;

    while(!correctAnswer){
    cout<<"Podaj z ilu znakow ma skladac sie twoje haslo(Wpisz liczbe pomiedzy 6-32): "<<endl;
    cin>>numberOfChars;
        if(numberOfChars<6 || numberOfChars>32)
            cout<<"Twoja liczba jest poza zakresem. "<<endl;
        else
            correctAnswer = true;
    }



    cout<<"Czy twoje haslo ma zawierac male i wielkie litery? 1 - Tak, 2 - Nie: "<<endl;
    if(UserCommunicator::userInputExceptionHandler() == 1) {
        normalAndCapital = true;
    }



    cout<<"Czy twoje haslo ma zawierac znaki specjalne? 1 - Tak, 2 - Nie: "<<endl;
     ;
    if(UserCommunicator::userInputExceptionHandler() == 1) {
        specialSymbols = true;
    }


    srand((unsigned int) time (NULL));
    int max ,min, randomNumber;

    for(int i=0; i<numberOfChars; i++){
        if(normalAndCapital && specialSymbols) {
            max = 122;
            min = 33;
            do {
                randomNumber = (rand() % (max - min)) + min;
            }while(randomNumber>90 && randomNumber<97);
            password += (char) randomNumber;

        }else if(normalAndCapital){
            max = 122;
            min = 48;
            do {
                randomNumber = (rand() % (max - min)) + min;
            }while(!(randomNumber<58 || (randomNumber>64 && randomNumber<91) || (randomNumber>96 && randomNumber<123)));
            password += (char) randomNumber;

        }else if(specialSymbols){
            max = 64;
            min = 33;

            randomNumber = (rand() % (max - min)) + min;
            password += (char) randomNumber;
        }else{
            max = 57;
            min = 48;
            randomNumber = (rand() % (max - min)) + min;
            password += (char) randomNumber;
        }
    }
    return password;
}
double PasswordManager::passwordScore() {

    double currentScore = 100;
    int specialSigns = 0;
    int numbers = 0;
    int letters = 0;
    int capital = 0;
    bool illegalCharacters = false;
    set<char> set;
    currentScore -= currentPassword.length()<12?(12-(double)currentPassword.length())*5:(12-(double)currentPassword.length())*2;
    for(char _char : currentPassword){
        set.insert(_char);
    }
    currentScore -= (currentPassword.length() - set.size())*2.5;
    for(char _char : currentPassword) {
        if ((_char > 32 && _char < 48) || (_char > 57 && _char < 65) || (_char > 93 && _char < 97) ||
            (_char > 122 && _char < 127))
            specialSigns++;
        else if (_char > 47 && _char < 58)
            numbers++;
        else if (_char > 64 && _char < 91)
            capital++;
        else if (_char > 96 && _char < 123)
            letters++;
        else
            illegalCharacters = true;
    }
        currentScore -= specialSigns<2?(2-specialSigns)*15:0;
        currentScore -= numbers<1?20:0;
        currentScore -= capital<1?15:0;
        currentScore -= letters<1?15:0;

        if(illegalCharacters)
            currentScore = 0;
        else if(currentScore>100)
            currentScore = 100;

        return currentScore;

}


