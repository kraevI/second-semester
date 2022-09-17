#include <iostream>

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
            for (unsigned int i = 0; i < index - 1; i++) {
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
    cout << index << "'th element value: " << n->value << '\n';
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



int main()
{
    List* list = new List;
    unsigned int list_size = 12;
    for (unsigned int i = 0; i <= list_size; i++) {
        new_Node_to_the_right_place(list, 0, i);
    }
    print(list);


    return 0;

}

