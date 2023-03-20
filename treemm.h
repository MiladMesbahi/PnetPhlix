#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <list>
#include <iostream>

template <typename KeyType, typename ValueType>
class TreeMultimap
{
public:
    // Iterator class for the TreeMultimap
    class Iterator
    {
    public:
        // Default constructor for an empty Iterator
        Iterator()
        {
            a = m_list.begin();
        }
        // Constructor to initialize Iterator with a list
        Iterator(std::list<ValueType> newList)
        {
            m_list = newList;
            a = m_list.begin();
            
        }
        // Get the current value from the iterator
        ValueType& get_value() const
        {
            return *a;
        }
        // Check if the iterator is valid (not at the end of the list)
        bool is_valid() const
        {
            return !(a == m_list.end());
        }
        // Advance the iterator to the next value
        void advance()
        {
            a++;
        }
        
    private:
        typename std::list<ValueType>::iterator a;
        std::list<ValueType> m_list;
    };
    // Default constructor for TreeMultimap
    TreeMultimap()
    {
        center = nullptr;
    }
    // Destructor for TreeMultimap
    ~TreeMultimap()
    {
        deleteTree(center);
    }
    // Insert a key-value pair into the TreeMultimap
    void insert(const KeyType& key, const ValueType& value)
    {
        insertInOrder(center, key, value);
    }
    // Find and return an iterator for the given key
    Iterator find(const KeyType& key) const
    {
        return findKey(center, key);
    }
    
private:
    // Node structure for the binary search tree
    struct Node
    {
        Node* left; // Pointer to left child node
        Node* right; // Pointer to right child node
        std::list<ValueType> values; // List of values for the same key
        KeyType key;
    };
    
    Node* center; // Root node of the tree
    
    // Helper function to delete the tree using post-order traversal
    void deleteTree(Node* p)
    {
        if (p == nullptr)
            return;
        deleteTree(p->left);
        deleteTree(p->right);
        delete p;
    }
    
    // Helper function to insert a key-value pair into the tree
    void insertInOrder(Node* p, KeyType key, ValueType value)
    {
        if (p == nullptr){
            // If the tree is empty, create a new node as the root
            Node* newp = new Node;
            center = newp;
            center->key = key;
            center->values.push_back(value);
            center->left = nullptr;
            center->right = nullptr;
            return;
        }
        if (key < p->key){
            if (p->left == nullptr){
                // If the left child is null, insert a new node as the left child
                Node* newp = new Node;
                p->left = newp;
                newp->key = key;
                newp->values.push_back(value);
                newp->left = nullptr;
                newp->right = nullptr;
                return;
            }
            // Recursively insert the key-value pair in the left subtree
            insertInOrder(p->left, key, value);
        }
        if (key > p->key){
            if (p->right == nullptr){
                // If the right child is null, insert a new node as the right child
                Node* newp = new Node;
                p->right = newp;
                newp->key = key;
                newp->values.push_back(value);
                newp->left = nullptr;
                newp->right = nullptr;
                return;
            }
            // Recursively insert the key-value pair in the right subtree
            insertInOrder(p->right, key, value);
        }
        if (key == p->key)
            // If the key already exists in the tree, add the value to the existing key's values list
            p->values.push_back(value);
    }
    
    // Helper function to find a key in the tree and return an iterator for the corresponding value list
    Iterator findKey(Node* p, KeyType key) const{
        if (p == nullptr)
            // If the tree is empty or the key is not found, return an invalid iterator
            return Iterator();
        if (p->key == key)
        {
            // If the key is found, create an iterator for the values list
            Iterator a = Iterator(p->values);
            return a;
        }
        if (p->key > key)
            // If the current key is greater than the search key, search the left subtree
            return findKey(p->left, key);
        if (p->key < key)
            // If the current key is less than the search key, search the right subtree
            return findKey(p->right, key);
        
        // If none of the conditions match, return an invalid iterator (should not be reached)
        return Iterator();
    }
};
#endif // TREEMULTIMAP_INCLUDED

//DONE
