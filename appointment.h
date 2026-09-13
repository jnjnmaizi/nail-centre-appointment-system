// appointment.h
#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include "customer.h"
#include "artist.h"
#include "service.h"

// enum for months
typedef enum { JAN=1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC } Month;

// enum for status
enum Status { UNPAID, PAID };

// struct
struct Appointment {
    int id;

    struct Customer* customer;
    struct Artist* artist;
    struct Service* service;

    struct {
        int year;
        Month month;
        int day;
    } date;

    int hour;
    enum Status status;

    struct Appointment* next;
};

// functions
void makeAppointment(struct Appointment** head, int id,struct Customer* customer, struct Artist* artist, struct Service* service,int year, Month month, int day, int hr);
                                                                                 
int cancelAppointment(struct Appointment** head, int id);

void editAppointment(struct Appointment* appointment,struct Artist* newArtist,struct Service* newService,int newYear, Month newMonth, int newDay, int hr,struct Appointment* allAppointments);
                     
void findAppointmentsByCustomer(struct Appointment* head, struct Customer* customer);
void findAppointmentsByArtist(struct Appointment* head, struct Artist* artist);
void processPaymentAndPrintReceipt(struct Appointment* head, struct Customer* customer);

void freeAppointments(struct Appointment* head);
void saveAppointments(struct Appointment* head, const char* filename);
void loadAppointments(struct Appointment** head, const char* filename,struct Customer* customers,struct Artist* artists,struct Service services[],int serviceCount);
                                                                                       
void printAppointment(struct Appointment* app);

#endif