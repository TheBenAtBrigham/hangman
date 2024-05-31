#ifndef OPEN_H
#define OPEN_H

#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>

using namespace std;
class Open {
public:
  // Open (string, string);
  void DebugMess(string);
  string RandomizeTheWord(string);
  string TimeAndDate();
  void SaveScore(string, int);
  void ScoreBoard(string, bool, bool);

}; // must  be same as class Open in open.cpp.
#endif
