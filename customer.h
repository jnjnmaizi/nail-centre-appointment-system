#ifndef CUSTOMER_H
#define CUSTOMER_H


typedef struct Customer {
    int id;
    char name[50];
    char phone[15];
    struct Customer *next;
} Customer;


void addCustomer( Customer** head, int id , const char *name, const char *phone);
Customer* findCustomer(Customer* head ,int id);
void printCustomers( Customer* head);
void freeCustomers( Customer* head);
void loadCustomers(Customer** head, const char *filename);
void saveCustomers(Customer* head, const char *filename);

#endif
