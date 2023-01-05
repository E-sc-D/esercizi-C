#include <stdio.h>
#include <stdlib.h>
#include "variant.c"

struct Node
{
    var data;
    struct Node *next;
    struct Node *previous;
};

struct Iterator
{
    int current_index;
    struct Node *current_node;
};

struct List
{
    struct Node *head;
    struct Iterator iterator;
}
typedef List;

// MUST BE USED TO INITIALIZE A LIST, otherwise the head pointer might not be NULL
List list_new()
{
    List new_list;
    new_list.head = NULL;
    new_list.iterator.current_index = -1;
    new_list.iterator.current_node = NULL;
    return new_list;
}

// ##############################
//      Internal functions       
// ##############################

// Shouldn't be used outside of the library, sets the iterator to NULL
// to allow for iterator_forward to work
void list_iterator_init(List* list)
{
    list->iterator.current_index = -1;
    list->iterator.current_node = NULL;
}

// Shouldn't be used outside of the library, moves the iterator forward,
// onto the next item in list. Returns 1 if successful, 0 if not
int list_iterator_forward(List* list) 
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
int list_iterator_backward(List* list) 
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
struct Node * list_node_get(List* list, int index) 
{
    if(index == -1)
    {
        list_iterator_init(list);
        while(list_iterator_forward(list));
        return list->iterator.current_node;
    }
    else
    {
        list_iterator_init(list);
        while(list_iterator_forward(list) && list->iterator.current_index != index);
        if(list->iterator.current_index == index)
            return list->iterator.current_node;
        else
            return NULL;
    }
}

// Shouldn't be used outside of the library, it removes the node at the position specified, 
// freeing the memory and then moving the next one at the removed one's place.
// Returns 1 if successful, 0 if not
int list_node_remove(List* list, int index) 
{
    struct Node* node_to_remove = list_node_get(list, index);
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
int list_node_insert(List* list, int index, struct Node* node_to_insert) 
{
    struct Node* old_node = list_node_get(list, index);
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
void list_node_add_back(List* list, struct Node* node_to_add) 
{
    struct Node* last_node = list_node_get(list, -1);
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
void list_node_add_front(List* list, struct Node* node_to_add)
{
    struct Node* old_head = list_node_get(list, 0);
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
int list_length_get(List* list)
{
    int length = 0;
    list_iterator_init(list);
    while (list_iterator_forward(list))
        length++;

    return length;
}

// Gets the data value of an existing list node
// Returns the index-nth element of list, if index is -1, returns the last one
// Returns a ReturnValue struct containing the requested data and a flag which
// tells if the data is valid or not.
var list_element_get(List* list, int index) 
{
    var new_variant = var_null;
    struct Node* node = list_node_get(list, index);
    if(node != NULL)
        new_variant = var_set_var(node->data);   
    return new_variant;
}

// Sets the data value of an existing list node
// Returns 1 if successful, 0 if not
int list_element_set(List* list, int index, var data) 
{
    struct Node* node = list_node_get(list, index);
    if(node != NULL)
    {
        node->data = var_set_var(data);
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
int list_element_insert(List* list, int index, var data)
{
    struct Node* new_node = malloc(sizeof(struct Node));
    if(new_node == NULL) // malloc can return NULL if there's not memory available
        return 0;
    new_node->data = var_set_var(data);
    int returnValue = list_node_insert(list, index, new_node);
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
int list_element_add(List* list, var data) 
{
    struct Node* new_node = malloc(sizeof(struct Node));
    if(new_node == NULL) // malloc can return NULL if there's not memory available
        return 0;
    new_node->data = var_set_var(data);
    list_node_add_back(list, new_node);
    // As specified in node_add_back and node_add_front, these methods cannot fail,
    return 1; // so the function immediately returns 1 without doing any checks.
}

// Alias for add_element(), pushes data into the back of the list
// Returns 1 if successful, 0 if not
int list_push_back(List* list, var data)
{
    return list_element_add(list, data);
}

// Pushes data into the front of the list
// Returns 1 if successful, 0 if not
int list_push_front(List* list, var data)
{
    struct Node* new_node = malloc(sizeof(struct Node));
    if(new_node == NULL) // malloc can return NULL if there's not memory available
        return 0;
    new_node->data = var_set_var(data);
    list_node_add_front(list, new_node);
    // As specified in node_add_back and node_add_front, these methods cannot fail,
    return 1; // so the function immediately returns 1 without doing any checks.
}

int list_push_at(List* list, int index, var data)
{
    list_element_insert(list, index, data);
}

// Pops data from the back of the list, meaning the last item will be returned
// and deleted from the list. Returns the DATA_TYPE
var list_pop_back(List* list)
{
    var data = list_element_get(list, -1);
    list_node_remove(list, -1);
    return data;
}

// Pops data from the front of the list, meaning the first item will be returned
// and deleted from the list. Returns the DATA_TYPE
var list_pop_front(List* list)
{
    var data = list_element_get(list, 0);
    list_node_remove(list, 0);
    return data;
}

var list_pop_at(List* list, int index)
{
    var data = list_element_get(list, index);
    list_node_remove(list, index);
    return data;
}

// Peeks data from the front of the list, meaning the first item will be returned
// and NOT deleted from the list. Returns the DATA_TYPE
var list_peek_front(List* list)
{
    var data = list_element_get(list, 0);
    return data;
}

// Peeks data from the front of the list, meaning the first item will be returned
// and NOT deleted from the list. Returns the DATA_TYPE
var list_peek_back(List* list)
{
    var data = list_element_get(list, -1);
    return data;
}

var list_peek_at(List* list, int index)
{
    var data = list_element_get(list, index);
    return data;
}

// Converts the list to a dynamically allocated static array
// Can return NULL
var * list_to_array(List* list)
{
    var *array = malloc(sizeof(var) * list_length_get(list));
    list_iterator_init(list);
    while(list_iterator_forward(list))
        array[list->iterator.current_index] = list->iterator.current_node->data;
    return array;
}

// Converts the list to a dynamically allocated static array
List list_from_array(int length, var *array)
{
    List list = list_new();
    int i;
    for(i = 0; i < length; i++)
        list_push_back(&list, array[i]);
    return list;
}

// Removes every item from the list
void list_clear(List* list)
{
    list_iterator_init(list);
    while(list_iterator_forward(list))
        list_node_remove(list, list->iterator.current_index);
}