#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <iostream>
#include "Node.hpp"

using namespace std;

/*....DO NOT EDIT BELOW....*/
template <class T>
class LinkedList {
    private:
		/*First node of the linked-list*/
        Node<T>* head;
        /*Last node of the linked-list*/
		Node<T>* tail;
		/*size of the linked-list*/
		size_t  size;
    public:

        LinkedList();
        LinkedList(const LinkedList<T>& ll);
        LinkedList<T>& operator=(const LinkedList<T>& ll);
        ~LinkedList();

        /* Return head of the linked-list*/
        Node<T>* getHead() const;
        /* Set head of the linked-list*/
        void setHead(Node<T>* n);
        /* Return tail of the linked-list*/
        Node<T>* getTail() const;
        /* Set tail of the linked-list*/
        void setTail(Node<T>* n);
        /* Get the previous node of the node that contains the data item.
         * If the head node contains the data item, this method returns NULL.*/
        Node<T>* findPrev(const T& data) const;
        /* Get the node that stores the data item.
         * If data is not found in the list, this function returns NULL.*/
        Node<T>* findNode(const T& data) const;
        /* Insert a new node to store the data item.
         * The new node should be placed after the “prev” node.
         * If prev is NULL then insert new node to the head.*/
        void insertNode(Node<T>* prev, const T& data);
        /* This method is used to delete the node that is next to “prevNode”.
         * PS:prevNode is not the node to be deleted. */
        void deleteNode(Node<T>* prevNode);
        /* This method is used to clear the contents of the list.*/
        void clear();
        /* This method returns true if the list empty, otherwise returns false.*/
        bool isEmpty() const;
        /* This method returns the current size of the list. */
        size_t getSize() const;
        /*Prints the list. This method was already implemented. Do not modify.*/
        void print() const;
};

template <class T>
void LinkedList<T>::print() const{
    const Node<T>* node = head;
    while (node) {
        std::cout << node->getData();
        node = node->getNext();
    }
    cout<<std::endl;
}

/*....DO NOT EDIT ABOVE....*/

/* TO-DO: method implementations below */
template <class T>
LinkedList<T>::LinkedList(){
  head = NULL;
  tail = NULL;
  size = 0;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& ll){
  head = NULL;
  tail = NULL;
  size = 0;

    Node<T>* node = ll.getHead();
    while (node) {
        insertNode(tail,node->getData());
        node=node->getNext();
        tail->setNext(NULL);
}
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& ll){
  if (this != &ll){
      clear();
      const Node<T>* node = ll.getHead();
      while (node) {
          insertNode(tail,node->getData());
          node=node->getNext();
          tail->setNext(NULL);
  }
  }
  return *this;
}

template <class T>
LinkedList<T>::~LinkedList(){
    clear();
}

template <class T>
Node<T>* LinkedList<T>::getHead() const{
  return head;
}

template <class T>
void LinkedList<T>::setHead(Node<T>* n){
  if (n!=NULL and n==head->getNext()){
  size-=1;}
  head = n;
}

template <class T>
Node<T>*LinkedList<T>::getTail() const{
  return tail;
}

template <class T>
void LinkedList<T>::setTail(Node<T>* n){
  tail = n;
}

template <class T>
Node<T>* LinkedList<T>::findPrev(const T& data) const{
  Node<T>*p = head;
  while (p != tail){
    if (p->getNext()->getData() == data){
      return p;
      break;
    }
    p=p->getNext();
  }
  return NULL;
}

template <class T>
Node<T>* LinkedList<T>::findNode(const T& data) const{

  if (data==tail->getData()){
    return tail;
  }
  Node<T>*p = head;
  while (p){
    if (p->getData() == data){
      return p;
      break;
    }
    p=p->getNext();
  }
  return NULL;
}

template <class T>
void LinkedList<T>::insertNode(Node<T>* prev, const T& data){

    Node<T>* node = new Node<T>(data);
    Node<T>* tem;

    if (head==NULL){
        head = node;
        tail = node;
    }

    else if (prev == NULL){
        head = node;
        /*CORRECT:
        node->setNext(head);
        head = node;*/
    }

    else if (prev == tail){
        prev->setNext(node);
        tail = node;
    }

    else{
      tem = prev->getNext();
      prev->setNext(node);
      node->setNext(tem);
    }
    size+=1;
}

template <class T>
void LinkedList<T>::deleteNode(Node<T>* prevNode){

  if (prevNode){
    Node<T>* temp = prevNode->getNext();
    prevNode->setNext(temp->getNext());
    delete temp;
  }
  size-=1;
}
template <class T>
void LinkedList<T>::clear(){

      Node<T>* p = head;
      while (p) {
          Node<T>* tmp = p;
          p = p->getNext();
          delete tmp;
      }
      head = NULL;
      tail = NULL;
      size=0;
}

template <class T>
bool LinkedList<T>::isEmpty() const{
  return head==NULL && tail==NULL;
}

template <class T>
size_t LinkedList<T>::getSize() const{
  return size;
}

/* end of your implementations*/


#endif
