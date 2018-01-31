#include <iostream>
#include <array>
#include <random>
#include <fstream>
#include <conio.h>

#include "ini.h"
/////////////////////////////////
#define GAME_TITLE Gra
/////////////////////////////////
//Easy - 6; Normal - 8; Hard - 10; default: 8
#define GAME_LEVEL 6 //REMEMBER - IF YOU OVERDRIVE THIS SHIT, EFFECTS MAYBE INCALCULABLE
/////////////////////////////////
//Variety of traps (1-12); default 12
#define TRAPS 10
/////////////////////////////////
//Dice walls - default: 6
#define DICEWALL 6
/////////////////////////////////
//Board length; default: 70
#define BOARDLENGTH 70
/////////////////////////////////
//Number of players; default: 2
#define PLAYERS 2
/////////////////////////////////

using namespace std;
int main();
class Player
{

public:

    friend class Game;
    string name;
    int position;
    bool tour;

/*
*    void moveon(int x) //Moveing in your turn
*    {
*        position = x;
*    }
*/

    void create(int i = 0)
    {
        if(i == 0) cout << "Introduce yourself.." << endl;
        cout << i+1 << ") Player Name: "; cin >> name;
        position = 0;
        tour = false;
    }

    Player()
    {
       name = "Player";
       position = 0;
       tour = false;
    }
};

class Game
{
public:
    string data;
    fstream file;
    int board[BOARDLENGTH];

    int dice(int w = DICEWALL) //Keep'n rolling
    {
        if(w <= 0)
        cout << "Error: Dice has no walls!!"<<endl;
        else
        return rand()% w + 1;
    }

    int trap() //Check your fatality :D
    {
/* Returns(12):
* 0: Lost Turn
* 1-8: Some loses
* 9-11: Some getting
* 12: Back to start
*/
        int a = rand()% TRAPS;
        switch(a)
        {
        case 0:
            {
            cout << "you fall into huge hole, you had broked your leg" << endl;
            return 2;
            //break;
            }
        case 1:
            {
            cout << "you had step into slippy slime, in one moment your chin checked hardness of step on which you've stand" << endl;
            return 2;
            //break;
            }
        case 2:
            {
            cout << "somthing kick you back..." << endl;
            return 2;
            //break;
            }
        case 3:
            {
            cout << "sleep well..." << endl;
            return 0;
            //break;
            }
        case 4:
            {
            cout << " Wooot??" << endl;
            return 11;
            //break;
            }
        case 5:
            {
            cout << " Wooot??" << endl;
            return 11;
            //break;
            }
        case 6:
            {
            cout << " Wooot??" << endl;
            return 11;
            //break;
            }
        case 7:
            {
            cout << " Wooot??" << endl;
            return 11;
            //break;
            }
        case 8:
            {
            cout << " Wooot??" << endl;
            return 11;
            //break;
            }
        case 9:
            {
            cout << " Wooot??" << endl;
            return 11;
            //break;
            }
        case 10:
            {
            cout << " Wooot??" << endl;
            return 11;
            //break;
            }
        case 11:
            {
            cout << " Wooot??" << endl;
            return 12;
            //break;
            }
        }
    }

    int spoke(int choice, int &position, string &name)
    {
        switch(choice)
        {
        case 1:
            {
            cout << "\nnothing happend.";
            return 0;
            }
        case 2:
            {
            position -= dice();
            cout <<"\n"<< name <<", someone fondly huge your ass...\n";
            return 0;
            }
        case 3:
            {
            cout << "\nYou trying to fall him down..\n";
                if(dice()==DICEWALL)
                    {
                    position = 0;
                    cout << name <<" head, hit hardly the first step of game\n";
                    return 0;
                    }
                else
                    {
                    cout << "\n You just tried...";
                    }
            }
        }
    }

void opendoc()
{
    string data1;
    file.open( "data.txt", ios::in );
    if( file.good() )
    {
        while( !file.eof() )
        {
            getline( file, data1 );
            data += data1;
        }
    }
    else
    {
    cout << "Error: Can not open the file!!" << endl;
    }
}

void board_creation() //Making some mess on game board
{
    int a;
    for(int i = 0; i < BOARDLENGTH; i++)
    {
        a = dice(GAME_LEVEL);
        if(a >= 0 && a <= 5)
        board[i] = 0;
        else
        board[i] = 1;
    }
}

int gameplay(int P, bool &luck)
{   int pp = 0;
    if(board[P]==0)
        {
            cout << "has moved quickly ahead.\n" << endl;
        return P;
        }
        else
        {
            pp = trap();
        if(pp==12)
        {
            cout << "back to start." <<endl;
            return P-P;
        }
        else if((P-pp)<0)
            {
                cout <<"additional dice roll"<< endl;
                luck = true;
                return P;
            }
        else if(pp==0)
            {
            cout << "lost turn..." << endl;
            return P;
            }
        else if(pp>=1 && pp<=8)
            {
            cout <<"you fallen from "<<P<<" to " <<P-pp<< endl;
            return P-pp;
            }
        else if(pp==9)
            {
            pp = dice();
            cout << "you move additional " << pp << " steps" << endl;
            return P+pp;
            }
        else if(pp==10)
            {
            cout <<"additional dice roll"<<endl;
            luck = true;
            return P;
            }
        else if(pp==11)
        {
            pp = dice();
            cout <<"Culumbus! You move " <<pp<< " steps forward and get additional rolling." << endl;
            luck = true;
            return P+pp;
        }
        else cout << "Something went wrong..." << endl;
        }
}

    Game() //Konstruktor
    {
    board_creation();
    opendoc();
    }

    ~Game() //Destrukor
    {
        file.close();
    }
};


int main()
{
    inicjalizacja();
    Game * G = new Game;
    Player * P = new Player[PLAYERS];
    cout <<"============================ INTRODUCTION ===============================\n";
    cout << G->data;
    cout <<"\n=========================================================================\n";
    for(int i = 0; i < PLAYERS; i++)
    {
    P[i].create(i);
    }

    cin.clear();
    cin.sync();
    int i,j,roll,tour;
    roll = tour = i = j = 0;
    system("cls");
    bool loop = true;
    while(loop) // Main game l00p ]:->
    {
    cout << "==================== TOUR "<< ++tour <<  " ==================" << endl;
    cout << "== Now: " << P[i].name << " Pos: " << P[i].position << endl;
    roll = G->dice();
    cout << "== Rolling: "<< roll << endl << endl;
    P[i].position += roll;
    cout << P[i].name << ", ";
    P[i].position = G->gameplay(P[i].position, P[i].tour);

//////////////////////////////// PLAYER MEET //////////////////////////////////////////////
    if(P[0].position == P[1].position && P[0].position!=0 && P[1].position!=0)
    {
        int a;
        cout << "You spoke another player..\nLet see, what you can to do...\n";
        cout << "1) Nothing...\n";
        cout << "2) Kick him!\n";
        cout << "3) Try to fall him down..\n";
        cout << "Choice: ";
        cin >> a;
        cout << "\n";
        cin.clear();
        cin.sync();
        if(i==1)
        G->spoke(a, P[0].position, P[0].name);
        else
        G->spoke(a, P[1].position, P[1].name);
    getch();
    }
    ////////////////////////////////////////////////////////////////////////////////

        for(int p = 0; p <= 1; p++)
    {
        if(P[p].position>=BOARDLENGTH)
        {
            cout << "\nPlayer " <<P[p].name<< " won!" << endl;
            loop=false;
        }
        else
        {
        cout << "== " << P[p].name << "\t[" <<P[p].position<< "] ==" << endl;
        }
    }
    //========================== Creating new game board ============================//
    if(j==15)
    {
    string a= "!@%%^%*&%^&#";
        for(int i = 0; i < 8; i++)
        {
        a += a;
        cout << a;
        }
        system("cls");
        cout << "The board has blinded both of you with a great flash..." << endl;
        cout << "Something has changed..." << endl;
        G->board_creation();
        j = 0;
    }
    j++;
//================================================================================//

    if(P[i].tour==true)
    {
    getchar();
    P[i].tour=false;
    system("cls");
    continue;
    }
    else
    {
    if(i==0){i++;} else{i--;} // TOUR CHANGE BETWEEN PLAYERS
    getchar();
    system("cls");
    continue;
    }
    }
    cout << "================================================";
    cout << "\nThanks for play!\n Greets from Aterves & Pisia!!\n";
    getch();
    return 0;
}
