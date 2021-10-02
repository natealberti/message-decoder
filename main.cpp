// author: nate alberti
// date: september 2021
// purpose: reads data from a file in the home directory,
// and computes the frequency of every letter in the message,
// and also tells the most used letter and how many times it
// was used.

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

char to_lowercase(char input);
void compute_frequency(char message[], int accumulators[26]);
void read_file(fstream &file, char arr[]);
void display_chart(int accumulators[26], int message_length);
void most_used_letter(int accumulators[], char &letter, int &uses);

int main() {

    // reading the file and putting it into a char array
    // and displaying it
    fstream file;
    char message[81];
    string const HOME = std::getenv("HOME") ? std::getenv("HOME") : ".";
    file.open( HOME + "/data.txt", ios::in);
    read_file(file, message);
    cout << "message: ";
    for(int i = 0; message[i] != '\0'; i++) {
        cout << message[i];
    }
    cout << endl;
    cout << endl;

    //message length
    int message_length = 0;
    for(int i = 0; message[i] != '\0'; i++) {
        message_length++;
    }

    // giving an array of accumulators and counts how many
    // times each letter shows up
    // also displays it
    int accumulators[26];
    compute_frequency(message, accumulators);
    display_chart(accumulators, message_length);

    //displaying the usage of the most used letter
    char most_used;
    int uses;
    most_used_letter(accumulators, most_used, uses);
    cout << endl;
    cout << "The most used letter is ";
    cout << (char) most_used;
    cout << " and it was used " + to_string(uses) + " times.";


    return 0;
}


// method to read text from a file and return it in a reference parameter array
// read continuously until you hit the null character
void read_file(fstream &file, char arr[]) {
        int i = 0;
        char character;
        while (!file.eof()) {
            character= file.get();
            arr[i] = character;
            ++i;
        }
        arr[i] = '\0';
}

// method to receive the message array and count how many times each letter appears
// it is also given the array of 26 accumulators passed by reference
// go thru each character (convert to lowercase if necessary), compute the index,
// and increase that accumulator
// ignore non-alphabetical characters
void compute_frequency(char message[], int accumulators[]) {
    //initializing accumulators to zero
    for(int i = 0; i < 27; i++) {
        accumulators[i] = 0;
   }

    // counting each occurrence of a letter in the message
    // index = letter - 'a'
    // ignoring non-alphabetical symbols.
    for(int i = 0; message[i] != '\0'; i++) {
        char character = to_lowercase(message[i]);
        message[i] = character;
        if(character < 123 && character > 96) {
            int index = character - 'a';
            accumulators[index]++;
        }
    }
}

// make the letter lowercase
// if already lowercase or non-alphabetical, ignore
// add the constant 'a'-'A' to the uppercase letters to make them lowercase
char to_lowercase(char input) {
    int offset = 'a' - 'A';
    if(input < 'Z' && input > 'A') {
        input += offset;
    }
    return input;
}

// takes in the accumulators array and outputs the frequency chart
void display_chart(int accumulators[26], int message_length) {
    cout << "letter\tfrequency" << endl;
    for(int i = 0; i < 27; i++) {
        if(accumulators[i] != 0) {
            char character = 'a' + i;
            double frequency = (double)accumulators[i]/message_length*100;
            cout << (char)character;
            cout << "\t\t" + to_string(frequency) + "%" << endl;
        }
    }
}

// given the accumulator array, it shows which was used most frequently and
// the number of times it was used
void most_used_letter(int accumulators[], char &letter, int &uses) {
    uses = 0;
    for(int i = 0; i < 27; i++) {
        if(accumulators[i] > uses) {
            letter = 'a' + i;
            uses = accumulators[i];
        }
    }
}