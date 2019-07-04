#include<iostream>
#include <list>
#include <iterator> 
using namespace std;
// template


class Node{
public:
    Node* next;
    Node* prev;
    Node* value;
    int data;
};

class LinkedList{
public:
    int length;
    Node* head;
    Node* tail;
    LinkedList(){
        this->length = 0;
        this->head = NULL;
        this->tail = NULL;
    }
    void addNodeLast(Node* n){
        if(this->length == 0){
            this->head = n;
        }
        else{
            this->tail->next = n;
            n->prev = this->tail;
        }
        this->tail = n;
        this->length++;
    }

    void addNodeFront(Node* n){
        if(this->length == 0){
            this->tail = n;
        }
        else{
            this->head->prev = n;
            n->next = head;
        }
        this->head = n;
        this->length++;
    }

    void addLast(int data){
        Node* newNode = new Node();
        newNode->data = data;
        addNodeLast(newNode);
    }

    void addFront(int data){
        Node* newNode = new Node();
        newNode->data = data;
        addNodeFront(newNode);
    }

    void displayList(){
        Node* temp = this->head;
        for(int i=0;i<this->length;i++){
            cout<<temp->data<<" ";
            temp = temp->next;
        }
        cout<<endl;
    }
};

// int main(){
//     LinkedList* l = new LinkedList();
//     l->displayList();
//     l->addFront(5);
//     l->addFront(7);
//     l->addFront(2);
//     l->displayList();
//
//
//
//
//
// }
