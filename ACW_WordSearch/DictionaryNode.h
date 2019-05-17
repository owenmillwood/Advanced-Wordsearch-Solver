#pragma once

#include <string>

using namespace std;

class DictionaryNode
{
public:
	DictionaryNode(void);
	explicit DictionaryNode(const char& letter);
	DictionaryNode (const DictionaryNode&);
	DictionaryNode& operator=(const DictionaryNode&);
	~DictionaryNode(void);
	
	void  setNextNode(DictionaryNode* const node);
	void  SetDownNode(DictionaryNode* const node);
	void setLetter(const char& letter);
	char getLetter(void)const;
	DictionaryNode* getNextNode(void) const;
	DictionaryNode* getNextNodeDown(void) const;

private:
	char m_letter;
	DictionaryNode* m_NextNode;
	DictionaryNode* m_NextNodeDown;
};

