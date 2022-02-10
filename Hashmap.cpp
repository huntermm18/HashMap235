#include "Hashmap.h"
#include <vector>


Hashmap::Hashmap() {
	mapSize = 0;
	for(int i = 0; i < BUCKETS; i++) {
		buckets[i] = NULL;
	}
}

Hashmap::~Hashmap() {
	clear();
}

void Hashmap::insert(string key, int value) {

	int &valptr = at(key);
	valptr = value;
}

bool Hashmap::contains(string key) const {
	int bucketNumber = hash(key);
	Node* head = buckets[bucketNumber];

	while(head != NULL) {
		if (head->key == key) { // if found
			return true;
		}
		head = head->next;
	
	}
	return false;

}

int Hashmap::get(string key) const {
	int bucketNumber = hash(key);
	Node* head = buckets[bucketNumber];

	while(head != NULL) {
		if (head->key == key) { // if found
			return head->value;
		}
		head = head->next;

	}
	throw invalid_argument(""); 

}

int& Hashmap::operator [](string key) 
{
	return at(key);
}


bool Hashmap::remove(string key) {
	unsigned int bucket = hash(key);
	Node *current = buckets[bucket];

	while(current != NULL && (current->key != key)) {
		current = current->next;
	}

	if(current == NULL) {
		return false;
	}

	if(current->next != NULL) {
			current->next->prev = current->prev;

	}

	if(current->prev == NULL) {
			buckets[bucket] = current->next;

	}
	else {
		current->prev->next = current->next;
	}
	
	delete current;
	mapSize--;
	return true;
	
}

bool Hashmap::deleteLast(int bucketNum) {
	Node* current = buckets[bucketNum];

	if (current == NULL) {
		return false;

	}
	
	while (current != NULL) {
		current = current->next;

	}
	
	delete current;
	return true;
}

void Hashmap::clear() {

// 	for (int i = 0; i < BUCKETS; ++i) {
// 		Node* current = buckets[i];
// 		Node* temp = current;
		
// 		while (current != NULL) {
// //			cout << "value: " << current->key << endl;
// 			if(current->next !=NULL) {
// 				current->next->prev = NULL;
// 			}
// 			current = current->next;
// 			delete temp;
// 			mapSize--;
// 			temp = current;
// 		}
// 	}


	for(int i = 0; i < BUCKETS; ++i) {
		Node* current = buckets[i];
		while (current != NULL) {
			if(current->next !=NULL) {
				current->next->prev = NULL;
			}
			buckets[i] = current->next;
			delete current;
			mapSize--;
			current = buckets[i];
		}
		
	}


}

void Hashmap::printString() {
	stringstream ss;
	for (int i = 0; i < BUCKETS; i++) {
		Node *head = buckets[i];
		if(head == NULL) { // The hash bucket was empty
			ss << "[" << i << "]" << endl;
		} 
		else {
			//There was something in this hash bucket
			ss << "[" << i << "]";
			while(head != NULL) {
				ss << head->key << " => " << head->value;
				if(head->next != NULL) {
					ss << ", ";
				}
				head = head->next;
			}
			ss << endl;
		}
	}
	 cout << ss.str();
}


string Hashmap::toString() const {
	stringstream ss;
//	Node* current; 
	for (int i = 0; i < BUCKETS; i++) {
		Node *head = buckets[i];
		if(head == NULL) { // The hash bucket was empty
			ss << "[" << i << "]" << endl;
		} 
		else {
			//There was something in this hash bucket
			ss << "[" << i << "]";
			while(head != NULL) {
				ss << head->key << " => " << head->value;
				if(head->next != NULL) {
					ss << ", ";
				}
				head = head->next;
			}
			ss << endl;
		}
	}
	return ss.str();
}

int Hashmap::size() const {
	return mapSize;
}

string Hashmap::toSortedString() const {
	stringstream ss;
	priority_queue<Node*, vector<Node*>, NodeCompare> nodeHeap;
	for(int i = 0; i < BUCKETS; i++) {
		Node *current = buckets[i];
		while(current != NULL)
		{
			nodeHeap.push(current);
			current = current->next;
		}
	}
	while(!nodeHeap.empty())
	{
		Node* top = nodeHeap.top();
		ss << top->key << " => " << top->value << endl;
		nodeHeap.pop(); // Pop it off
	}
	return ss.str();
}

unsigned int Hashmap::hash(string key) const {
	unsigned int hashCode = 0;
	for(int i = 0; i <key.length(); i++) {
		hashCode = hashCode * 31 + key.at(i);
	}
	return hashCode % BUCKETS;
}

int& Hashmap::at(string name) {
		int hashval = hash(name);
		Node *ptr = buckets[hashval];
		while(ptr != NULL) {
			// cout <<"comparing "<<name<<" first "<<ptr->context.first<<endl;
			if(name == ptr->key) { // We found it
				break;
			} else {
			  //cout << "ptr"<< ptr<<"next "<< ptr->next<<endl;
			  ptr = ptr->next;
			}
		}
		if(ptr == NULL) { // We need to create a new node, put it on the front of the list
		  mapSize++; 
			ptr = new Node;
			ptr->next = NULL;
			ptr->prev = NULL;


			ptr->next = buckets[hashval];
			buckets[hashval] = ptr;
			ptr->key = name;
			if(ptr->next) {//update: make sure next node in list has right prev
				ptr->next->prev = ptr;
			}
			

		}
		//cout << "return "<< static_cast<void*>(&(ptr->context.second))<<endl;
		return(ptr->value);
	}

	void Hashmap::addToVect(Node* toAdd) {}