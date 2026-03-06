#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <utility>
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
            outfile << card.character << " " << card.romaji <<std::endl;
        }
        std::cout<<"Succesfully saved "<<deck.size()<<" characters to file."<<std::endl;
        outfile.close();
    }
    else {
        std::cout<<"Error : Could not open txt file"<<std::endl;
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
    if (chara == "quit" || chara == "QUIT" || chara == "Quit") {
        return true;
    }
    return false;
}
void quizdeck(const std::vector<HiraganaCard>& deck) {
    if (deck.empty()){
        std::cout<<"Your deck is empty! Load some cards first to have a quiz. \n";
        return;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0,deck.size()-1);
    std::string answer;
    std::cout<<"\n QUIZ MODE \n";
    std::cout<<"Type quit to exit back to the main menu \n";
    while(true) {
        int randomindex = distrib(gen);
        HiraganaCard target = deck[randomindex];
        std::cout<<"What is the romaji for "<<target.character<<"? :";
        std::getline(std::cin,answer);
        for (char &l : answer) {
            l = std::toupper(l);
        }
        if (wantstoquit(answer)) break;
        if (answer == target.romaji) {
            std::cout<<"\nCorrect Answer!\n";
        } else {
            std::cout<<"\nWrong Answer. The correct answer is "<<target.romaji<<".\n";
        }
    }
}
int main() {
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
                std::cout<<"\n --Add mode-- \n";
                std::cout<<"Type in quit to exit\n";
                std::string inputchar;
                std::string inputromaji;
                while(true) {
                    std::cout<<"Enter a kana :";
                    std::getline(std::cin,inputchar);
                    if(wantstoquit(inputchar)) break;
                    std::cout<<"\nEnter the romaji of the given kana :";
                    std::getline(std::cin,inputromaji);
                    for (char &l : inputromaji) {
                        l = std::toupper(l);
                    }
                    if(wantstoquit(inputromaji)) break;
                    deck.push_back(HiraganaCard(inputchar,inputromaji));
                    std::cout<<"Card added to the deck succesfully!\n";
                }
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