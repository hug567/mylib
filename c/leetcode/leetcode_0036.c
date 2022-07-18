/*
 * leetcode 36: 有效的数独 [中等]
 * 2022-07-18
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
#define SUDOKU_COL_SIZE 9

bool isValidLine(char *line, int size)
{
    int i, idx;
    char times[SUDOKU_COL_SIZE] = {0};
    
    for (i = 0; i < size; i++) {
        idx = line[i] - '1';
        if (idx >= 0) {
            if (times[idx] > 0) {
                return false;
            }
            times[idx] = times[idx] + 1;
        }
    }
    return true;
}

void Fill3x3toLine(char **_board, int x, int y, char *line)
{
    int i, j, idx = 0;
#ifdef LOCAL_DEBUG
    char (*board)[SUDOKU_COL_SIZE] = (char(*)[SUDOKU_COL_SIZE])_board;
#else
    char **board = _board;
#endif

    for (i = x; i < x + 3; i++) {
        for (j = y; j < y + 3; j++) {
            line[idx] = board[i][j];
            idx++;
        }
    }
}

bool isValidSudoku(char** _board, int boardSize, int* boardColSize)
{
    int i, j;
    char line[SUDOKU_COL_SIZE];
#ifdef LOCAL_DEBUG
    char (*board)[SUDOKU_COL_SIZE] = (char(*)[SUDOKU_COL_SIZE])_board;
#else
    char **board = _board;
#endif

    for (i = 0; i < SUDOKU_COL_SIZE; i++) {
        for (j = 0; j < SUDOKU_COL_SIZE; j++) {
            line[j] = board[i][j];
        }
        if (!isValidLine(line, SUDOKU_COL_SIZE)) {
            return false;
        }
    }
    for (i = 0; i < SUDOKU_COL_SIZE; i++) {
        for (j = 0; j < SUDOKU_COL_SIZE; j++) {
            line[j] = board[j][i];
        }
        if (!isValidLine(line, SUDOKU_COL_SIZE)) {
            return false;
        }
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            Fill3x3toLine(_board, i * 3, j * 3, line);
            if (!isValidLine(line, SUDOKU_COL_SIZE)) {
                return false;
            }
        }
    }

    return true;
}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
    char board[][9] = {
            {'5','3','.','.','7','.','.','.','.'},
            {'6','.','.','1','9','5','.','.','.'},
            {'.','9','8','.','.','.','.','6','.'},
            {'8','.','.','.','6','.','.','.','3'},
            {'4','.','.','8','.','3','.','.','1'},
            {'7','.','.','.','2','.','.','.','6'},
            {'.','6','.','.','.','.','2','8','.'},
            {'.','.','.','4','1','9','.','.','5'},
            {'.','.','.','.','8','.','.','7','9'},
    };
    int boardSize = 9;
    int boardColSize[9] = {9, 9, 9, 9, 9, 9, 9, 9, 9};
    Log("is valid sudoku: %d(1)\n", isValidSudoku((char **)board, boardSize, boardColSize));
}

void TestCase2(void)
{
    char board[][9] = {
            {'8','3','.','.','7','.','.','.','.'},
            {'6','.','.','1','9','5','.','.','.'},
            {'.','9','8','.','.','.','.','6','.'},
            {'8','.','.','.','6','.','.','.','3'},
            {'4','.','.','8','.','3','.','.','1'},
            {'7','.','.','.','2','.','.','.','6'},
            {'.','6','.','.','.','.','2','8','.'},
            {'.','.','.','4','1','9','.','.','5'},
            {'.','.','.','.','8','.','.','7','9'},
    };
    int boardSize = 9;
    int boardColSize[9] = {9, 9, 9, 9, 9, 9, 9, 9, 9};
    Log("is valid sudoku: %d(0)\n", isValidSudoku((char **)board, boardSize, boardColSize));
}

void TestCase3(void)
{
    char board[][9] = {
            {'.','.','4','.','.','.','6','3','.'},
            {'.','.','.','.','.','.','.','.','.'},
            {'5','.','.','.','.','.','.','9','.'},
            {'.','.','.','5','6','.','.','.','.'},
            {'4','.','3','.','.','.','.','.','1'},
            {'.','.','.','7','.','.','.','.','.'},
            {'.','.','.','5','.','.','.','.','.'},
            {'.','.','.','.','.','.','.','.','.'},
            {'.','.','.','.','.','.','.','.','.'},
    };
    int boardSize = 9;
    int boardColSize[9] = {9, 9, 9, 9, 9, 9, 9, 9, 9};
    Log("is valid sudoku: %d(0)\n", isValidSudoku((char **)board, boardSize, boardColSize));
}

int main(void)
{
    TestCase1();
    TestCase2();
    TestCase3();
    return 0;
}