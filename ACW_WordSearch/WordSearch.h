#pragma once
#include <string>
#include <vector>
#include "Dictionary.h"
#include "DictionaryNode.h"


class WordSearch {
	const char* puzzleName = "wordsearch_grid.txt";
	const char* dictionaryName = "dictionary.txt";
	const char *filenameUsing;
	char ** puzzleArrayPointer;
	int puzzleSize;	
	std::vector<std::string>  wordList;
	std::vector<std::string>  foundWords;
	std::vector<std::string>  foundGridPositions;
	bool isAdvancedSolverCheck;
	int gridCellsVisited;
	int dictionaryEntryCounter;
	Dictionary wordDictionary;
	// Add your code here

public:
	explicit WordSearch(const char * const filename);	
	WordSearch(const WordSearch&);
	WordSearch& operator=(const WordSearch&);
	~WordSearch();

	void ReadSimplePuzzle();
	void ReadSimpleDictionary();
	void ReadAdvancedPuzzle();
	void ReadAdvancedDictionary();
	void SolvePuzzleSimple();	
	bool Check(const volatile char &requiredChar, char const pPuzzleArrayPointer) const;
	void SolvePuzzleAdvanced();
	void WriteResults(const	double loadTime, const double solveTime) const;

	// Add your code here
};

