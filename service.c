#include "service.h"
#include <stdio.h>
#include <string.h>

// check if ID exists
int isDuplicateID(struct Service services[], int count, int id) {
   for (int i = 0; i < count; i++) {
      if (services[i].id == id) {
         return 1;
      }
   }
   return 0;
}

// add service
void addService(struct Service services[], int* count, int id, const char* name, float price) {
   if (*count >= MAX_SERVICES) {
      printf("cannot add more services\n");
      return;
   }

   if (isDuplicateID(services, *count, id)) {
      printf("Error: service with ID %d already exists\n", id);
      return;
   }

   services[*count].id = id;

   // safer copy
   strncpy(services[*count].name, name, sizeof(services[*count].name) - 1);
   services[*count].name[sizeof(services[*count].name) - 1] = '\0';

   services[*count].price = price;

   (*count)++;
   printf("service with ID: %d added successfully\n", id);
}

// delete service
void deleteService(struct Service services[], int* count, int id) {
   for (int i = 0; i < *count; i++) {
      if (services[i].id == id) {
      
         for (int j = i; j < *count - 1; j++) {
            services[j] = services[j + 1];
         }
      
         (*count)--;
         printf("delete service successfully\n");
         return;
      }
   }

   printf("can't delete service\n");
}

// print services
void printServices(struct Service services[], int count) {
   if (count == 0) {
      printf("list of services is empty.\n");
      return;
   }

   printf("\n*** Service List ***\n");
   for (int i = 0; i < count; i++) {
      printf("ID: %d | Name: %s | Price: %.2f\n",
            services[i].id,
            services[i].name,
            services[i].price);
   }
}

// save to file
void saveServices(struct Service services[], int count, const char* filename) {
   FILE* file = fopen(filename, "w");
   if (!file) {
      printf("Error opening file\n");
      return;
   }

   for (int i = 0; i < count; i++) {
      fprintf(file, "%d|%s|%.2f\n",
             services[i].id,
             services[i].name,
             services[i].price);
   }

   fclose(file);
}

// load from file (with duplicate protection)
void loadServices(struct Service services[], int* count, const char* filename) {
   FILE* file = fopen(filename, "r");
   if (!file) {
      printf("Error opening file\n");
      return;
   }

   *count = 0;

   while (*count < MAX_SERVICES &&
         fscanf(file, "%d|%[^|]|%f\n",
                &services[*count].id,
                services[*count].name,
                &services[*count].price) == 3) {
   
      if (!isDuplicateID(services, *count, services[*count].id)) {
         (*count)++;
      }
   }

   fclose(file);
}