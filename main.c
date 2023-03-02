#include<stdio.h>
#include<stdbool.h>
/* Sudoku dimension */
const int rows = 9;
const int cols = 9;
/* Helper variables */
bool isValidSudoku = false;
void red () {
 printf("\033[0;31m");
}
void purple() {
 printf("\033[0;95m");
}
void green () {
printf("\033[0;32m");
}
void blue () {
printf("\033[0;34m");
}
void reset () {
 printf("\033[0m");
}
void newLine(){
printf("\n");
}
void greet(){
newLine();
purple();
printf("|-------------------------|\n");
printf("|Welcome to sudoku solver |\n");
printf("|-------------------------|\n");
reset();
newLine();
}
void printInstructions(bool isInValid){
red();
if(!isInValid){
printf("Instructions : \n");
printf("1) Please enter zero incase of blank spaces\n");
printf("2) Make sure you enter total of 81 elements\n");
printf("3) Enter elements only between 0 to 9\n");
}else{
printf("Rules : \n");
printf("1)Every row of 9 numbers must include all digits 1 through 9 in any order\n");
printf("2)Every column of 9 numbers must include all digits 1 through 9 in any order\n");
printf("3)Every 3 by 3 subsection of the 9 by 9 square must include all digits 1 through 9\n");
}
newLine();
reset();
}
void printBoard(int board[rows][cols], char colorChoice){
int i, j;
purple();
if(colorChoice == 'p'){
newLine();
printf("The state of board before : ");
newLine();
newLine();
}else if(colorChoice == 'g'){
green();
newLine();
printf("The state of board after : ");
newLine();
newLine();
}
printf("-------------------------------\n");
for (i = 0; i < rows; ++i)
{
printf("|");
for(j = 0; j < cols; ++j){
printf(" %d ",board[i][j]);
if((j+1) % 3 == 0){
printf("|");
}
}
printf("\n");
if((i+1) % 3 == 0){
printf("-------------------------------\n");
}
}
reset();
}
void byeMessage(){
blue();
newLine();
printf("That was quick !, Hope to see you again with new problem :)");
}

void takeInput(int board[rows][cols]){
for (int i = 0; i < rows; ++i)
{
for(int j = 0; j < cols; ++j){
scanf("%d", &board[i][j]);
}
}
}
bool validNumbers(int board[rows][cols]){
for (int i = 0; i < rows; ++i)
{
for(int j = 0; j < cols; ++j){
if(board[i][j] > 9 || board[i][j] < 0){
return false;
}
}
}
return true;
}
void checkForValidInput(int board[rows][cols]){
while(!validNumbers(board)){
red();
newLine();
printf("Please make sure that each number is between 1 to 9, re-enter the sudoku...\n");
newLine();
reset();
takeInput(board);
}
}
bool isPossibleNumber(int board[rows][cols], int x, int y, int val){
for(int j = 0; j < cols; j++){
if(board[x][j] == val){
return false;
}
}
for(int i = 0; i < rows; i++){
if(board[i][y] == val){
return false;
}
}
int smI = (x / 3) * 3;
int smJ = (y / 3) * 3;
for(int i = 0; i < 3; i++){
for(int j = 0; j < 3; j++){
if(board[smI + i][smJ + j] == val){
return false;
}
}
}
return true;
}
void sudokuSolver(int board[rows][cols], int i, int j){
if(i == rows){
isValidSudoku = true;
printBoard(board, 'g');
return;
}
int nextI= 0,nextJ = 0;
if(j == cols - 1){
nextI = i + 1;
nextJ = 0;
}else {
nextI = i;
nextJ = j + 1;
}
if(board[i][j] != 0){
sudokuSolver(board, nextI, nextJ);
}else{
for(int possibleAnswer = 1; possibleAnswer <= 9; possibleAnswer++)
{
if(isPossibleNumber(board, i , j , possibleAnswer)){
board[i][j] = possibleAnswer;
sudokuSolver(board, nextI, nextJ);
board[i][j] = 0;
}
}
}
}
/* Main funtion */
int main(){
int board[rows][cols];
greet();
printInstructions(false);
start:
takeInput(board);
checkForValidInput(board);
printBoard(board, 'p');
 sudokuSolver(board, 0, 0);
 if(!isValidSudoku){
red();
newLine();
 printf("The entered sudoku is invalid, Please re-enter the values\n");
printInstructions(true);
reset();
goto start;
 }else{
byeMessage();
}
return 0;
}