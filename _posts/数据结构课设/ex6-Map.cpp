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
        {"��ͨ��¥","ȫ��Ϊ�ִ���ͨ���ģ�������ҪΪ�������������������ѧԺ��ʵ���ң��Լ������칫������\n"},
        {"����","�Ϻ����ɽ����㸻��·2793�š�\n"},
        {"ʵѵ����","����ʵѵ��������¥������ѧ���ճ�ʹ�û�����ʵ��������γ̵Ĺ��ܡ�\n"},
        {"ͼ���","�佨�����Ϊ27000��ƽ����ʵ��ȫ���ܽ��ĺͼ������������7�����ĺ�һ��רҵ�����Ҽ�1��������⡣\n"},
        {"����¥","��֯��װѧԺ���������ѧԺ����¥��\n"},
        {"��ʳ��","���������������ʳ�ã���������ʳ�á�����ʳ�á�\n"},
        {"����","�Ϻ����ɽ����Ļ�·800Ū��\n"},
        {"����¥","�׳��齫¥����һ��19��¥�ߵ���¥��3��ȹ¥��ѧУ�󲿷ֵİ칫���Ŷ��ڴ�¥��\n"},
        {"����","�Ϻ����ɽ�������·333�ţ�ΪѧУ���š�\n"},
        {"��ѧ¥","����A~F6��¥���е��󲿷��ճ���ѧ������\n"},
        {"һʳ��","�����ѧ¥�����ʳ�ã������˽̹�ʳ�á�\n"}
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

        // ���¾�������
        for (int i = 0; i < MAX_NODES; i++) {
            if (!visited[i] && adjacencyMatrix[minIndex][i] != 0x3f
                && dist[minIndex] + adjacencyMatrix[minIndex][i] < dist[i]) {
                dist[i] = dist[minIndex] + adjacencyMatrix[minIndex][i];
                last[i] = minIndex;
            }
        }
    }
    printf("�� %s �� %s ����̾���: %d\n", nodes[end].name, nodes[start].name, dist[end]);
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
    printf("   1.����\n\n");
    printf("0.��ͨ¥ 2.ʵѵ¥ 8.����¥ 9.����\n\n");
    printf("   3.ͼ���\n\n");
    printf("   4.����¥    9.��ѧ¥  10.һʳ��\n\n");
    printf("5.��ʳ��\n\n");
    printf("        6.����\n\n");
}

int main() {
    while (true) {
        system("cls");
        mapshow();
        int choice;
        printf("-------[1]�ڵ��ѯ-------\n");
        printf("-------[2]�ڵ㵼��-------\n");
        printf("-------[3]�˳���ͼ-------\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                printf("����Ҫ��ѯ�Ľڵ���ţ�");
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
                    printf("�޸ýڵ�");
                }
                else {
                    printf("\n%d��λ�ã�", bfs);
                    printf("%s ", nodes[bfs].name);
                    printf("%s", nodes[bfs].description.c_str());
                }
                system("pause");
                break;
            }
            case 2: {
                printf("\n���뵼����� �յ���ţ�");
                int startNode, endNode;
                scanf("%d %d", &startNode, &endNode);
                dijkstra(endNode, startNode);
                printf("�� %s �� %s �����·��: ", nodes[startNode].name, nodes[endNode].name);
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