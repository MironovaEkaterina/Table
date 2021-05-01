#pragma once
#include <iostream>
#include <vector>
#include <iterator>
#include <list>
const size_t P = 99971;
typedef unsigned int key_type;

template<class T>
struct Pair {
	key_type key;
	T data;
	Pair(key_type k, T elem) {
		key = k;
		data = elem;
	}
};

template<class T>
class TableInterface {
public:
	virtual bool insert(key_type k, const T& elem) = 0;
	virtual bool erase(key_type k) = 0;
	//virtual int find_key(key_type k) = 0;
	virtual Pair<T> find(key_type k) = 0;
	virtual size_t GetSize() = 0;
	virtual bool IsEmpty() = 0;
	virtual void clear() = 0;
};

template<class T>
class TableByArray : public TableInterface<T> {
protected:
	std::vector<Pair<T>> storage;
	size_t size;
public:
	size_t GetSize() override {
		return size;
	}
	bool IsEmpty() override {
		return (size == 0);
	}
	void clear() override {
		for (size_t i = 0; i < size; i++)
			storage.pop_back();
		size = 0;
	}
};

template<class T>
class UnsortedTable : public TableByArray<T> {
	using TableByArray<T>::storage;
	using TableByArray<T>::size;
public:
	UnsortedTable() {
		size = 0;
	}

	UnsortedTable(UnsortedTable& t) {
		storage = t.storage;
		size = t.size;
	}

	int find_key(key_type k){
		if (size == 0) return -1;
		for (size_t i = 0; i < size; i++)
			if (storage[i].key == k) return i;
		return -1;
	}

	bool insert(key_type k, const T& elem) override {
		if (find_key(k) != -1) throw "The element with this key already exists";
		storage.push_back(Pair<T>(k, elem));
		size++;
		return 1;
	}

	bool erase(key_type k) override {
		int index = find_key(k);
		if (index == -1) throw "The element with this key does not exist";
		storage[index] = storage[size - 1];
		storage.pop_back();
		size--;
		return 1;
	}

	Pair<T> find(key_type k) override {
		int index = find_key(k);
		if (index == -1) throw "The element with this key does not exist";
		else
			return storage[index];
	}


};

template<class T>
class SortedTable : public TableByArray<T> {
	using TableByArray<T>::storage;
	using TableByArray<T>::size;
public:
	SortedTable() {
		this->storage = {};
		this->size = 0;
	}

	SortedTable(SortedTable& t) {
		this->storage = t.storage;
		this->size = t.size;
	}

	int find_key(key_type k){
		if (size == 0) return -1;
		int mid;
 		int st = 0, fn = size - 1, s = -1;
		while (st < fn) {
			mid = (st + fn) / 2;
			if (k == storage[mid].key) return mid;
			if (k < storage[mid].key)
				fn = mid - 1;
			else
				st = mid + 1;
		}
		if (k == storage[st].key)
			return st;
		if (st+1<size)
			if (k == storage[st+1].key)
				s = st + 1;
		return s;
	}

	bool insert(key_type k, const T& elem) override {
		if (size == 0) {
			storage.push_back(Pair<T>(k, elem));
			size++;
			return 1;
		}
		int mid;
		int st = 0, fn = size - 1;
		while (st < fn) {
			mid = (st + fn) / 2;
			if (k == storage[mid].key) throw "The element with this key already exists";
			if (k < storage[mid].key)
				fn = mid - 1;
			else
				st = mid + 1;
		}
		if (k == storage[st].key) throw "The element with this key already exists";
		if (fn >= 0) if (k == storage[fn].key) throw "The element with this key already exists";
		if (k > storage[st].key)
			storage.insert(storage.begin() + st + 1, Pair<T>(k, elem));
		else
			storage.insert(storage.begin() + st, Pair<T>(k, elem));
		size++;
		return 1;
	}

	bool erase(key_type k) override {
		int index = find_key(k);
		if (index == -1) throw "The element with this key does not exist";
		storage.erase(storage.begin() + index);
		size--;
		return 1;
	}

	Pair<T> find(key_type k) override {
		int index = find_key(k);
		if (index == -1) throw "The element with this key does not exist";
		else
			return storage[index];
	}
};

template<class T>
class HashTable: public TableInterface<T> {
private:
	size_t HashFunc(size_t x) {
		return(((a * x + b) % P) % max_size);
	}
public:
	std::vector<std::list<Pair<T>>> storage;
	size_t size,max_size;
	size_t a, b;
	HashTable(int n) {
		a = rand() % P;
		b = rand() % P;
		size = 0;
		max_size = n*n;
		storage.resize(max_size);
	}
	HashTable(HashTable& ht) {
		storage = ht.storage;
		size = ht.size;
		max_size = ht.max_size;
		a = ht.a;
		b = ht.b;
	}
	bool insert(key_type k, const T& elem) override{
		size_t i = HashFunc(k);
		for (auto it = storage[i].begin(); it != storage[i].end(); ++it)
			if (it->key == k) throw "The element with this key already exists";
		storage[i].push_back(Pair<T>(k, elem));
		size++;
		return 1;
	}

	bool erase(key_type k) override {
		size_t i = HashFunc(k);
		int f = 0;
		for (auto it = storage[i].begin(); it != storage[i].end(); ++it) {
			if (it->key == k) { 
				storage[i].erase(it);
				size--;
				f = 1;
				break;
			}
		}
		if (f==0) throw "The element with this key does not exists";
		return 1;
	}

	Pair<T> find(key_type k) override{
		size_t i = HashFunc(k);
		int f = 0;
		for (auto it = storage[i].begin(); it != storage[i].end(); ++it) {
			if (it->key == k)
				f = 1;
				return Pair<T>(k, it->data);
		}
		if (f==0) throw "The element with this key does not exists";
	}

	size_t GetSize()  override {
		return size;
	}
	bool IsEmpty() override {
		return (size == 0);
	}
	void clear() override {
		storage.clear();
		size = 0;
	}
};