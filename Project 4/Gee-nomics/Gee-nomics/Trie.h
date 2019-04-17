#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>

template<typename ValueType>
class Trie
{
public:
    Trie()
    {
        m_root = nullptr;
        m_root = new Node("");
    }
    ~Trie()
    {
        resetHelper(m_root);
    }
    
    //resets the Trie by deleting every Node except the root.
    inline void reset()
    {
        resetHelper(m_root);
        m_root = nullptr;
        m_root = new Node("");
    }
    
    //inserts a value into the trie, along with the associated value
    inline void insert(const std::string& key, const ValueType& value)
    {
        std::string keyCopy = key;
        ins(m_root->m_children[choosePointerToFollow(key[0])], keyCopy, value);
    }
    
    //if exactMatchOnly is true, search for an Exact Match of key in the Trie
    //if exactMatchOnly is false, search for exact matches of key in the trie as well as
    //strings that only have one differing character in trie
    std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const
    {
        std::vector<ValueType> v;
        std::string keyCopy = key;
        findHelp(m_root->m_children[choosePointerToFollow(key[0])], keyCopy, exactMatchOnly, v);
        return v;
    }

      // C++11 syntax for preventing copying and assignment
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;

private:
    struct Node
    {
        Node(std::string label)
        {
            m_label = label;
            
            for (int x = 0; x < 127; x++)
            {
                m_children[x]=nullptr;
            }
        }
        
        Node* m_children[127]; //there are 127 UNICODE characters, thus each node could have 127 possible children
        std::vector<ValueType> m_items;
        std::string m_label;
    };
    Node* m_root;
    
    //a helper function that recursively checks if there are matches for key in the trie
    void findHelp(Node* n, std::string key, bool exactMatchOnly, std::vector<ValueType>& v) const
    {
        if (n == nullptr)
            return;
        if (key.size() == 0)
            return;
        //if the first character matches, continue moving down the tree
        if (key.substr(0,1) == n->m_label)
        {
            //if key size is one, we have found the word
            if (key.size() == 1)
            {
                for(int x = 0; x < n->m_items.size(); x++)
                {
                    v.push_back(n->m_items[x]);
                }
                return;
            }
            key = key.substr(1);
            for (int x = 0; x < 127; x++)
            {
                findHelp(n->m_children[x], key, exactMatchOnly, v);
            }
        }
        //else we have made a mistake, and now continue down with exactMatchOnly set to true
        else if (exactMatchOnly == false)
        {
            if (key.size() == 1)
            {
                for(int x = 0; x < n->m_items.size(); x++)
                {
                    v.push_back(n->m_items[x]);
                }
                return;
            }
            exactMatchOnly = true;
            key = key.substr(1);
            for (int x = 0; x < 127; x++)
            {
                findHelp(n->m_children[x], key, exactMatchOnly, v);
            }
        }
        else
        {
            return;
        }
    }
    
    //recursive function that deletes all nodes in the tree
    void resetHelper(Node* ptr)
    {
        if (ptr == nullptr)
            return;
        for (int x = 0; x < 127; x++)
        {
            resetHelper(ptr->m_children[x]);
        }
        delete ptr;
    }
    
    //recursive function that inserts a value into the Trie, one letter at a time
    void ins(Node*& n, std::string& key, const ValueType& value)
    {
        if (key.size() == 0)
        {
            return;
        }
        if (n == nullptr)
        {
            n = new Node(key.substr(0,1));
        }
        if (key.size() == 1)
        {
            n->m_items.push_back(value);
            return;
        }
        key = key.substr(1); // move past the current letter
        ins(n->m_children[choosePointerToFollow(key[0])], key, value);
    }
    
    //converts the character to an integer
    int choosePointerToFollow(char c) const
    {
        int val = c;
        return val;
    }
    
};

#endif // TRIE_INCLUDED
