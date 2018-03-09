#ifndef MYSTACK_HPP
#define MYSTACK_HPP
#include "Node.hpp"

/*You are free to add private/public members inside this template..*/
template <class T>
class MyStack{
    private:
    Node<T> *top;
    public:
    /*Default constructor*/
    MyStack();
    /*copy constructor*/
    MyStack(const MyStack<T>& rhs);
    /*destructor*/
    ~MyStack();
    /*overloaded = operator*/
    MyStack<T>& operator=(const MyStack<T>& rhs);
    /*returns true if stack is empty*/
    bool isEmpty() const;
    /*push newItem to stack*/
    void push(const T& newItem);
    /*pop item from stack*/
    void pop();
    /*return top item of the stack*/
    Node<T>* Top() const;
	/*Prints the stack entries. This method was already implemented. Do not modify.*/
    void print() const;
};

template <class T>
void MyStack<T>::print() const{
    const Node<T>* node = top;
    while (node) {
        std::cout << node->getData();
        node = node->getNext();
    }
    cout<<std::endl;
}

template <class T>
MyStack<T>::MyStack(){
  top = NULL;
}

template <class T>
MyStack<T>::MyStack(const MyStack<T>& rhs){
  top = NULL;
	*this = rhs;
}

template <class T>
MyStack<T>::~MyStack(){
  while(!isEmpty()){
    pop();
  }
}

template <class T>
MyStack<T>& MyStack<T>::operator=(const MyStack<T>& rhs){
   if (this != &rhs) {
      while (!isEmpty()){
         pop();
       }
	   if (!rhs.Top()){
         top = NULL;
       }
      else {
         top = new Node<T>(rhs.Top()->getData());

         Node<T>* q = rhs.Top()->getNext();
         Node<T>* p = top;
         while (q) {
            p->setNext(new Node<T>(q->getData()));
            p = p->getNext();
            q = q->getNext();
         }
         p->setNext(NULL);
     }
  }
  return *this;
}

template <class T>
bool MyStack<T>::isEmpty() const{
  return top == NULL;
}

template <class T>
void MyStack<T>::push(const T& newItem){
  Node<T>* node = new Node<T>(newItem);
  Node<T>* tem;
  tem = top;
  top = node;
  top->setNext(tem);
}

template <class T>
void MyStack<T>::pop(){
   if (!isEmpty()){
      Node<T> *tmp = top;
      top = top->getNext();
      delete tmp;
   }
}

template <class T>
Node<T>* MyStack<T>::Top() const{
  if (isEmpty()){
  return NULL;
}
  return top;
}

/* TO-DO: method implementations below */

#endif /* MYSTACK_HPP */
