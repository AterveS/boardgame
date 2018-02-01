#include <iostream>
#include <array>
#include <random>
#include <fstream>
#include <conio.h>
#include <windows.h>
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

void fontcolor(int c)
{
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //FONT COLOR INITIALIZER
SetConsoleTextAttribute(hConsole, c); // FONT COLOR
}

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
        if(i == 0) cout << "Przedstawcie siê.." << endl;
        cout << i+1 << ") Imiê: "; cin >> name;
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
            cout << "spad³ do dziury i znalaz³ wyjœcie 2 pozycje wstecz..." << endl;
            return 2;
            //break;
            }
        case 1:
            {
            cout << "nie zwracaj¹c wiêkszej uwagi, Ÿle stan¹³ na stopniu... piêknym fiflokiem polecia³ dwa miejsca wstecz..." << endl;
            return 2;
            //break;
            }
        case 2:
            {
            cout << "coœ ciê kopnê³o..." << endl;
            return 2;
            //break;
            }
        case 3:
            {
            cout << "œpij dobrze..." << endl;
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
        int trying;
        switch(choice)
        {
        case 1:
            {
            cout << "\nnic siê nie dzieje.";
            return 0;
            }
        case 2:
            {
            cout <<"\n"<< name << " proboje siê broniæ\nJeœli "<< name <<" wyrzuci 1 lub 6 wygra t¹ walkê!\n";
            trying = dice();
            cout << "Rzut: " << trying << endl;
            if(trying==1 || trying==6)
            {
                fontcolor(10);
                cout <<"\n" << name << " obroni³ siê!\n";
                fontcolor(7);
                return 0;
            }
            else
            {
            position -= dice();
            fontcolor(12);
            cout <<"\n"<< name <<", dostajesz kopa w ty³ek...\n";
            fontcolor(7);
            return 0;
            }
            }
        case 3:
            {
            cout << "\nPróbujesz zrzuciæ go ze stopnia..\n";
                if(dice()==DICEWALL)
                    {
                    position -= 10;
                    fontcolor(10);
                    cout << "SUKCES!!\n";
                    fontcolor(7);
                    cout << name <<" uderza twardo g³ow¹ o stopieñ, kilka miejsc ni¿ej\n";
                    return 0;
                    }
                else
                    {
                    fontcolor(12);
                    cout << "PORA¯KA\n";
                    fontcolor(7);
                    cout << "No có¿... przynajmniej próbowa³eœ...\n";
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
            cout << "idzie szybko przed siebie.\n" << endl;
        return P;
        }
        else
        {
            pp = trap();
        if(pp==12)
        {
            cout << "INFO::";
            fontcolor(12);
            cout <<" Wracasz na start." <<endl;
            fontcolor(7);
            return P-P;
        }
        else if((P-pp)<0)
            {
                cout <<"INFO::";
                fontcolor(10);
                cout <<" Dodatkowy rzut kostk¹"<< endl;
                fontcolor(7);
                luck = true;
                return P;
            }
        else if(pp==0)
            {
            cout << "INFO::";
            fontcolor(12);
            cout <<" Tracisz kolejke..." << endl;
            fontcolor(7);
            return P;
            }
        else if(pp>=1 && pp<=8)
            {
            cout <<"INFO::";
            fontcolor(12);
            cout <<" Spadasz z "<<P<<" na " <<P-pp<< endl;
            fontcolor(7);
            return P-pp;
            }
        else if(pp==9)
            {
            pp = dice();
            cout << "INFO::";
            fontcolor(10);
            cout << " Poruszasz sie dodatkowo " << pp << " miejsc" << endl;
            fontcolor(7);
            return P+pp;
            }
        else if(pp==10)
            {
            cout <<"INFO::";
            fontcolor(10);
            cout<<" Dodatkowy rzut kostk¹"<<endl;
            fontcolor(7);
            luck = true;
            return P;
            }
        else if(pp==11)
        {
            pp = dice();
            cout <<"INFO::";
            fontcolor(10);
            cout <<" Culumbus! Idziesz " <<pp<< " miejsc do przodu oraz masz dodatkowy rzut kostk¹." << endl;
            fontcolor(7);
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
    fontcolor(7);
    inicjalizacja();
    Game * G = new Game;
    Player * P = new Player[PLAYERS];
    cout <<"============================== WSTÊP ===================================\n";
    cout << G->data;
    cout <<"\n=========================================================================\n";
    for(int i = 0; i < PLAYERS; i++)
    {
    fontcolor(6);
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
    fontcolor(6);
    cout << "==================== TURA "<< ++tour <<  " ==================" << endl;
    fontcolor(7);
    cout << "== Teraz: ";
    fontcolor(10);
    cout << P[i].name;
    fontcolor(7);
    cout << " Poz: ";
    fontcolor(10);
    cout << P[i].position << endl;
    roll = G->dice();
    fontcolor(7);
    cout << "== Rrzut: ";
    fontcolor(10);
    cout << roll << endl << endl;
    fontcolor(7);
    P[i].position += roll;
    cout << P[i].name << ", ";
    P[i].position = G->gameplay(P[i].position, P[i].tour);

//////////////////////////////// PLAYER MEET //////////////////////////////////////////////
    if(P[0].position == P[1].position && P[0].position!=0 && P[1].position!=0)
    {
        int a;
        do{
        fontcolor(3);
        cout << "Spotykasz gracza na tym samym stopniu..\nHmm co by mu tu zrobiæ..\n";
        fontcolor(7);
        cout << "-------------MENU----------------\n";
        fontcolor(11);
        cout << "1) W sumie to nic...\n";
        cout << "2) Kopnij go!\n";
        cout << "3) Spróbuj zrzuciæ go na dó³..\n";
        fontcolor(7);
        cout << "---------------------------------\n";
        fontcolor(3);
        cout << "Wybór: ";
        fontcolor(10);
        cin >> a;
        cout << "\n";
        }while(!cin.good());
        fontcolor(7);
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
            cout << "\nGracz " <<P[p].name<< " wygra³!" << endl;
            loop=false;
        }
        else
        {
        cout << "== " << P[p].name << "\t[";
        fontcolor(6);
        cout <<P[p].position;
        fontcolor(7);
        cout << "] ==" << endl;
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
        fontcolor(14);
        cout << "Wielki b³ysk z serca gry oœlepi³ was na moment..." << endl;
        cout << "Macie nieodparte wra¿enie, ¿e coœ siê zmieni³o..." << endl;
        G->board_creation();
        j = 0;
        fontcolor(7);
    }
    j++;
//================================================================================//

    if(P[i].tour==true) // TOUR - HAPPY ROLL
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
