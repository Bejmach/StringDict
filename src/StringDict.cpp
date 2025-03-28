#include "StringOperations.h"
#include<StringDict.h>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

Element PreElement::ToElement(){
	Element element;
	element.key = this->key;
	element.type = this->type;
	return element;
}

Node::~Node(){
	if(left!=nullptr){
		delete left;
	}
	if(right!=nullptr){
		delete right;
	}
}

std::string SD::ReadFile(std::string path){
	std::ifstream file(path, std::ios::binary);
	
	if(!file){
		std::cout<<"failed to open file: "<<path<<std::endl;
		return{};
	}

	std::ostringstream content;
	content << file.rdbuf();
	file.close();
	return content.str();
}
std::vector<PreElement> SD::PrepareData(std::string data){
	
	std::istringstream stream(data);

	unsigned int lineCount = std::count(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>(), '\n')+1;
	std::vector<PreElement> elements(lineCount);

	stream.clear();
	stream.seekg(0);

	std::string line;
	int i=0;
	while(std::getline(stream, line)){
		PreElement element;
		std::vector<std::string> elementValues = SO::Split(line, " ");
		if(elementValues.size() != 2){
			std::cout<<"Error on line"<<i<<". File not formated correctly. Line: \""<<line<<"\""<<std::endl;
			return {};
		}
		if(std::isdigit(elementValues[0][0]) || std::isdigit(elementValues[1][0])){
			std::cout<<"Error on line"<<i<<". Key or Value Can't start from number and symbols. Line: \""<<line<<"\""<<std::endl;
			return {};
		}
		element.key = elementValues[0];
		element.type = elementValues[1];
		element.value = SO::Value(elementValues[0]);
		elements[i] = element;
		i+=1;
	}
	return elements;
}

// Partition function for QuickSort
int SD::Partition(std::vector<PreElement>& arr, int low, int high) {
    int pivot = arr[high].value;  // Choosing the last element as pivot
    int i = low - 1;              // Index of smaller element

    for (int j = low; j < high; j++) {
        if (arr[j].value < pivot) { // Sorting in ascending order
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]); // Place pivot in correct position
    return i + 1;
}

// QuickSort function
void SD::QuickSort(std::vector<PreElement>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = Partition(arr, low, high);

        QuickSort(arr, low, pivotIndex - 1);  // Left subarray
        QuickSort(arr, pivotIndex + 1, high); // Right subarray
    }
}

// Helper function to sort a vector of PreElements
void SD::SortElements(std::vector<PreElement>& elements) {
    if (!elements.empty()) {
        QuickSort(elements, 0, elements.size() - 1);
    }
}

std::vector<ParsedElement> SD::ParseElements(std::vector<PreElement> elements){
	int differentValues = 0;
	int curValue = -1;
	for(int i=0; i<elements.size(); i++){
		if(elements[i].value != curValue){
			differentValues += 1;
			curValue = elements[i].value;
		}
	}

	std::vector<ParsedElement> parsedElements(differentValues);

	int i = -1;
	curValue = -1;
	for(int j=0; j<elements.size(); j++){
		if(elements[j].value != curValue){
			i+=1;
			curValue = elements[j].value;
		}
		parsedElements[i].value = curValue;
		parsedElements[i].elements.push_back(elements[j].ToElement());
	}
	return parsedElements;
}

// Function to build a balanced BST from a sorted vector of ParsedElements
Node* SD::BuildBalancedTree(const std::vector<ParsedElement>& elements, int start, int end) {
    if (start > end) return nullptr;

    int mid = start + (end - start) / 2;
    Node* root = new Node(elements[mid]);

    root->left = BuildBalancedTree(elements, start, mid - 1);
    root->right = BuildBalancedTree(elements, mid + 1, end);

    return root;
}

// In-order traversal (for testing)
void SD::InorderTraversal(Node* root) {
    if (!root) return;
    InorderTraversal(root->left);
    std::cout << root->value << " ";
    InorderTraversal(root->right);
}

Node* SD::CreateBTree(std::string data){
	std::vector<PreElement> elementVec = PrepareData(data);
	SortElements(elementVec);
	std::vector<ParsedElement> parsedElements = SD::ParseElements(elementVec);
	return BuildBalancedTree(parsedElements, 0, parsedElements.size()-1);
}

std::vector<Element> SD::CreateList(std::string data){
	std::vector<PreElement> elementVec = PrepareData(data);
	std::vector<Element> elements(elementVec.size());
	for(int i=0; i<elementVec.size(); i++){
		elements[i] = elementVec[i].ToElement();
	}
	return elements;
}

std::unordered_map<std::string, std::string> SD::CreateUM(std::string data){
	std::vector<PreElement> elementVec = PrepareData(data);
	std::unordered_map<std::string, std::string> um;
	for(int i=0; i<elementVec.size(); i++){
		um.insert({elementVec[i].key, elementVec[i].type});
	}
	return um;
}


Element* SD::Find(Node* root, std::string key){
	int keyValue = SO::Value(key);

	while (root){
		if(keyValue < root->value){
			root = root->left;
		}
		else if(keyValue > root->value){
			root = root->right;
		}
		else{
			for(int i=0; i<root->elements.size(); i++){
				if(root->elements[i].key == key){
					return &root->elements[i];
				}
			}
			break;
		}
	}
	std::cout<<"element not in diccionary"<<std::endl;
	return nullptr;
}
Element SD::Find(std::vector<Element> root, std::string key){
	for(int i=0; i<root.size(); i++){
		if(root[i].key == key){
			return root[i];
		}
	}

	std::cout<<"element not in diccionary"<<std::endl;
	return {0,0};
}

std::string SD::Find(std::unordered_map<std::string, std::string> um, std::string key){
	auto it = um.find(key);
	if(it!=um.end()){
		return it->second;
	}
	return nullptr;
}


