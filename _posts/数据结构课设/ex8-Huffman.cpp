#include <cstdio>
#include <conio.h>
#include <cstdlib>
#include <iostream>

#define MAXVAL 10000.0
struct HuffmanTreeNode{
    char data;
    double weight;
    int parent,lchild,rchild;
};
struct HuffmanTree{
    HuffmanTreeNode *node;
    int n;
};
struct Codetype{
    char *bits;
    int start;
};
void SortHufmtree(HuffmanTree *tree){
    int i,j,k;
    HuffmanTreeNode temp;
    if (tree==NULL)
        return;
    for (i=0;i<tree->n;i++)
    {
        k=i;
        for(j=i+1;j<tree->n;j++)
            if (tree->node[j].weight>tree->node[k].weight)
                k=j;
        if (k!=i)
        {
            temp=tree->node[i];
            tree->node[i]=tree->node[k];
            tree->node[k]=temp;
        }
    }
}
Codetype* HuffmanCode(HuffmanTree *tree){
    int i,j,p,k;
    Codetype *code;
    if (tree==NULL)
        return NULL;
    code=(Codetype*)malloc(tree->n*sizeof(Codetype));
    for (i=0;i<tree->n;i++)
    {
        printf("%c ",tree->node[i].data);
        code[i].bits=(char*)malloc(tree->n*sizeof(char));
        code[i].start=tree->n-1;
        j=i;
        p=tree->node[i].parent;
        while(p!=-1){
            if (tree->node[p].lchild==j)
                code[i].bits[code[i].start]='0';
            else
                code[i].bits[code[i].start]='1';

            code[i].start--;
            j=p;
            p=tree->node[p].parent;
        }
        for (k=code[i].start+1;k<tree->n;k++)
            printf("%c",code[i].bits[k]);
        printf("\n");
    }
    return code;
}
HuffmanTree* BuildHuffmanTree(HuffmanTree *tree){
    int i,j,p1,p2,m;
    float small1,small2;
    m=2*(tree->n)-1;
    for (i=tree->n;i<m;i++)
    {
        tree->node[i].parent=-1;
        tree->node[i].lchild=-1;
        tree->node[i].rchild=-1;
        tree->node[i].weight=0.0;
    }
    for (i=tree->n;i<m;i++)
    {
        small1=small2=MAXVAL;
        for (j=0;j<=i-1;j++)
        {
            if (tree->node[j].parent==-1 && tree->node[j].weight<=small1)
            {
                small1=tree->node[j].weight;
                p1=j;
            }
        }
        for (j=0;j<=i-1;j++)
        {
            if (tree->node[j].parent==-1 && tree->node[j].weight<=small2 && (j!=p1))
            {
                small2=tree->node[j].weight;
                p2=j;
            }
        }
        tree->node[p1].parent=tree->node[p2].parent=i;
        tree->node[i].weight=tree->node[p1].weight+tree->node[p2].weight;

        tree->node[i].lchild=p1;
        tree->node[i].rchild=p2;
    }
    return tree;
}
HuffmanTree* CreateHuffmanTreeFromSourceFile(){
    FILE *textfile,*datafile;
    char ch;
    int i,j=0,n=0;
    float count[128];
    HuffmanTree *tree;

    if ((textfile=fopen("1.txt","r"))==NULL){
        printf("\n�Ҳ���1.txt");
        return NULL;
    }
    for(i=0;i<128;i++)
        count[i]=0;

    ch=fgetc(textfile);
    while(!feof(textfile)){
        for(i=0;i<128;i++)
            if (ch==char(i)){
                count[i]++;
                break;
            }
        ch=fgetc(textfile);
    }

    datafile=fopen("data.txt","w");
    for (i=0;i<128;i++)
        if (count[i]!=0)
            n++;
    fprintf(datafile,"%d\n",n);
    tree=(HuffmanTree*)malloc(sizeof(HuffmanTree));
    tree->node=(HuffmanTreeNode*)malloc((2*n-1)*sizeof(HuffmanTreeNode));

    tree->n=n;

    printf("\nԴ�ļ����ַ�������Ȩֵ��Ϣ���£�\n");

    for(i=0;i<128;i++)
        if (count[i]!=0)
        {
            fprintf(datafile,"%c  %.0f\n",char(i),count[i]);
            printf("%c %.0f\n",char(i),count[i]);
            tree->node[j].data=char(i);
            tree->node[j].weight=count[i];
            tree->node[j].parent=-1;
            tree->node[j].lchild=-1;
            tree->node[j].rchild=-1;
            j++;
        }
    SortHufmtree(tree);
    BuildHuffmanTree(tree);
    fclose(textfile);
    fclose(datafile);
    printf("\n��������������ϣ��ѽ�Ȩֵ��Ϣ������data.txt\n");
    return tree;
}

HuffmanTree* CreateHuffmanTreeByInput(){
    int n;
    HuffmanTree *tree;
    int i;
    FILE *datafile;
    tree=(HuffmanTree*)malloc(sizeof(HuffmanTree));
    datafile=fopen("data.txt","w");

    printf("�������ַ�����");
    scanf("%d",&n);
    if (n<=0)
    {
        printf("\n������������\n");
        return NULL;
    }
    tree->node=(HuffmanTreeNode*)malloc((2*n-1)*sizeof(HuffmanTreeNode));
    tree->n=n;

    for (i=0;i<n;i++)
    {
        tree->node[i].parent=-1;
        tree->node[i].lchild=-1;
        tree->node[i].rchild=-1;
        tree->node[i].weight=0.0;
    }
    fprintf(datafile,"%d\n",n);
    for (i=0;i<n;i++)
    {
        printf("\n�����%d���ַ�����Ȩֵ��",i+1);
        std::cin>>tree->node[i].data;
        std::cin>>tree->node[i].weight;
        fprintf(datafile,"%c  %.3f\n",tree->node[i].data,tree->node[i].weight);
    }
    fclose(datafile);

    SortHufmtree(tree);
    BuildHuffmanTree(tree);
    printf("\n��������������ϣ��ѽ�Ȩֵ��Ϣ������data.txt\n");
    return tree;
}
HuffmanTree* CreateHuffmanTreeFromDataFile(){
    FILE *datafile;
    int i,n;
    HuffmanTree *tree;
    if ((datafile=fopen("data.txt","r"))==NULL){
        printf("\n����������δ����\n");
        return NULL;
    }

    fscanf(datafile,"%d",&n);
    fgetc(datafile);
    tree=(HuffmanTree*)malloc(sizeof(HuffmanTree));
    tree->node=(HuffmanTreeNode*)malloc((2*n-1)*sizeof(HuffmanTreeNode));
    tree->n=n;
    for (i=0;i<n;i++){
        tree->node[i].data=fgetc(datafile);
        fscanf(datafile,"%f\n",&tree->node[i].weight);
        tree->node[i].parent=-1;
        tree->node[i].lchild=-1;
        tree->node[i].rchild=-1;
    }
    fclose(datafile);

    SortHufmtree(tree);
    BuildHuffmanTree(tree);
    return tree;
}


HuffmanTree* Encoding(HuffmanTree *tree){
    FILE *textfile,*codefile;
    char ch;
    int i,j;
    Codetype *code;

    if (tree==NULL)
    {
        tree=CreateHuffmanTreeFromDataFile();
        if (tree==NULL)
            return NULL;
    }

    if ((textfile=fopen("1.txt","r"))==NULL){
        printf("\n�Ҳ����ļ�1.txt\n");
        return NULL;
    }

    printf("\nԴ�ļ���ԭ�����£�\n");
    ch=fgetc(textfile);
    while(!feof(textfile)){
        printf("%c",ch);
        ch=fgetc(textfile);
    }

    printf("\n�ַ����Ĺ������������£�\n");
    code=HuffmanCode(tree);
    codefile=fopen("CodeFile.txt","w");
    fseek(textfile,0,SEEK_SET);
    ch=fgetc(textfile);
    while (!feof(textfile))
    {
        for(i=0;i<tree->n;i++)
            if (ch==tree->node[i].data){
                for(j=code[i].start+1;j<tree->n;j++)
                    fputc(code[i].bits[j],codefile);
                break;
            }
        if (i==tree->n)
        {
            fclose(codefile);
            return NULL;
        }
        ch=fgetc(textfile);
    }
    fclose(codefile);

    printf("\n����ɹ�,�ѽ�����д��CodeFile.txt,�������£�\n");
    codefile=fopen("CodeFile.txt","r");
    ch=fgetc(codefile);
    while(!feof(codefile)){
        printf("%c",ch);
        ch=fgetc(codefile);
    }
    printf("\n");
    fclose(textfile);
    fclose(codefile);
    return tree;
}

void Decoding(HuffmanTree *tree){
    FILE *codefile,*decodefile;
    char ch;
    int i;

    if (tree==NULL){
        tree=CreateHuffmanTreeFromDataFile();
        if (tree==NULL)
            return ;
    }

    if ((codefile=fopen("CodeFile.txt","r"))==NULL){
        printf("\n�Ҳ����ļ�CodeFile.txt\n");
        return;
    }

    printf("\n�����ļ�ԭ�����£�\n");
    ch=fgetc(codefile);
    while(!feof(codefile)){
        printf("%c",ch);
        ch=fgetc(codefile);
    }

    decodefile=fopen("DecodeFile.txt","w");
    fseek(codefile,0,SEEK_SET);
    ch=fgetc(codefile);
    while(!feof(codefile))
    {
        for(i=2*tree->n-2;tree->node[i].lchild>=0 && tree->node[i].rchild>=0 && ch!=EOF;)
        {
            if(ch=='0')
                i = tree->node[i].lchild;
            else if(ch=='1')
                i = tree->node[i].rchild;
            else{
                printf("\n�����쳣�ַ�%c��������ȷ���롣\n",ch);
                return ;
            }
            if (i==-1){
                printf("\n�����뵱ǰ���������ṹ�������������ȷ���롣\n",ch);
                fclose(decodefile);
                return;
            }
            ch=fgetc(codefile);
        }
        if (tree->node[i].lchild>=0 && tree->node[i].rchild>=0){
            printf("\n�����ļ��������ݲ������������������롣\n",ch);
            fclose(decodefile);
            return;
        }

        fputc(tree->node[i].data,decodefile);
    }
    fclose(decodefile);

    printf("\n\n����ɹ��������ѱ�����DecodeFile.txt\n");
    printf("�������£�\n");
    decodefile=fopen("DecodeFile.txt","r");
    ch=fgetc(decodefile);
    while(!feof(decodefile)){
        printf("%c",ch);
        ch=fgetc(decodefile);
    }
    printf("\n");
    fclose(codefile);
    fclose(decodefile);
}

int main(){
    HuffmanTree *tree=NULL;
    int choice;
    while(true) {
        system("cls");
        printf("------[1]���ļ����б���--------\n");
        printf("------[2]��������б���--------\n");
        printf("------[3]�����ݽ�������--------\n");
        printf("------[4]�˳�������ϵͳ--------\n");
        scanf("%d", &choice);
        printf("\n");
        switch (choice)
        {
            case 1:{
                tree=CreateHuffmanTreeFromSourceFile();
                tree=Encoding(tree);
                system("pause");
                break;
            }
            case 2:{
                tree=CreateHuffmanTreeByInput();
                tree=Encoding(tree);
                system("pause");
                break;
            }
            case 3:{
                Decoding(tree);
                system("pause");
                break;
            }
            case 4:{
                return 0;
            }
            default:{
                printf("��Ч��ѡ�\n");
                system("pause");
                break;
            }
        }
    }
}

