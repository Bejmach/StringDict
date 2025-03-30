#include <StringOperations.h>
#include<StringDict.h>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

Element PreElement::ToElement(){
	Element element;
	element.key = this->key;
	element.value = this->value;
	return element;
}

Dict::~Dict(){
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
		element.value = elementValues[1];
		element.id = SO::Value(elementValues[0]);
		elements[i] = element;
		i+=1;
	}
	return elements;
}

// Partition function for QuickSort
int SD::Partition(std::vector<PreElement>& arr, int low, int high) {
    int pivot = arr[high].id;  // Choosing the last element as pivot
    int i = low - 1;              // Index of smaller element

    for (int j = low; j < high; j++) {
        if (arr[j].id < pivot) { // Sorting in ascending order
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
	int differentIds = 0;
	int curId = -1;
	for(int i=0; i<elements.size(); i++){
		if(elements[i].id != curId){
			differentIds += 1;
			curId = elements[i].id;
		}
	}

	std::vector<ParsedElement> parsedElements(differentIds);

	int i = -1;
	curId = -1;
	for(int j=0; j<elements.size(); j++){
		if(elements[j].id != curId){
			i+=1;
			curId = elements[j].id;
		}
		parsedElements[i].id = curId;
		parsedElements[i].elements.push_back(elements[j].ToElement());
	}
	return parsedElements;
}

// Function to build a balanced BST from a sorted vector of ParsedElements
Dict* SD::BuildBalancedTree(const std::vector<ParsedElement>& elements, int start, int end) {
    if (start > end) return nullptr;

    int mid = start + (end - start) / 2;
    Dict* root = new Dict(elements[mid]);

    root->left = BuildBalancedTree(elements, start, mid - 1);
    root->right = BuildBalancedTree(elements, mid + 1, end);

    return root;
}

// In-order traversal (for testing)
void SD::InorderTraversal(Dict* root) {
    if (!root) return;
    InorderTraversal(root->left);
    std::cout << root->id << " ";
    InorderTraversal(root->right);
}

Dict* SD::CreateBTree(std::string data){
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
		um.insert({elementVec[i].key, elementVec[i].value});
	}
	return um;
}


Element* SD::Find(Dict* root, std::string key){
	int keyId = SO::Value(key);

	while (root){
		if(keyId < root->id){
			root = root->left;
		}
		else if(keyId > root->id){
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
	return nullptr;
}
Element SD::Find(std::vector<Element> root, std::string key){
	for(int i=0; i<root.size(); i++){
		if(root[i].key == key){
			return root[i];
		}
	}

	return {"",""};
}

std::string SD::Find(std::unordered_map<std::string, std::string> um, std::string key){
	auto it = um.find(key);
	if(it!=um.end()){
		return it->second;
	}
	return nullptr;
}


