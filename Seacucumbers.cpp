#include "UsefulFunctions.hpp"
#include <iostream>
#include <fstream>
#include <string>

int MAC(int x, int y, int& sum){
    sum += x*y;
    return sum;
}

int square(int x){
    int xSquared = x*x;
    return xSquared;
}


int main()
{
	std::cout << "Let's move some sea cucumbers!!" << std::endl;

	std::fstream myFile;
	std::string PuzzleInput = TestFile();
	myFile.open(PuzzleInput, std::ios::in); //read from text file
	if (myFile.is_open()) 
	{

		std::cout << "Opened the file... " << std::endl;

		int row_count = 0;
		int col_count = 0;
		std::string line;

		// determine ammount of rows and columns in the matrix
		while (getline(myFile, line)) {
			row_count = row_count + 1;
			col_count = int(line.size());
		}
		std::cout << "amount of rows: " << row_count << ",  ammount of columns: " << col_count << std::endl;

		//allocate memory
		int** SouthHerd = new int* [row_count];
		for (int i = 0; i < row_count; i++) {
			SouthHerd[i] = new int[col_count];
		}
		int** EastHerd = new int* [row_count];
		for (int i = 0; i < row_count; i++) {
			EastHerd[i] = new int[col_count];
		}

		bool showmatrix;
		std::cout << "show the matrix?" << std::endl;
		std::cin >> showmatrix;
		std::cout << std::endl;

		//FUNCTIONS
		CreateHerds(SouthHerd, EastHerd, PuzzleInput, col_count, row_count);
		if (showmatrix) {
			std::cout << "The Cucumbers going to the south: " << std::endl;
			showHerd(SouthHerd, col_count, row_count);
			std::cout << "The Cucumbers going to the east: " << std::endl;
			showHerd(EastHerd, col_count, row_count);
		}

		//Move Cucumbers!
		bool DoesItStop = MoveEast(SouthHerd, EastHerd, col_count, row_count, true, 0); //pass true so it will return step = 0 for an already stationary field of cucumbers!

	
		//deallocate
		for (int i = 0; i < row_count; i++) {
			delete[] SouthHerd[i];
		}
		delete[] SouthHerd;
		SouthHerd = NULL;

		for (int i = 0; i < row_count; i++) {
			delete[] EastHerd[i];
		}
		delete[] EastHerd;
		EastHerd = NULL;
		myFile.close();
	}
}