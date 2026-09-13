#ifndef ARTIST_H
#define ARTIST_H

#define MAX_NAME_LEN 50
#define MAX_PHONE_LEN 20
#define MAX_NATID_LEN 20
#define MAX_ADDR_LEN 100

typedef union {
    char phone[MAX_PHONE_LEN];
    char nationalId[MAX_NATID_LEN];
    char address[MAX_ADDR_LEN];
} ContactInfo;

typedef struct Artist {
    int id;
    char name[MAX_NAME_LEN];
    int Ctype;
    ContactInfo contact;
    struct Artist *next;
} Artist;

void addArtist(Artist** head, int id, const char *name, int Ctype, const char *contactValue);
void deleteArtist(Artist** head, int id);
Artist *findArtist(Artist* head, int id);
void printArtists(Artist* head);
void freeArtists(Artist* head);
void loadArtists(Artist** head, const char *filename);
void saveArtists(Artist* head, const char *filename);

#endif
