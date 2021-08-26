#include<iostream>
#include<stdlib.h>

template <typename E>
class NodeList {
		
	private:
		struct Node {
			E 		elem;
			Node* 	prev;
			Node* 	next;
		};
		
	public:
		class Iterator {
			public: 
				E& 				operator*();
				bool 			operator==(const Iterator& p) const;
				bool 			operator!=(const Iterator& p) const;
				Iterator& 		operator++();
				Iterator& 		operator--();
				friend class	NodeList;
		
			private:
				Node* v;
				Iterator(Node* u);
		};
		
	public:
		NodeList(); 												// default constructor
		int 		size() 	const; 									// list size
		bool 		empty() const; 									// is the list empty?
		Iterator 	begin() const; 									// beginning position
		Iterator 	end() 	const; 									// (just beyond) last position
		void		insertFront(const E& e); 						// insert at front
		void 		insertBack(const E& e); 						// insert at rear
		void 		insert(const Iterator& p, const E& e); 			// insert e before p
		void 		eraseFront(); 									// remove first
		void		eraseBack(); 									// remove last
		void 		erase(const Iterator& p); 
	
	private:
		int n;
		Node* header;
		Node* trailer;
};


template <typename E>
NodeList<E>::Iterator::Iterator(Node* u) {
		v = u;
}

template <typename E>	
E& NodeList<E>::Iterator::operator*() {
	return v -> elem;
}

template <typename E>
bool NodeList<E>::Iterator::operator==(const Iterator& p) const {
	return (v == p.v);
}

template <typename E>
bool NodeList<E>::Iterator::operator!=(const Iterator& p) const {
	return (v != p.v);
}

template <typename E>
typename NodeList<E>::Iterator& NodeList<E>::Iterator::operator++() {
	v = v -> next;
	return *this;
}

template <typename E>
typename NodeList<E>::Iterator& NodeList<E>::Iterator::operator--() {
	v = v -> prev;
	return *this;
}

template <typename E>
NodeList<E>::NodeList() {
	n = 0;
	header = new Node;
	trailer = new Node;
	header -> next = trailer;
	trailer -> prev = header;
}

template <typename E>
int NodeList<E>::size() const {
	return n;
}

template <typename E>
bool NodeList<E>::empty() const {
	return (n == 0);
}

template <typename E>
typename NodeList<E>::Iterator NodeList<E>::begin() const {
	return Iterator(header -> next);
};

template <typename E>
typename NodeList<E>::Iterator NodeList<E>::end() const {
	return Iterator(trailer);
}

template <typename E>
void NodeList<E>::insert(const typename NodeList<E>::Iterator& p, const E& e) {
	Node* w = p.v;
	Node* u = w -> prev;
	Node* t = new Node;
	t -> elem = e;
	t -> next = w; w -> prev = t;
	t -> prev = u; u -> next = t;
	n++;
}

template <typename E>
void NodeList<E>::insertFront(const E& e) {
	insert(begin(), e);
}

template <typename E>
void NodeList<E>::insertBack(const E& e) {
	insert(end(), e);
}

template <typename E>
void NodeList<E>::erase(const Iterator& p) {
	Node* v = p.v;
	Node* w = v -> next;
	Node* u = v -> prev;
	u -> next = w;
	w -> prev = u;
	delete v;
	n--;
}

template <typename E>
void NodeList<E>::eraseFront() {
	erase(begin());
}

template <typename E>
void NodeList<E>::eraseBack() {
	erase(--end());
}


int main() {
	std::string symbol = "^";
	std::string line;
	
	NodeList<std::string> List;

	List.insertFront(symbol);
	
	NodeList<std::string>::Iterator p = List.begin();
	NodeList<std::string>::Iterator q = List.begin();
	
	std::cout << *p << std::endl;
	
	while (std::getline(std::cin, line)) {
	
		if(line.size() > 7) {
		
			int pos = line.find(" ");
			std::string command = line.substr(0, 6);
			std::string text = line.substr(pos + 1, line.size());
			
			List.insert(q, text);
			
			for(p = List.begin(); p != List.end(); ++p) {
				std::cout << *p;
			}
			
			std::cout << std::endl;
		}
		
		else if(line == "left") {
			if(q == List.begin()) {
				for(p = List.begin(); p != List.end(); ++p) {
					std::cout << *p;
				}
				std::cout << std::endl;
			}
			
			else {
				NodeList<std::string>::Iterator t = --q;
				List.insert(q, symbol);
				--q;
				++t;
				List.erase(t);
				for(p = List.begin(); p != List.end(); ++p) {
					std::cout << *p;
				}
				std::cout << std::endl;
			}
		}
		
		else if(line == "right") {
		
			if(List.size() == 1 || q == (--List.end())) {
			
				for(p = List.begin(); p != List.end(); ++p) {
					std::cout << *p;
				}
					
				std::cout << std::endl;
			}
			
			else {
			
				++q;
				
				NodeList<std::string>::Iterator t = ++q;
				List.insert(q, symbol);
				
				--q;
				--t;
				--t;
				--t;
				
				List.erase(t);
				
				for(p = List.begin(); p != List.end(); ++p) {
					std::cout << *p;
				}
				
				std::cout << std::endl;
			}	
		}
		
		else if(line == "rdelete") {
		
			if((List.size() == 1) || (q == (--List.end()))) {
			
				for(p = List.begin(); p != List.end(); ++p) {
					std::cout << *p;
				}
				
				std::cout << std::endl;
			}
				
			else {
			
				++q;
				List.erase(q);
				--q;
				
				for(p = List.begin(); p != List.end(); ++p) {
						std::cout << *p;
				}
				
				std::cout << std::endl;
			}
		}
		
		else if(line == "ldelete") {
		
			if((List.size() == 1) || (q == List.begin())) {
			
				for(p = List.begin(); p != List.end(); ++p) {
						std::cout << *p;
				}
				
				std::cout << std::endl;
			}
			
			else {
				--q;
				List.erase(q);
				++q;
				
				for(p = List.begin(); p != List.end(); ++p) {
						std::cout << *p;
				}
				
				std::cout << std::endl;
			}
		}
	}		
}
