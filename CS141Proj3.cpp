// prog3WhichLangMacbeth.cpp
//    Use letter frequency counts to determine what language text is in.
//
// Author: Aryan Thaman
// Date: 17th Oct, 2018
// Class: CS 141, Fall 2018
// Language: C++
//
// Translations of Macbeth were created online using Google translate, starting with the
// English version at http://shakespeare.mit.edu/macbeth/full.html
// To trigger the translation option, I went to the Chrome browser / Settings / Language
// option and changed the default language, which triggered showing the translation option
// for the English Macbeth page when it was displayed.  The translated text was then
// copy/pasted into a text file and saved.  The texts are stored using the multi-byte
// UTF-8 format, explained at https://en.wikipedia.org/wiki/UTF-8, though here we are
// not attempting to count more than the first 128 alphabetical characters.
//
/* Results of running program are:

 */

#include <iostream>
#include <cctype>       // For the letter checking functions
#include <fstream>      // For file input
#include <iomanip>      // For setw
#include <cstdlib>      // For exit
#include <cmath>        // For abs
using namespace std;

#define LIMIT 26

// Initializes fileNames array with all the file names
void InitializeWithFiles(string fileNames[]){
  fileNames[0] = "MacbethEnglish.txt";
  fileNames[1] = "MacbethFinnish.txt";
  fileNames[2] = "MacbethFrench.txt";
  fileNames[3] = "MacbethGerman.txt";
  fileNames[4] = "MacbethHungarian.txt";
  fileNames[5] = "MacbethItalian.txt";
  fileNames[6] = "MacbethPortuguese.txt";
  fileNames[7] = "MacbethSpanish.txt"; 
}

// Used when swapping of characters is required
  // in 1D character array on the basis of the corresponding
    // 1D int array. 
void MakeSameChange1D( char inputlettersArray[], int j ){
    char temp = ' '; 
    temp = inputlettersArray[j];
    inputlettersArray[j] = inputlettersArray[j+1];
    inputlettersArray[j+1] = temp;
}

// Used when swapping of characters is required
  // in 2D character array on the basis of the corresponding
    // 2D int array. 
void MakeSameChange2D( char lettersArray[][8], int k, int i){
    char temp = ' ';
    temp = lettersArray[k][i];
    lettersArray[k][i] = lettersArray[k+1][i];
    lettersArray[k+1][i] = temp;
}

// Bubble sort for 1D array
void BubbleSort1D( int inputletterCtr[], char inputlettersArray[]){
    int temp;
    for (int i=0; i<LIMIT; i++){ // sort loop 1
        for (int j = 0; j < LIMIT-1; j++){ // sort loop 2
            if (inputletterCtr[j] < inputletterCtr[j+1]){
                // makes the swap in corresponding char array
                MakeSameChange1D(inputlettersArray, j);
                temp = inputletterCtr[j];
                inputletterCtr[j] = inputletterCtr[j+1];
                inputletterCtr[j+1] = temp;
            }
        }
    }
}

// Bubble sort in 2D array
void BubbleSort2D( int lettersCtr[][8], char lettersArray[][8] ){
    int temp;
    for( int i=0; i<8; i++ ){ // fileNumbers
        for( int j=0; j < LIMIT; j++ ){ // sort loop 1
            for( int k = 0; k < LIMIT-1; k++ ){ // sort loop 2
                if ( lettersCtr[k][i] < lettersCtr[k+1][i] ){
                    // makes the swap in corresponding char array
                    MakeSameChange2D(lettersArray, k, i);
                    temp = lettersCtr[k][i];
                    lettersCtr[k][i] = lettersCtr[k+1][i];
                    lettersCtr[k+1][i] = temp;
                }
            }
        }
    }
}

// Displays FrequencyTable for step 1
void DisplayFrequencyTable( int lettersCtr[][8], string fileNames[]){
    cout << "Letter Frequency Counts:" << endl;
    cout << setw(8) << "Engl" << setw(6) << "Finn" << setw(6) << "Fren" << setw(6) << "Germ" << setw(6) << "Hung" << setw(6) << "Ital" << setw(6) << "Port" << setw(6) << "Span" << endl;

    // Initializing lettersCtr to 0
    for(int i=0; i<LIMIT; i++){
        for(int j=0; j<8; j++){
            lettersCtr[i][j] = 0;   
        }
    }
  
    // inputing characters from file 
      // and displaying table
    char c = ' ';    // input character
    for(int i=0; i<LIMIT; i++){    
        cout << (char)(i+'A') << ":";    
        for(int j=0; j<8; j++){
            ifstream iFile;
            // open input file and verify
            iFile.open( fileNames[j].c_str() );   // Convert C++ string to expected C-style string 
            if( !iFile.is_open() ){
               cout << "Could not find input file.  Exiting..." << endl;
               exit( -1);
            }

            while( iFile >> c ){
                // convert alphabetic input characters to upper case
                if( isalpha( c ) ){
                    c = toupper( c );
                    if( c - 'A' == i ){
                        lettersCtr[i][j]++; // update letter count, using the character as the index
                    }
                }  
            }
            iFile.close(); // close input file
            cout << setw(6) << lettersCtr[i][j];
        }  
    cout << endl;
    } 
}

// Display Ordered Frequency Table used in step 2 
void DisplayFrequencyOrder( int lettersCtr[][8], char lettersArray[][8] ){  
    // Initializing Letter Array to letters from A to Z
    for(int i = 0; i < LIMIT; i++ ){
        for( int j =0; j < 8; j++ ){
            lettersArray[i][j] = (char)(i + 'A');
        }
    }
    
    BubbleSort2D( lettersCtr, lettersArray );
    cout << endl << "Letter frequency order:" << endl;
    cout << setw(8) << "Engl" << setw(6) << "Finn" << setw(6) << "Fren" << setw(6) << "Germ" << setw(6) << "Hung" << setw(6) << "Ital" << setw(6) << "Port" << setw(6) << "Span" << endl;    
    for( int i = 0; i < LIMIT; i++ ){    
        for( int j = 0; j < 8; j++ ){
            cout << setw(6) << lettersArray[i][j];
        }    
    cout << endl;
    } 
}

// Displays letter counters for the input 
void DisplayletterCounts( int inputletterCtr[], char inputlettersArray[], char lettersArray[][8]){
    char c = ' '; // input character
  
    // initialize inputletterCtr to 0
    for (int i=0; i<LIMIT; i++){
        inputletterCtr[i]=0; 
    }

    // Initializing inputlettersArray to letters from A to Z
    for(int i = 0; i < LIMIT; i++){
        inputlettersArray[i] = (char)(i+'A');
    }
  
    // inputing user text and updating letter counters
    cout << endl << "Copy and paste a paragraph of text to be analyzed, followed by ^z (PC) or ^d (Mac): " << endl;
    for(int i=0; i<LIMIT; i++){
        while ( cin >> c ){
            if( isalpha( c )){
            c = toupper( c );
            inputletterCtr[ c - 'A' ]++;
            }
        }
    }
    
    // output lines
    for(int i = 0; i < LIMIT; i++){
        cout << (char)(i+'A') << ":" << inputletterCtr[i] << " ";
    }
    cout << endl << "Letter frequency order:" << endl;
    cout << setw(8) << "Engl" << setw(6) << "Finn" << setw(6) << "Fren" << setw(6) << "Germ" << setw(6) << "Hung" << setw(6) << "Ital" << setw(6) << "Port" << setw(6) << "Span" << setw(6) << "User" << endl;
    
    // sorting and displaying table
    BubbleSort1D( inputletterCtr, inputlettersArray);
    for( int i = 0; i < LIMIT; i++ ){    
        for( int j = 0; j < 8; j++ ){
            cout << setw(6) << lettersArray[i][j];
        }    
    cout << setw(6) << inputlettersArray[i] << endl;
    }
}

// Identifies language in step 4
void IdentifyLanguage( char inputlettersArray[], char lettersArray[][8] ){  
    int diff[8]; // will contain difference of indexes for each language
    for(int i=0; i<8; i++){
        diff[i]=0;
    }
    
    // calculating the difference for every language
    for( int i = 0; i < 8; i++ ){
        for( int j = 0; j < LIMIT; j++ ){
            for( int k = 0; k < LIMIT; k++ ){
                if(inputlettersArray[j]==lettersArray[k][i]){
                    if(abs(k-j)>=4){
                        diff[i] = diff[i] + abs(k-j);
                        
                    }
                }
            }
        }
    }
    
    // finding the smallest difference
    int fileNum = 0; 
    int smallest = diff[0];
    for(int i=0; i<8; i++){
        if (diff[i]<smallest){
            smallest = diff[i];
            fileNum = i;
        }
    }
    
    // Outputing the correct language
    cout << "Language is ";
    switch( fileNum ){
        case 0: cout << "English" << endl; break;
        case 1: cout << "Finnish" << endl; break;
        case 2: cout << "French" << endl; break;
        case 3: cout << "German" << endl; break;
        case 4: cout << "Hungarian" << endl; break;
        case 5: cout << "Italian" << endl; break;
        case 6: cout << "Portuguese" << endl; break;
        case 7: cout << "Spanish" << endl; break;
        default: cout << "Couldn't find language. Sorry." << endl;
    }
}

int main(){
  
    int lettersCtr[LIMIT][8]; // Contains the frequency values
    char lettersArray[LIMIT][8]; // Contains the letters for each language
  
    int inputletterCtr[LIMIT]; // Contains the frequency values for input language
    char inputlettersArray[LIMIT]; // Contains the letters for input language
  
    string fileNames[8]; // contains names of all the files being used
    InitializeWithFiles(fileNames); 
  
    int choice=0; // contains user's selection in the menu
  
    do{
        // Menu for the program
        cout << "Program 3: Which Language." << endl << endl;
        cout << "Select from the following stages of output to display: " << endl;
        cout << "1. Letter frequency counts \n" << "2. Letter frequency order \n";
        cout << "3. Get user input and display frequency counts \n" << "4. Get user input, display frequency counts, and display language \n"; 
        cout << "0. Exit the program" << endl;
        cout << "Your choice -->";
        cin >> choice;

        if( choice >= 1 ){
            DisplayFrequencyTable(lettersCtr, fileNames); // step 1
        }
        if( choice >= 2 ){
            DisplayFrequencyOrder(lettersCtr, lettersArray); // step 2
        }
        if( choice >= 3 ){
            DisplayletterCounts(inputletterCtr, inputlettersArray, lettersArray); // step 3
        }
        if( choice >= 4 ){
            IdentifyLanguage(inputlettersArray, lettersArray); // step 4
        }
    }while(choice>5);

    return 0;
}
