#include <cstdio>
#include <cstring>
#include <fstream>
#define TABLE_SIZE 10

typedef struct {
    char name[50] = "-1";
    char address[100] = "-1";
} Contact;

typedef struct {
    char phoneNum[20] = "-1";
    Contact contact;
} HashNode;

void initHash(HashNode hashTable[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        strcpy(hashTable[i].phoneNum, "-1");
    }
}

int hashFunction(char phoneNum[]) {
    int sum = 0;
    for (int i = 0; i < strlen(phoneNum); i++) {
        sum += phoneNum[i];
    }
    return sum % TABLE_SIZE;
}

void insertContact(HashNode hashTable[], char phoneNum[], char name[], char address[]) {
    int index = hashFunction(phoneNum);
    while (strcmp(hashTable[index].phoneNum, "-1") != 0) {
        index = (index + 1) % TABLE_SIZE;
    }

    strcpy(hashTable[index].phoneNum, phoneNum);
    strcpy(hashTable[index].contact.name, name);
    strcpy(hashTable[index].contact.address, address);
}

void save(HashNode hashTable[]){
    std::ofstream ofs;
    ofs.open("contacts.txt", std::ios::out);
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        ofs<<hashTable[i].phoneNum<<"\t" <<
        hashTable[i].contact.name<<"\t" <<
        hashTable[i].contact.address<<std::endl;

    }
    ofs.close();
}

void load(HashNode* hashTable){
    std::ifstream ifs;
    ifs.open("contacts.txt", std::ios::in);
    if (ifs.is_open())
    {
        printf("�ɹ���ȡͨѶ¼������ѡ��\n");
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            ifs>>hashTable[i].phoneNum
            >>hashTable[i].contact.name
            >>hashTable[i].contact.address;
        }
    }else{
        printf("δ�ҵ�contacts.txt");
    }
    ifs.close();

}

void findContact(HashNode hashTable[], char phoneNum[]) {
    int index = hashFunction(phoneNum);
    while (strcmp(hashTable[index].phoneNum, phoneNum) != 0) {
        index = (index + 1) % TABLE_SIZE;
        if (strcmp(hashTable[index].phoneNum, "") == 0 || index == hashFunction(phoneNum)) {
            printf("δ�ҵ����ֻ������Ӧ��ͨѶ����Ϣ��\n");
            return;
        }
    }

    printf("������%s\n", hashTable[index].contact.name);
    printf("��ַ��%s\n", hashTable[index].contact.address);
}

int main() {
    HashNode hashTable[TABLE_SIZE];
    initHash(hashTable);

    while (true) {
        system("cls");
        load(hashTable);
        char name[50];
        char address[100];
        char phoneNum[20];
        int choice;
        printf("-------[1]¼�����-------\n");
        printf("-------[2]��ѯ����-------\n");
        printf("-------[3]�˳�ϵͳ-------\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                printf("�������ֻ��ţ�");
                scanf(" %s", &phoneNum);
                printf("������������");
                scanf(" %s", &name);
                printf("�������ַ��");
                scanf(" %s", &address);
                insertContact(hashTable, phoneNum, name, address);

                save(hashTable);
                system("pause");
                break;
            }
            case 2: {
                printf("�������ֻ��ţ�");
                scanf(" %s", &phoneNum);
                findContact(hashTable, phoneNum);
                printf("\n");
                system("pause");
                break;
            }
            default: {
                return 0;
            }
        }
    }
}
