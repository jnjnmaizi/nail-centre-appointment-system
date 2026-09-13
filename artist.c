#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "artist.h"

void addArtist(Artist** head, int id, const char *name, int Ctype, const char *contactValue) {
    Artist *newArtist = (Artist *)malloc(sizeof(Artist));

    if (!newArtist) {
        printf("Memory allocation failed.\n");
        return;
    }

    newArtist->id = id;
    strcpy(newArtist->name, name);
    newArtist->Ctype = Ctype;

    switch (Ctype) {
        case 1:
            strcpy(newArtist->contact.phone, contactValue);
            break;

        case 2:
            strcpy(newArtist->contact.nationalId, contactValue);
            break;

        case 3:
            strcpy(newArtist->contact.address, contactValue);
            break;
    }

    newArtist->next = *head;
    *head = newArtist;

    printf("Artist with ID: %d added successfully. \n", newArtist->id);
}

void deleteArtist(Artist** head, int id) {
    Artist *cur = *head;
    Artist *prev = NULL;

    while (cur) {
        if (cur->id == id) {
            if (prev)
                prev->next = cur->next;
            else
                *head = cur->next;

            free(cur);
            printf("Artist deleted successfully.\n");
            return;
        }

        prev = cur;
        cur = cur->next;
    }

    printf("Artist not found.\n");
}

Artist *findArtist(Artist* head, int id) {
    Artist *cur = head;

    while (cur) {
        if (cur->id == id)
            return cur;

        cur = cur->next;
    }

    return NULL;
}

void printArtists(Artist* head) {
    if (!head) {
        printf("No artists found.\n");
        return;
    }

    printf("\n%-6s %-20s %-12s %-30s\n",
           "ID", "Name", "Type", "Contact");
    printf("%-6s %-20s %-12s %-30s\n",
           "------", "--------------------", "------------", "------------------------------");

    Artist *cur = head;
    while (cur) {
        char *typeStr = "Unknown";  // ← always initialized (fixes undefined behavior)
        char *info    = "";

        switch (cur->Ctype) {
            case 1: typeStr = "Phone";       info = cur->contact.phone;      break;
            case 2: typeStr = "National ID"; info = cur->contact.nationalId; break;
            case 3: typeStr = "Address";     info = cur->contact.address;    break;
        }

        printf("%-6d %-20s %-12s %-30s\n",
               cur->id, cur->name, typeStr, info);

        cur = cur->next;
    }
    printf("\n");
}

void freeArtists(Artist* head) {
    Artist *temp;

    while (head!= NULL) {
        temp=head;
        head=head->next;
        free(temp);
    }
}

void loadArtists(Artist** head, const char *filename) {
    FILE *fp = fopen(filename, "r");

    if (!fp)
        return;

    int id, type;
    char name[MAX_NAME_LEN];
    char contact[MAX_ADDR_LEN];

    while (fscanf(fp, "%d|%49[^|]|%d|%99[^\n]\n",
                  &id, name, &type, contact) == 4) {

        addArtist(head, id, name, type, contact);
    }

    fclose(fp);
}

void saveArtists(Artist* head, const char *filename) {
    FILE *fp = fopen(filename, "w");

    if (!fp) {
        printf("Error saving artists.\n");
        return;
    }

    while (head != NULL) {
        fprintf(fp, "%d|%s|%d|",
                head->id,
                head->name,
                head->Ctype);

        if (head->Ctype == 1)
            fprintf(fp, "%s\n", head->contact.phone);

        else if (head->Ctype == 2)
            fprintf(fp, "%s\n", head->contact.nationalId);

        else
            fprintf(fp, "%s\n", head->contact.address);

        head = head->next;
    }

    fclose(fp);
}