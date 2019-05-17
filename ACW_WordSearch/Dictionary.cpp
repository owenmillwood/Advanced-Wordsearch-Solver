#include "Dictionary.h"
#include <iostream>

Dictionary::Dictionary(void) : m_head(0)
{
}

Dictionary::Dictionary (const Dictionary&) : m_head(0)
{

}

Dictionary::~Dictionary(void)
{
	if (m_head)
	{
		try
		{
			DictionaryNode *currentNode = m_head;
			DictionaryNode *nextNode = currentNode->getNextNode();
			DictionaryNode *downNode;
			DictionaryNode *nextDownNode;
			do
			{
				if (currentNode->getNextNodeDown() != 0)
				{
					downNode = currentNode->getNextNodeDown();
					nextDownNode = downNode->getNextNodeDown();
					while (downNode->getNextNodeDown() != nullptr)
					{
						delete downNode;
						downNode = nextDownNode;
						if (downNode != 0) nextDownNode = downNode->getNextNodeDown();
					} 
				}
				delete currentNode;
				currentNode = nextNode;
				if (currentNode != 0) nextNode = currentNode->getNextNode();
			} while (currentNode != 0);
			m_head = 0;
		}
		catch (exception& e)
		{
			cout << e.what() << endl;
		}
		if (m_head) delete m_head;
	}
}

void Dictionary::addWord(const string& word)
{
	int letterCount = 0;
	DictionaryNode *currentNode;
	bool isEndCheck = false;
	bool incrementCheck = true;

	if (!m_head)
	{
		m_head = new DictionaryNode();
	}
	currentNode = m_head;
	
	while (isEndCheck == false)
	{
		if (currentNode->getLetter() == word[letterCount])
		{			
			currentNode = currentNode->getNextNodeDown();
			incrementCheck = true;
			while (currentNode->getNextNodeDown() != 0)
			{
				if (incrementCheck == true)
				{
					letterCount++;
				}
				incrementCheck = true;
				if (currentNode->getLetter() != word[letterCount])
				{
					if (currentNode->getNextNode() == 0)
					{						
						isEndCheck = true;
						break;
					}
					else
					{
						currentNode = currentNode->getNextNode();
						incrementCheck = false;
					}
				}
				else
				{
					currentNode = currentNode->getNextNodeDown();					
				}
			}
		}
		else if(currentNode->getNextNode() == 0)
		{			
			isEndCheck = true;
			break;
		}
		else
		{
			currentNode = currentNode->getNextNode();
		}
	}

	if (isEndCheck == true)
	{
		currentNode->setNextNode(new DictionaryNode(word[letterCount]));
		currentNode = currentNode->getNextNode();
		letterCount++;

		while (letterCount < word.length() + 1)
		{
			currentNode->SetDownNode(new DictionaryNode(word[letterCount]));
			currentNode = currentNode->getNextNodeDown();
			letterCount++;
		}
	}	
}

DictionaryNode const* const Dictionary::getHeadNode(void)const
{
	return m_head;
}