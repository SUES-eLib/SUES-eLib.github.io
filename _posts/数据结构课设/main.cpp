#include <cstdio>
#include <cstdlib>

typedef struct Node {
    int data;
    int pos;
    struct Node* next;
} Node;

Node* createNode(int data, int pos) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->pos = pos;
    newNode->next = NULL;
    return newNode;
}

void insertAtEnd(Node** head, int data, int pos) {
    Node* newNode = createNode(data, pos);
    if (*head == NULL) {
        *head = newNode;
        newNode->next = *head;
    } else {
        Node* temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = *head;
    }
}

void printList(Node* head) {
    Node* temp = head;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

void deleteKthNode(Node** head, int k) {
    if (k == 1) {
        Node* temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }
    Node* curr = (*head)->next;
    int count = 2;
    while (curr != NULL) {
        if (count == k) {
            (*head)->next = curr->next;
            printf("���ߣ�%d ", curr->data);
            printf("λ�ã�%d\n", curr->pos);
            free(curr);
            return;
        } else {
            *head = curr;
            curr = curr->next;
            count++;
        }
    }
}

int main(){
    int N, k, pos;
    printf("�˿���(N)��");
    scanf("%d", &N);
    printf("��������(k)��");
    scanf("%d", &k);
    Node* head = NULL;
    for (int i = 1; i <= N; i++) {
        pos = i;
        insertAtEnd(&head, i, pos);
    }
    printf("����������\n");
    struct Node* current = head;
    for(int i = N; i > N/2;current = current->next, i--){
        deleteKthNode(&current, k);
    }
    printf("�Ҵ���������\n");
    printList(current);
    return 0;
}