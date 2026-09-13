// service.h
#ifndef SERVICE_H
#define SERVICE_H

#define MAX_SERVICES 10

struct Service {
    int id;
    char name[50];
    float price;
};

// functions
void addService(struct Service services[], int* count, int id, const char* name, float price);
void deleteService(struct Service services[], int* count, int id);
void printServices(struct Service services[], int count);

void saveServices(struct Service services[], int count, const char* filename);
void loadServices(struct Service services[], int* count, const char* filename);

#endif