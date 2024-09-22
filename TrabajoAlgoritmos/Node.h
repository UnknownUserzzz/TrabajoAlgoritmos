#pragma once
template <typename T>
class Node {
public:
    T data;
    Node* next;
    
    Node() {
		this->data = 0;
        this->next = nullptr;
	}

    Node(T data) {
        this->data = data;
        this->next = nullptr;
    }
};