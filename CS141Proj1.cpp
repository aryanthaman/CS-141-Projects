/* prog1Step4.cpp
 *    Play the dice game, where each user chooses the Red, Green or Blue die.
 * 
 * Class: CS 141
 * Author: Aryan Thaman
 * Lab: Tues 9am
 * System:  C++ online in codio.com
 *
 *   45 Programming Style Rubric (Given only if program runs substantially correctly)
 *         5 This rubric is included in the program
 *        10 Variable names are meaningful and use camel-case (e.g. totalCount)
 *        10 Comments: Has header.  Comments on each significant block of code
 *        10 Appropriate data and control structures
 *        10 Code Layout: Appropriate indentation and blank lines
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>    // Needed for rand() to work
using namespace std;

    // To generate Random Num for Red Die
    int randR(){
        int randNum = rand() % 6;
        int dieValue;
        if( randNum < 1 ){
            dieValue = 1;
        } 
        else{
            dieValue = 4;
        }
        return dieValue;
    }

    // To generate Random Num for Green Die
    int randG(){
        int randNum = rand() % 6;
        int dieValue;
        if( randNum < 3 ){
            dieValue = 2;
        } 
        else{
            dieValue = 5;
        }
        return dieValue;
    }

    // To generate Random Num for Blue Die
    int randB(){
        int randNum = rand() % 6;
        int dieValue;
        if( randNum < 1 ){
            dieValue = 6;
        } 
        else{
            dieValue = 3;
        }
        return dieValue;
    }


int main(){

    // Step 1 Output lines
    cout << "Class: CS 141" << endl;
    cout << "Lab: Tues 5am" << endl; 
    cout << "System:  C++ in codio.com" << endl;
    cout << "Welcome to the dice game, where you and your opponent each choose " << endl;
    cout << "one of the red, green or blue dice and roll them." << endl << endl;
    cout << "The dice contain the following sides:" << endl;
    cout << "    Red: 1 4 4 4 4 4" << endl;
    cout << "  Green: 2 2 2 5 5 5" << endl;
    cout << "   Blue: 6 3 3 3 3 3" << endl << endl;
    cout << "Enter the die colors (R G or B): ";

    // Initializing Required Variables: P1 is player 1, P2 is player 2;
    char dieColor[2];
    int numP1, numP2, ctrP1=0, ctrP2=0;
    
    // Asking for input -> die colors
    for( int i=0; i<2; i++ ){
        cin >> dieColor[i];
    }
    
    // Loop to iterate 50 times
      // Switch case used to detect color and call appropriate functions
    for( int i = 0; i < 50; i++ ){  
        switch( dieColor[0] ){
            case 'R' : numP1 = randR(); break;
            case 'G' : numP1 = randG(); break;
            case 'B' : numP1 = randB();
        }
      
        switch( dieColor[1] ){
            case 'R' : numP2 = randR(); break;
            case 'G' : numP2 = randG(); break;
            case 'B' : numP2 = randB();
        }
    
        // Counting score
        if( numP1 > numP2 ){
            ctrP1++;
        }
        else{
            ctrP2++;
        }
    
        // Final Output using setw() function
        cout << endl << setw(3) << i + 1 << ". "<< dieColor[0] << ":" << numP1 << " ";
        cout << dieColor[1] << ":" << numP2 << ", "; 
        cout << "Score: " << setw(2) <<ctrP1 << " to " << setw(2) << ctrP2 ;
        
    }

    return 0;
    
} //end main()
