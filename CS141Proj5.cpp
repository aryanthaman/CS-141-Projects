/* prog5Wumpus.cpp
 * MADE BY: ARYAN THAMAN
 
 Description: Navigate a maze to kill the Wumpus.
 Implementation of a 1972 game by Gregory Yob.
 
 Results of a program run are shown below:

      
 */

#include <iostream>
#include <iomanip>   // for setw()
#include <cctype>    // for toupper()
#include <cstdlib>   // for rand() and srand()
#include <ctime>     // to seed random number generator with time(0)
using namespace std;

// global constants
#define MAX_LINE_LENGTH 81
#define NUMBER_OF_ROOMS 20

//--------------------------------------------------------------------------------
void displayCave()
{
        cout<< "       ______18______             \n"
            << "      /      |       \\           \n"
            << "     /      _9__      \\          \n"
            << "    /      /    \\      \\        \n"
            << "   /      /      \\      \\       \n"
            << "  17     8        10     19       \n"
            << "  | \\   / \\      /  \\   / |    \n"
            << "  |  \\ /   \\    /    \\ /  |    \n"
            << "  |   7     1---2     11  |       \n"
            << "  |   |    /     \\    |   |      \n"
            << "  |   6----5     3---12   |       \n"
            << "  |   |     \\   /     |   |      \n"
            << "  |   \\       4      /    |      \n"
            << "  |    \\      |     /     |      \n"
            << "  \\     15---14---13     /       \n"
            << "   \\   /            \\   /       \n"
            << "    \\ /              \\ /        \n"
            << "    16---------------20           \n"
            << endl;
}//end displayCave()


//--------------------------------------------------------------------------------
void displayInstructions()
{
    cout<< "Hunt the Wumpus:                                             \n"
        << "The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
        << "room has 3 tunnels leading to other rooms.                   \n"
        << "                                                             \n"
        << "Hazards:                                                     \n"
        << "1. Two rooms have bottomless pits in them.  If you go there you fall and die.  \n"
        << "2. Two other rooms have super-bats.  If you go there, the bats grab you and    \n"
        << "   fly you to some random room, which could be troublesome.  Then those bats go\n"
        << "   to a new room different from where they came from and from the other bats.  \n"
        << "3. The Wumpus is not bothered by the pits or bats, as he has sucker feet and   \n"
        << "   is too heavy for bats to lift.  Usually he is asleep.  Two things wake      \n"
        << "   him up: Anytime you shoot an arrow, or you entering his room.  When he      \n"
        << "   wakes he moves if he is in an odd-numbered room, but stays still otherwise. \n"
        << "   After that, if he is in your room, he eats you and you die!                 \n"
        << "                                                                               \n"
        << "Moves:                                                                         \n"
        << "On each move you can do the following, where input can be upper or lower-case: \n"
        << "1. Move into an adjacent room.  To move enter 'M' followed by a space and      \n"
        << "   then a room number.                                                         \n"
        << "2. Shoot your guided arrow through a list of up to three adjacent rooms, which \n"
        << "   you specify.  Your arrow ends up in the final room.                         \n"
        << "   To shoot enter 'S' followed by the number of rooms (1..3), and then the     \n"
        << "   list of the desired number (up to 3) of adjacent room numbers, separated    \n"
        << "   by spaces. If an arrow can't go a direction because there is no connecting  \n"
        << "   tunnel, it ricochets and moves to the lowest-numbered adjacent room and     \n"
        << "   continues doing this until it has traveled the designated number of rooms.  \n"
        << "   If the arrow hits the Wumpus, you win! If the arrow hits you, you lose. You \n"
        << "   automatically pick up the arrow if you go through a room with the arrow in  \n"
        << "   it.                                                                         \n"
        << "3. Enter 'R' to reset the person and hazard locations, useful for testing.     \n"
        << "4. Enter 'C' to cheat and display current board positions.                     \n"
        << "5. Enter 'D' to display this set of instructions.                              \n"
        << "6. Enter 'P' to print the maze room layout.                                    \n"
        << "7. Enter 'X' to exit the game.                                                 \n"
        << "                                                                               \n"
        << "Good luck!                                                                     \n"
        << " \n"
        << endl;
}//end displayInstructions()

//------------------------------------------------------------
void ExitProgram(){ // prints statement before exiting pregram
    cout << endl << "Exiting Program ...";
    exit(0);
}

// -----------------------------------------------------------
int GenRandom(){ // generates random number between 1 to 20
    return rand()%20 + 1;
}

// ----------------------------
void checkIfSame( int impLocations[], int n){ 
    // initializing impLocations by calling random function
    // checking if it is same to another impLocation.
    // using recursion
    impLocations[n] = GenRandom();
    int flag = 0;
    for(int i=0; i<6; i++){
        int pos = n;
        if(impLocations[i]==impLocations[n] && i!=n){
            flag = 1;
            break;
        }
    }
    if(flag == 1){
        checkIfSame(impLocations,n);
    }
}

//--------------------------------------------------------------------------------
void CheckHazards( int Rooms[][3], int impLocations[]){
    // check hazards when one moves into a room
    
    //Pits
    if( impLocations[4] == impLocations[0] || impLocations[5] == impLocations[0] ){
        cout << "Aaaaaaaaahhhhhh.... " << endl << "You fall into a pit and die. ";
        ExitProgram();
    }
  
    //Wumpus
    int currentRoom = impLocations[0];
    if(impLocations[0] == impLocations[1]){
        if(impLocations[0]%2 == 1){
            impLocations[1] = Rooms[currentRoom][0];
            cout << "You hear a slithering sound, as the Wumpus slips away." << endl << "Whew, that was close!";
        }
        else{
            cout << "You briefly feel a slimy tentacled arm as your neck is snapped." << endl << "It is over.";
            ExitProgram();
        }
    }

    //bats
    if( impLocations[3] == impLocations[0] || impLocations[2] == impLocations[0] ){
        if(impLocations[2] == impLocations[0]){
            checkIfSame(impLocations, 0);
            checkIfSame(impLocations, 2);
        }
        else{
            checkIfSame(impLocations, 3);
            checkIfSame(impLocations, 0);
        }      
        cout << "Woah... you're flying!" << endl << "You've just been transported by bats to room " << impLocations[0];
    }

    //FoundArrow
    if(impLocations[0]==impLocations[6]){
        cout << "Congratulations, you found the arrow and can once again shoot.";
        impLocations[6] = -1;
    }
}

//--------------------------------------------------------------------------------
void CheckNeighbours( int Rooms[][3], int impLocations[]){
    // check adjacent Rooms to sense hazards
    int currentRoom = impLocations[0];
    int tempArray[2] = {-1,-1};
    for(int i=0; i<3; i++){
        //Wumpus
        if(Rooms[currentRoom][i] == impLocations[1]){
            cout << "You smell a stench. ";   
        }
      
        //Bats
        if(Rooms[currentRoom][i] == impLocations[2] || Rooms[currentRoom][i] == impLocations[3]){
            tempArray[0]=1;
        }
                
        //Pits
        if(Rooms[currentRoom][i] == impLocations[4] || Rooms[currentRoom][i] == impLocations[5]){
            tempArray[1]=1;
        }
    }
    if(tempArray[0]!= -1){
        cout << "You feel a draft. ";
    }
    if(tempArray[1]!= -1){
        cout << "You hear rustling of bat wings. ";
    }
}

//--------------------------------------------------------------------------------
void MakeMove( int Rooms[][3], int impLocations[], int &moveCtr){    
    int moveToRoom;
    int currentRoom = impLocations[0];
    cin >> moveToRoom;
    if(moveToRoom != Rooms[currentRoom][0] && moveToRoom != Rooms[currentRoom][1] && moveToRoom != Rooms[currentRoom][2]){
        // check invalid
        cout << endl << "Invalid move. Please retry." << endl;
        moveCtr--;
    }
    else{
        // check valid
        impLocations[0] = moveToRoom; // update person location
        CheckHazards(Rooms, impLocations);
    }
}

//--------------------------------------------
void Repercussions( int theRoom, bool ricochet, int Rooms[][3], int impLocations[], int shootTheseRooms[]){
    // repercussion if arrow ricochets
    if(theRoom == impLocations[1] && ricochet == false){
        cout << "Wumpus has just been pierced by your deadly arrow!" << endl << "Congratulations on your victory, you awesome hunter you." ;
        ExitProgram();
    }
    if(theRoom == impLocations[1] && ricochet == true){
        cout << "Your arrow ricochet killed the Wumpus, you lucky dog!" << endl << "Accidental victory, but still you win!";
        ExitProgram();
    }
    if(theRoom == impLocations[0] && ricochet == false){
        cout << "You just shot yourself. " << endl << "Maybe Darwin was right.  You're dead.";
        ExitProgram();
    }
    if(theRoom == impLocations[0] && ricochet == true){
        cout << "You just shot yourself, and are dying." << endl << "It didn't take long, you're dead.";
        ExitProgram();
    }
}

// -------------------------------------------
void Shoot( int Rooms[][3], int impLocations[]){
    if(impLocations[6]!=-1){
        cout << "Sorry, you can't shoot an arrow you don't have.  Go find it.";
    }
    else{
        int shootNum;
        int shootTheseRooms[4];
        shootTheseRooms[0]=impLocations[0];
        cout << "Enter the number of rooms (1..3) into which you want to shoot, followed by the rooms themselves: ";
        cin >> shootNum;
        for(int i = 1; i < shootNum+1; i++){
            cin >> shootTheseRooms[i];
        }
        for(int i=1; i<shootNum+1; i++){
            // arrow ricochets
            if(shootTheseRooms[i]!=Rooms[shootTheseRooms[i-1]][0] && shootTheseRooms[i]!=Rooms[shootTheseRooms[i-1]][1] && shootTheseRooms[i]!=Rooms[shootTheseRooms[i-1]][2]){
                cout << "Room " << shootTheseRooms[i] << " is not adjacent.  Arrow ricochets...";
                shootTheseRooms[i] = Rooms[shootTheseRooms[i-1]][0];
                Repercussions(shootTheseRooms[i], true, Rooms, impLocations, shootTheseRooms);
            }
            else{ // arrow doesn't ricochets
                Repercussions(shootTheseRooms[i], false, Rooms, impLocations, shootTheseRooms);
            }
        }
        // code to relocate wumpus to smallest numerical adjacent room and update ArrowRoom
        impLocations[6]=shootTheseRooms[shootNum];
        impLocations[1]=Rooms[impLocations[1]][0];
    }
}

//-----------------------------------------------
void Cheat(int impLocations[]){
    cout << endl << "Cheating! Game elements are in the following rooms:" << endl << "Player Wumpus Bats1 Bats2 Pit1 Pit2 Arrow" << endl;
    cout << setw(4) << impLocations[0] << setw(7) << impLocations[1] << setw(7) << impLocations[2];
    cout << setw(6) << impLocations[3] << setw(5) << impLocations[4] << setw(5) << impLocations[5] << setw(6) << impLocations[6] << endl;
}

//--------------------------------------------
void Reset(int impLocations[]){
    cout << endl << "(Remember arrow value of -1 means it is with the person.)" << endl << "Enter the 7 room locations (1..20) for player, wumpus, bats1, bats2, pit1, pit2, and arrow:" << endl << endl;
    int newLocations[7];
    for(int i=0; i<7; i++){
        cin >> newLocations[i];
        impLocations[i]=newLocations[i];
    }
}

//--------------------------------------------------------------------------------
int main()
{   
    // Seed the random number generator.  Change seed to time(0) to change output each time.
    // srand(time(0));
    srand(1);   // Use this version in what you turn in
    
		//displayCave();
		//displayInstructions();

    int Rooms[21][3] = { {0,0,0}, {2,5,8}, {1,3,10}, {2,4,12}, {3,5,14}, {1,4,6}, {5,7,15}, {6,8,17}, {1,7,9}, {8,10,18}, {2,9,11}, {10,12,19}, {3,11,13}, {12,14,20}, {4,13,15}, {6,14,16}, {15,17,20}, {7,16,18}, {9,17,19}, {11,18,20}, {13,16,19} };
    int impLocations[7] = {0,0,0,0,0,0,0};
    
    // initializing all 7 impLocations in order mentioned in implementation details on course website
    impLocations[6] = -1;
    checkIfSame(impLocations, 2);
    checkIfSame(impLocations, 3);
    checkIfSame(impLocations, 4);
    checkIfSame(impLocations, 5);
    checkIfSame(impLocations, 1);
    checkIfSame(impLocations, 0);

    char choice;
    int moveCtr = 1;
		do{
        cout << "You are in room " << impLocations[0] << ". ";
        CheckNeighbours(Rooms, impLocations);
        cout << endl << endl << moveCtr << ". Enter your move (or 'D' for directions): "; 
        cin >> choice;
        choice = toupper(choice);
        switch (choice){
            case 'M': 
                MakeMove(Rooms, impLocations, moveCtr);
                break;
            case 'S':
                Shoot(Rooms, impLocations);
                break;
            case 'R':
                Reset( impLocations);
                moveCtr--;
                break;
            case 'C':
                Cheat( impLocations);
                moveCtr--;
                break;
            case 'D':
                displayInstructions();
                moveCtr--;
                break;
            case 'P':
                displayCave();
                moveCtr--;
                break;
            case 'X':
                ExitProgram();
                break;
            default:
                cout << "Wrong entry";
        }
        moveCtr++;
    }while(choice!=0);
    
}//end main()
