#pragma once
#include <string>
#include <vector>

struct HashNode
{
	std::string key;
	int value;
	HashNode* next;

	HashNode(std::string k,int v):key(k),value(v),next(nullptr){}
};

class MyHashTable
{
private:
	std::vector<HashNode*> m_buckets;
	size_t m_size;
	size_t m_capacity;

	size_t hashFunction(const std::string& key) const {
		size_t hash = 0;
		for (char c : key) {
			hash = hash * 31 + c;
		}
		return hash % m_capacity;
	}

public:
	MyHashTable(size_t capacity = 16):m_size(0),m_capacity(capacity) {
		m_buckets.assign(m_capacity, nullptr);
	}

	~MyHashTable() {
		for (int i = 0; i < m_capacity; ++i) {
			HashNode* curr = m_buckets[i];
			while (curr != nullptr) {
				HashNode* temp = curr->next;
				delete curr;
				curr = temp;
			}
		}
	}

	void put(const std::string& key, int value) {
		size_t hashCode = hashFunction(key);
		HashNode* target = m_buckets[hashCode];
		while (target) {
			if (target->key == key) {
				target->value = value;
				return;
			}
			target = target->next;
		}
		HashNode* newNode = new HashNode(key, value);
		newNode->next = m_buckets[hashCode];
		m_buckets[hashCode] = newNode;
		m_size++;
	}

	int get(const std::string& key) const {
		size_t hashCode = hashFunction(key);
		HashNode* target = m_buckets[hashCode];
		while (target) {
			if (target->key == key) return target->value;
			target = target->next;
		}
		return -1;
	}

	void remove(const std::string& key) {
		size_t hashCode = hashFunction(key);
		HashNode* target = m_buckets[hashCode];
		if (target == nullptr) {
			return;
		}
		if (target->key == key) {
			m_buckets[hashCode] = target->next;
			delete target;
			m_size--;
		}
		else {
			HashNode* curr = target->next;
			HashNode* prev = target;
			while (curr) {
				if (curr->key == key) {
					prev->next = curr->next;
					delete curr;
					m_size--;
					return;
				}
				curr = curr->next;
				prev = prev->next;
			}
		}
	}
};