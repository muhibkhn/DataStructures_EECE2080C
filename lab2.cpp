#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <stdlib.h>
#include <string>

#define MAX_PLAYERS 10   //Definng the max players as 10


using namespace std;

// Class dice implementing the number of sides on a dice.
// The class also implements a function roll() which performs a
// single roll of the die by generating a random number based on the number
// of sides on the dice.

class Dice {
// Private : Declaring num_Sides as the Number of the sides on the die
private:
    int num_Sides;

// Public: - Class constructor for the sides on the die
public:
    Dice(int num_Sides) 
    {
        this->num_Sides = num_Sides;
        srand((unsigned)time(0));
    }

    int roll() 
    {
        int a = rand() % num_Sides + 1;
        return a;
    }
};


// Class Player which represents and stores the Player's Name and Score.
class Player {
// Private: 
// Declaring variables 
// -name for Player's Name
// -score for the Player's Score
private:
    string name;
    int score;

//Public: 
// - Class constructor
// - Getter for Player's name and score
// - addtoScore() to increase the player's score by a specific value
public:
    //Class constrcutor
    Player(string Name, int Score) 
    {   
        this->name = Name;
        this->score = Score;

    }
    // Getter : Player Name
    string getName() 
    {
        return name;
    }
    // Getter : Score
    int getScore() 
    {
        return score;
    }
    // Increase the player's score by a specific value
    void addToScore(int val) 
    {
        score = score + val;
    }
};

// Abstract class DiceGame which implements the basic information of a dice game.
class DiceGame {
// Private:
// getNameScore() it uses and defines delimiter to store the player's Name and Score in the Scorecard file
private:
    void getNameScore(string line, char delimiter, string& name_1, int& score_1) 
    {
        int delimiterIdx = -1;
        for (int i = 0; line[i] != '\0'; i++)
        {
            if (line[i] == delimiter) 
            {
                delimiterIdx = i;
            }
        }
        name_1 = line.substr(0, delimiterIdx);
        score_1 = atoi(line.substr(delimiterIdx + 1, delimiterIdx + 2).c_str());
    }
   
// Protected:
//  - players is the array of pointers to point to the Player objects
//  - Dice is the pointers to point to the Dice object
//  - Variables num_Players, num_Dice are temp values
protected:
    Player* players[MAX_PLAYERS];
    Dice* dice;
    int num_Players, num_Dice;

// Public:
// - virtual void play() is a pure virtual function to be implement in the certain classes
// - initPlayers() is a function to accept the name and score of each player from the user. Creates 
//   instances of the “Player” class and adds them to an array that is referenced by the pointer “players”.
// - displayScores() is a function to display scores of each player
// - writeScoresToFile() is a function to write the players scores in the file 
// - findHighestScore() is a function to display the highest score of the game in the file
public:
    //Pure virtual function
    virtual void play() 
    {

    };

    void initPlayers() 
    {
        string Name;
        int score=0;
        int i = 0;
        while (i < num_Players) {
            cout << "Enter the Player's Name: ";
            cin >> Name;
            cout<<"Enter Score: ";
            cin>> score;
            players[i] = new Player(Name, score);
            i = i + 1;
        }
    }

    void displayScores() 
    {
        cout<<"Display Scores: " << endl;
        for (int i = 0; i < num_Players; i++)
        {
            cout << players[i]->getName() << ":"<< players[i]->getScore() << endl; 
        }
    }

    void writeScoresToFile(char* file_Name) 
    {
        ofstream Text_File(file_Name, ios::app); 
        if (Text_File.is_open())
        {
            for (int i = 0; i < num_Players; i++)
            {
                Text_File << players[i]->getName() << ":" << players[i]->getScore() << endl; 
            }
            Text_File.close(); 
        }
        else
        {
            cout << "Unable to open the text file!"; 
        }
    }

    void findHighestScore(char* file_Name) 
    {
        string line, name, maxName;
        int score, maxScore = 0;
        ifstream Text_File(file_Name);

        if (Text_File.is_open())
        {
            while (getline(Text_File, line))
            {
                score = 0;
                getNameScore(line, ':', name, score);
                if (score > maxScore) {
                    maxScore = score;
                    maxName = name;
                }
            }
            Text_File.close();
            cout << "Player with the highest score: " << endl << maxName << ": " << maxScore;
        }
        else {
            cout << "Unable to read from ip file";
        }
    }
};


// the class KnockOut inherits from the class DiceGame
class KnockOut : public DiceGame {
private:
    int Knock_Out_Score=0;
    int remainingPlayers=0;
    int sr=0;
public:
    
    KnockOut(int num_Sides, int num_Players, int num_Dice) 
    {
        dice=new Dice(num_Sides);
        this->num_Dice = num_Dice;
        this->num_Players = num_Players;
        for(int i=0;i<num_Dice;i++){
            Knock_Out_Score+=dice->roll();
        }
    }

    // We define the virtual function play() here for the game KnockOut
    void play()
    {
        int Roll_Sum, remaining_Players;
        
        Player *Original_Players[10];
        for (int i = 0; i < num_Players; i++)
        {
            Original_Players[i]=new Player(players[i]->getName() , 0); 
            
        }

        remaining_Players = num_Players;
        while (remaining_Players > 1)
        {
           
            for (int i = 0; i < num_Players; i++)
            {
                Roll_Sum = 0;
                for (int j = 0; j < num_Dice; j++)
                {
                    Roll_Sum += dice->roll();
                }

                if (Roll_Sum == Knock_Out_Score)
                {   
                    cout<< endl <<Original_Players[i]->getName()<<" is knocked out " << endl;
                    remaining_Players--; 
                    Original_Players[i]->addToScore(-1);
                    break;
                }
                
            }
        }
      
        for (int i = 0; i < num_Players; i++)
        {   
            if (Original_Players[i]->getScore() >=0) 
            {   cout<<"GAME WINNER: " << endl;
                
                players[i]->addToScore(10); 
                cout<<players[i]->getName()<<':'<< players[i]->getScore()<<endl;
                break;
            }
        }

    }
};


// class BostonDiceGame inherits from the class DiceGame
class BostonDiceGame : public DiceGame
{
private:
    int maxroll=0,temp_1;
public:
    BostonDiceGame(int num_Sides, int num_Players, int num_Dice) 
    {
        dice=new Dice(num_Sides);
        this->num_Players = num_Players;
        this->num_Dice = num_Dice; 
    }
    //We define the virtual function play() here for the game Boston Dice Game
    void play()
    {   
        int scoret=0,j=0;
        for(int i=0;i<num_Players;i++)
        {
            scoret=0;
            for(j=0;j<num_Dice;j++){
                maxroll=-1;
                for(int k=j;k<num_Dice;k++)
                {
                    temp_1=dice->roll();
                    if(maxroll<temp_1){
                        maxroll=temp_1;
                    }
                }
                scoret+=maxroll;
            }
            players[i]->addToScore(scoret);
        }
    }
};


// Main Funtion
int main()
{   DiceGame* object;
    int game, num_Players, num_Dice, num_Sides;
    cout << "Which game would you like to play?" << endl << "1. Knock Out " << endl << "2. Boston Dice Game" << endl;
    cin >> game;
    cout << "Enter the number of dice: ";
    cin >> num_Dice;
    cout << endl;
    cout << "Enter the number of sides on the die: ";
    cin >> num_Sides;
    cout << endl;
    cout << "Enter the number of Players: ";
    cin >> num_Players;
    cout << endl;
    if (game == 1) 
    {
        KnockOut object2(num_Sides, num_Players, num_Dice);
        object = &object2;   
    }
    else 
    {
        BostonDiceGame object2(num_Sides, num_Players, num_Dice);
        object = &object2;
    }
    
    object->initPlayers();
    object->play();
    object->displayScores();
    object->writeScoresToFile("scorecard.txt");
    object->findHighestScore("scorecard.txt");
    return 1;
    
}