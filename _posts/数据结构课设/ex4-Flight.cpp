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
    printf("航班号：%s\n", record.flightNo);
    printf("起点站：%s\n", record.departure);
    printf("终点站：%s\n", record.destination);
    printf("起飞时间：%s\n", record.departureTime);
    printf("到达时间：%s\n", record.arrivalTime);
    printf("飞机型号：%s\n", record.aircraftModel);
    printf("票价：%.2f\n", record.ticketPrice);
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
        printf("成功读取通讯录，请您选择：\n");
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
        printf("------[1]航班录入--------\n");
        printf("------[2]航班号查询------\n");
        printf("------[3]其他查询--------\n");
        printf("------[4]退出系统--------\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                printf("请输入航班号：");
                scanf(" %s", &fno);
                printf("请输入起点：");
                scanf(" %s", &depart);
                printf("请输入终点：");
                scanf(" %s", &des);
                printf("请输入起飞时间：");
                scanf(" %s", &departTime);
                printf("请输入到达时间：");
                scanf(" %s", &arriTime);
                printf("请输入飞机型号：");
                scanf(" %s", &airModel);
                printf("请输入票价：");
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
                printf("请输入航班号：");
                scanf(" %s", &fno);
                sortByFlightNo(flightRecords,numRecords);
                int i = binarySearch(flightRecords,numRecords,fno);
                if(i==-1){
                    printf("无该航班");
                }else{
                    displayFlightRecord(flightRecords[i]);
                }
                system("pause");
                break;
            }
            case 3:{
                int sort;
                system("cls");
                printf("请选择查询内容：\n");
                printf("------[1]起点--------\n");
                printf("------[2]终点--------\n");
                printf("------[3]起飞--------\n");
                printf("------[4]到达--------\n");
                printf("------[5]型号--------\n");
                printf("------[6]票价--------\n");
                printf("------[7]退出--------\n");
                scanf("%d", &sort);
                switch (sort) {
                    case 1:{
                        printf("请输入起点：");
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
                        printf("请输入终点：");
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
                        printf("请输入起飞时间：");
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
                        printf("请输入到达时间：");
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
                        printf("请输入飞机型号：");
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
                        printf("请输入票价：");
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