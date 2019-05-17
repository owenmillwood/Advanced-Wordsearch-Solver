#include "WordSearch.h"

#include <iostream>
#include <fstream>
#include <ostream>
#include <iterator>
#include <string>
#include <algorithm>
#include <vector>
#include <list>


using namespace std;

WordSearch::WordSearch(const char * const filename) :puzzleArrayPointer(nullptr), puzzleSize(), isAdvancedSolverCheck(), gridCellsVisited(0), dictionaryEntryCounter(0){
	filenameUsing = filename;
}

WordSearch::WordSearch(const WordSearch&): filenameUsing(), puzzleArrayPointer(nullptr), puzzleSize(), isAdvancedSolverCheck(), gridCellsVisited(0), dictionaryEntryCounter(0)
 {

}

WordSearch::~WordSearch() {
	// Add your code here
	delete[] puzzleArrayPointer[0];
	delete[] puzzleArrayPointer;
}

void WordSearch::ReadSimplePuzzle() {
	// Add your code here
	ifstream fin(puzzleName);
	if (fin.is_open())
	{
		fin >> puzzleSize;
	}

	//cout << puzzleSize << endl;

	puzzleArrayPointer = new char*[puzzleSize];
	char * const simpleArrayData = new char[puzzleSize * puzzleSize];

	for (int i = 0; i < puzzleSize; i++)
	{
		puzzleArrayPointer[i] = simpleArrayData + puzzleSize * i;
	}

	int i, j;
	const int rowAndCol = puzzleSize;

	for (i = 0; i < rowAndCol; i++)
	{
		for (j = 0; j < rowAndCol; j++)		//i = row, j = col
		{
			char c;
				fin >> c;
				puzzleArrayPointer[i][j] = c;
			//cout << puzzleArrayPointer[i][j] << ' ';
		}
		//cout << '\n';
	}

}

void WordSearch::ReadSimpleDictionary() {
	// Add your code here
	string line;
	ifstream dictionaryFile(dictionaryName);

	int i = 0;
	while (getline(dictionaryFile, line))
	{		
		wordList.push_back(line);
		//cout << wordList[i] << endl;
		i++;
	}
}

void WordSearch::ReadAdvancedPuzzle() {
	// Add your code here
	ifstream fin(puzzleName);
	if (fin.is_open())
	{
		fin >> puzzleSize;
	}

	//cout << puzzleSize << endl;

	puzzleArrayPointer = new char*[puzzleSize];
	char * const simpleArrayData = new char[puzzleSize * puzzleSize];

	for (int i = 0; i < puzzleSize; i++)
	{
		puzzleArrayPointer[i] = simpleArrayData + puzzleSize * i;
	}

	int i, j;
	const int rowAndCol = puzzleSize;

	for (i = 0; i < rowAndCol; i++)
	{
		for (j = 0; j < rowAndCol; j++)		//i = row, j = col
		{
			fin >> puzzleArrayPointer[i][j];
			//cout << puzzleArrayPointer[i][j] << ' ';
		}
		//cout << '\n';
	}
}

void WordSearch::ReadAdvancedDictionary() {
	// Add your code here
	string word;
	ifstream dictionaryFile(dictionaryName);	
	
	while (getline(dictionaryFile, word))
	{
		wordDictionary.addWord(word);
	}
}

void WordSearch::SolvePuzzleSimple() {
	//Add your code here
	isAdvancedSolverCheck = false;
	string currentWord;	
	char currentWordChar;
	char currentPuzzleChar;
	int currentRow, currentColumn;
	int nextRow, nextCol;
	int startPosCol, startPosRow;
	int wordCharCount = 0;
	dictionaryEntryCounter = 0;
	bool breakCheck = false;
	bool foundCheck;
	int currentWordLength;
	string startPosRowString, startPosColString, jointCoordinates;


	for (int i = 0; i < puzzleSize; i++)  //for each row in the puzzle grid
	{
		currentRow = i;
		gridCellsVisited++;

		for (int j = 0; j < puzzleSize; j++)  //for each column in the puzzle grid
		{
			currentColumn = j;
			currentPuzzleChar = puzzleArrayPointer[i][j];
			gridCellsVisited++;

			for (int k = 0; k < wordList.size(); k++)	 //iterate through wordList
			{
				breakCheck = false;
				currentWord = wordList[k];
				dictionaryEntryCounter++;
				currentWordChar = currentWord[wordCharCount];
				currentWordLength = currentWord.length();

				if (currentPuzzleChar == currentWordChar)
				{
					startPosRow = currentRow;
					startPosCol = currentColumn;
					nextRow = currentRow;
					nextCol = currentColumn;

					for (int m = 1; m < currentWordLength; m++)  //right check
					{
						if (nextCol + 1 > puzzleSize - 1)
						{
							break;
						}
						
						foundCheck = Check(currentWord[m], puzzleArrayPointer[nextRow][nextCol + 1]);// RIGHT CHECK
						gridCellsVisited++;

						if (foundCheck == false)  //if letters do not match
						{
							break;
						}
						else if (m == currentWordLength - 1 && foundCheck == true)  //determines if the whole word has been found in the puzzle grid
						{
							startPosRowString = to_string(startPosRow);
							startPosColString = to_string(startPosCol);
							jointCoordinates = (startPosRowString + " " + startPosColString);
							foundGridPositions.push_back(jointCoordinates);
							foundWords.push_back(currentWord);
							wordList.erase(wordList.begin() + k);
							breakCheck = true;
							break;
						}
						else
						{
							nextCol++;
							continue;
						}
					}

					if (breakCheck == true)
					{
						continue;
					}
					nextRow = currentRow;
					nextCol = currentColumn;

					for (int n = 1; n < currentWordLength; n++)  //diag right down check
					{
						if (nextCol + 1 > puzzleSize - 1 || nextRow + 1 > puzzleSize - 1)
						{
							break;
						}
						foundCheck = Check(currentWord[n], puzzleArrayPointer[nextRow + 1][nextCol + 1]);// DOWN RIGHT CHECK
						gridCellsVisited++;

						if (foundCheck == false)  //if letters do not match
						{
							break;
						}
						else if (n == currentWordLength - 1 && foundCheck == true)  //determines if the whole word has been found in the puzzle grid
						{
							startPosRowString = to_string(startPosRow);
							startPosColString = to_string(startPosCol);
							jointCoordinates = (startPosRowString + " " + startPosColString);
							foundGridPositions.push_back(jointCoordinates);
							foundWords.push_back(currentWord);
							wordList.erase(wordList.begin() + k);
							breakCheck = true;
							break;
						}
						else
						{
							nextCol++;
							nextRow++;
							continue;
						}
					}

					if (breakCheck == true)
					{
						continue;
					}
					nextRow = currentRow;
					nextCol = currentColumn;

					for (int o = 1; o < currentWordLength; o++)  //down check
					{
						if (nextRow + 1 > puzzleSize - 1)
						{
							break;
						}
						foundCheck = Check(currentWord[o], puzzleArrayPointer[nextRow + 1][nextCol]);// DOWN CHECK
						gridCellsVisited++;

						if (foundCheck == false)  //if letters do not match
						{
							break;
						}
						else if (o == currentWordLength - 1 && foundCheck == true)  //determines if the whole word has been found in the puzzle grid
						{
							startPosRowString = to_string(startPosRow);
							startPosColString = to_string(startPosCol);
							jointCoordinates = (startPosRowString + " " + startPosColString);
							foundGridPositions.push_back(jointCoordinates);
							foundWords.push_back(currentWord);
							wordList.erase(wordList.begin() + k);
							breakCheck = true;
							break;
						}
						else
						{
							nextRow++;
							continue;
						}
					}

					if (breakCheck == true)
					{
						continue;
					}
					nextRow = currentRow;
					nextCol = currentColumn;

					for (int p = 1; p < currentWordLength; p++)  //diag left down check
					{
						if (nextCol - 1 < 0 || nextRow + 1 > puzzleSize - 1)
						{
							break;
						}
						foundCheck = Check(currentWord[p], puzzleArrayPointer[nextRow + 1][nextCol - 1]);// DOWN LEFT
						gridCellsVisited++;

						if (foundCheck == false)  //if letters do not match
						{
							break;
						}
						else if (p == currentWordLength - 1 && foundCheck == true)  //determines if the whole word has been found in the puzzle grid
						{
							startPosRowString = to_string(startPosRow);
							startPosColString = to_string(startPosCol);
							jointCoordinates = (startPosRowString + " " + startPosColString);
							foundGridPositions.push_back(jointCoordinates);
							foundWords.push_back(currentWord);
							wordList.erase(wordList.begin() + k);
							breakCheck = true;
							break;
						}
						else
						{
							nextRow++;
							nextCol--;
							continue;
						}
					}

					if (breakCheck == true)
					{
						continue;
					}
					nextRow = currentRow;
					nextCol = currentColumn;

					for (int q = 1; q < currentWordLength; q++)  //left check
					{
						if (nextCol - 1 < 0)
						{
							break;
						}
						foundCheck = Check(currentWord[q], puzzleArrayPointer[nextRow][nextCol - 1]);
						gridCellsVisited++;

						if (foundCheck == false)  //if letters do not match
						{
							break;
						}
						else if (q == currentWordLength - 1 && foundCheck == true)  //determines if the whole word has been found in the puzzle grid
						{
							startPosRowString = to_string(startPosRow);
							startPosColString = to_string(startPosCol);
							jointCoordinates = (startPosRowString + " " + startPosColString);
							foundGridPositions.push_back(jointCoordinates);
							foundWords.push_back(currentWord);
							wordList.erase(wordList.begin() + k);
							breakCheck = true;
							break;
						}
						else
						{
							nextCol--;
							continue;
						}
					}

					if (breakCheck == true)
					{
						continue;
					}
					nextRow = currentRow;
					nextCol = currentColumn;

					for (int r = 1; r < currentWordLength; r++)  //diag left up check
					{
						if (nextCol - 1 < 0 || nextRow - 1 < 0)
						{
							break;
						}
						foundCheck = Check(currentWord[r], puzzleArrayPointer[nextRow - 1][nextCol - 1]);// UP LEFT CHECK
						gridCellsVisited++;

						if (foundCheck == false)  //if letters do not match
						{
							break;
						}
						else if (r == currentWordLength - 1 && foundCheck == true)  //determines if the whole word has been found in the puzzle grid
						{
							startPosRowString = to_string(startPosRow);
							startPosColString = to_string(startPosCol);
							jointCoordinates = (startPosRowString + " " + startPosColString);
							foundGridPositions.push_back(jointCoordinates);
							foundWords.push_back(currentWord);
							wordList.erase(wordList.begin() + k);
							breakCheck = true;
							break;
						}
						else
						{
							nextRow--;
							nextCol--;
							continue;
						}
					}

					if (breakCheck == true)
					{
						continue;
					}
					nextRow = currentRow;
					nextCol = currentColumn;

					for (int s = 1; s < currentWordLength; s++)  //up check
					{
						if (nextRow - 1 < 0)
						{
							break;
						}
						foundCheck = Check(currentWord[s], puzzleArrayPointer[nextRow - 1][nextCol]);// UP CHECK
						gridCellsVisited++;

						if (foundCheck == false)  //if letters do not match
						{
							break;
						}
						else if (s == currentWordLength - 1 && foundCheck == true)  //determines if the whole word has been found in the puzzle grid
						{
							startPosRowString = to_string(startPosRow);
							startPosColString = to_string(startPosCol);
							jointCoordinates = (startPosRowString + " " + startPosColString);
							foundGridPositions.push_back(jointCoordinates);
							foundWords.push_back(currentWord);
							wordList.erase(wordList.begin() + k);
							breakCheck = true;
							break;
						}
						else
						{
							nextRow--;
							continue;
						}
					}

					if (breakCheck == true)
					{
						continue;
					}
					nextRow = currentRow;
					nextCol = currentColumn;

					for (int s = 1; s < currentWordLength; s++)  //diag right up check
					{
						if (nextCol + 1 > puzzleSize - 1 || nextRow - 1 < 0)
						{
							break;
						}
						foundCheck = Check(currentWord[s], puzzleArrayPointer[nextRow - 1][nextCol + 1]);// UP RIGHT CHECK
						gridCellsVisited++;

						if (foundCheck == false)  //if letters do not match
						{
							breakCheck = true;
							break;
						}
						else if (s == currentWordLength - 1 && foundCheck == true)  //determines if the whole word has been found in the puzzle grid
						{
							startPosRowString = to_string(startPosRow);
							startPosColString = to_string(startPosCol);
							jointCoordinates = (startPosRowString + " " + startPosColString);
							foundGridPositions.push_back(jointCoordinates);
							foundWords.push_back(currentWord);
							wordList.erase(wordList.begin() + k);
							breakCheck = true;
							break;
						}
						else
						{
							nextRow--;
							nextCol++;
							continue;
						}
					}

					if (breakCheck == true)
					{
						continue;
					}
					nextRow = currentRow;
					nextCol = currentColumn;
				}

				else  //letter does not match thus break loop to move to next word
				{
					wordCharCount = 0;
					continue;
				}
			}
		}
	}
}

void WordSearch::SolvePuzzleAdvanced() {

	isAdvancedSolverCheck = true;
	gridCellsVisited = 0;

	int currentRow, currentColumn, nextRow, nextCol, startPosRow, startPosCol;
	char wordFirstLetter;
	char volatile currentDictionaryLetter, currentPuzzleChar;
	
	bool foundCheck;	
	bool changeNodeCheck = true;
	string startPosRowString, startPosColString, jointCoordinates;
	string tempWordString = "";
	DictionaryNode const* currentNode = wordDictionary.getHeadNode();
	

	for (int i = 0; i < puzzleSize; i++)
	{
		currentRow = i;
		gridCellsVisited++;
		for (int j = 0; j < puzzleSize; j++)
		{
			currentColumn = j;
			currentPuzzleChar = puzzleArrayPointer[i][j];
			gridCellsVisited++;			
			currentNode = &(*wordDictionary.getHeadNode());

			while (currentNode->getNextNode())
			{
				currentNode = currentNode->getNextNode();
				currentDictionaryLetter = currentNode->getLetter();
				if (currentNode->getLetter() == currentPuzzleChar) //if match, check letters down
				{
					wordFirstLetter = currentDictionaryLetter;
					tempWordString += currentDictionaryLetter;
					startPosRow = currentRow;
					startPosCol = currentColumn;
					nextRow = currentRow;
					nextCol = currentColumn;

					while (currentNode->getNextNodeDown() != 0)  //right check
					{
						if (changeNodeCheck == true)
						{
							currentNode = currentNode->getNextNodeDown();
							currentDictionaryLetter = currentNode->getLetter();
							dictionaryEntryCounter++;
						}
						changeNodeCheck = true;

						if (currentNode->getNextNodeDown() == '\0')
						{
							break;
						}

						if (nextCol + 1 > puzzleSize - 1)
						{							
							break;
						}

						foundCheck = Check(currentDictionaryLetter, puzzleArrayPointer[nextRow][nextCol + 1]);
						gridCellsVisited++;

						if (foundCheck == false && currentNode->getNextNode() != 0)  //if letters do not match
						{
							currentNode = currentNode->getNextNode();
							dictionaryEntryCounter++;
							currentDictionaryLetter = currentNode->getLetter();
							changeNodeCheck = false;
							continue;													
						}

						if (foundCheck == false && currentNode->getNextNode() == 0)
						{
							break;
						}

						else if (foundCheck == true)  //determines if the whole word has been found in the puzzle grid
						{
							tempWordString += currentDictionaryLetter;
							nextCol++;
							continue;
						}
					}
					if (foundCheck == true && currentNode->getNextNode() == 0)
					{
						startPosRowString = to_string(startPosRow);
						startPosColString = to_string(startPosCol);
						jointCoordinates = (startPosRowString + " " + startPosColString);
						foundGridPositions.push_back(jointCoordinates);
						foundWords.push_back(tempWordString);					
					}
					else
					{
						tempWordString = "";						
					}

					
					nextRow = currentRow;
					nextCol = currentColumn;
					currentNode = &(*wordDictionary.getHeadNode());
					dictionaryEntryCounter++;
					while (currentNode->getNextNode() != 0)
					{
						currentNode = currentNode->getNextNode();
						dictionaryEntryCounter++;
						if (currentNode->getLetter() == currentPuzzleChar)
						{
							break;
						}
						else
						{
							continue;
						}
					}						
					tempWordString = wordFirstLetter;					

					while (currentNode->getNextNodeDown() != 0)  //down right check
					{
						if (changeNodeCheck == true)
						{
							currentNode = currentNode->getNextNodeDown();
							dictionaryEntryCounter++;
							currentDictionaryLetter = currentNode->getLetter();
						}
						changeNodeCheck = true;

						if (currentNode->getNextNodeDown() == '\0')
						{
							break;
						}

						if (nextCol + 1 > puzzleSize - 1 || nextRow + 1 > puzzleSize - 1)
						{
							break;
						}

						foundCheck = Check(currentDictionaryLetter, puzzleArrayPointer[nextRow + 1][nextCol + 1]);
						gridCellsVisited++;

						if (foundCheck == false && currentNode->getNextNode() != 0)  //if letters do not match
						{
							currentNode = currentNode->getNextNode();
							dictionaryEntryCounter++;
							currentDictionaryLetter = currentNode->getLetter();
							changeNodeCheck = false;
							continue;
						}

						if (foundCheck == false && currentNode->getNextNode() == 0)
						{
							break;
						}

						else if (foundCheck == true)  //determines if the whole word has been found in the puzzle grid
						{
							tempWordString += currentDictionaryLetter;
							nextCol++;
							nextRow++;
							continue;
						}
					}
					if (foundCheck == true && currentNode->getNextNodeDown() == 0)
					{
						startPosRowString = to_string(startPosRow);
						startPosColString = to_string(startPosCol);
						jointCoordinates = (startPosRowString + " " + startPosColString);
						foundGridPositions.push_back(jointCoordinates);
						foundWords.push_back(tempWordString);
					}
					else
					{
						tempWordString = "";
					}

					nextRow = currentRow;
					nextCol = currentColumn;
					currentNode = &(*wordDictionary.getHeadNode());
					dictionaryEntryCounter++;
					while (currentNode->getNextNode() != 0)
					{
						currentNode = currentNode->getNextNode();
						dictionaryEntryCounter++;
						if (currentNode->getLetter() == currentPuzzleChar)
						{
							break;
						}
						else
						{
							continue;
						}
					}
					tempWordString = wordFirstLetter;					

					while (currentNode->getNextNodeDown() != 0)  //down check
					{
						if (changeNodeCheck == true)
						{
							currentNode = currentNode->getNextNodeDown();
							dictionaryEntryCounter++;
							currentDictionaryLetter = currentNode->getLetter();
						}
						changeNodeCheck = true;

						if (currentNode->getNextNodeDown() == '\0')
						{
							break;
						}

						if (nextRow + 1 > puzzleSize - 1)
						{
							break;
						}

						foundCheck = Check(currentDictionaryLetter, puzzleArrayPointer[nextRow + 1][nextCol]);
						gridCellsVisited++;

						if (foundCheck == false && currentNode->getNextNode() != 0)  //if letters do not match
						{
							currentNode = currentNode->getNextNode();
							dictionaryEntryCounter++;
							currentDictionaryLetter = currentNode->getLetter();
							changeNodeCheck = false;
							continue;
						}

						if (foundCheck == false && currentNode->getNextNode() == 0)
						{
							break;
						}

						else if (foundCheck == true)  //determines if the whole word has been found in the puzzle grid
						{
							tempWordString += currentDictionaryLetter;
							nextRow++;
							continue;
						}
					}
					if (foundCheck == true && currentNode->getNextNodeDown() == 0)
					{
						startPosRowString = to_string(startPosRow);
						startPosColString = to_string(startPosCol);
						jointCoordinates = (startPosRowString + " " + startPosColString);
						foundGridPositions.push_back(jointCoordinates);
						foundWords.push_back(tempWordString);
					}

					else
					{
						tempWordString = "";
					}

					nextRow = currentRow;
					nextCol = currentColumn;
					currentNode = &(*wordDictionary.getHeadNode());
					dictionaryEntryCounter++;
					while (currentNode->getNextNode() != 0)
					{
						currentNode = currentNode->getNextNode();
						if (currentNode->getLetter() == currentPuzzleChar)
						{
							break;
						}
						else
						{
							continue;
						}
					}
					tempWordString = wordFirstLetter;					

					while (currentNode->getNextNodeDown() != 0)  //diag left down check
					{
						if (changeNodeCheck == true)
						{
							currentNode = currentNode->getNextNodeDown();
							dictionaryEntryCounter++;
							currentDictionaryLetter = currentNode->getLetter();
						}
						changeNodeCheck = true;

						if (currentNode->getNextNodeDown() == '\0')
						{
							break;
						}

						if (nextCol - 1 < 0 || nextRow + 1 > puzzleSize - 1)
						{
							break;
						}

						foundCheck = Check(currentDictionaryLetter, puzzleArrayPointer[nextRow + 1][nextCol -1]);
						gridCellsVisited++;

						if (foundCheck == false && currentNode->getNextNode() != 0)  //if letters do not match
						{
							currentNode = currentNode->getNextNode();
							dictionaryEntryCounter++;
							currentDictionaryLetter = currentNode->getLetter();
							changeNodeCheck = false;
							continue;
						}

						if (foundCheck == false && currentNode->getNextNode() == 0)
						{
							break;
						}

						else if (foundCheck == true)  //determines if the whole word has been found in the puzzle grid
						{
							tempWordString += currentDictionaryLetter;
							nextRow++;
							nextCol--;
							continue;
						}
					}
					if (foundCheck == true && currentNode->getNextNodeDown() == 0)
					{
						startPosRowString = to_string(startPosRow);
						startPosColString = to_string(startPosCol);
						jointCoordinates = (startPosRowString + " " + startPosColString);
						foundGridPositions.push_back(jointCoordinates);
						foundWords.push_back(tempWordString);
					}
					else
					{
						tempWordString = "";
					}

					nextRow = currentRow;
					nextCol = currentColumn;
					currentNode = &(*wordDictionary.getHeadNode());
					dictionaryEntryCounter++;
					while (currentNode->getNextNode() != 0)
					{
						currentNode = currentNode->getNextNode();
						if (currentNode->getLetter() == currentPuzzleChar)
						{
							break;
						}
						else
						{
							continue;
						}
					}
					tempWordString = wordFirstLetter;					

					while (currentNode->getNextNodeDown() != 0)  //left check
					{
						if (changeNodeCheck == true)
						{
							currentNode = currentNode->getNextNodeDown();
							dictionaryEntryCounter++;
							currentDictionaryLetter = currentNode->getLetter();
						}
						changeNodeCheck = true;

						if (currentNode->getNextNodeDown() == '\0')
						{
							break;
						}

						if (nextCol - 1 < 0)
						{
							break;
						}

						foundCheck = Check(currentDictionaryLetter, puzzleArrayPointer[nextRow][nextCol - 1]);
						gridCellsVisited++;

						if (foundCheck == false && currentNode->getNextNode() != 0)  //if letters do not match
						{
							currentNode = currentNode->getNextNode();
							dictionaryEntryCounter++;
							currentDictionaryLetter = currentNode->getLetter();
							changeNodeCheck = false;
							continue;
						}

						if (foundCheck == false && currentNode->getNextNode() == 0)
						{
							break;
						}

						else if (foundCheck == true)  //determines if the whole word has been found in the puzzle grid
						{
							tempWordString += currentDictionaryLetter;
							nextCol--;
							continue;
						}
					}
					if (foundCheck == true && currentNode->getNextNodeDown() == 0)
					{
						startPosRowString = to_string(startPosRow);
						startPosColString = to_string(startPosCol);
						jointCoordinates = (startPosRowString + " " + startPosColString);
						foundGridPositions.push_back(jointCoordinates);
						foundWords.push_back(tempWordString);
					}
					else
					{
						tempWordString = "";
					}

					nextRow = currentRow;
					nextCol = currentColumn;
					currentNode = &(*wordDictionary.getHeadNode());
					dictionaryEntryCounter++;
					while (currentNode->getNextNode() != 0)
					{
						currentNode = currentNode->getNextNode();
						if (currentNode->getLetter() == currentPuzzleChar)
						{
							break;
						}
						else
						{
							continue;
						}
					}
					tempWordString = wordFirstLetter;					

					while (currentNode->getNextNodeDown() != 0)  //left up check
					{
						if (changeNodeCheck == true)
						{
							currentNode = currentNode->getNextNodeDown();
							dictionaryEntryCounter++;
							currentDictionaryLetter = currentNode->getLetter();
						}
						changeNodeCheck = true;

						if (currentNode->getNextNodeDown() == '\0')
						{
							break;
						}

						if (nextCol - 1 < 0 || nextRow - 1 < 0)
						{
							break;
						}

						foundCheck = Check(currentDictionaryLetter, puzzleArrayPointer[nextRow - 1][nextCol - 1]);
						gridCellsVisited++;

						if (foundCheck == false && currentNode->getNextNode() != 0)  //if letters do not match
						{
							currentNode = currentNode->getNextNode();
							dictionaryEntryCounter++;
							currentDictionaryLetter = currentNode->getLetter();
							changeNodeCheck = false;
							continue;
						}

						if (foundCheck == false && currentNode->getNextNode() == 0)
						{
							break;
						}

						else if (foundCheck == true)  //determines if the whole word has been found in the puzzle grid
						{
							tempWordString += currentDictionaryLetter;
							nextCol--;
							nextRow--;
							continue;
						}
					}
					if (foundCheck == true && currentNode->getNextNodeDown() == 0)
					{
						startPosRowString = to_string(startPosRow);
						startPosColString = to_string(startPosCol);
						jointCoordinates = (startPosRowString + " " + startPosColString);
						foundGridPositions.push_back(jointCoordinates);
						foundWords.push_back(tempWordString);
					}
					else
					{
						tempWordString = "";
					}

					nextRow = currentRow;
					nextCol = currentColumn;
					currentNode = &(*wordDictionary.getHeadNode());
					dictionaryEntryCounter++;
					while (currentNode->getNextNode() != 0)
					{
						currentNode = currentNode->getNextNode();
						if (currentNode->getLetter() == currentPuzzleChar)
						{
							break;
						}
						else
						{
							continue;
						}
					}
					tempWordString = wordFirstLetter;					

					while (currentNode->getNextNodeDown() != 0)  //up check
					{
						if (changeNodeCheck == true)
						{
							currentNode = currentNode->getNextNodeDown();
							dictionaryEntryCounter++;
							currentDictionaryLetter = currentNode->getLetter();
						}
						changeNodeCheck = true;

						if (currentNode->getNextNodeDown() == '\0')
						{
							break;
						}

						if (nextRow - 1 < 0)
						{
							break;
						}

						foundCheck = Check(currentDictionaryLetter, puzzleArrayPointer[nextRow - 1][nextCol]);
						gridCellsVisited++;

						if (foundCheck == false && currentNode->getNextNode() != 0)  //if letters do not match
						{
							currentNode = currentNode->getNextNode();
							dictionaryEntryCounter++;
							currentDictionaryLetter = currentNode->getLetter();
							changeNodeCheck = false;
							continue;
						}

						if (foundCheck == false && currentNode->getNextNode() == 0)
						{
							break;
						}

						else if (foundCheck == true)  //determines if the whole word has been found in the puzzle grid
						{
							tempWordString += currentDictionaryLetter;
							nextRow--;
							continue;
						}
					}
					if (foundCheck == true && currentNode->getNextNodeDown() == 0)
					{
						startPosRowString = to_string(startPosRow);
						startPosColString = to_string(startPosCol);
						jointCoordinates = (startPosRowString + " " + startPosColString);
						foundGridPositions.push_back(jointCoordinates);
						foundWords.push_back(tempWordString);
					}
					else
					{
						tempWordString = "";
					}

					nextRow = currentRow;
					nextCol = currentColumn;
					currentNode = &(*wordDictionary.getHeadNode());
					dictionaryEntryCounter++;
					while (currentNode->getNextNode() != 0)
					{
						currentNode = currentNode->getNextNode();
						if (currentNode->getLetter() == currentPuzzleChar)
						{
							break;
						}
						else
						{
							continue;
						}
					}
					tempWordString = wordFirstLetter;					

					while (currentNode->getNextNodeDown() != 0)  //up right check
					{
						if (changeNodeCheck == true)
						{
							currentNode = currentNode->getNextNodeDown();
							dictionaryEntryCounter++;
							currentDictionaryLetter = currentNode->getLetter();
						}
						changeNodeCheck = true;

						if (currentNode->getNextNodeDown() == '\0')
						{
							break;
						}

						if (nextCol + 1 > puzzleSize - 1 || nextRow - 1 < 0)
						{
							break;
						}

						foundCheck = Check(currentDictionaryLetter, puzzleArrayPointer[nextRow - 1][nextCol + 1]);
						gridCellsVisited++;

						if (foundCheck == false && currentNode->getNextNode() != 0)  //if letters do not match
						{
							currentNode = currentNode->getNextNode();
							dictionaryEntryCounter++;
							currentDictionaryLetter = currentNode->getLetter();
							changeNodeCheck = false;
							continue;
						}

						if (foundCheck == false && currentNode->getNextNode() == 0)
						{
							break;
						}

						else if (foundCheck == true)  //determines if the whole word has been found in the puzzle grid
						{
							tempWordString += currentDictionaryLetter;
							nextRow--;
							nextCol++;
							continue;
						}
					}
					if (foundCheck == true && currentNode->getNextNodeDown() == 0)
					{
						startPosRowString = to_string(startPosRow);
						startPosColString = to_string(startPosCol);
						jointCoordinates = (startPosRowString + " " + startPosColString);
						foundGridPositions.push_back(jointCoordinates);
						foundWords.push_back(tempWordString);
					}
					else
					{
						tempWordString = "";
					}
				}
				else
				{
					continue;
				}
			}				
		}
	}
}

bool WordSearch::Check(const volatile char & requiredChar, char const pPuzzleArrayPointer)const
{
	if (pPuzzleArrayPointer == requiredChar)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void WordSearch::WriteResults(const double loadTime, const double solveTime) const {
	// Add your code here
	if (isAdvancedSolverCheck == false)
	{
		ofstream outputFile;
		outputFile.open(filenameUsing);
		outputFile << "NUMBER_OF_WORDS_MATCHED ";
		outputFile << foundWords.size() << endl << endl;
		outputFile << "WORDS_MATCHED_IN_GRID" << endl;
		for (int i = 0; i < foundWords.size(); i++)
		{
			
			outputFile << foundGridPositions[i] + (" ");
			outputFile << foundWords[i] << endl;
		}
		outputFile << endl;
		outputFile << "WORDS_UNMATCHED_IN_GRID" << endl;
		for (int i = 0; i < wordList.size(); i++)
		{
			outputFile << wordList[i] << endl;
		}
		outputFile << endl;
		outputFile << "NUMBER_OF_GRID_CELLS_VISITED ";
		outputFile << gridCellsVisited << endl << endl;
		outputFile << "NUMBER_OF_DICTIONARY_ENTRIES_VISITED ";
		outputFile << dictionaryEntryCounter << endl << endl;
		outputFile << "TIME_TO_POPULATE_GRID_STRUCTURE ";
		outputFile << loadTime << endl << endl;
		outputFile << "TIME_TO_SOLVE_PUZZLE ";
		outputFile << solveTime;		

		outputFile.close();		
	}

	else if (isAdvancedSolverCheck == true)
	{
		ofstream outputFile;
		outputFile.open(filenameUsing);
		outputFile << "NUMBER_OF_WORDS_MATCHED ";
		outputFile << foundWords.size() << endl << endl;
		outputFile << "WORDS_MATCHED_IN_GRID" << endl;
		for (int i = 0; i < foundWords.size(); i++)
		{
			outputFile << foundGridPositions[i] + (" ");
			outputFile << foundWords[i] << endl;
		}
		outputFile << endl;
		outputFile << "WORDS_UNMATCHED_IN_GRID" << endl;

		string line;
		ifstream dictionaryFile(dictionaryName);
		std::vector<std::string>  wordListUntouched;

		int i = 0;
		while (getline(dictionaryFile, line))
		{
			wordListUntouched.push_back(line);			
			i++;
		}

		for (int i = 0; i < wordListUntouched.size(); i++)
		{
			for (int j = 0; j < foundWords.size(); j++)
			{
				if (wordListUntouched[i] == foundWords[j])
				{					
					wordListUntouched[i] = "";
				}
				else
				{
					continue;
				}
			}			
		}

		for (int k = 0; k < wordListUntouched.size(); k++)
		{
			if (wordListUntouched[k] == "")
			{
				continue;
			}
			else
			{
				outputFile << wordListUntouched[k] << endl;
			}			
		}
		
		outputFile << endl;
		outputFile << "NUMBER_OF_GRID_CELLS_VISITED ";
		outputFile << gridCellsVisited << endl << endl;
		outputFile << "NUMBER_OF_DICTIONARY_ENTRIES_VISITED ";
		outputFile << dictionaryEntryCounter << endl << endl;
		outputFile << "TIME_TO_POPULATE_GRID_STRUCTURE ";
		outputFile << loadTime << endl << endl;
		outputFile << "TIME_TO_SOLVE_PUZZLE ";
		outputFile << solveTime;

		outputFile.close();
	}
}