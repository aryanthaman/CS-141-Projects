/*  mastermind.cpp
 
    Class: CS 141, Fall 2018  
	  Tues 5pm lab
    System: Mac OS using xCode
    Author: Dale Reed
 
    45 points Grading Rubric for Programming Style
 
        10 Meaningful identifier names
        10 Comments: Has header.  Comments on each block of code
        10 Functional Decomposition
        10 Appropriate data and control structures
         5 Code Layout: Appropriate indentation and blank lines
*/
#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;


//-------------------------------------------------------------------

// HEADER DOCUMENTATION
/*    Class: CS 141, Fall 2018.  
	  Tues 9am lab
    System: C++ in Codio
    Author: Aryan Thaman
*/

// ASSIGNS THE HIDDEN DIGITS RANDOMLY (INVOKES WHEN INPUT IS 'r')
void InputR(int hiddenDigit[]){
    hiddenDigit[0] = rand() % 10;
    hiddenDigit[1] = rand() % 10;
    hiddenDigit[2] = rand() % 10;
}

// ASSIGNS THE HIDDEN DIGITS WITH USER INPUT (INVOKES WHEN INPUT IS 's')
void InputS(int hiddenDigit[]){
    int totalNum;   // takes in user's number which is then divided into digits 
    cout << "Enter three distinct digits each in the range 0..9 (e.g. 354): " ;
    cin >> totalNum;
    hiddenDigit[2] = totalNum % 10;
    hiddenDigit[1] = ( totalNum / 10 ) % 10;
    hiddenDigit[0] = totalNum / 100;
}

// INPUTS THE USER'S GUESS
void InputVal(int userDigit[]){
    int totalNum;   // takes in user's guess which is then divided into digits 
    cin >> totalNum;
    userDigit[2] = totalNum % 10;
    userDigit[1] = ( totalNum / 10 ) % 10;
    userDigit[0] = totalNum / 100;
}

// CHECKS IN PLACE AND OUT OF PLACE DIGITS AND UPDATES COUNTERS APPROPRIATELY
void InPlaceOutPlace( int userDigit[], int hiddenDigit[], int &inPlaceCtr, int &outPlaceCtr){
    for (int i = 0; i < 3; i++ ){
        for (int j = 0; j < 3; j++){        
            if (userDigit[i] == hiddenDigit[j] && i==j){
                inPlaceCtr++;
            } 
            else if(userDigit[i] == hiddenDigit[j] && i!=j){
                outPlaceCtr++;
            }          
        }
    }
}

// MAIN FUNCTION
int main(){
  
    char inputChar;   // gets 's' or 'r' 
    int hiddenDigit[2];   // array to store hidden digits
    int userDigit[2];   // array to store user's guess
  
    // OUTPUT LINES
    cout << "Program: 2 MasterMind" << endl;  
    cout << "The program selects 3 distinct random digits 0..9." << endl; 
    cout << "On each turn you guess 3 digits.  The program indicates" << endl;
    cout << "how many are correct. You have 10 moves to guess the number." << endl << "Good luck!" << endl << endl;  
    cout << "Press 's' to set the three digits, or 'r' to randomize them: ";
    
    cin >> inputChar;   // 's' or 'r' 
    cout << endl;
  
    // CHECK IF INPUT IS 'r' AND CALL APPROPRIATE FUNCTION 
    if( inputChar == 'r' ){
        InputR(hiddenDigit);
    }
    
    // CHECK IF INPUT IS 's' AND CALL APPROPRIATE FUNCTION
    if( inputChar == 's' ){
        InputS(hiddenDigit);
    }
    
    // OUTPUT LINES
    cout << "Input of 000 displays the hidden digits.  Input of 999 exits the program." << endl << endl << endl;
    cout << setw(36) << "In place" << setw(14) << "Out of place" << endl;
    cout << setw(36) << "--------" << setw(14) << "------------" << endl; 
  
    // LOOP FOR 10 GUESSES
    for (int i = 1; i <= 10; i++ ){   
        int inPlaceCtr = 0, outPlaceCtr = 0;   
        cout << i << ". Your guess: ";
        InputVal(userDigit);   // divides the user's number into digits 
      
        // 000 CASE
        if (userDigit[0]==0 && userDigit[1]==0 && userDigit[2]==0){
            cout << "   Hidden digits are: ";
            cout << hiddenDigit[0] << hiddenDigit[1] << hiddenDigit[2] << endl;
            i--;
        }
        
        // 999 CASE
        else if (userDigit[0]==9 && userDigit[1]==9 && userDigit[2]==9){
            cout << "   Exiting loop..." << endl << endl;
            cout << "   Better luck next time." << endl << endl;
            cout << "Exiting program..." ;
            exit(0);
        }
      
        // ALL OTHER CASES 
        else{
            InPlaceOutPlace(userDigit, hiddenDigit, inPlaceCtr, outPlaceCtr);   // updates values of both the counters 
            cout << setw(24) << "You entered: " << userDigit[0] << userDigit[1] << userDigit[2];
            cout << setw(6) << inPlaceCtr << setw(11) << outPlaceCtr << endl;
            
            // CHECK FOR WIN
            if (inPlaceCtr == 3){
                cout << endl << "*** Congratulations! ***" << endl << endl;
                cout << "Exiting program..." << endl;
                exit(0);
            }
        }
    }
    
    // MAX NUMBER OF GUESSES CASE
    cout << endl << setw(3) << "   Better luck next time." << endl << endl;
    cout << "Exiting program...";
    
	return 0;
}
