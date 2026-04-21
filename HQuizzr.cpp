#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <utility>
#include <windows.h>
class HiraganaCard {
    public:
        std::string character{"Unknown"};
        std::string romaji{"Unknown"};
        HiraganaCard(std::string c, std::string r): character{std::move(c)}, romaji{std::move(r)} {};
};
void savedeck(const std::vector<HiraganaCard>& deck){
    std::ofstream outfile("Hiragana.txt");
    if(outfile.is_open()){
        for(const auto& card : deck){
            outfile << card.character << " " << card.romaji << "\n";
        }
        std::cout<<"\nSuccesfully saved "<<deck.size()<<" characters to file.\n";
        outfile.close();
    }
    else {
        std::cout<<"\nError : Could not open txt file\n"<<std::endl;
    }
    
}
void loaddeck(std::vector<HiraganaCard>& deck) {
    std::ifstream infile("Hiragana.txt");
    std::string tempchar;
    std::string tempromaji;
    if(infile.is_open()) {
        while (infile >> tempchar >> tempromaji) {
            deck.push_back(HiraganaCard(tempchar,tempromaji));
        }
        std::cout<<"Succesufully loaded cards from txt file."<<std::endl;
        infile.close();
    }
    else {
        std::cout<<"ERROR : Could not find the hiragana txt file"<<std::endl;
    }
}
bool wantstoquit(std::string chara) {
    for (char &quit : chara){
        quit = std::tolower(quit);
    }
    if(chara == "quit") {
        return true;
    }
    return false;
}
void add_mode(std::vector<HiraganaCard>& deck) {
    std::cout<<"\n --Add mode-- \n";
    std::cout<<"Type in quit to exit\n";
    std::string inputchar;
    std::string inputromaji;
    while(true) {
        std::cout<<"Enter a kana :";
        std::getline(std::cin,inputchar);
        if(wantstoquit(inputchar)) return;;
        std::cout<<"\nEnter the romaji of the given kana :";
        std::getline(std::cin,inputromaji);
        for (char &l : inputromaji) {
            l = std::toupper(l);
        }
    }
    if(wantstoquit(inputromaji)) return;
    deck.push_back(HiraganaCard(inputchar,inputromaji));
    std::cout<<"Card added to the deck succesfully!\n";

}
void quizdeck(const std::vector<HiraganaCard>& deck) {
    if (deck.empty()){
        std::cout<<"Your deck is empty! Load some cards first to have a quiz. \n";
        return;
    }
    int score{0},question{0};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0,deck.size()-1);
    std::string answer;
    std::cout<<"\n QUIZ MODE \n";
    std::cout<<"Type quit to exit back to the main menu \n";
    while(true) {
        int randomindex = distrib(gen);
        
        HiraganaCard target = deck[randomindex];
        std::cout<<"\nWhat is the romaji for "<<target.character<<"? :";
        std::getline(std::cin,answer);
        for (char &l : answer) {
            l = std::tolower(l);
        }
        if (wantstoquit(answer)){ 
            std::cout<<"\nYou got "<<score<<" out of "<<question<<" right!";
            break;
        }
        question++;
        if (answer == target.romaji) {
            score++;
            std::cout<<"\nCorrect Answer!\n";
        } else {
            std::cout<<"\nWrong Answer. The correct answer is "<<target.romaji<<".\n";
        }
    }
}
int main() {
    SetConsoleOutputCP(CP_UTF8);
    std::vector<HiraganaCard> deck;
    loaddeck(deck);
    int choice = 0;
    while(true){
        std::cout<<"\n ===Japanese Flashcards=== \n";
        std::cout<<"1. Add new cards.\n";
        std::cout<<"2. Quiz Mode.\n";
        std::cout<<"3. Save and Exit.\n";
        std::cout<<"Enter an option from the given :";
        if(!(std::cin>>choice)) {
            std::cout<<"\nInvalid Input! Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(1000,'\n');
            continue;
        }
        std::cin.ignore(1000,'\n');
        switch(choice) {
            case 1: {
                add_mode(deck);
                break;
            }
            case 2: {
                quizdeck(deck);
                break;
            }
            case 3: {
                savedeck(deck); 
                std::cout<<"Exiting....\n";
                return 0;
            }
            default : {
                std::cout<<"Please enter according to the option given.\n";
            }
        }
    }
    return 0;
}