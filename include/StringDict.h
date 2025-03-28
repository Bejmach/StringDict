#ifndef STRINGDICT_H
#define STRINGDICT_H

#include<iostream>
#include <unordered_map>
#include<vector>
#include<fstream>

#include<StringOperations.h>


struct Element{
	std::string key;
	std::string value;
};

struct PreElement{
	int id;
	std::string key;
	std::string value;

	Element ToElement();
};

struct ParsedElement{
	int id;
	std::vector<Element> elements;
};

struct Node{
	Node *left;
	Node *right;

	int id;
	std::vector<Element> elements;

	Node(ParsedElement element) : id(element.id), elements(element.elements), left(nullptr), right(nullptr){}
	~Node();
};

class SD{
	private:
		static std::vector<PreElement> PrepareData(std::string data);
		static int Partition(std::vector<PreElement>& arr, int low, int high);
		static void QuickSort(std::vector<PreElement>& arr, int low, int high);
		static void SortElements(std::vector<PreElement>& elements);
		static std::vector<ParsedElement> ParseElements(std::vector<PreElement> elements);
		static Node* BuildBalancedTree(const std::vector<ParsedElement>& elements, int start, int end);

	public:
		static std::string ReadFile(std::string path);
		static Node* CreateBTree(std::string data);
		static std::vector<Element> CreateList(std::string data);
		static std::unordered_map<std::string, std::string> CreateUM(std::string data);
		static void InorderTraversal(Node* root);
		static Element* Find(Node* root, std::string key);
		static Element Find(std::vector<Element> root, std::string key);
		static std::string Find(std::unordered_map<std::string, std::string> root, std::string key);
};

#endif
