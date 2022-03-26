#include <string>
#include <iostream>

#ifndef USEFULFUNCTIONS_HPP
#define USEFULLFUNCTIONS_HPP

#endif /* USEFULFUNCTIONS_HPP */


int MAC(int x, int y, int& sum);
int square(int x);

int integerAdder(int a, int b);
std::string TestFile();
void CreateHerds(int** SouthHeard, int** EastHeard, std::string PuzzleInput, int cols, int rows);
void showHerd(int** matrix, int cols, int rows);
bool MoveEast(int** SouthHerd, int** EastHerd, int cols, int rows, bool same, int step);
void MoveSouth(int** SouthHerd, int** EastHerd, int cols, int rows, bool same, int step);