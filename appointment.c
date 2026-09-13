// appointment.c
#include "appointment.h"
#include "customer.c"
#include "artist.c"

#include <stdio.h>
#include <stdlib.h>

void makeAppointment(struct Appointment** head, int id, struct Customer* customer, 
               struct Artist* artist, struct Service* service, int year, Month month, 
               int day, int hr) {
               
               // The selected artist must not have another appointment at the same date and time
               struct Appointment *temp = *head;
               while (temp) {
        if (temp->artist->id == artist->id && temp->date.year == year && temp->date.month == month && 
       temp->date.day == day && temp->hour == hr) {
    printf("Artist already has an appointment at that time.\n");
          return ; 
            }
        temp = temp->next;
    }
               
   struct Appointment* newApp = (struct Appointment*)malloc(sizeof(struct Appointment));
    //if (!newApp) return NULL;
    newApp->id = id;
    newApp->customer = customer;
    newApp->artist = artist;
    newApp->service = service;
    newApp->date.year = year;
   newApp->date.month = month;
   newApp->date.day = day;
    newApp->hour = hr;
    newApp->status = UNPAID;
    newApp->next = *head;
    *head = newApp;
    printf("Appointment created, and added successfully \n");
   }

int cancelAppointment(struct Appointment** head, int id) {
   struct Appointment* current = *head;
   struct Appointment* prev = NULL;
    while (current) {
        if (current->id == id) {
            if (current->status == PAID) 
            return 0;
            
            if (prev) prev->next = current->next;
            else *head = current->next;
            free(current);
            return 1;
        }
        prev = current;
        current = current->next;
    }
    return 0;// if not found
}

void editAppointment(struct Appointment* appointment, struct Artist* newArtist, 
      struct Service* newService, int newYear, Month newMonth, int newDay,int newhr,
      struct Appointment* allAppointments ) {
        
    // The selected artist must not have another appointment at the same date and time
               struct Appointment *temp = allAppointments;
               while (temp) {
        if (temp->artist->id == newArtist->id && temp->date.year == newYear &&
         temp->date.month == newMonth && temp->date.day == newDay && temp->hour == newhr) {
            printf("can't edit this appointment , because artest has appointment.\n"); 
            return ; 
            }
        temp = temp->next;
    }
    
    appointment->artist = newArtist;
    appointment->service = newService;
    appointment->date.year = newYear;
    appointment->date.month = newMonth;
    appointment->date.day = newDay;
     appointment->hour = newhr ; 
   printf("edit successfully.\n") ; 
}

void findAppointmentsByCustomer(struct Appointment* head,  struct Customer* customer) {
    int found = 0;
    while (head) {
        if (head->customer->id == customer->id) {
            printAppointment(head);
            found = 1;
        }
        head = head->next;
    }
    if (found == 0 )
     printf("No appointments found for this customer.\n");
}

void findAppointmentsByArtist(struct Appointment* head,struct Artist* artist) {
    int found = 0;
    while (head) {
        if ( head->artist->id == artist->id) {
            printAppointment(head);
            found = 1;
        }
        head = head->next;
    }
    if (found == 0 ) 
    printf("No appointments found for this artist.\n");
}

void processPaymentAndPrintReceipt(struct Appointment* head,struct Customer* customer) {
    float total = 0;
    int found = 0;
    printf("\n***Receipt for Customer: %s (ID: %d) ===\n", customer->name, customer->id);
    printf("Unpaid Services:\n");
    while (head) {
        if (head->customer->id == customer->id && head->status == UNPAID) {
            printf("- %s: %.2f\n", head->service->name, head->service->price);
            total += head->service->price;
            head->status = PAID;
            found = 1;
        }
        head = head->next;
    }
    if (found == 0 ) {
        printf("No unpaid appointments.\n");
        return;
    }
    printf("Total Due: %.2f\n", total);
    printf("Marking all as paid...\n");
}

void printAppointment(struct Appointment* app) {
    const char* months[] = {"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    printf("Appointment ID: %d | Customer: %s | Artist: %s | Service: %s | Date: %d-%s-%d | Time: %d:00 | Status: %s\n",
           app->id, app->customer->name, app->artist->name, app->service->name,
           app->date.day, months[app->date.month], app->date.year, app->hour, app->status == PAID ? "Paid" : "Unpaid");
}
//==================================
void freeAppointments(struct Appointment* head) {
   struct Appointment* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void saveAppointments(struct Appointment* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) return;
    while (head) {
        fprintf(file, "%d|%d|%d|%d|%d|%d|%d|%d\n", head->id, head->customer->id, head->artist->id, head->service->id,
                head->date.year, head->date.month, head->date.day, head->hour, head->status);
        head = head->next;
    }
    fclose(file);
}

void loadAppointments(struct Appointment** head, const char* filename,
         struct Customer* customers, struct Artist* artists,struct Service services[], int serviceCount) {
    FILE* file = fopen(filename, "r");
    if (!file) return;
    int id, custId, artId, servId, year, month, day, hour, status;
    while (fscanf(file, "%d|%d|%d|%d|%d|%d|%d|%d\n", &id, &custId, &artId, &servId, &year, &month, &day, &hour, &status) == 9) {
        struct Customer* cust = findCustomer(customers, custId);
        struct Artist* art = findArtist(artists, artId);
        struct Service* serv = NULL;
        for (int i = 0; i < serviceCount; i++) {
            if (services[i].id == servId) { serv = &services[i]; break; }
        }
        if (cust && art && serv) {
           struct Appointment* newApp = (struct Appointment*)malloc(sizeof(struct Appointment));
            newApp->id = id;
            newApp->customer = cust;
            newApp->artist = art;
            newApp->service = serv;
            newApp->date.year = year;
            newApp->date.month = (Month)month;
            newApp->date.day = day;
            newApp->hour = hour;
            newApp->status = (enum Status)status;
            newApp->next = *head;
            *head = newApp;
        }
    }
    fclose(file);
}

int getNextAppointmentId(struct Appointment* head) {
    int maxId = 0;
    while (head) {
        if (head->id > maxId) maxId = head->id;
        head = head->next;
    }
    return maxId + 1;
}