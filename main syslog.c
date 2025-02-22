#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Bagli liste dugumu yapisi
typedef struct Node {
    char log_entry[1024];   // Syslog girdisini tutacak alan
    struct Node *next;      // Sonraki dugume isaretci
} Node;

// Yeni bir dugum olusturma fonksiyonu
Node* create_node(const char* log_entry) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Bellek ayirma hatasi!\n");
        return NULL;
    }
    strncpy(new_node->log_entry, log_entry, sizeof(new_node->log_entry));
    new_node->next = NULL;
    return new_node;
}

// Bagli listeye yeni bir dugum ekleme fonksiyonu
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

// Bagli listeyi yazdirma fonksiyonu
void print_list(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%s\n", temp->log_entry);
        temp = temp->next;
    }
}

// Bellek temizleme fonksiyonu
void free_list(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Syslog dosyasini okuma fonksiyonu
void read_syslog(const char* filepath, Node** head) {
    FILE* file = fopen(filepath, "r");
    if (file == NULL) {
        printf("Dosya acilamadi: %s\n", filepath);
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

    // Syslog dosyasini oku ve bagli listeye ekle
    read_syslog("/var/log/syslog", &syslog_list);

    // Bagli listeyi yazdir
    printf("Syslog Girdileri:\n");
    print_list(syslog_list);

    // Bellek temizleme
    free_list(syslog_list);

    return 0;
}

