//
// Created by Grzegorz Olszewski on 24/05/2023.
//

#include "iostream"
#include "FileOperator.h"


#include "UserCommunicator.h"
string UserCommunicator::mainPassword;
string UserCommunicator::pathChooser() {

    int userChoice;
    string passwordAttempt;
    bool accessGranted = false;
    while (!accessGranted) {
        cout << "Prosze zalogowac sie podajac haslo:" << endl;
        std::getline(cin, passwordAttempt);
        if (!(accessGranted = authorization(passwordAttempt)))
            cout << "Niestety podales bledne haslo, sprobuj jeszcze raz." << endl;
        else {
            mainPassword = passwordAttempt;
        }
  }

        cout
                << "Witamy w menadżerze hasel. \nMożesz podać scieżkę do pliku z którego chcesz skorzystać (1) lub wybrać plik "
                   "znajdujący się w folderze programu (2), dokonaj wyboru wpisując 1 lub 2." << endl;
        cin >> userChoice;
        switch (userChoice) {
            case 1:
                cout << "Podaj scieżkę absolutną do pliku" << endl;
                cin >> filePath;
                break;
            case 2:
                filePath = fileOperator.fileChooser();
                break;
        }

        return filePath;
}

UserCommunicator::UserCommunicator(): fileOperator(pathChooser()){


    fileOperator.wypiszHasla();

    cout<<endl;

    bool finished = false;

    while(!finished) {
        int usersChoice = -1;
        while (usersChoice < 0 || usersChoice > 8) {
            cout << "Oto lista mozliwych operacji, ktore mozesz wykonac w wybranym przez siebie pliku:"
                    "\n 1 - Wyszukaj hasla " // tutaj jeszcze beda parametry ktore mozna wybrac
                    "\n 2 - Posortuj hasla " // tutaj podajemy po czym mozemy posortowac conajmniej 2 np. nazwa i kategoria
                    "\n 3 - Dodaj haslo "
                    "\n 4 - Edytuj haslo "
                    "\n 5 - Usun haslo " //Przed kazdym usunieciem informujemy uzytkownika szczegolnie jezeli usuwamy wiecej niz jedno
                    "\n 6 - Dodaj kategorie "
                    "\n 7 - Usun kategorie" << endl;
            cin >> usersChoice;
            if (usersChoice < 0 || usersChoice > 8)
                cout << "Prosze podaj liczbe z zakresu od 1 do 7" << endl;
        }

        switch (usersChoice) {
            case 1:
                fileOperator.searchPassword();
                break;
            case 2:
                fileOperator.sortPasswords();
                break;
            case 3:
                fileOperator.addPassword(passwordManager.passwordCreation());
                break;
            case 4:
                fileOperator.editPassword();
                break;
            case 5:
                fileOperator.deletePassword();
                break;
            case 6:
                cout<<"Prosze podac kategorie, ktora chcesz dodac:"<<endl;
                fileOperator.addCategory(UserCommunicator::userEmptyStringExceptionHandler());
                cout<<"Kategoria zostala pomyslnie dodana"<<endl;
                break;
            case 7:
                fileOperator.deleteCategory();
                break;
        }

        cout<<"Czy chcesz wykonac kolejna operacje? Tak - 1, Nie - 2 "<<endl;
        if(UserCommunicator::userInputExceptionHandler()==2)
            finished = true;
    }
}

int UserCommunicator::userInputExceptionHandler() {
    string userInput;

    while(userInput.empty()){
        std::getline(cin, userInput);
    }
    while(userInput != "1"  && userInput != "2"){
        cout<<"Niestety dostarczono niewlasciwa wartosc prosze podac 1 lub 2"<<endl;
        std::getline(cin, userInput);
    }
    return std::stoi(userInput);
}

string UserCommunicator::userEmptyStringExceptionHandler() {
    string input;
    while(input.empty()){
        std::getline(cin, input);
    }

    return input;
}

int UserCommunicator::userOneToFiveChoiceExceptionHandler() {
    string userChoice;
    while(userChoice.empty()){
        std::getline(cin, userChoice);
    }

    while (userChoice != "1" && userChoice != "2" && userChoice != "3" && userChoice != "4" && userChoice != "5") {
        cout << "Niestety dostarczono niewlasciwa wartosc prosze podac 1, 2, 3, 4 lub 5" << endl;
        cin >> userChoice;
    }
    return std::stoi(userChoice);
}

bool UserCommunicator::authorization(const string& password) {

    string passwordCheck = "CBGFFPGHGJELBBEDGHFJBPGCGEABGCGEEC";
    if(EncoderDecoder::decoder(password, passwordCheck)==password) {
        return true;
    }else
        return false;

}




