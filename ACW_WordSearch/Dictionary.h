#pragma once
#include "DictionaryNode.h"

class Dictionary
{
public:
	Dictionary(void);
	Dictionary (const Dictionary&);
	Dictionary& operator=(const Dictionary&);
	~Dictionary(void);	

	void addWord(const string& word);
    DictionaryNode const* const getHeadNode(void) const;

private:
	DictionaryNode * m_head;
};

