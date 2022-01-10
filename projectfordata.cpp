
#include <stdio.h>
#include <stdlib.h>



struct Node {
    int data;
    struct Node* next;

};

typedef struct Node Node;
//empty lists
Node* first_head = NULL;  
Node* last_first = NULL;
Node* temp_first = NULL;

Node* second_head = NULL;
Node* last_second = NULL;
Node* temp_second = NULL;

Node* print = NULL;

// multiplicand number as a linked list.
Node addFirstNode(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node)); // allocate node.
    new_node->data = data; // put in the data.
    new_node->next = NULL; // make next of new node as NULL.
    
    // updating the empty lists(for first) with new_node here.
    if (first_head == NULL) { 
        first_head = new_node; 
        last_first = first_head;
        temp_first = first_head;
    }
    // traverse till the last node.
    else {
        last_first->next = new_node; // change the next of last node.
        last_first = last_first->next;
    }
    return *new_node;
}
// multiplier number as a linked list.
Node addSecondNode(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node)); // allocate node.
    new_node->data = data; // put in the data.
    new_node->next = NULL; // make next of new node as NULL.

    // updating the empty lists(for second) with new_node here.
    if (second_head == NULL) {
        second_head = new_node;
        last_second = second_head;
        temp_second = second_head;
    }
    // traverse till the last node
    else {
        last_second->next = new_node; // change the next of last node.
        last_second = last_second->next;
    }
    return *new_node;
}


Node* createProduct(int data) { //create linked list function for multiply function. 

    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

// reverse linked list
Node* reverse(Node* head) {
    Node* current = head; //current as head.
    Node* next; 
    Node* prev = NULL;
    while (current != NULL) {
        next = current->next; // store next.
        current->next = prev; // reverse current node pointer
        //move pointers one position.
        prev = current;
        current = next;
    }

    return prev;
}

Node* multiply(Node* head1, Node* head2) {

    Node* llmultiply;
    llmultiply = createProduct(0);
    Node* result = llmultiply;
    Node* result_check = llmultiply;

    Node* num1 = head1; // we get num1 from head1.
    while (num1) { // there is a loop for the multiplication. ex num1= 152, num2=57. i must multiply all of num1 digits with num2 last digit, then i multiply num1 digits with num2 first digit.


        // this part so important!!! this logic changes everything and this is most confusing part.

        //for ex     if we delete this part
        //  12                                      12
        //  15                                      15
        //x-----      -------->>>                x-----      
        //  60                                      60
        // 12        will be like this            12
        //+-----                                 +----- 
        // 180                                    1260
        //(my first bug was here)
        result_check = result; // result_check updated from result. 
        //fixed.
        int carry = 0; // we are multiply digit by digit , for ex num1 = 5 num2 = 3 so num1*num2=15 then we must have carry, carry hold 1 and ->data will be 5.
        Node* num2 = head2; // we get num2 from head2.
        while (num2) {

            result_check->data += carry + (num1->data * num2->data);
            if (result_check->data > 9) {
                carry = result_check->data / 10;
                result_check->data = result_check->data % 10;
            }
            else
                carry = 0;


            if (!result_check->next) { // if result_check dont have next element then set as 0.

                result_check->next = createProduct(0);
            }

            result_check = result_check->next; // go forward

            num2 = num2->next; // we dont want infinite loop so num2 must go forward also.
        }

        if (carry > 0) // we have in the range of 1 to 9 integer, we add carry to result_check->data( next digit by digit multiply) 3*6+(1). 
            result_check->data += carry;

        num1 = num1->next; // we dont want infinite loop also num1 must go forward.
        result = result->next; // result go forward.
    }

    llmultiply = reverse(llmultiply); // get linked list reverse// call reverse function//
    if (llmultiply->data == 0) { // if data eqauls to 0 then result will be updated from llmultilpy->next then llmulitply will be erased and recreated and updated from result.
        result = llmultiply->next;
        free(llmultiply);
        llmultiply = result;
    }

    return llmultiply;
}

// linked list print.
void print_list(Node* head) {

    print = head; // print is now head.
    // if print(head) is not empty then print linked list data, like 1->2-> .
    while (print != NULL) {
        printf("%d->", print->data);
        print = print->next;
    }

}


int main() {

    // call file opener with name input.
    FILE* input;
    int carpim, carpan; //2 integers defined to be updated by the input txt file.

    input = fopen("input.txt", "r"); // open input.txt file.

    if (input == NULL) // if input.txt file is empty then show error and close the file opener.
    {
        printf("Unsupported input file.");
        fclose(input);
    }

    else // if input.txt file is have some integers then first line is int carpim, second line is int carpan, after update this values close file opener.
    {
        fscanf(input, "%d", &carpim);
        fscanf(input, "%d", &carpan);
        fclose(input);
    }

    //if int carpim not equals to 0 then get number elements one by one to linked list.
    while (carpim != 0) {

        int node = carpim % 10;
        carpim = carpim / 10;
        addFirstNode(node);
    }
    //lets print carpim number as a linked list With print_list function.
    print_list(first_head);
    printf("\n");

    //if int carpan not equals to 0 then get number elements one by one to linked list.
    while (carpan != 0) {
        int node = carpan % 10;
        carpan = carpan / 10;
        addSecondNode(node);
    }
    //print carpan number as a linked list With print_list function.
    print_list(second_head);
    printf("\n");

    // multiply carpim and carpan linked list then print the result.
    // Here I could update the output.txt and then print the output.txt file. I printed the output with this method because it confused me.
    print_list(multiply(temp_first, temp_second));

    // call file opener with name output.
    FILE* output;
    output = fopen("output.txt", "w"); // lets run in write mode.

    Node* output_integer; // output_integer linked list.
    output_integer = multiply(temp_first, temp_second); // multiply carpim and carpan linked list then update output_integer.
    long long int output_number = 0; // initialize output_number.it must be long long int, because we are talking about large large numbers.
    while (output_integer) { //  read linked list and transform to integer. this is reversed process. i use in this project int to ll, ll to int.
        output_number += output_integer->data;
        output_number *= 10;
        output_integer = output_integer->next;
    }
    output_number /= 10; // this is solved my second bug. output.txt show one more 0 at the end of the number. it removes the redundant zero of the number and gives the correct result.
    fprintf(output, "%lli", output_number); // long long integer output_number going to ---> output.txt.
    fclose(output); // close file opener.

    return 0;
}

