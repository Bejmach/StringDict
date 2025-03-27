#ifndef STRINGDICT_H
#define STRINGDICT_H

#include<iostream>
#include<vector>
#include<fstream>

#include<StringOperations.h>


struct Element{
	std::string key;
	std::string type;
};

struct PreElement{
	int value;
	std::string key;
	std::string type;

	Element ToElement();
};

struct ParsedElement{
	int value;
	std::vector<Element> elements;
};

struct Node{
	Node *left;
	Node *right;

	int value;
	std::vector<Element> elements;

	Node(ParsedElement element) : value(element.value), elements(element.elements), left(nullptr), right(nullptr){}
	~Node();
};

class SD{
	private:
		static std::vector<PreElement> ReadFile(std::string path);
		static int Partition(std::vector<PreElement>& arr, int low, int high);
		static void QuickSort(std::vector<PreElement>& arr, int low, int high);
		static void SortElements(std::vector<PreElement>& elements);
		static std::vector<ParsedElement> ParseElements(std::vector<PreElement> elements);
		static Node* BuildBalancedTree(const std::vector<ParsedElement>& elements, int start, int end);

	public:
		static Node* FromFile(std::string path);
		static void InorderTraversal(Node* root);
		static Element* Find(Node* root, std::string key);
		static Element* Find(Node* root, int keyValue);
};

#endif
