#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

struct Contact {
    char name[40], phone[15];
};

struct Contact list[MAX];
int count = 0;

// convert string to lowercase
void toLower(char *s) {
    for (; *s; s++) *s = tolower(*s);
}

// find contact index by name (case-insensitive)
int find(char *name) {
    char n1[40], n2[40];
    strcpy(n1, name); toLower(n1);
    for (int i = 0; i < count; i++) {
        strcpy(n2, list[i].name); toLower(n2);
        if (strcmp(n1, n2) == 0) return i;
    }
    return -1;
}

// add contact
void add() {
    if (count >= MAX) return;
    struct Contact c;
    printf("Name: "); fgets(c.name, 40, stdin); c.name[strcspn(c.name, "\n")] = 0;
    printf("Phone: "); fgets(c.phone, 15, stdin); c.phone[strcspn(c.phone, "\n")] = 0;
    if (find(c.name) != -1) { printf("Already exists!\n"); return; }
    list[count++] = c;
    printf("Added!\n");
}

// search
void search() {
    char name[40];
    printf("Search name: "); fgets(name, 40, stdin); name[strcspn(name, "\n")] = 0;
    int i = find(name);
    if (i == -1) printf("Not found!\n");
    else printf("%s - %s\n", list[i].name, list[i].phone);
}

// update
void update() {
    char name[40];
    printf("Update name: "); fgets(name, 40, stdin); name[strcspn(name, "\n")] = 0;
    int i = find(name);
    if (i == -1) { printf("Not found!\n"); return; }
    printf("Old phone: %s\nNew phone: ", list[i].phone);
    fgets(list[i].phone, 15, stdin);
    list[i].phone[strcspn(list[i].phone, "\n")] = 0;
    printf("Updated!\n");
}

// list all
void listAll() {
    if (count == 0) { printf("No contacts.\n"); return; }
    printf("\n--- Contact List ---\n");
    for (int i = 0; i < count; i++)
        printf("%d. %s - %s\n", i + 1, list[i].name, list[i].phone);
}

// reset
void reset() {
    count = 0;
    printf("All contacts cleared!\n");
}

// main menu
int main() {
    int ch;
    char line[10];
    printf("=== CONTACT BOOK ===\n");
    while (1) {
        printf("\n1.Add 2.Search 3.Update 4.List 5.Reset 6.Exit\nChoice: ");
        if (!fgets(line, 10, stdin)) break;
        sscanf(line, "%d", &ch);
        switch (ch) {
            case 1: add(); break;
            case 2: search(); break;
            case 3: update(); break;
            case 4: listAll(); break;
            case 5: reset(); break;
            case 6: return 0;
            default: printf("Invalid!\n");
        }
    }
}