#ifndef _LRH_H_
#define _LRU_H_
 
#include <iostream>
#include <unordered_map> //C++11
#include <vector>

using namespace std;

template <typename K, typename V>
struct Node{
    K key;
    V value;
    Node *prev, *next;
};

template <typename K, typename V>
class LRUCache{
public:
    LRUCache(size_t size);
    ~LRUCache();
    void Put(K key, V value);
    V Get(K key);
    int getCount() { return count; } // cache miss count
private:
    void attach(Node<K,V> *node);
    void detach(Node<K,V> *node);
    int count;
    unordered_map<K, Node<K,V>* > hashmap_; //store cache nodes
    vector<Node<K,V>* > free_entries_; //to check the cache full or not
    Node<K,V> *head_, *tail_;
    Node<K,V> *entries_; //the first address of lru
};

template <typename K, typename V>
LRUCache::LRUCache(size_t size){
    count = 0;
    entries_ = new Node<K,V>[size];
    for (size_t i=0; i<size; ++i) {
        free_entries_.push_back(entries_+i);
    }
    head_ = new Node(K,V);
    tail_ = new Node(K,V);
    head_->prev = NULL;
    head_->next = tail_;
    tail_->prev = head_;
    tail_->next = NULL;
}

template <typename K, typename V>
LRUCache::~LRUCache(){
    delete head_;
    delete tail_;
    delete [] entries_;
}

template <typename K, typename V>
void LRUCache::Put(K key, V value){
    Node<K,V> *node = hashmap_[key];
    if (NULL != node) {
        detach(node);
        node->key = key;
        node->value = value;
        attach(node);
    } else {
        if (free_entries_.empty()) {
            node = tail_->prev;
            detach(node);
            hashmap_.erase(node->key);
        } else {
            node = free_entries_.back();
            free_entries_.pop_back();
        }
        node->key = key;
        node->value = value;
        hashmap_[key] = node;
        attach(node);
    }
}

template <typename K, typename V>
V LRUCache::Get(K key) {
    Node<K,V> *node = hashmap_[key];
    if (NULL != node) {
        detach(node);
        attach(node);
        return node->value;
    } else {
        ++count;
        //Put(key, V());
        return V();
    }
}

template <typename K, typename V>
void LRUCache::attach(Node<K,V> *node) {
    node->next = head_->next;
    head_->next = node;
    node->next->prev = node;
    node->prev = head_;
}

template <typename K, typename V>
void LRUCache::detach(Node<K,V> *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

#endif
