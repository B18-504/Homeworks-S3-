#ifndef INTERFACE_H
#define INTERFACE_H
#define GREEN "\033[0;32m"
#define WHITE "\033[0m"

#include <vector>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

int getch()
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

struct InterfaceItem {
    void (*performer)(void*) = nullptr;
    std::string name = "none";
    std::string type = "Default"; //YesNo or MultiState or Default
    std::string* states = nullptr;
    int statesLength = 0;
    int state = 0; //Position in array
    bool yesNo = false; //0-no 1-yes
};

class Interface {
    public:
        int addItem(InterfaceItem item) {
            items.push_back(item);
            length++;

            if (item.type == "YesNo"){
                this->ynStates.push_back(item.name);
                if (item.yesNo){
                    this->ynStates.push_back("yes");
                }else{
                    this->ynStates.push_back("no");
                }
            }

            if (item.type == "MultiState"){
                this->multiStates.push_back(item.name);
                this->multiStates.push_back(item.states[item.state]);
            }

            return length-1;
        }

        void drawMenu() {
            std::cout << "Menu:\n";
            for (int i = 0; i < length; i++){
                InterfaceItem currentItem = items[i];
                if (marked == i) {
                    std::cout << GREEN << currentItem.name << WHITE;
                }else{
                    std::cout << currentItem.name;
                }

                if(currentItem.type == "Default"){
                    std::cout << "\n";
                    continue;
                }

                if (currentItem.type == "YesNo"){
                    if(currentItem.yesNo) std::cout << ": Да\n";
                    else std::cout << ": Нет\n";
                    continue;
                }

                if (currentItem.type == "MultiState"){
                    std::cout << ": " << currentItem.states[currentItem.state] << "\n";
                    continue;
                }
            }
        }

        void start() {
            std::system("clear");
            this->drawMenu();
            while (true) {
                int ch = getch();
                if (ch == 113){
                    break;
                }
                if (ch == 10){
                    std::system("clear");
                    if(items[marked].type == "Default"){
                        items[marked].performer((void*)this);
                        int listener;
                        while(listener = getch()){
                            if (listener == 113) break;
                        }
                        std::system("clear");
                        this->drawMenu();
                    }
                    continue;
                }

                getch();
                ch = getch();

                switch(ch) {
                    case 65: //UP
                        if (marked > 0) marked--;
                        std::system("clear");
                        drawMenu();
                        break;
                    case 66: //DOWN
                        if (marked < length-1) marked++;
                        std::system("clear");
                        drawMenu();
                        break;
                    case 68: //LEFT
                        if (items[marked].type == "MultiState") {
                            if(items[marked].state > 0) items[marked].state--;
                            this->setMultiState(items[marked].name, items[marked].states[items[marked].state]);
                        }
                        if (items[marked].type == "YesNo") {
                            items[marked].yesNo = !items[marked].yesNo;
                            this->setYnState(items[marked].name, items[marked].yesNo);
                        }
                        std::system("clear");
                        drawMenu();
                        break;
                    case 67: //RIGHT
                        if (items[marked].type == "MultiState") {
                            if(items[marked].state < items[marked].statesLength - 1) items[marked].state++;
                            this->setMultiState(items[marked].name, items[marked].states[items[marked].state]);
                        }
                        if (items[marked].type == "YesNo") {
                            items[marked].yesNo = !items[marked].yesNo;
                            this->setYnState(items[marked].name, items[marked].yesNo);
                        }
                        std::system("clear");
                        drawMenu();
                        break;
                }
            }
        }

        void setYnState(std::string ynTitle, bool state){
            for(int i = 0; i < this->ynStates.size(); i+=2){
                if (ynStates[i] == ynTitle){
                    if (state) ynStates[i + 1] = "yes";
                    else ynStates[i + 1] = "no";
                    return;
                }
            }
        }

        void setMultiState(std::string ynTitle, std::string state){
            for(int i = 0; i < this->multiStates.size(); i+=2){
                if (multiStates[i] == ynTitle){
                    multiStates[i + 1] = state;
                    return;
                }
            }
        }

        void* getDataSet(int index){
            return this->dataSets[index];
        }

        std::string getYnState(std::string ynTitle){
            for(int i = 0; i < this->ynStates.size(); i+=2){
                if (ynStates[i] == ynTitle) return ynStates[i + 1];
            }
            return "None";
        }

        std::string getMultiState(std::string multiTitle){
            for(int i = 0; i < this->multiStates.size(); i+=2){
                if (multiStates[i] == multiTitle) return multiStates[i + 1];
            }
            return "None";
        }

        void addDataSet(void* pointer){
            this->dataSets.push_back(pointer);
        }

        void restoreDataSet(void* pointer, int index){
            this->dataSets[index] = pointer;
        }

    private:
        std::vector<InterfaceItem> items;
        int length = 0;
        int marked = 0;
        std::vector<void*> dataSets;
        std::vector<std::string> ynStates;
        std::vector<std::string> multiStates;
};

#endif