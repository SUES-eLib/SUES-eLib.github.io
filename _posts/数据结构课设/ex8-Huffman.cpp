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
        printf("\n找不到1.txt");
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

    printf("\n源文件的字符集及其权值信息如下：\n");

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
    printf("\n哈夫曼树建立完毕，已将权值信息保存至data.txt\n");
    return tree;
}

HuffmanTree* CreateHuffmanTreeByInput(){
    int n;
    HuffmanTree *tree;
    int i;
    FILE *datafile;
    tree=(HuffmanTree*)malloc(sizeof(HuffmanTree));
    datafile=fopen("data.txt","w");

    printf("请输入字符数：");
    scanf("%d",&n);
    if (n<=0)
    {
        printf("\n您的输入有误。\n");
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
        printf("\n输入第%d个字符及其权值：",i+1);
        std::cin>>tree->node[i].data;
        std::cin>>tree->node[i].weight;
        fprintf(datafile,"%c  %.3f\n",tree->node[i].data,tree->node[i].weight);
    }
    fclose(datafile);

    SortHufmtree(tree);
    BuildHuffmanTree(tree);
    printf("\n哈夫曼树建立完毕，已将权值信息保存至data.txt\n");
    return tree;
}
HuffmanTree* CreateHuffmanTreeFromDataFile(){
    FILE *datafile;
    int i,n;
    HuffmanTree *tree;
    if ((datafile=fopen("data.txt","r"))==NULL){
        printf("\n哈夫曼树尚未建立\n");
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
        printf("\n找不到文件1.txt\n");
        return NULL;
    }

    printf("\n源文件的原文如下：\n");
    ch=fgetc(textfile);
    while(!feof(textfile)){
        printf("%c",ch);
        ch=fgetc(textfile);
    }

    printf("\n字符集的哈夫曼编码如下：\n");
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

    printf("\n编码成功,已将代码写入CodeFile.txt,代码如下：\n");
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
        printf("\n找不到文件CodeFile.txt\n");
        return;
    }

    printf("\n代码文件原文如下：\n");
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
                printf("\n存在异常字符%c，不能正确译码。\n",ch);
                return ;
            }
            if (i==-1){
                printf("\n编码与当前哈夫曼树结构不相符，不能正确译码。\n",ch);
                fclose(decodefile);
                return;
            }
            ch=fgetc(codefile);
        }
        if (tree->node[i].lchild>=0 && tree->node[i].rchild>=0){
            printf("\n代码文件编码内容不完整，不能完整译码。\n",ch);
            fclose(decodefile);
            return;
        }

        fputc(tree->node[i].data,decodefile);
    }
    fclose(decodefile);

    printf("\n\n译码成功，译文已保存至DecodeFile.txt\n");
    printf("译文如下：\n");
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
        printf("------[1]对文件进行编码--------\n");
        printf("------[2]对输入进行编码--------\n");
        printf("------[3]对数据进行译码--------\n");
        printf("------[4]退出哈夫曼系统--------\n");
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
                printf("无效的选项。\n");
                system("pause");
                break;
            }
        }
    }
}

