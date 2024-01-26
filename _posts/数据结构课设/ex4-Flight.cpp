#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#define MAX_FLIGHTS 100

typedef struct {
    char flightNo[10] = "-1";
    char departure[20] = "-1";
    char destination[20] = "-1";
    char departureTime[10] = "-1";
    char arrivalTime[10] = "-1";
    char aircraftModel[20] = "-1";
    float ticketPrice = 0;
} FlightRecord;

int binarySearch(FlightRecord records[], int numRecords, char searchFlightNo[]) {
    int low = 0, high = numRecords - 1, mid;
    
    while (low <= high) {
        mid = (low + high) / 2;
        if (strcmp(records[mid].flightNo, searchFlightNo) == 0) {
            return mid;
        }
        if (strcmp(records[mid].flightNo, searchFlightNo) < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

void sortByFlightNo(FlightRecord records[], int numRecords) {
    int i, j;
    FlightRecord temp;
    for (i = 0; i < numRecords - 1; i++) {
        for (j = 0; j < numRecords - i - 1; j++) {
            if (strcmp(records[j].flightNo, records[j + 1].flightNo) > 0) {
                temp = records[j];
                records[j] = records[j + 1];
                records[j + 1] = temp;
            }
        }
    }
}

void displayFlightRecord(FlightRecord record) {
    printf("����ţ�%s\n", record.flightNo);
    printf("���վ��%s\n", record.departure);
    printf("�յ�վ��%s\n", record.destination);
    printf("���ʱ�䣺%s\n", record.departureTime);
    printf("����ʱ�䣺%s\n", record.arrivalTime);
    printf("�ɻ��ͺţ�%s\n", record.aircraftModel);
    printf("Ʊ�ۣ�%.2f\n", record.ticketPrice);
    printf("-----------------------------\n");
}

void save(int numRecords, FlightRecord fight[]){
    std::ofstream ofs;
    ofs.open("flight.txt", std::ios::out);
    ofs<<numRecords<<std::endl;
    for (int i = 0; i < numRecords; i++)
    {
        ofs<<fight[i].flightNo<<"\t"
            <<fight[i].departure<<"\t"
            <<fight[i].destination<<"\t"
            <<fight[i].departureTime<<"\t"
            <<fight[i].arrivalTime<<"\t"
            <<fight[i].aircraftModel<<"\t"
            <<fight[i].ticketPrice<<std::endl;
    }
    ofs.close();
}

void load(int* numRecords, FlightRecord* fight) {
    std::ifstream ifs;
    ifs.open("flight.txt", std::ios::in);
    if (ifs.is_open()) {
        printf("�ɹ���ȡͨѶ¼������ѡ��\n");
        ifs>>*numRecords;
        for (int i = 0; i < *numRecords; i++) {
            ifs>>fight[i].flightNo
                >>fight[i].departure
                >>fight[i].destination
                >>fight[i].departureTime
                >>fight[i].arrivalTime
                >>fight[i].aircraftModel
                >>fight[i].ticketPrice;
        }
    } else {
        printf("flight.txt");
    }
    ifs.close();
}

int main() {
    FlightRecord flightRecords[MAX_FLIGHTS];
    int numRecords;
    while (true) {
        system("cls");
        load(&numRecords, flightRecords);
        char fno[10];
        char depart[20];
        char des[20];
        char departTime[10];
        char arriTime[10];
        char airModel[20];
        float tkPrice;

        int choice;
        printf("------[1]����¼��--------\n");
        printf("------[2]����Ų�ѯ------\n");
        printf("------[3]������ѯ--------\n");
        printf("------[4]�˳�ϵͳ--------\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                printf("�����뺽��ţ�");
                scanf(" %s", &fno);
                printf("��������㣺");
                scanf(" %s", &depart);
                printf("�������յ㣺");
                scanf(" %s", &des);
                printf("���������ʱ�䣺");
                scanf(" %s", &departTime);
                printf("�����뵽��ʱ�䣺");
                scanf(" %s", &arriTime);
                printf("������ɻ��ͺţ�");
                scanf(" %s", &airModel);
                printf("������Ʊ�ۣ�");
                scanf("%f", &tkPrice);

                strcpy(flightRecords[numRecords].flightNo,fno);
                strcpy(flightRecords[numRecords].departure,depart);
                strcpy(flightRecords[numRecords].destination,des);
                strcpy(flightRecords[numRecords].departureTime,departTime);
                strcpy(flightRecords[numRecords].aircraftModel,airModel);
                strcpy(flightRecords[numRecords].arrivalTime,arriTime);
                flightRecords[numRecords].ticketPrice=tkPrice;
                numRecords++;

                save(numRecords, flightRecords);
                system("pause");
                break;
            }
            case 2: {
                printf("�����뺽��ţ�");
                scanf(" %s", &fno);
                sortByFlightNo(flightRecords,numRecords);
                int i = binarySearch(flightRecords,numRecords,fno);
                if(i==-1){
                    printf("�޸ú���");
                }else{
                    displayFlightRecord(flightRecords[i]);
                }
                system("pause");
                break;
            }
            case 3:{
                int sort;
                system("cls");
                printf("��ѡ���ѯ���ݣ�\n");
                printf("------[1]���--------\n");
                printf("------[2]�յ�--------\n");
                printf("------[3]���--------\n");
                printf("------[4]����--------\n");
                printf("------[5]�ͺ�--------\n");
                printf("------[6]Ʊ��--------\n");
                printf("------[7]�˳�--------\n");
                scanf("%d", &sort);
                switch (sort) {
                    case 1:{
                        printf("��������㣺");
                        scanf(" %s", &depart);
                        for (int i = 0; i < numRecords; ++i) {
                            if(strcmp(flightRecords[i].departure, depart) == 0){
                                displayFlightRecord(flightRecords[i]);
                            }
                        }
                        system("pause");
                        break;
                    }
                    case 2:{
                        printf("�������յ㣺");
                        scanf(" %s", &des);
                        for (int i = 0; i < numRecords; ++i) {
                            if(strcmp(flightRecords[i].destination, des) == 0){
                                displayFlightRecord(flightRecords[i]);
                            }
                        }
                        system("pause");
                        break;
                    }
                    case 3:{
                        printf("���������ʱ�䣺");
                        scanf(" %s", &departTime);
                        for (int i = 0; i < numRecords; ++i) {
                            if(strcmp(flightRecords[i].departureTime, departTime) == 0){
                                displayFlightRecord(flightRecords[i]);
                            }
                        }
                        system("pause");
                        break;
                    }
                    case 4:{
                        printf("�����뵽��ʱ�䣺");
                        scanf(" %s", &arriTime);
                        for (int i = 0; i < numRecords; ++i) {
                            if(strcmp(flightRecords[i].arrivalTime, arriTime) == 0){
                                displayFlightRecord(flightRecords[i]);
                            }
                        }
                        system("pause");
                        break;
                    }
                    case 5:{
                        printf("������ɻ��ͺţ�");
                        scanf(" %s", &airModel);
                        for (int i = 0; i < numRecords; ++i) {
                            if(strcmp(flightRecords[i].aircraftModel, airModel) == 0){
                                displayFlightRecord(flightRecords[i]);
                            }
                        }
                        system("pause");
                        break;
                    }
                    case 6:{
                        printf("������Ʊ�ۣ�");
                        scanf("%f", &tkPrice);
                        for (int i = 0; i < numRecords; ++i) {
                            if(flightRecords[i].ticketPrice==tkPrice){
                                displayFlightRecord(flightRecords[i]);
                            }
                        }
                        system("pause");
                        break;
                    }
                    default:{
                        system("pause");
                        break;
                    }
                }
            }
            default: {
                return 0;
            }
        }
    }
}