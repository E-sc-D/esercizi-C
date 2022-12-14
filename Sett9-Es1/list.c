#include <stdio.h>
#include <stdlib.h>

#ifndef DATA_TYPE
#error DATA_TYPE not defined
#else

struct Node
{
    DATA_TYPE data;

    struct Node *next;
    struct Node *previous;
};

struct Iterator
{
    int current_index;
    struct Node *current_node;
    //struct Node *next;
    //struct Node *previous;
};

struct List
{
    struct Node *head;
    struct Iterator iterator;    
}
typedef List;

// MUST BE USED TO INITIALIZE A LIST, otherwise the head pointer might not be NULL
List new_list()
{
    List new_list;
    new_list.head = NULL;
    return new_list;
}

// ##############################
//      Internal functions       
// ##############################

// Shouldn't be used outside of the library, sets the iterator to NULL
// to allow for iterator_forward to work
void iterator_init(List* list)
{
    list->iterator.current_index = -1;
    list->iterator.current_node = NULL;
}

// Shouldn't be used outside of the library, moves the iterator forward,
// onto the next item in list. Returns 1 if successful, 0 if not
int iterator_forward(List* list) 
{
    if(list->iterator.current_node == NULL && list->head != NULL)
    {
        list->iterator.current_index = 0;
        list->iterator.current_node = list->head;
    }
    else if(list->iterator.current_node != NULL && list->iterator.current_node->next != NULL)
    {
        list->iterator.current_index++;
        list->iterator.current_node = list->iterator.current_node->next;
        return 1;
    }
    else
    {
        return 0;
    }
}

// Shouldn't be used outside of the library, moves the iterator backward, onto the previous item in list.
// Returns 1 if successful, 0 if not
int iterator_backward(List* list) 
{
    if(list->iterator.current_node != NULL && list->iterator.current_node->previous != NULL)
    {
        list->iterator.current_index--;
        list->iterator.current_node = list->iterator.current_node->previous;
        return 1;
    }
    else
    {
        return 0;
    }
}

// Shouldn't be used outside of the library, gets a node at the position specified.
// Returns the index-nth node of list, if index is -1, returns the last one. CAN return NULL!
struct Node * node_get(List* list, int index) 
{
    if(index == -1)
    {
        iterator_init(list);
        while(iterator_forward(list));
        return list->iterator.current_node;
    }
    else
    {
        iterator_init(list);
        while(iterator_forward(list) && list->iterator.current_index != index);
        if(list->iterator.current_index == index)
            return list->iterator.current_node;
        else
            return NULL;
    }
}

// Shouldn't be used outside of the library, it removes the node at the position specified, 
// freeing the memory and then moving the next one at the removed one's place.
// Returns 1 if successful, 0 if not
int node_remove(List* list, int index) 
{
    struct Node* node_to_remove = node_get(list, index);
    struct Node* previous_node = node_to_remove->previous; // Can be NULL
    struct Node* next_node = node_to_remove->next; // Can be NULL
    if(node_to_remove != NULL)
    {
        free(node_to_remove);
        if(previous_node != NULL)
            previous_node->next = next_node;
        else
            list->head = next_node;
        if(next_node != NULL)
            next_node->previous = previous_node;
        
        return 1;
    }
    else
    {
        return 0;
    }
}

// Shouldn't be used outside of the library, it inserts a node at the position specified,
// moving the old one after the newly inserted one. Cannot insert at position 0 (first item) or -1 / length - 1 (last item)
// Returns 1 if successful, 0 if not
int node_insert(List* list, int index, struct Node* node_to_insert) 
{
    struct Node* old_node = node_get(list, index);
    struct Node* previous_node = old_node->previous; // Can be NULL
    if(node_to_insert != NULL && old_node != NULL && previous_node != NULL)
    {
        previous_node->next = node_to_insert;
        node_to_insert->previous = previous_node;
        old_node->previous = node_to_insert;
        node_to_insert->next = old_node;

        return 1;
    }
    else
    {
        return 0;
    }
}

// Shouldn't be used outside of the library, it adds a node to the list by getting the last node and changing its pointing address
// If no last node has been found then the list is of length 0 and the node to add will be set as the list's head
// Doesn't return anything as it should be impossible for it to fail
void node_add_back(List* list, struct Node* node_to_add) 
{
    struct Node* last_node = node_get(list, -1);
    if(node_to_add != NULL && last_node != NULL)
    {
        last_node->next = node_to_add;
        node_to_add->previous = last_node;
        node_to_add->next = NULL;
    }
    else if(node_to_add != NULL && last_node == NULL)
    {
        list->head = node_to_add;
        node_to_add->next = NULL;
        node_to_add->previous = NULL;
    }
}

// Shouldn't be used outside of the library, it adds a node to the list by setting it as new head and changing its pointing address
// If no last node has been found then the list is of length 0 and the node to add will be set as the list's head
// Doesn't return anything as it should be impossible for it to fail
void node_add_front(List* list, struct Node* node_to_add)
{
    struct Node* old_head = node_get(list, 0);
    if(node_to_add != NULL && old_head != NULL)
    {
        list->head = node_to_add;
        node_to_add->previous = NULL;
        node_to_add->next = old_head;
        old_head->previous = node_to_add;
    }
    else if(node_to_add != NULL && old_head == NULL)
    {
        list->head = node_to_add;
        node_to_add->next = NULL;
        node_to_add->previous = NULL;
    }
}

// ##############################
//        Useful functions       
// ##############################

// Gets the list length
int get_length(List* list)
{
    int length = 0;
    iterator_init(list);
    while (iterator_forward(list))
        length++;

    return length;
}

// Gets the data value of an existing list node
// Returns the index-nth element of list, if index is -1, returns the last one
DATA_TYPE get_element(List* list, int index) 
{
    struct Node* node = node_get(list, index);
    if(node != NULL)
        return node->data;
    else
        return; // GCC returns a warning for this (find a better way to handle node being NULL)
}

// Sets the data value of an existing list node
// Returns 1 if successful, 0 if not
int set_element(List* list, int index, DATA_TYPE data) 
{
    struct Node* node = node_get(list, index);
    if(node != NULL)
    {
        node->data = data;
        return 1;
    }
    else
    {
        return 0;
    }
}

// Creates a new node and assigns it the data to insert into the list, then the whole node gets inserted with node_insert()
// A malloc is here
// Returns 1 if successful, 0 if not
int insert_element(List* list, int index, DATA_TYPE data)
{
    struct Node* new_node = malloc(sizeof(struct Node));
    if(new_node == NULL) // malloc can return NULL if there's not memory available
        return 0;
    new_node->data = data;
    int returnValue = node_insert(list, index, new_node);
    if(!returnValue)
    {
        free(new_node);
        return 0;
    }
    else
    {
        return 1;
    }
}

// Creates a new node and assigns it the data to add into the list, then the whole node gets added with node_add()
// A malloc is here
// Returns 1 if successful, 0 if not
int add_element(List* list, DATA_TYPE data) 
{
    struct Node* new_node = malloc(sizeof(struct Node));
    if(new_node == NULL) // malloc can return NULL if there's not memory available
        return 0;
    new_node->data = data;
    node_add_back(list, new_node);
    // As specified in node_add_back and node_add_front, these methods cannot fail,
    return 1; // so the function immediately returns 1 without doing any checks.
}

// Alias for add_element(), pushes data into the back of the list
// Returns 1 if successful, 0 if not
int push_back(List* list, DATA_TYPE data)
{
    return add_element(list, data);
}

// Pushes data into the front of the list
// Returns 1 if successful, 0 if not
int push_front(List* list, DATA_TYPE data)
{
    struct Node* new_node = malloc(sizeof(struct Node));
    if(new_node == NULL) // malloc can return NULL if there's not memory available
        return 0;
    new_node->data = data;
    node_add_front(list, new_node);
    // As specified in node_add_back and node_add_front, these methods cannot fail,
    return 1; // so the function immediately returns 1 without doing any checks.
}

// Pops data from the back of the list, meaning the last item will be returned
// and deleted from the list. Returns the DATA_TYPE
DATA_TYPE pop_back(List* list)
{
    DATA_TYPE data = get_element(list, -1);
    node_remove(list, -1);
    return data;
}

// Pops data from the front of the list, meaning the first item will be returned
// and deleted from the list. Returns the DATA_TYPE
DATA_TYPE pop_front(List* list)
{
    DATA_TYPE data = get_element(list, 0);
    node_remove(list, 0);
    return data;
}

// Peeks data from the front of the list, meaning the first item will be returned
// and NOT deleted from the list. Returns the DATA_TYPE
DATA_TYPE peek_front(List* list)
{
    DATA_TYPE data = get_element(list, 0);
    return data;
}

// Peeks data from the front of the list, meaning the first item will be returned
// and NOT deleted from the list. Returns the DATA_TYPE
DATA_TYPE peek_back(List* list)
{
    DATA_TYPE data = get_element(list, -1);
    return data;
}

// Converts the list to a dynamically allocated static array
// Can return NULL
DATA_TYPE * list_to_array(List* list)
{
    DATA_TYPE * array = malloc(sizeof(DATA_TYPE) * get_length(list));
    iterator_init(list);
    while(iterator_forward(list))
        array[list->iterator.current_index] = list->iterator.current_node->data;
    return array;
}

// Converts the list to a dynamically allocated static array
List list_from_array(int length, DATA_TYPE * array)
{
    List list = new_list();
    int i;
    for(i = 0; i < length; i++)
        push_back(&list, array[i]);
    return list;
}

// Removes every item from the list
void clear(List* list)
{
    iterator_init(list);
    while(iterator_forward(list))
        node_remove(list, list->iterator.current_index);
}

#endif