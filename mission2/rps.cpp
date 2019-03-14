#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char * argv[]) 
{
    cout << "Hello! Lets play RPS." << endl;
    string again = "yes";
    while (again == "yes") 
    {
        int user;
        int pc;
        cout << "Select Rock - 1; Papper - 2; Scissors - 3: ";
        cin >> user;
        pc = 1 + (rand() % 3);
        cout << pc << endl;
        if ((user == 1 && pc == 2) || (user == 2 && pc == 3) || (user == 3 && pc == 1)) 
        {
            cout << "You're LOSER!" << endl;
        } else if ((user == 1 && pc == 1) || (user == 2 && pc == 3) || (user == 3 && pc == 3)) 
        {
            cout << "Round draw." << endl;
        } else 
        {
            cout << "We have winner.";
        }
        cout << "Again? (yes/no): ";
        cin >> again;
    }
}