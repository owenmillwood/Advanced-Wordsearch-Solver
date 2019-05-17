#include "DictionaryNode.h"

DictionaryNode::DictionaryNode(void) : m_NextNode(0), m_NextNodeDown(0)
{
	setLetter('s');
}

DictionaryNode::DictionaryNode(const char& letter) : m_NextNode(0), m_NextNodeDown(0)
{
	setLetter(letter);
}

DictionaryNode::DictionaryNode(const DictionaryNode&) : m_letter(), m_NextNode(0), m_NextNodeDown(0)
{

}


DictionaryNode::~DictionaryNode(void)
{
}

void DictionaryNode::setNextNode(DictionaryNode* const node)
{
	m_NextNode = node;
}

void DictionaryNode::SetDownNode(DictionaryNode* const node)
{
	m_NextNodeDown = node;
}

void DictionaryNode::setLetter(const char& letter)
{
	m_letter = letter;
}

char DictionaryNode::getLetter()const
{
	return m_letter;
}

DictionaryNode* DictionaryNode::getNextNode(void) const
{
	return m_NextNode;
}

DictionaryNode* DictionaryNode::getNextNodeDown(void) const
{
	return m_NextNodeDown;
}





