//
//  stack.cpp
//  HW1-Maze-With-Stacks
//
//  Created by Selim Gül on 21.03.2022.
//

#include "stack.h"
#include <iostream>

using namespace std;

template <class Object>
Stack<Object>::Stack(){
    topOfStack = NULL;
}

template <class Object>
Stack<Object>::Stack(const Stack<Object>&rhs){
    topOfStack = NULL;
    *this = rhs;
}

template <class Object>
Stack<Object>::~Stack(){
    makeEmpty();
}

template <class Object>
void Stack<Object>::pop(){
    if(isEmpty()){
        cout << "Stack is empty!" << endl;
    }
    Node* top = topOfStack;
    topOfStack = topOfStack -> next;
    delete top;
}

template <class Object>
void Stack<Object>::push(const Object&o){
    topOfStack = new Node(o, topOfStack);
}

template <class Object>
void Stack<Object>::makeEmpty(){
    while (!isEmpty()) {
        pop();
    }
}

template <class Object>
bool Stack<Object>::isEmpty() const{
    if (topOfStack != nullptr)
        return false;
    else
        return true;
}


