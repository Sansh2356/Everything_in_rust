#include <iostream>
using namespace std;
class Node
{
public:
    int value;
    Node *prev;
    Node *next;
    Node(int val)
    {
        this->value = val;
        this->next = NULL;
        this->prev = NULL;
    }
};
class DoublyLinkedList
{
public:
    Node *head = NULL;
    Node *tail = NULL;
    int len;
    DoublyLinkedList()
    {
        this->len = 0;
    }
    void insert_at_head(int value)
    {
        Node *newNode = new Node(value);
        if (head == NULL)
        {
            head = newNode;
            tail = head;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        len++;
    }
    void insert_at_tail(int value)
    {
        Node *newNode = new Node(value);
        if (tail == NULL)
        {
            tail = newNode;
            head = tail;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        len++;
    }
    void insert_at_position(int pos, int value)
    {
        if (pos > len || pos < 1)
        {
            cout << "Invalid position for deletion";
            return;
        }
        if (pos == 1)
            this->insert_at_head(value);
        else if (pos == len)
            this->insert_at_tail(value);
        else
        {
            Node *newNode = new Node(value);
            Node *temp = head;
            while (pos != 1)
            {
                temp = temp->next;
                pos--;
            }
            temp->prev->next = newNode;
            newNode->prev = temp->prev;
            newNode->next = temp;
        }
        len++;
    }
    void delete_at_position(int pos)
    {
        if (head == NULL)
        {
            cout << "Currently linked list is empty no values to be deleted" << endl;
            return;
        }
        if (pos > len || pos < 1)
        {
            cout << "Invalid position for deletion";
            return;
        }
        if (pos == 1)
        {
            head->next->prev = NULL;
            head = head->next;
        }
        else if (pos == len)
        {
            tail->prev->next = NULL;
            tail = tail->prev;
        }
        else
        {
            Node *temp = head;
            while (pos != 1)
            {
                temp = temp->next;
                pos--;
            }
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }
        len--;
    }
    void iterate()
    {
        Node *temp = head;
        while (temp != NULL)
        {
            cout << temp->value << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    ~DoublyLinkedList()
    {
        cout << "Destructor called" << endl;
        delete head;
        delete tail;
    }
};
int main()
{
    DoublyLinkedList *newList = new DoublyLinkedList();
    newList->insert_at_head(1);
    newList->insert_at_head(2);
    newList->insert_at_head(3);
    newList->insert_at_tail(4);
    newList->insert_at_tail(5);
    newList->insert_at_tail(6);
    newList->insert_at_head(7);
    newList->insert_at_position(2, 20);
    newList->iterate();
    newList->delete_at_position(1);
    newList->delete_at_position(2);
    newList->iterate();
    newList->insert_at_position(1, 20);
    newList->insert_at_position(3, 20);
    newList->iterate();
}