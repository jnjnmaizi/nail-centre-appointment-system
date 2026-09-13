#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"

void addCustomer( Customer** head, int id , const char *name, const char *phone) {
    Customer *newCust = (Customer *)malloc(sizeof(Customer));
    if (!newCust) {
        printf("Memory allocation failed.\n");
        return;
    }
    newCust->id = id;
    strcpy(newCust->name, name);
    strcpy(newCust->phone, phone);
    newCust->next = *head;
    *head = newCust;

    printf("Customer with ID: %d added successfully.\n", newCust->id);
}

Customer* findCustomer( Customer* head ,int id) {
    Customer *cur = head;
    while (cur!=NULL) {
        if (cur->id == id) return cur;
        cur = cur->next;
    }
    return NULL;
}

void printCustomers(Customer* head) {
    if (head== NULL) {
        printf("No customers found.\n");
        return;
    }
    printf("\n%-6s %-30s %-15s\n", "ID", "Name", "Phone");
    printf("%-6s %-30s %-15s\n", "------", "------------------------------", "---------------");
    Customer *cur = head;
    while (cur != NULL) {
        printf("%-6d %-30s %-15s\n", cur->id, cur->name, cur->phone);
        cur = cur->next;
    }
    printf("\n");
}

void freeCustomers(Customer* head) {
    Customer *cur = head;
    while (cur) {
        Customer *tmp = cur;
        cur=cur->next;
        free(tmp);
    
    }
    
}

void loadCustomers(Customer** head, const char *filename) {
    FILE *fp = fopen(filename, "r"); // for reading
    if (!fp) return;
    int id;
    char name[50], phone[15]; 
    while (fscanf(fp, "%d|%49[^|]|%14[^\n]\n", &id, name, phone) == 3) { // 3 values to read
     addCustomer(head , id , name , phone);
    } 
    fclose(fp);

    
}

void saveCustomers( Customer* head , const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) { printf("Error saving customers.\n"); return; }
    Customer *cur = head;
    while (cur) {
        fprintf(fp, "%d|%s|%s\n", cur->id, cur->name, cur->phone);
        cur = cur->next;
    }
    fclose(fp);
}
