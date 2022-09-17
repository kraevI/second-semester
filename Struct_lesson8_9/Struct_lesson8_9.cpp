#include <iostream>
using namespace std;

struct Node {
    int value = -1;
    Node* next;
};

struct List {
    unsigned size = 0;
    Node* head;
    Node* tail;
};

void new_Node_to_the_right_place(List* list, unsigned int index, int value) {
    if ((index > list->size) || (index < 0)) cout << "Error: this position does not exist in this list" << '\n';
    else {
        Node* n = new Node;
        n->value = value;
        if (index == 0) {
            n->next = list->head;
            list->head = n;
        }
        else if (index == list->size) {
            n->next = n;
            list->tail->next = n;
            list->tail = n;
        }
        else {
            Node* helper = list->head;
            for (unsigned int i = 0; i < index-1; i++) {
                helper = helper->next;
            }
            n->next = helper->next;
            helper->next = n;
        }
        list->size++;
    }
}

// get the i‘th element value by index
int get_value(List* list, unsigned int index) {
    if ((index > list->size - 1) || (index < 0)) cout << "Error: this index does not exist" << '\n';
    Node* n = list->head;
    for (unsigned int i = 0; i < index; i++) {
        n = n->next;
    }
    cout << index <<"'th element value: " << n->value << '\n';
    return n->value;
}

// clear i'th element of the list
void clear(List* list, unsigned int index) {
    if ((index > list->size - 1) || (index < 0)) cout << "Error: this index does not exist" << '\n';
    else {
        if (index == 0) {
            Node* helper = list->head;
            list->head = list->head->next;
            delete helper;
        }
        else if (index == list->size - 1) {
            Node* helper = list->head;
            for (unsigned int i = 0; i < index - 1; i++) {
                helper = helper->next;
            }
            list->tail = helper;
            delete helper->next;
        }
        else {
            Node* helper = list->head;
            for (unsigned int i = 0; i < index - 1; i++) {
                helper = helper->next;
            }
            Node* helper_2 = helper->next;
            helper->next = helper_2->next;
            delete helper_2;
        }
        list->size--;
    }
}

void clear_all(List* list) {
    unsigned int size = list->size;
    for (unsigned int i = 0; i < size; i++) {
        clear(list, 0);
    }
}

// print all elements of the list
void print(List* list) {
    if (list->size == 0) cout << "The list is empty" << '\n';
    else {
        Node* n = list->head;
        for (unsigned int i = 0; i < list->size; i++) {
            cout << n->value << " ";
            n = n->next;
        }
        cout << endl;
    }
}


/*int main(){

    Node* n = new Node;
    n->value = 5;
    n->next = n;
    List* list = new List;
    list->head = n;
    list->tail = n;
    list->size++;
    print(list);

    new_Node_to_the_right_place(list, 9, 11);
    new_Node_to_the_right_place(list, 0, 0);
    new_Node_to_the_right_place(list, list->size, 87);
    print(list);

    new_Node_to_the_right_place(list, 2, 13);
    print(list);

    get_value(list, 3);

    clear(list, 3);
    print(list);

    clear_all(list);
    print(list);
    
    cout << endl;
    return 0;
}*/



struct DoubleNode {
    int value = -1;
    DoubleNode* prev;
    DoubleNode* next;
};

struct DoubleList {
    unsigned size = 0;
    DoubleNode* head;
    DoubleNode* tail;
};

void new_DoubleNode_to_the_right_place(DoubleList* list, unsigned int index, int value) {
    if ((index > list->size) || (index < 0)) cout << "Error: this position does not exist in this list" << '\n';
    else {
        DoubleNode* n = new DoubleNode;
        n->value = value;
        if (index == 0) {
            n->prev = n;
            n->next = list->head;
            list->head->prev = n;
            list->head = n;
        }
        else if (index == list->size) {
            n->prev = list->tail;
            n->next = n;
            list->tail->next = n;
            list->tail = n;
        }
        else {
            DoubleNode* helper = list->head;
            for (unsigned int i = 0; i < index - 1; i++) {
                helper = helper->next;
            }
            n->next = helper->next;
            helper->next->prev = n;
            n->prev = helper;
            helper->next = n;
        }
        list->size++;
    }
}

void new_DoubleNode_to_back(DoubleList* list, int value) {
    DoubleNode* n = new DoubleNode;
    n->value = value;
    n->prev = list->tail;
    n->next = n;
    list->tail->next = n;
    list->tail = n;
    list->size++;
}

void new_DoubleNode_to_front(DoubleList* list, int value) {
    DoubleNode* n = new DoubleNode;
    n->value = value;
    n->prev = n;
    n->next = list->head;
    list->head->prev = n;
    list->head = n;
    list->size++;
}

// add new node with value new_val in front of i‘th node
int new_DoubleNode_insert(DoubleList* list, unsigned int index, int value) {
    if ((index < 0) || (index >= list->size)) {
        cout << "Error: this position does not exist in this list" << '\n';
        return -1;
    }
    DoubleNode* n = new DoubleNode;
    n->value = value;
    DoubleNode* helper = list->head;
    for (unsigned int i = 0; i < index - 1; i++) {
        helper = helper->next;
    }
    n->next = helper->next;
    helper->next->prev = n;
    n->prev = helper;
    helper->next = n;
    list->size++;
    return 0;
}

// get the i‘th element by index
int get_value(DoubleList* list, unsigned index) {
    if ((index > list->size - 1) || (index < 0)) {
        cout << "Error: this index does not exist" << '\n';
        return 0;
    }
    
    DoubleNode* n = list->head;
    for (unsigned int i = 0; i < index; i++) {
        n = n->next;
    }
    cout << index << "'th element value: " << n->value << '\n';
    return n->value;
}

// print all elements of the list in forward
void print(DoubleList* list) {
    if (list->size == 0) cout << "The list is empty" << '\n';
    else {
        DoubleNode* n = list->head;
        for (unsigned int i = 0; i < list->size; i++) {
            cout << n->value << " ";
            n = n->next;
        }
        cout << endl;
    }
}

// print all elements of the list in reverse
void printReverse(DoubleList* list) {
    if (list->size == 0) cout << "The list is empty" << '\n';
    else {
        DoubleNode* n = list->tail;
        for (unsigned int i = 0; i < list->size; i++) {
            cout << n->value << " ";
            n = n->prev;
        }
        cout << endl;
    }
}

// delete i‘th element
void clear(DoubleList* list, unsigned index) {
    if ((index > list->size - 1) || (index < 0)) cout << "Error: this index does not exist" << '\n';
    else {
        if (index == 0) {
            DoubleNode* helper = list->head;
            list->head = list->head->next;
            list->head->prev = list->head;
            delete helper;

        }
        else if (index == list->size - 1) {
            DoubleNode* helper = list->tail;
            list->tail = list->tail->prev;
            list->tail->next = list->tail;
            delete helper;
        }
        else {
            DoubleNode* helper = list->head;
            for (unsigned int i = 0; i < index; i++) {
                helper = helper->next;
            }
            helper->prev->next = helper->next;
            helper->next->prev = helper->prev;
            delete helper;
        }
        list->size--;
    }
}

// clear all elements of the list
void clear_all(DoubleList* list) {
    unsigned int size = list->size;
    for (unsigned int i = 0; i < size; i++) {
        clear(list, 0);
    }
}


int main(){
    DoubleNode* n = new DoubleNode;
    //n->value = 5;
    //n->next = n;
    DoubleList* list = new DoubleList;
    list->head = n;
    list->tail = n;
    list->size++;
    print(list);

    new_DoubleNode_to_front(list, 90);
    print(list);

    new_DoubleNode_to_back(list, 50);
    print(list);

    get_value(list, 10);
    
    printReverse(list);

    clear(list, list->size - 1);
    print(list);

    clear_all(list);
    print(list);

    cout << endl;
    delete list;
    return 0;
}