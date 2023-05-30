//
// Created by Grzegorz Olszewski on 24/05/2023.
//

#include "FileOperator.h"

#include <utility>
#include <sstream>
#include "iostream"
#include "filesystem"
#include "UserCommunicator.h"
#include "math.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;

FileOperator::FileOperator(const string& filePath): filePath(filePath) {


    std::fstream passwordFile(filePath, std::ios::in);
    if(passwordFile.is_open()){
        string line;
        while(std::getline(passwordFile, line)){
            passwordLines.push_back(PasswordLine::fromLineToPasswordLine(line));
        }
        passwordFile.close();
    }

    for(const PasswordLine& passwordLine : passwordLines) {
        addCategory(passwordLine.getCategory());
    }


}

string FileOperator::fileChooser() {
    auto dirPath = string("../PlikiZHaslami");
    std::map<string, string> mapa;
    string fileName;
    bool fileChosen = false; //wystarczy while true ale nwm czy dobrze tak bedzie
    auto dirIter = std::filesystem::directory_iterator(dirPath);
    for(auto const& entry : dirIter){
        if(entry.is_regular_file())
            mapa.insert({entry.path().filename().string(), entry.path().string()});
    }
    cout<<"Wybierz plik z ktorego chcesz skorzystac, sposrod wypisanych plikow"
          " wpisujac jego dokladna nazwe wraz z rozszerzeniem .txt"<<endl;
    for(auto[k, v] : mapa){
        cout<<k<<" ";
    }
    cout<<endl;

    while(!fileChosen){
        cin>>fileName;
        if(mapa.find(fileName) == mapa.end())
            cout<<"Niestety nazwa pliku zostala blednie wpisana prosze sprobowac raz jeszcze"<<endl;
        else
            return mapa.at(fileName);
    }

}

void FileOperator::addCategory(const string &category) {
    categories.insert(category);
}

void FileOperator::addPassword(string const& password) {

    string name, category, site, login, line;
    int userChoice;
    cout<<"Prosze podac nazwe hasla:"<<endl;
    name = UserCommunicator::userEmptyStringExceptionHandler();
    cout<<"Czy chcesz wybrac jedna z instniejacych kategorii (1) lub wpisac wlasna kategorie (2). Wpisz 1 lub 2."<<endl;
    if(UserCommunicator::userInputExceptionHandler() == 2){
        cout << "Prosze podac kategorie: " << endl;
        category = UserCommunicator::userEmptyStringExceptionHandler();
        addCategory(category);
    }else{
        if(categories.empty()) {
            cout << "Niestety nie utowrzono jeszcze zadnej kategorii, prosze wpisac nowa kategorie:" << endl;
            category = UserCommunicator::userEmptyStringExceptionHandler();
            addCategory(category);
        }else{
            std::vector vec(categories.begin(), categories.end());
            do {
                cout << "Wybierz jedna z kategorii wpisujac poprzedzajaca ja liczbe: " << endl;
                for (int i = 0; i < vec.size(); i++) {
                    cout <<std::to_string(i) + " - " +  vec.at(i)<<endl;
                }
                cin>>userChoice;

            } while (userChoice<0 || userChoice>=categories.size());
                category = vec.at(userChoice);
        }
    }

    cout<<"Czy chcesz wpisac strone? Tak - 1, Nie - 2"<<endl;
    userChoice = UserCommunicator::userInputExceptionHandler();
    if(userChoice == 1) {
        cout << "Podaj strone do ktorej odpowiada haslo: "<<endl;
        site = UserCommunicator::userEmptyStringExceptionHandler();
    }else
        site = "---";

    userChoice = 0;

    cout<<"Czy chcesz wpisac login? Tak - 1, Nie - 2"<<endl;
    userChoice = UserCommunicator::userInputExceptionHandler();
    if(userChoice == 1) {
        cout << "Podaj login ktoremu odpowiada haslo: "<<endl;
        login = UserCommunicator::userEmptyStringExceptionHandler();
    }else
        login = "---";

    line = EncoderDecoder::encoder(name) + " "
            + EncoderDecoder::encoder(password) + " "
            + EncoderDecoder::encoder(category) + " "
            + EncoderDecoder::encoder(site) + " "
            + EncoderDecoder::encoder(login) + "\n";

    passwordLines.push_back(PasswordLine::fromLineToPasswordLine(line));
}

vector<PasswordLine> FileOperator::searchPassword() {

    bool finished = false;
    string userInput;
    int intUserInput;
    vector<PasswordLine> foundPasswords = passwordLines;
    vector<PasswordLine> matchingPasswords;
    while(!finished){
        cout<<"Prosze wybrac na podstawie jakiego parametru wyszukac haslo :"
              "\n 1 - Nazwa"
              "\n 2 - Haslo"
              "\n 3 - Kategoria"
              "\n 4 - Strona WWW / Serwis"
              "\n 5 - Login"<<endl;
        intUserInput = UserCommunicator::userOneToFiveChoiceExceptionHandler();

        cout<<"Prosze podac wartosc parametru:"<<endl;
        userInput = UserCommunicator::userEmptyStringExceptionHandler();

        for(const PasswordLine& passwordLine: foundPasswords)
            switch (intUserInput) {
                case 1:
                    if(passwordLine.getName() == userInput)
                        matchingPasswords.push_back(passwordLine);
                    break;
                case 2:
                    if(passwordLine.getPassword() == userInput)
                        matchingPasswords.push_back(passwordLine);
                    break;
                case 3:
                    if(passwordLine.getCategory() == userInput)
                        matchingPasswords.push_back(passwordLine);
                    break;
                case 4:
                    if(passwordLine.getSite() == userInput)
                        matchingPasswords.push_back(passwordLine);
                    break;
                case 5:
                    if(passwordLine.getLogin() == userInput)
                        matchingPasswords.push_back(passwordLine);
                    break;
            }
        if(matchingPasswords.empty()){
            cout<<"Niestety nie znaleziono zadnego hasla odpowiadajacego podanym wymaganiom, "
                  "czy chcesz sprobowac jeszcze raz? Tak - 1, Nie - 2"<<endl;
            if(UserCommunicator::userInputExceptionHandler()==2)
                finished = true;
        }else {
            cout <<"Znalezione hasla to: "<<endl;
            for(const PasswordLine& passwordLine: matchingPasswords)
                cout<<passwordLine.operator string()<<endl;
            cout<<"Czy ponowic wyszukiwanie wsrod znalezionych hasel? Tak - 1, Nie - 2 "<<endl;
            if(UserCommunicator::userInputExceptionHandler() == 2)
                finished = true;

            foundPasswords = matchingPasswords;
            matchingPasswords.clear();
        }
    }
    return foundPasswords;
}

void FileOperator::editPassword() {

    cout<<"Wyszukaj hasla, ktore bedziesz chcial edytowac"<<endl;
    vector<PasswordLine> toEdit = FileOperator::searchPassword();
    vector<int> possibleChoices;
    int index;
    int userChoice;
    bool finished = false;
    string stringInput;
    cout<<"Wybierz linie, ktore chcesz edytowac wpisujac poprzedzajaca je cyfre."<<endl;
    for(int i=0; i<passwordLines.size(); i++){
        for(int j = 0; j<toEdit.size(); j++){
            if(passwordLines[i] == toEdit[j]) {
                cout << std::to_string(i) + " - " + passwordLines[i].operator string()<<endl;
                possibleChoices.push_back(i);
            }
        }
    }
    cin>>index;
    while(std::find(possibleChoices.begin(), possibleChoices.end(), index) == possibleChoices.end()){
        cout<<"Niestety podana wartosc nie odpowiada zadnemu ze znalezionych hasel, sprobuj ponownie."<<endl;
        cin>>index;
    }

    while(!finished) {
        cout<<"Prosze wybrac parametr do zmiany :"
              "\n 1 - Nazwa"
              "\n 2 - Haslo"
              "\n 3 - Kategoria"
              "\n 4 - Strona WWW / Serwis"
              "\n 5 - Login"<<endl;

        userChoice = UserCommunicator::userOneToFiveChoiceExceptionHandler();


        switch (userChoice) {
            
            case 1:
                cout<<"Prosze wprowadzic nowa nazwe: "<<endl;
                passwordLines[index].setName(UserCommunicator::userEmptyStringExceptionHandler());
                break;
            case 2:
                cout<<"Prosze wprowadzic nowe haslo: "<<endl;
                passwordLines[index].setPassword(UserCommunicator::userEmptyStringExceptionHandler());
                break;
            case 3:
                cout<<"Prosze wprowadzic nowa kategorie: "<<endl;
                stringInput = UserCommunicator::userEmptyStringExceptionHandler();
                addCategory(stringInput);
                passwordLines[index].setCategory(stringInput);
                break;
            case 4:
                cout<<"Prosze wprowadzic nowa strone: "<<endl;
                passwordLines[index].setSite(UserCommunicator::userEmptyStringExceptionHandler());
                break;
            case 5:
                cout<<"Prosze wprowadzic nowy login: "<<endl;
                passwordLines[index].setLogin(UserCommunicator::userEmptyStringExceptionHandler());
                break;
        }

        cout<<"Czy chcesz zmienic jeszcze jakis parametr? Tak - 1, Nie - 2"<<endl;
        if(UserCommunicator::userInputExceptionHandler()==2)
            finished = true;
    }



}



FileOperator::~FileOperator() {

    std::fstream passwordFileOut(filePath, std::ios::out);
    while(passwordFileOut.is_open()){
        for(const PasswordLine& passwordLine:passwordLines)
            passwordFileOut<<PasswordLine::fromPasswordToEncodedLine(passwordLine) + "\n";
        passwordFileOut.close();
    }

}

void FileOperator::wypiszHasla() {

    for(const PasswordLine& passwordLine : passwordLines){
        cout<<passwordLine.operator string()<<endl;
    }
//    categories.clear();
}

void FileOperator::sortPasswords() {

    vector<int> parameters;
    bool finished;
    int userChoice;

    auto nameComparator = [](PasswordLine parameter1, PasswordLine parameter2) -> bool{
        return std::lexicographical_compare(parameter1.getName().begin(), parameter1.getName().end(),
                                            parameter2.getName().begin(), parameter2.getName().end());
    };
    auto passwordComparator = [](PasswordLine parameter1, PasswordLine parameter2) -> bool{
        return std::lexicographical_compare(parameter1.getPassword().begin(), parameter1.getPassword().end(),
                                            parameter2.getPassword().begin(), parameter2.getPassword().end());
    };
    auto categoryComparator = [](PasswordLine parameter1, PasswordLine parameter2) -> bool{
        return std::lexicographical_compare(parameter1.getCategory().begin(), parameter1.getCategory().end(),
                                            parameter2.getCategory().begin(), parameter2.getCategory().end());
    };
    auto siteComparator = [](PasswordLine parameter1, PasswordLine parameter2) -> bool{
        return std::lexicographical_compare(parameter1.getSite().begin(), parameter1.getSite().end(),
                                            parameter2.getSite().begin(), parameter2.getSite().end());
    };
    auto loginComparator = [](PasswordLine parameter1, PasswordLine parameter2) -> bool{
        return std::lexicographical_compare(parameter1.getLogin().begin(), parameter1.getLogin().end(),
                                            parameter2.getLogin().begin(), parameter2.getLogin().end());
    };

    while(!finished) {
        cout << "Wybierz parametry, po ktorych chcesz posortowac hasla, na ten moment zostaly dodane "
             << parameters.size() << " parametry, konieczne jest podanie conajmniej 2. Wybierz sposrod: "
                                     "\n 1 - Nazwa"
                                     "\n 2 - Haslo"
                                     "\n 3 - Kategoria"
                                     "\n 4 - Strona WWW / Serwis"
                                     "\n 5 - Login" << endl;
        userChoice = UserCommunicator::userOneToFiveChoiceExceptionHandler();
        while (std::find(parameters.begin(), parameters.end(), userChoice) != parameters.end()) {
            cout<<"Parametr - "<<userChoice<<" zostal juz wybrany, prosze wybrac inny parametr!"<<endl;
            userChoice = UserCommunicator::userOneToFiveChoiceExceptionHandler();
        }

        parameters.push_back(userChoice);
        if (parameters.size() >= 2 && parameters.size() < 5) {
            cout << "Czy chcesz dodac kolejny parametr? Tak - 1, Nie - 2" << endl;
            if (UserCommunicator::userInputExceptionHandler() == 2)
                finished = true;
        } else if (parameters.size() == 5) {
            cout << "Dodales juz wszystkie mozliwe parametry." << endl;
            finished = true;
        }
    }

    cout<<"Przechodze do sortowania!"<<endl;

    std::reverse(parameters.begin(), parameters.end()); //odwracam zeby sortowac w takiej kolejnosci jak podawalem parametry

    while(!parameters.empty()) {
        switch (parameters.back()) {
            case 1:
                std::sort(passwordLines.begin(), passwordLines.end(), nameComparator);
                break;
            case 2:
                std::sort(passwordLines.begin(), passwordLines.end(), passwordComparator);
                break;
            case 3:
                std::sort(passwordLines.begin(), passwordLines.end(), categoryComparator);
                break;
            case 4:
                std::sort(passwordLines.begin(), passwordLines.end(), siteComparator);
                break;
            case 5:
                std::sort(passwordLines.begin(), passwordLines.end(), loginComparator);
                break;
        }
        parameters.pop_back();
    }

    cout<<"Gotowe, hasla posortowane!"<<endl;

}

void FileOperator::deletePassword() {

    vector<PasswordLine> toDelete;
    int userInput;

    cout<<"Prosze wyszukac hasla ktore chcesz usunac."<<endl;
    toDelete = searchPassword();
    while(toDelete.empty()){
        cout<<"Nie dostarczono zadnych hasel. Chcesz sprobowac ponownie? Tak - 1, Nie - 2"<<endl;
        if(UserCommunicator::userInputExceptionHandler()==2)
            return;
    }

    for(int i=0; i<toDelete.size(); i++){

        cout<<"Czy na pewno chcesz usunac to haslo?: "<<toDelete.at(i).operator string()<<endl;
        cout<<"Tak - 1, Nie - 2"<<endl;
        if(UserCommunicator::userInputExceptionHandler() == 1)
            for(int j=0; j<passwordLines.size(); j++){
                if(passwordLines.at(j) == toDelete.at(i)){
                    passwordLines.erase(passwordLines.begin() + j);
                    cout << "Haslo: " << toDelete.at(i).operator string() << ", zostalo usuniete." << endl;
                }
            }
    }
}

void FileOperator::deleteCategory() {

    int userInput;
    string chosenCategory;
    vector<string> categoriesVec(categories.begin(), categories.end());
    cout<<"Wybierz kategorie, ktora chcesz usunac."<<endl;
    for(int i=0; i<categoriesVec.size(); i++){
        cout<<i<<" - "<<categoriesVec.at(i)<<endl;
    }

    do {
        cout<<"Wpisz liczbe z zakresu 0 - "<<(categoriesVec.size()-1)<<", odpowiadajaca wybranej kategorii."<<endl;
        cin >> userInput;
    }while(userInput>0 && userInput<categoriesVec.size());

    chosenCategory = categoriesVec.at(userInput);

    for(int i=0; i<passwordLines.size(); i++){
        if(passwordLines.at(i).getCategory() == chosenCategory)
            passwordLines.erase(passwordLines.begin() + i);
    }

    categories.erase(chosenCategory);

    cout<<"Kategoria "<<chosenCategory<<", wraz ze wszystkimi haslami, ktore do niej nalezaly zostala usunieta."<<endl;

}
