#include <iostream>

int generate(int);
void playFunc();
int selectLevel();
int game(int);
bool play = true;

int main()
{
    playFunc();
}


void playFunc() {
    int level = 1;
    char choose;
    while (play) {
        std::cout << "[Level " << level << "] Woul'd like to play? [p] - play, [l] - select level, [q] - exit." << std::endl;
        std::cin >> choose;
        switch (choose) {
            case 'p':
                game(level);
            break;
            case 'l':
                level = selectLevel();
            break;
            case 'q':
                play = false;
            break;
            default:
                std::cout << "Wrong symbol!" << std::endl;
            break;
        }
    }
}


int game(int level) {
    int count = 10;
    int number = generate(level);
    int guess = 0;
    while (count > 0 && play) {
        std::cout << "You have " << count << " attempts." << std::endl << "Choose a number betwen 0 and " << level*10 << std::endl;
        std::cin >> guess;
        if (guess == number) {
            std::cout << "You WIN! Attempts: " << 11-count << std::endl;
            break;
        } else {
            std::cout <<"Wrong number!" << std::endl;
            if (guess < number) {
                std::cout << "Greater!" << std::endl;
            } else {
                std::cout << "Less!" << std::endl;
            }
            count--;
        }
    }
    if (count > 0) {
        return 0;
    } else {
        std::cout << "You lost!" << std::endl;
    }
}

int generate(int level) {
    int number = rand()%100;
    if (number >= level*10) {
        number = generate(level);
    }
    return number;
}

int selectLevel() {
    int level = 1;
    do {
        std::cout << "Enter level: ";
        std::cin >>level;
    } while (level > 10);
    return level;
}
