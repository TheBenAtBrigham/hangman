#include "open.h"
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

void DebugMess(string);
string RandomizeTheWord(string);
string TimeAndDate();
void SaveScore(string, int);
void ScoreBoard(string, bool, bool);

void Open::DebugMess(string mess) { cout << "test " << mess << endl; }



// get the word from the words.txt file by random choice.
string Open::RandomizeTheWord(string filepath) {

  string chosenWord;
  vector<string> v;
  ifstream reader(filepath);
  if (reader.is_open()) {
    while (std::getline(reader, chosenWord))
      v.push_back(chosenWord);

    int randLine = rand() % v.size();
    chosenWord = v.at(randLine);
    reader.close();
  }
  transform(chosenWord.begin(), chosenWord.end(), chosenWord.begin(),
            ::toupper);

  return chosenWord;
}

// Save to file score.txt
void Open::SaveScore(string filename, int score) {

  vector<string> v;
  ifstream reader(filename);
  string strData;
  if (reader.is_open()) {
    while (std::getline(reader, strData))
      v.push_back(strData);
    reader.close();
  }
  string printDate = TimeAndDate();
  string newScore = to_string(score) + ", " + printDate;
  v.push_back(newScore);

  ofstream myfile;

  myfile.open(filename);

  for (auto i: v)
  {
    myfile << i << endl;
  }

  myfile.close();


  std::cout << "\u001b[2J";
  ScoreBoard("Scoreboard", true, true);
  for (auto i: v)
  {
    ScoreBoard(i, false, false);
  }
  ScoreBoard("Program has ended.", true, true);

}

// return time and date
string Open::TimeAndDate() {
  time_t t = time(0);
  tm *now = localtime(&t);
  string date = to_string((now->tm_mon + 1)) + "/" + to_string(now->tm_mday) +
                "/" + to_string((now->tm_year + 1900));
  return date;
}

// scoreboard
void Open::ScoreBoard(string message, bool PrintTop, bool PrintBottom) {
  if (PrintTop) {
    cout << "+-------------------------+" << endl;
    cout << "|";
  } else {
    cout << "|";
  }
  bool front = true;
  for (int i = message.length(); i < 25; i++) // i < 33
  {
    if (front) {
      message = " " + message;
    } else {
      message = message + " ";
    }
    front = !front;
  }
  cout << message.c_str();
  if (PrintBottom) {
    cout << "|" << endl;
    cout << "+-------------------------+" << endl;
  } else {
    cout << "|" << endl;
  }
}

