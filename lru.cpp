#include <iostream>
#include <unordered_map>
#include <map>
using namespace std;
class SinglyNode
{
public:
    int value;
    SinglyNode *next;
    SinglyNode(int value)
    {
        this->value = value;
        this->next = NULL;
    }
};
class SinglyLinkedList
{
public:
    SinglyNode *head = NULL;
    SinglyNode *tail = NULL;
    SinglyLinkedList()
    {
    }
    void insert_at_head(int value)
    {
        SinglyNode *newNode = new SinglyNode(value);
        if (this->head == NULL)
        {
            head = newNode;
            tail = head;
        }
        else
        {
            this->head->next = newNode;
            head = newNode;
        }
    }
    void iterate()
    {
        SinglyNode *temp = this->tail;
        while (temp != NULL)
        {
            cout << temp->value << " ";
            temp = temp->next;
        }
        free(temp);
    }
    void delete_node(SinglyNode *&node_to_delete, SinglyNode *&prev_node)
    {
        prev_node->next = node_to_delete->next;
        free(node_to_delete);
    }
};
class Node
{
public:
    int val;
    int key;
    Node *prev;
    Node *next;
    Node(int key, int val)
    {
        this->key = key;
        this->val = val;
        this->prev = NULL;
        this->next = NULL;
    }
};
class LRUCache
{
public:
    unordered_map<int, Node *> m;
    int capacity;
    int curr_len;
    // all the nodes will remain in between the
    // tail and head, the last one i.e. at the head will be the lru node
    // and the latest one i.e. at the tail will be the mru node
    Node *head;
    Node *tail;
    LRUCache(int capacity)
    {
        this->capacity = capacity;
        this->curr_len = 0;
        this->head = new Node(-1, -1);
        this->tail = new Node(-1, -1);
        this->head->next = tail;
        this->tail->prev = head;
    }
    int get(int key)
    {
        if (m.count(key) == true)
        {
            int prev_val = m[key]->val;
            m[key]->prev->next = m[key]->next;
            m[key]->next->prev = m[key]->prev;
            Node *newnode = new Node(key, prev_val);
            newnode->prev = tail->prev;
            tail->prev->next = newnode;
            tail->prev = newnode;
            newnode->next = tail;
            m[key] = newnode;
            // traverse();
            return prev_val;
        }
        return -1;
    }
    void traverse()
    {
        Node *temp = head;
        while (temp != NULL)
        {
            cout << temp->key << " " << temp->val << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    void put(int key, int value)
    {
        if (m.count(key) == true)
        {
            m[key]->prev->next = m[key]->next;
            m[key]->next->prev = m[key]->prev;
            Node *newnode = new Node(key, value);
            newnode->prev = tail->prev;
            tail->prev->next = newnode;
            tail->prev = newnode;
            newnode->next = tail;
            m[key] = newnode;

            return;
        }
        else
        {
            if (curr_len < capacity)
            {
                Node *newnode = new Node(key, value);
                newnode->prev = tail->prev;
                tail->prev->next = newnode;
                tail->prev = newnode;
                newnode->next = tail;
                m[key] = newnode;
                curr_len++;
            }
            else if (curr_len >= capacity)
            {
                int evict_key = head->next->key;
                head->next = m[evict_key]->next;
                m[evict_key]->next->prev = head;
                m.erase(m.find(evict_key));
                Node *newnode = new Node(key, value);
                newnode->prev = tail->prev;
                tail->prev->next = newnode;
                tail->prev = newnode;
                newnode->next = tail;
                m[key] = newnode;
            }
        }
    }
};

int main()
{
    LRUCache *cache = new LRUCache(50);
    SinglyLinkedList *new_list = new SinglyLinkedList();
    new_list->insert_at_head(1);
    new_list->insert_at_head(2);
    new_list->insert_at_head(3);
    new_list->insert_at_head(4);
    new_list->iterate();
}