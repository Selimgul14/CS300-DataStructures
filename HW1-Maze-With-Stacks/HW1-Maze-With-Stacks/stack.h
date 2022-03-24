//
//  stack.h
//  HW1-Maze-With-Stacks
//
//  Created by Selim Gül on 21.03.2022.
//

#ifndef stack_h
#define stack_h

template<class Object>
class Stack {
public:
    Stack();
    Stack(const Stack&rhs);
    ~Stack();
    void pop();
    void push(const Object&o);
    void makeEmpty();
    bool isEmpty() const;
    Object topAndPop();
    const Object &top() const;
    //const Stack & operator=(const Stack&rhs);
    
private:
    struct Node{
        Object current;
        Node *next;
        Node(const Object & _current, Node * n = nullptr): current(_current), next(n){}
    };
    Node *topOfStack;
    
};

#endif /* stack_h */
