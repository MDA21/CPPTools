#pragma once
#include <unordered_map>

struct DLinkedNode
{
	int key;
	int value;
	DLinkedNode* prev;
	DLinkedNode* next;
	DLinkedNode() :key(0), value(0), prev(nullptr), next(nullptr) {}
	DLinkedNode(int _key,int _value):key(_key),value(_value),prev(nullptr),next(nullptr){}
};

class MyLRUCache
{
private:
	int m_capacity;
	int m_size;
	DLinkedNode* dummy_head;
	DLinkedNode* dummy_tail;
	std::unordered_map<int, DLinkedNode*> m_map;

	void addNodeToHead(DLinkedNode* node) {
		node->next = dummy_head->next;
		dummy_head->next->prev = node;
		dummy_head->next = node;
		node->prev = dummy_head;
	}

	void removeNode(DLinkedNode* node) {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}

	void moveToHead(DLinkedNode* node) {
		removeNode(node);
		addNodeToHead(node);
	}

	DLinkedNode* removeTail() {
		DLinkedNode* temp = dummy_tail->prev;
		removeNode(temp);
		return temp;
	}

public:
	MyLRUCache(int capacity) :m_capacity(capacity),m_size(0) {
		dummy_head = new DLinkedNode();
		dummy_tail = new DLinkedNode();
		dummy_head->next = dummy_tail;
		dummy_tail->prev = dummy_head;
	}
	~MyLRUCache() {
		DLinkedNode* curr = dummy_head;
		while (curr) {
			DLinkedNode* next_node = curr->next;
			delete curr;
			curr = next_node;
		}
	}

	int get(int key) {
		if (!m_map.contains(key)) return -1;
		DLinkedNode* foundNode = m_map[key];
		moveToHead(foundNode);
		return foundNode->value;
	}

	void put(int key, int value) {
		if (!m_map.contains(key)) {
			DLinkedNode* new_node = new DLinkedNode(key, value);
			m_map[key] = new_node;
			addNodeToHead(new_node);

			if (++m_size > m_capacity) {
				DLinkedNode* tailNode = removeTail();
				m_map.erase(tailNode->key);
				delete tailNode;
				m_size--;
			}
		}
		else {
			DLinkedNode* foundNode = m_map[key];
			foundNode->value = value;
			moveToHead(foundNode);
		}
	}
};