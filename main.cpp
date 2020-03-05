#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <vector>
#include <map>
#include <stdlib.h>
#include <list>

using namespace std;

//PART2
//this function reads in from a file (file name parameter) and stores in a vector,
//then prints that vector to a file
vector<string> vectorFile(string filename) {
    string inputFileName = filename;
    inputFileName.append(".txt");
    ifstream inputFile;
    inputFile.open(inputFileName.c_str());
    
    string word;
    vector<string> wordvector;
    while (inputFile >> word) {
        //remove punctuation
        for (int i = 0; i < word.size(); i++) {
            if (!isalpha(word[i])) {
                word.erase(i--, 1);
            }
        }
        //store each word of the file in a set
        wordvector.push_back(word);
    }
    //close the inputfile
    inputFile.close();
    
    //write to outputfile
    ofstream outputFile;
    string outputFileName = filename;
    outputFileName.append("_vector.txt");
    outputFile.open(outputFileName.c_str());
    for (int i = 0; i < wordvector.size(); i++) {
        outputFile << wordvector.at(i) << endl;
    }
    outputFile.close();
    
    return wordvector;
}

int main(int argC, char *argV[]) {
        
        string state;
        
        //PART1
        //check argument count...
        //error statement incase of too many arguments
        if (argC != 2) {
            cout << "Usage: " << argV[0] << " <filename>\n";
            return 1;
        }
        
        string userArgument = argV[1];
        string inputFileName = userArgument;
        inputFileName.append(".txt");

        //make sure we can open the file...
        ifstream inputFile;
        inputFile.open(inputFileName.c_str());  //"r" opens the file for reading from
        if (inputFile == NULL) {
            cout << "Could not open " << argV[1] << "!!\n";
            return 2;
        }
        
        //read from the file and store in a set
        string word;
        set<string> wordset;
        while (inputFile >> word) {
            //remove punctuation
            for (int i = 0; i < word.size(); i++) {
                if (!isalpha(word[i])) {
                    word.erase(i--, 1);
                }
            }
            //store each word of the file in a set
            wordset.insert(word);
        }
        //close the inputfile
        inputFile.close();
        
        //Print the contents of the set to a new file with each string
        //in the set appearing on a new line.
        ofstream outputFile;
        string outputFileName = userArgument;
        outputFileName.append("_set.txt");
        outputFile.open(outputFileName.c_str());
        
        //use an iterator to access each item in the set and output it to the file
        set<string>::iterator it;
        for (it = wordset.begin(); it != wordset.end(); it++) {
            outputFile << *it << endl;
        }
        
        outputFile.close();
        
        //PART2 (SEE FUNCTION ABOVE)
        //calls the vectorFile function
        vector<string> wordvector;
        wordvector = vectorFile(userArgument);
        
        //PART3
        //create a map of strings to string
        //that has the string as the key, and the next word in the vector as the value.
        map<string, string> wordmap;
        string last="";
        for (int i = 0; i < wordvector.size(); i++) {
            wordmap[last] = wordvector.at(i);
            last = wordvector.at(i);
        }
        
        //print the map to a file
        outputFileName = userArgument;
        outputFileName.append("_1_1.txt");
        outputFile.open(outputFileName.c_str());
        map<string, string>::iterator it2;
        for (it2 = wordmap.begin(); it2 != wordmap.end(); it2++) {
            outputFile << it2->first << ", " << it2->second << endl;
        }
        outputFile.close();
        
        //PART4
        /*
        state = "";
        for(int i = 0; i < 100; i++){
            cout << wordmap[state] << " ";
            state = wordmap[state];
        }           
        cout << endl;
        */
        
        //PART5
        map<string, vector<string> > wordmaptovector;
        state = "";
        for(int i = 0; i < wordvector.size(); i++) {
            wordmaptovector[state].push_back(wordvector.at(i));
            state = wordvector.at(i);
        }
        
        //print the map to a file
        outputFileName = userArgument;
        outputFileName.append("_1_many.txt");
        outputFile.open(outputFileName.c_str());
        map<string, vector<string> >::iterator it3;
        for (it3 = wordmaptovector.begin(); it3 != wordmaptovector.end(); it3++) {
            outputFile << it3->first << ": ";
            for (int i = 0; i < it3->second.size(); i++) {
                outputFile << it3->second.at(i) << ", ";
            }
            outputFile << endl;
        }
        outputFile.close();
        
        //generate random sermon of 100 words
        srand(time(NULL)); // this line initializes the random number generated
                   // so you dont get the same thing every time
        state = "";
        for (int i = 0; i < 100; i++) {
          int ind = rand() % wordmaptovector[state].size();
          cout << wordmaptovector[state][ind] << " ";
          state = wordmaptovector[state][ind];
        }
        cout << endl << endl;
        
        //PART6
        //not understanding
        map<list<string>, vector<string> > wordmap2;
        list<string> state1;
        int M = 2;
        for (int i = 0; i < M; i++) {
            state1.push_back("");
        }
                        
        for (vector<string>::iterator it=wordvector.begin(); it!=wordvector.end(); it++) {
            wordmap2[state1].push_back(*it);
            state1.push_back(*it);
            state1.pop_front();
        }
        
        state1.clear();
        for (int i = 0; i < M; i++) {
        state1.push_back("");
        }
        for (int i = 0; i < 100; i++) {
            int ind = rand() % wordmap2[state1].size();
            cout << wordmap2[state1][ind]<<" ";
            state1.push_back(wordmap2[state1][ind]);
            state1.pop_front();
        }
    
    return 0;    
}