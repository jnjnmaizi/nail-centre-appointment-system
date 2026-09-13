// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "service.c"
#include "appointment.c"

int isValidDate(int year, int month, int day) ;
int hasFuturePaidAppointments(struct Appointment* appointments, int artId) ;
int hasFuturePaidAppointmentsForService(struct Appointment* appointments, int serviceId);

int main() {
   struct Customer* customers = NULL;
   struct Artist* artists = NULL;
   struct Service services[MAX_SERVICES];
   int serviceCount = 0;
   struct Appointment* appointments = NULL;
    
   loadCustomers(&customers, "customers.txt");
   loadArtists(&artists, "artists.txt");
   loadServices(services, &serviceCount, "services.txt");
   loadAppointments(&appointments, "appointments.txt", customers, artists, services, serviceCount);
   printf("Data loaded successfully.\n");
    
    
   int choice;
   do {
      printf("\n");
      printf("==================================================\n");
      printf("         NAIL CENTRE APPOINTMENT SYSTEM\n");
      printf("==================================================\n");
      printf("  [1] Add Customer\n");
      printf("  [2] Add Artist\n");
      printf("  [3] Add Service\n");
      printf("  [4] Make Appointment\n");
      printf("  [5] Cancel Appointment\n");
      printf("  [6] Edit Appointment\n");
      printf("  [7] Delete Service\n");
      printf("  [8] Delete Artist\n");
      printf("  [9] Find Customer Appointments\n");
      printf("  [10] Find Artist Appointments\n");
      printf("  [11] Process Payment & Print Receipt\n");
      printf("  [12] Print All Customers\n");
      printf("  [13] Print All Artists\n");
      printf("  [14] Print All Services\n");
      printf("  [15] Save and Exit\n");
      printf("==================================================\n");
      printf("Enter your choice: ");
      scanf("%d", &choice);        
      switch(choice) {
         case 1: //add customer
            printf("Enter customer id : ");
            int id ;
            scanf("%d" , &id); 
            if( findCustomer(customers , id) != NULL){
               printf("this id already exists.\n"); 
               break; 
            }
            char name[50], phone[15];
            getchar(); 
            printf("Enter customer name: ");
            fgets(name, 50, stdin);
                
            printf("Enter phone number: ");
         
            scanf("%s" , phone); 
            addCustomer(&customers, id, name, phone);
               
            break;
            
         case 2: //Add Artist
            printf("Enter artist id : ");
            int id2 ;
            scanf("%d" , &id2); 
            if( findArtist(artists , id2) != NULL){
               printf("this id already exists.\n"); 
               break; 
            }
            char nameArtist[50], info[100];
            int infoType;
            getchar();
            printf("Enter artist name: ");
            fgets(nameArtist, 50, stdin);
            
            printf("Info type (1-Phone, 2-National ID, 3-Address): ");
            scanf("%d", &infoType);
            getchar();
            printf("Enter info: ");
            fgets(info, 100, stdin);
                
            addArtist(&artists, id2, nameArtist, infoType, info);
                
            break;
            
         case 3: //Add Service
            if (serviceCount >= MAX_SERVICES) {
               printf("list of services is full \n");
               break;
            }
            int id3 ;
            printf("Enter id of service : " ); 
            scanf("%d" , &id3); 
            char name3[50];
            float price;
            getchar();
            printf("Enter service name: ");
            fgets(name3, 50, stdin);
                
            printf("Enter price: ");
            scanf("%f", &price);
            
            addService(services, &serviceCount, id3, name3, price);
               
            break;
            
         case 4:  //Make Appointment
            int custId, artId, servId, year, month, day, hour;
            printf("Enter customer ID: ");
            scanf("%d", &custId);
            struct Customer* cust = findCustomer(customers, custId);
            if (cust == NULL) {
               printf("Customer not found.\n");
               break; }
                  
            printf("Enter artist ID: ");
            scanf("%d", &artId);
            struct Artist* art = findArtist(artists, artId);
            if (art == NULL ) { 
               printf("Artist not found.\n"); 
               break; }
                
            printf("Enter service ID: ");
            scanf("%d", &servId);
            struct Service* serv = NULL;
            for (int i = 0; i < serviceCount; i++) 
               if (services[i].id == servId) { 
                  serv = &services[i]; 
                  break; }
                
            if (serv == NULL) { 
               printf("Service not found.\n"); 
               break; }
                
            printf("Enter year (2025-2030): ");
            scanf("%d", &year);
            printf("Enter month (1-12): ");
            scanf("%d", &month);
            printf("Enter day: ");
            scanf("%d", &day);
            printf("Enter hour (13-20): ");
            scanf("%d", &hour);
              
            if (!isValidDate(year, month, day) || hour < 13 || hour > 20) {
               printf("Invalid date or time.\n");
               break;
            }
                
            int appId ; 
            printf("Enter id of appointment : " ); 
            scanf("%d" , &appId ); 
            struct Appointment *temp = appointments;
            int found = 0 ; 
            while (temp) {
               if (temp->id == appId ) {
                  printf(" an appointment id already exists.\n");
                  found = 1 ; 
               }
               temp = temp->next;
            }
            if( found == 1 ) 
               break; 
                
                
            makeAppointment(&appointments, appId, cust, art, serv, year, (Month)month, day, hour);
            break;
            
         case 5: //Cancel Appointment
                
            printf("Enter appointment ID: ");
            scanf("%d", &appId);
            if (cancelAppointment(&appointments, appId)) 
               printf("Appointment cancelled.\n");
            else 
               printf("Cannot cancel paid appointment or appointment not found.\n");
            break;
            
         case 6: //Edit Appointment
            int  newArtId, newServId, newYear, newMonth, newDay, newHour;
            printf("Enter appointment ID: ");
            scanf("%d", &appId);
            found = 0; 
            struct Appointment* app = appointments;
            while (app){
               if( app->id == appId) {
                  found = 1;
                  break;}  
               else
                  app = app->next;
            }
                
            if (found == 0 ) { 
               printf("Appointment not found.\n"); 
               break; }
                
            if (app->status == PAID) { 
               printf("Cannot edit paid appointment.\n");
               break; }
                 
            printf("Enter new artist ID : ");
            scanf("%d", &newArtId);
            struct Artist* newArt = NULL;
            if (newArtId != 0) {
               newArt = findArtist(artists, newArtId);
               if (!newArt) { printf("Artist not found.\n"); 
                  break; }
            }
            printf("Enter new service ID : ");
            scanf("%d", &newServId);
            struct Service* newServ = NULL;
            for (int i = 0; i < serviceCount; i++) 
               if (services[i].id == newServId) { 
                  newServ = &services[i]; 
                  break; }
                    
            if (newServ == NULL) { 
               printf("Service not found.\n"); 
               break; }
                
            printf("Enter new year: ");
            scanf("%d", &newYear);
            printf("Enter new month (1-12): ");
            scanf("%d", &newMonth);
            printf("Enter new day: ");
            scanf("%d", &newDay);
            printf("Enter new hour: ");
            scanf("%d", &newHour);
            editAppointment(app, newArt, newServ, newYear, (Month)newMonth, newDay, newHour, 
                appointments);
                   
            break;
         case 7 : //Delete service
            printf("enter service id to delet : "); 
            scanf("%d" , &servId ) ;
            
            if( hasFuturePaidAppointmentsForService(appointments , servId) == 1 )
            {printf("can't delet service with future paid appontments \n"); 
               break; 
            }
         
            deleteService( services, &serviceCount , servId   ) ; 
            break; 
          
         case 8: //Delete artist
               
            printf("Enter artist ID to delete: ");
            scanf("%d", &artId);
            if( hasFuturePaidAppointments(appointments , artId) == 1 )
            {printf("can't delet artist with future paid appontments \n"); 
               break; 
            }
            deleteArtist(&artists, artId); 
         
            break;
            
         case 9: //Find Appointments of a Customer
            printf("Enter customer ID: ");
            scanf("%d", &custId);
            struct Customer* cust2 = findCustomer(customers, custId);
            if (cust2 == NULL) { 
               printf("Customer not found.\n"); 
               break; }
            findAppointmentsByCustomer(appointments, cust2);
            break;
            
         case 10: //Find Appointments of an Artist
            printf("Enter artist ID: ");
            scanf("%d", &artId);
            struct Artist* art2 = findArtist(artists, artId);
            if (art2== NULL) {
               printf("Artist not found.\n"); 
               break; }
            findAppointmentsByArtist(appointments, art2);
            break;
            
         case 11: //Process Payment and Print Receipt
            printf("Enter customer ID: ");
            scanf("%d", &custId);
            cust = findCustomer(customers, custId);
            if (cust == NULL) { printf("Customer not found.\n"); 
               break; }
            processPaymentAndPrintReceipt(appointments, cust);
                
            break;
            
         case 12:
            printCustomers(customers);
            break;
         case 13:
            printArtists(artists);
            break;
         case 14:
            printServices(services, serviceCount);
            break;
         case 15: 
            saveCustomers(customers, "customers.txt");
            saveArtists(artists, "artists.txt");
            saveServices(services, serviceCount, "services.txt");
            saveAppointments(appointments, "appointments.txt");
            printf("Data saved. Exiting...\n");
            break;
               
      
         default:
            printf("Invalid choice.\n");
      }
   } while (choice != 15);
    
   freeCustomers(customers);
   freeArtists(artists);
   freeAppointments(appointments);
   return 0;
}




int isValidDate(int year, int month, int day) {
   if (year < 2025 || year > 2030) 
      return 0;
   if (month < 1 || month > 12) 
      return 0;
   int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
   if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) 
      daysInMonth[2] = 29;
   return (day >= 1 && day <= daysInMonth[month]);
}

int hasFuturePaidAppointments(struct Appointment* appointments, int artId ) {
   return 0;
}

int hasFuturePaidAppointmentsForService(struct Appointment* appointments, int serviceId) {
   return 0;
}
