#include <algorithm>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>
#include "open.h"

using namespace std;

// clear the console without invoking a wordy command.
void ClearConsole() {
  std::cout << "\u001b[2J"; // macos
}

// print this to the console with ease.
void PrintBorderLine() { cout << "+-------------------------+" << endl; }

// print a message with '|' bordering it on the left and right. booleans added
// to invoke RrintBorderLine().
void PrintMessage(string message, bool PrintTop = true,
                  bool PrintBottom = true) {
  if (PrintTop) {
    PrintBorderLine();
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
    PrintBorderLine();
  } else {
    cout << "|" << endl;
  }
}

// Determining how the hang-man should appear.
void DrawTheHangman(int GuessCount = 0) {
  if (GuessCount >= 1)
    PrintMessage("|", false, false);
  else
    PrintMessage("", false, false);
  if (GuessCount >= 2)
    PrintMessage("|", false, false);
  else
    PrintMessage("", false, false);
  if (GuessCount >= 3)
    PrintMessage("o", false, false);
  else
    PrintMessage("", false, false);
  if (GuessCount == 4)
    PrintMessage("/  ", false, false);
  else if (GuessCount == 5)
    PrintMessage("/| ", false, false);
  else if (GuessCount >= 6)
    PrintMessage("/|\\", false, false);
  else
    PrintMessage("", false, false);
  if (GuessCount == 7)
    PrintMessage("/  ", false, false);
  else if (GuessCount >= 8)
    PrintMessage("/ \\", false, false);
  else
    PrintMessage("", false, false);
  PrintMessage("", false, false);
}

// Prints letters that have been guessed and have not been guessed.
void PrintTheLetters(string input, char fr, char to) {
  string s;
  for (char i = fr; i <= to; i++) {
    if (input.find(i) == string::npos) {
      s += i;
      s += " ";
    } else {
      s += "  ";
    }
  }
  PrintMessage(s, false, false);
}

// Show the entire alphabet and taken words.
void ShowAvailableAndTakenLetters(string taken) {
  PrintTheLetters(taken, 'A', 'J');
  PrintTheLetters(taken, 'K', 'S');
  PrintTheLetters(taken, 'T', 'Z'); //"" for strings and '' for characters.
}

bool CheckForWinAndMakeWord(string word, string guess) {
  bool won = true;
  string s;
  for (int i = 0; i < word.length(); i++) {
    if (guess.find(word[i]) == string::npos) {
      if (word[i] == ' ') {
        s += " ";
      } else if (word[i] == '-') {
        s += "- ";
      } else {
        won = false;
        s += "_ ";
      }
    } else {
      s += word[i];
      s += " ";
    }
  }
  PrintBorderLine();
  PrintMessage(s, false);
  return won;
}


  // Determine total turns
  int TotalTurns(string word, string guessed) {
    int error = 0;
    for (int i = 0; i < guessed.length(); i++) {
      if (word.find(guessed[i]) == string::npos) {
        error++;
      }
    }
    return error;
  }

  // main function of the main.cpp file.
  int main() {
    //time delay
    srand(time(0));
    
    //summon class Open.
    Open open;
    
    string guesses;
    int score = 0;
    string theWord;

    int tries = 0;
    bool gameIsWon = false;
    bool quitGame = false;
    string quitGameInput = "";
    while (!quitGame) {
      // get the word from the words.txt file by random choice.
      theWord = open.RandomizeTheWord("words.txt"); //RandomizeWord("words.txt");
      guesses = "";
      do {
        ClearConsole();
        PrintMessage("HANG-MAN!");
        DrawTheHangman(tries);
        PrintMessage("Score: " + to_string(score));
        ShowAvailableAndTakenLetters(guesses);
        gameIsWon = CheckForWinAndMakeWord(theWord, guesses);
        if (gameIsWon)
          break;
        char x;
        cout << "Enter your guess: ";
        cin >> x;
        if (guesses.find(x) == string::npos) {
          guesses += x;
          score = score + 100;
        }
        transform(guesses.begin(), guesses.end(), guesses.begin(),
                  ::toupper); // Capitalize the player's input
        tries = TotalTurns(theWord, guesses);
        cout << "" << endl;
      } while (tries < 8);

      ClearConsole();

      if (gameIsWon) {
        score = score + 100;
        PrintMessage("YOU WON!");
        DrawTheHangman(tries);
        PrintMessage("Score: " + to_string(score));
        ShowAvailableAndTakenLetters(guesses);
      } else {
        PrintMessage("YOU LOSE...");
        DrawTheHangman(tries);
        string quit;
        PrintMessage("Score: " + to_string(score));
        cout << "Enter any key to quit now: ";
        cin >> quit;
        ShowAvailableAndTakenLetters(guesses);
        quitGame = true;
      }

      PrintMessage(theWord);
      getchar();
      if (!quitGame) {
        cout << "Want to quit the game?: ";
        cin >> quitGameInput;
        transform(quitGameInput.begin(), quitGameInput.end(),
                  quitGameInput.begin(),
                  ::toupper); // Capitalize the player's input
        if (quitGameInput == "YES") {
          quitGame = true;
        }
      }
    }
    //SaveToScoreFile("score.txt", score);
    open.SaveScore("score.txt", score);
    
    return 0;
  }
