
#include "UsefulFunctions.hpp"
#include <iostream>
#include <fstream>
#include <string>

int integerAdder(int a, int b)
{
	int c = a + b;
	return c;
}

std::string TestFile()
{
	std::cout << "Use the test file?" << std::endl;
	bool Test;
	std::cin >> Test;
	std::cout << std::endl;
	std::string PuzzleInput;

	if (Test) {
		PuzzleInput = "MyTestinput.txt";
	}
	else {
		PuzzleInput = "input.txt";
	}
	return PuzzleInput;
}

void CreateHerds(int** SouthHerd, int**EastHerd, std::string PuzzleInput, int cols, int rows) {

	std::fstream myFile;
	myFile.open(PuzzleInput, std::ios::in); //read from text file
	if (myFile.is_open()) {
		std::string line;
		int rowIndex = 0;

		while (getline(myFile, line)) {
			for (int j = 0; j < cols; j++) {
				if (line[j] == 62) {
					EastHerd[rowIndex][j] = 1;
					SouthHerd[rowIndex][j] = 0;
				}
				else if (line[j] == 118) {
					SouthHerd[rowIndex][j] = 1;
					EastHerd[rowIndex][j] = 0;
				}
				else if (line[j] == 46)
				{
					SouthHerd[rowIndex][j] = 0;
					EastHerd[rowIndex][j] = 0;
				}
				else
				{
					std::cout << "Cucumber not found :(" << std::endl;
					SouthHerd[rowIndex][j] = 0;
					EastHerd[rowIndex][j] = 0;
				}
				
			}
			rowIndex = rowIndex + 1;
		}

		myFile.close();
	}
	std::cout << "this works just fine, Matrix Filled" << std::endl;
}

void showHerd(int** matrix, int cols, int rows) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::cout << matrix[i][j] << "  ";
		}
		std::cout << "\n";
	}
}


bool MoveEast(int** SouthHerd, int** EastHerd, int cols, int rows, bool same, int step)
{	
	//make a temporary new herd for the next timestep
	int** NextEastHerd = new int* [rows];
	for (int i = 0; i < rows; i++) {
		NextEastHerd[i] = new int[cols];
	}
	//Set default to 0
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			NextEastHerd[i][j] = 0;
		}
	}
	
	//Move to the east!
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (EastHerd[i][j] == 1)	//check if there is a cucumber in this spot
			{
				if (j != cols - 1)	//Just move east if it is not the last column, eg if no cucumbers need to be teleported 
				{
					if (EastHerd[i][j+1] == 0 && SouthHerd[i][j+1] == 0) //check if there is a cucumber in the adjacent place
					{
						NextEastHerd[i][j + 1] = 1;	//Cucumber moved succesfully
					}
					else
					{
						NextEastHerd[i][j] = 1; //Cucumber please stay put
					}
				}
				else // teleport me some cucumbers please
				{
					if (EastHerd[i][0] == 0 && SouthHerd[i][0] == 0) //check if there is a cucumber on the other side of the map
					{
						NextEastHerd[i][0] = 1;	//Cucumber teleported succesfully
					}
					else
					{
						NextEastHerd[i][j] = 1; //Cucumber please stay put
					}
				}
			}
			else	//If there aint no cucumber to move, what needs to be done?
			{
			}
		}
	}
	//Show me the next timestep
	//std::cout << "east moved cucumbers" << std::endl;
	//showHerd(NextEastHerd, cols, rows);
	
	//compare the two herds
	bool everythingSame = true;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (everythingSame) {
				if (EastHerd[i][j] == NextEastHerd[i][j]) {
					everythingSame = true;
				}
				else
				{
					everythingSame = false;
				}
			}
		}
	}

	//set the new herd to the default herd
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			EastHerd[i][j] = NextEastHerd[i][j];
		}
	}

	//deallocate
	for (int i = 0; i < rows; i++) {
		delete[] NextEastHerd[i];
	}
	delete[] NextEastHerd;
	NextEastHerd = NULL;

	//return everythingSame;

	if (everythingSame && same) {
		std::cout << "No more Cucumbers moving" << "\n";
		std::cout << step << "steps performed";
		return true;
	}
	else if(step > 1000) {
		std::cout << "step " << step << " ,iteration limit reached, this could go on forever" << std::endl;
		return false;
	}
	else {
		return false;
		step += 1;
		MoveSouth(SouthHerd, EastHerd, cols, rows, everythingSame, step);
		
	}

}

void MoveSouth(int** SouthHerd, int** EastHerd, int cols, int rows, bool same, int step)
{
	//make a temporary new herd for the next timestep
	int** NextSouthHerd = new int* [rows];
	for (int i = 0; i < rows; i++) {
		NextSouthHerd[i] = new int[cols];
	}
	//Set default to 0
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			NextSouthHerd[i][j] = 0;
		}
	}

	//Move to the south!
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (SouthHerd[i][j] == 1)	//check if there is a cucumber in this spot
			{
				if (i != rows - 1)	//Just move south if it is not the last row, eg if no cucumbers need to be teleported 
				{
					if (EastHerd[i+1][j] == 0 && SouthHerd[i+1][j] == 0) //check if there is a cucumber in the adjacent place
					{
						NextSouthHerd[i+1][j] = 1;	//Cucumber moved succesfully
					}
					else
					{
						NextSouthHerd[i][j] = 1; //Cucumber please stay put
					}
				}
				else // teleport me some cucumbers please
				{
					if (EastHerd[0][j] == 0 && SouthHerd[0][j] == 0) //check if there is a cucumber on the other side of the map
					{
						NextSouthHerd[0][j] = 1;	//Cucumber teleported succesfully
					}
					else
					{
						NextSouthHerd[i][j] = 1; //Cucumber please stay put
					}
				}
			}
			else	//If there aint no cucumber to move, what needs to be done?
			{
			}
		}
	}
	//Show me the next timestep
	//std::cout << "South moved cucumbers" << std::endl;
	//showHerd(NextSouthHerd, cols, rows);

	//compare the two herds
	bool everythingSame = true;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (everythingSame) {
				if (SouthHerd[i][j] == NextSouthHerd[i][j]) {
					everythingSame = true;
				}
				else
				{
					everythingSame = false;
				}
			}
		}
	}


	//set the new herd to the default herd
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			SouthHerd[i][j] = NextSouthHerd[i][j];
		}
	}

	//deallocate
	for (int i = 0; i < rows; i++) {
		delete[] NextSouthHerd[i];
	}
	delete[] NextSouthHerd;
	NextSouthHerd = NULL;

	//initiate next step
	MoveEast(SouthHerd, EastHerd, cols, rows, everythingSame, step);

	//return everythingSame;
}