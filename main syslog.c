#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Ba�l� liste d���m� yap�s�
typedef struct Node {
    char log_entry[1024];   // Syslog girdisini tutacak alan
    struct Node *next;      // Sonraki d���me i�aret�i
} Node;

// Ba�l� listeyi ba�latma
Node* create_node(const char* log_entry) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Bellek ay�rma hatas�!\n");
        return NULL;
    }
    strncpy(new_node->log_entry, log_entry, sizeof(new_node->log_entry));
    new_node->next = NULL;
    return new_node;
}

// Ba�l� listeye yeni bir d���m ekleme
void append(Node** head, const char* log_entry) {
    Node* new_node = create_node(log_entry);
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

// Ba�l� listeyi yazd�rma
void print_list(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%s\n", temp->log_entry);
        temp = temp->next;
    }
}

// Belle�i temizleme
void free_list(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Syslog dosyas�n� okuma
void read_syslog(const char* filepath, Node** head) {
    FILE* file = fopen(filepath, "r");
    if (file == NULL) {
        printf("Dosya a��lamad�: %s\n", filepath);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        append(head, line);
    }

    fclose(file);
}

int main() {
    Node* syslog_list = NULL;

    // Syslog dosyas�n� oku ve ba�l� listeye ekle
    read_syslog("/var/log/syslog", &syslog_list);

    // Ba�l� listeyi yazd�r
    printf("Syslog Entries:\n");
    print_list(syslog_list);

    // Belle�i temizle
    free_list(syslog_list);

    return 0;
}
