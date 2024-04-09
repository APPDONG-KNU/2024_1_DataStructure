## Sparse Matrix
아래와 같은 구조체를 선언한 다음에
```c
#define MAX_TERMS 101
typedef struct  {
    int col;
    int row;
    int value;
} term;
term a[MAX_TERMS];
```
a[0]에는 sparse matrix의 row와 col의 개수, 0이 아닌 항의 개수를 저장한다. 나머지는 row와 col 번호, 그리고 그 위치에 해당하는 value를 저장한다.
| |row|col|value|
|:--:|--:|--:|--:|
|a[0]|6|6|8|
|a[1]|0|0|15|
|a[2]|0|3|22|
|a[3]|0|5|-15|
|a[4]|1|1|11|
|a[5]|1|2|3|
|a[6]|2|3|-6|
|a[7]|4|0|91|
|a[8]|5|2|28|

### Transpose
```c
void transpose(term a[], term b[]) {
    int n, i, j, currentb;
    n = a[0].value;
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = n;
    if (n > 0) {
        currentb = 1;
        for (i = 0; i < a[0].col; i++)
            for (j = 1; j <= n; j++)
                if (a[j].col == i) {
                    b[currentb].row = a[j].col;
                    b[currentb].col = a[j].row;
                    b[currentb].value = a[j].value;
                    currentb++;
                }
    }
}
```
a의 row와 col을 바꾸어서 row 기준으로 정렬을 시켜서 b에 저장한다.

### Fast Transpose
```c
void fastTranspose(term a[], term b[]) {
    int rowTerms[MAX_COL], startingPos[MAX_COL];
    int i, j, numCols = a[0].col, numTerms = a[0].value;
    b[0].row = numCols; b[0].col = a[0].row; b[0].value = numTerms;
    if (numTerms > 0) {
        for (i = 0; i < numCols; i++) rowTerms[i] = 0;    // rowTerms를 0으로 초기화
        for (i = 1; i < numTerms; i++) rowTerms[a[i].col]++;    // transpose하면 col이 row가 되므로 a[0]에서 col에 i의 개수를 저장
        startingPos[0] = 1;
        for (i = 0; i < numCols; i++) startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];

        for (i = 1; i <= numTerms; i++) {
            j = startingPos[a[i].col]++;
            b[j].row = a[i].col; b[j].col = a[i].row;
            b[j].value = a[i].value;
        }
    }
}
```
![image](https://github.com/APPDONG-KNU/2024_1_DataStructure/assets/108786142/8100b5d8-9eb2-4971-a507-164385f7fd29)

0부터 순서대로 줄을 세우면 첫 번째 startingPos[i]는 b에서 i를 row 값으로 갖는 원소가 첫 번째 등장하게 될 index를 나타내게 된다.
해당 index를 저장하고 나면 startingPos[a[i].col]++를 하기 때문에 그 값이 증가한다.

