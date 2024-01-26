#include <cstdio>
#define N 8

void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c  ", board[i][j] ? 'Q' : '-');
        }
        printf("\n");
    }
}

bool isSafe(int board[N][N], int row, int col) {
    int i, j;
    // 检查列
    for (i = 0; i < row; i++)
        if (board[i][col])
            return false;
    // 左上对角线
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;
    // 右上对角线
    for (i = row, j = col; i >= 0 && j < N; i--, j++)
        if (board[i][j])
            return false;
    return true;
}

bool solveNQueens(int board[N][N], int row) {
    if (row == N)
        return true;
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row][col] = 1;
            if (solveNQueens(board, row + 1))
                return true;
            board[row][col] = 0;
        }
    }
    return false;
}

int main() {
    int board[N][N] = {0};
    printf("请在第一行选择一列作为皇后的初始坐标，输入纵坐标：\n");
    int x;
    scanf("%d", &x);
    board[0][x] = 1;
    if (solveNQueens(board, 1)) {
        printBoard(board);
    }
    return 0;
}
