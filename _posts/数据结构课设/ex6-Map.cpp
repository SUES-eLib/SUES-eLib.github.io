#include <cstdio>
#include <string>
#define MAX_NODES 11

typedef struct {
    char name[50];
    std::string description;
} Node;

int adjacencyMatrix[MAX_NODES][MAX_NODES]={
        {0,1,2,3,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f},
        {1,0,1,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f},
        {2,1,0,3,0x3f,0x3f,0x3f,5,0x3f,7,0x3f},
        {3,0x3f,3,0,4,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f},
        {0x3f,0x3f,0x3f,4,0,6,6,0x3f,0x3f,5,0x3f},
        {0x3f,0x3f,0x3f,0x3f,6,0,0x3f,0x3f,0x3f,0x3f,0x3f},
        {0x3f,0x3f,0x3f,0x3f,6,0x3f,0,0x3f,0x3f,0x3f,0x3f},
        {0x3f,0x3f,5,0x3f,0x3f,0x3f,0x3f,0,2,5,0x3f},
        {0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,2,0,0x3f,6},
        {0x3f,0x3f,7,0x3f,5,0x3f,0x3f,5,0x3f,0,0x3f},
        {0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,6,2,0}
};

Node nodes[MAX_NODES]={
        {"交通大楼","全称为现代交通中心，其中主要为机汽、轨道、电气三个学院的实验室，以及行政办公场所。\n"},
        {"北门","上海市松江区广富林路2793号。\n"},
        {"实训中心","工程实训中心所属楼，满足学生日常使用机房、实践操作类课程的功能。\n"},
        {"图书馆","其建筑面积为27000余平方，实行全开架借阅和计算机管理，共有7个借阅合一的专业阅览室及1个地下书库。\n"},
        {"艺术楼","纺织服装学院、艺术设计学院所属楼。\n"},
        {"二食堂","离宿舍区最近最大的食堂，包括清真食堂、飞行食堂。\n"},
        {"南门","上海市松江区文汇路800弄。\n"},
        {"行政楼","俗称麻将楼，有一个19层楼高的主楼和3栋裙楼，学校大部分的办公部门都在此楼。\n"},
        {"东门","上海市松江区龙腾路333号，为学校正门。\n"},
        {"教学楼","共有A~F6栋楼，承担大部分日常教学工作。\n"},
        {"一食堂","距离教学楼最近的食堂，包括了教工食堂。\n"}
};

bool visited[MAX_NODES];
int dist[MAX_NODES];
int last[MAX_NODES];

typedef struct {
    int queue[MAX_NODES];
    int front, rear;
} Queue;

void initQueue(Queue* q) {
    q->front = 0;
    q->rear = -1;
}

bool isQueueEmpty(Queue* q) {
    return (q->front > q->rear);
}

void enqueue(Queue* q, int node) {
    q->queue[++(q->rear)] = node;
}

int dequeue(Queue* q) {
    return q->queue[(q->front)++];
}

int breadthFirstSearch(int eNode, int numNodes) {
    Queue q;
    initQueue(&q);
    printf("BFS: ");
    visited[0] = true;
    enqueue(&q, 0);
    while (!isQueueEmpty(&q)) {
        int currentNode = dequeue(&q);
        printf("%d ", currentNode);
        if(currentNode==eNode) return currentNode;
        for (int i = 0; i < numNodes; i++) {
            if (adjacencyMatrix[currentNode][i]!=0x3f && !visited[i]) {
                enqueue(&q, i);
                visited[i] = true;
            }
        }
    }
    return -1;
}

void depthFirstSearch(int startNode, int eNode, int numNodes) {
    visited[startNode] = true;
    printf("%d ", startNode);
    for (int i = 0; i < numNodes; i++) {
        if (adjacencyMatrix[startNode][i]!=0x3f && !visited[i]) {
            depthFirstSearch(i, eNode, numNodes);
        }
    }

}

void dijkstra(int start, int end) {
    for (int i = 0; i < MAX_NODES; i++) {
        dist[i] = 0x3f;
        visited[i] = false;
    }

    dist[start] = 0;

    for (int count = 0; count < MAX_NODES - 1; count++) {
        int minDist = 0x3f;
        int minIndex = -1;

        for (int i = 0; i < MAX_NODES; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                minIndex = i;
            }
        }

        if (minIndex == -1) {
            break;
        }

        visited[minIndex] = true;

        // 更新距离数组
        for (int i = 0; i < MAX_NODES; i++) {
            if (!visited[i] && adjacencyMatrix[minIndex][i] != 0x3f
                && dist[minIndex] + adjacencyMatrix[minIndex][i] < dist[i]) {
                dist[i] = dist[minIndex] + adjacencyMatrix[minIndex][i];
                last[i] = minIndex;
            }
        }
    }
    printf("从 %s 到 %s 的最短距离: %d\n", nodes[end].name, nodes[start].name, dist[end]);
}

int way(int start, int end){
    if(last[end] == start){
        printf("%s ", nodes[start].name);
        return start;
    }else{
        printf("%s ", nodes[last[end]].name);
        return way(start, last[end]);
    }
}

void mapshow(){
    printf("   1.北门\n\n");
    printf("0.交通楼 2.实训楼 8.行政楼 9.东门\n\n");
    printf("   3.图书馆\n\n");
    printf("   4.艺术楼    9.教学楼  10.一食堂\n\n");
    printf("5.二食堂\n\n");
    printf("        6.南门\n\n");
}

int main() {
    while (true) {
        system("cls");
        mapshow();
        int choice;
        printf("-------[1]节点查询-------\n");
        printf("-------[2]节点导航-------\n");
        printf("-------[3]退出地图-------\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                printf("输入要查询的节点序号：");
                int eNode;
                scanf("%d", &eNode);

                for (int i = 0; i < MAX_NODES; i++) {
                    visited[i] = false;
                }
                int bfs = breadthFirstSearch(eNode, MAX_NODES);

                for (int i = 0; i < MAX_NODES; i++) {
                    visited[i] = false;
                }

                printf("\nDFS: ");
                depthFirstSearch(0, eNode, MAX_NODES);

                if (bfs > 10 || bfs < 0) {
                    printf("无该节点");
                }
                else {
                    printf("\n%d号位置：", bfs);
                    printf("%s ", nodes[bfs].name);
                    printf("%s", nodes[bfs].description.c_str());
                }
                system("pause");
                break;
            }
            case 2: {
                printf("\n输入导航起点 终点序号：");
                int startNode, endNode;
                scanf("%d %d", &startNode, &endNode);
                dijkstra(endNode, startNode);
                printf("从 %s 到 %s 的最短路径: ", nodes[startNode].name, nodes[endNode].name);
                printf("%s ", nodes[startNode].name);
                way(endNode, startNode);
                printf("\n");
                system("pause");
                break;
            }
            default: {
                system("cls");
                return 0;
            }
        }
    }
}