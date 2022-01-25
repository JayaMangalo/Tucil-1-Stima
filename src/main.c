#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pcolor.h"

char P[100][100];       //matrix of chars
int colour[100][100];  //matrix of chars that should be colored

char K[100][100];

int x;
int y;

int comparisoncount=0;
int currentword=1;
int word=0 ; //banyak word (+1 dari \n)

void Readinput(){
    FILE *ptr;
    char filename[100] = "..\\test\\"; 
    char name[100]; 
    printf("Enter Filename: ");
    scanf("%s",&name); 
    strcat(filename,name);
    ptr = fopen(filename, "r");
    char str[100];
    x=0;
    y=0;
    int first = 1;
    while (fgets(str, 50, ptr) != NULL) {
        if (str[0] == '\n'){
            first = 0;
        }
        if(first){
            char * token = strtok(str, " ");
            // loop through the string to extract all other tokens
            y = 0;
            while( token != NULL ) {
                P[x][y] = *token;
                token = strtok(NULL," ");
                y++;
            }
            
            x++;
        }
        else{
            strcpy(K[word],str);
            K[word][strlen(K[word])-1] = 0;  
            word++;
        }
        
    }

    fclose(ptr);
}

int searchword(int i, int j, char kata[100]){
    int length = strlen(kata);
    char compare[100];
    //up
    
    if (i - length + 1 >= 0){
        compare[length] = 0;
        for (int p = 0; p < length; p++)
        {
            compare[p] = P[i-p][j];
            comparisoncount++;
        }
        if (strcmp(kata,compare) == 0){
            for (int p = 0; p < length; p++)
            {
                colour[i-p][j] = currentword;
            }
            return 1;
        } 
    }
    //up-right
    if (i - length + 1 >= 0 && j + length - 1 <= y){
        compare[length] = 0;
        for (int p = 0; p < length; p++)
        {
            compare[p] = P[i-p][j+p];
            comparisoncount++;
        }
        if (strcmp(kata,compare) == 0){
            for (int p = 0; p < length; p++)
            {
                colour[i-p][j+p] = currentword;
            }
            return 1;
        } 
    }
    //right
    if (j + length - 1 <= y){
        compare[length] = 0;
        for (int p = 0; p < length; p++)
        {
            compare[p] = P[i][j+p];
            comparisoncount++;
        }
        if (strcmp(kata,compare) == 0){
            for (int p = 0; p < length; p++)
            {
                colour[i][j+p] = currentword;
            }
            return 1;
        } 
    }
    //down-right
    if (i + length - 1 <= x && j + length - 1 <= y){
        compare[length] = 0;
        for (int p = 0; p < length; p++)
        {
            compare[p] = P[i+p][j+p];
            comparisoncount++;
        }
        if (strcmp(kata,compare) == 0){
            for (int p = 0; p < length; p++)
            {
                colour[i+p][j+p] = currentword;
            }
            return 1;
        } 
    }
    //down
    if (i + length - 1 <= x){
        compare[length] = 0;
        for (int p = 0; p < length; p++)
        {
            compare[p] = P[i+p][j];
            comparisoncount++;
        }
        if (strcmp(kata,compare) == 0){
            for (int p = 0; p < length; p++)
            {
                colour[i+p][j] = currentword;
            }
            return 1;
        } 
    }
    //down-left
    if (i + length - 1 <= x && j - length + 1 >= 0){
        compare[length] = 0;
        for (int p = 0; p < length; p++)
        {
            compare[p] = P[i+p][j-p];
            comparisoncount++;
        }
        if (strcmp(kata,compare) == 0){
            for (int p = 0; p < length; p++)
            {
                colour[i+p][j-p] = currentword;
            }
            return 1;
        } 
    }
    //left
    if (j - length + 1 >= 0){
        compare[length] = 0;
        for (int p = 0; p < length; p++)
        {   
            compare[p] = P[i][j-p];
            comparisoncount++;
        }  
        if (strcmp(kata,compare) == 0){
            for (int p = 0; p < length; p++)
            {
                colour[i][j-p] = currentword;
            }
            return 1;
        } 
    }
    //up-left
    if (i - length + 1 >= 0 && j - length + 1 >= 0){
        compare[length] = 0;
        for (int p = 0; p < length; p++)
        {
            compare[p] = P[i-p][j-p];
            comparisoncount++;
        }
        if (strcmp(kata,compare) == 0){
            for (int p = 0; p < length; p++)
            {
                colour[i-p][j-p] = currentword;
            }
            return 1;
        } 
    }
    return 0;
}

void find(){
    for (int k = 1; k < word; k++) //all words
    {      
        int found = 0;
        for (int i = 0; i < x; i++)         // search for first letter of word 
        {                                   
            for (int j = 0; j < y; j++)     // search for first letter of word 
            {   
                if(!found){comparisoncount++;}
                if(K[k][0] == P[i][j] && !found ){
                    if (searchword(i,j,K[k])){
                        found = 1;
                    }
                }
            }
        }
        currentword++;
    }
}

void SetupColour(){
    for (int i = 0; i < x; i++)
    {
        /* code */
        for (int j = 0; j < y; j++)
        {   
            colour[i][j] = 0;
        }
    }
}

void test(){
    printf("x: %d",x);
    printf("y: %d",y);

    for (int i = 0; i < x; i++)
    {
        /* code */
        for (int j = 0; j < y; j++)
        {
            printf("%c ",P[i][j]);
        }
    }

    printf("Word: %d\n",word);

    for (int i = 1; i < word; i++){
        printf("%s\n",K[i]);
    }
     printf("test\n\n");
}

void printcolour(){
    printf("\nResult: \n");
    for (int i = 0; i < x; i++)
    {
        /* code */
        for (int j = 0; j < y; j++)
        {   
                if(colour[i][j] == 0){printf("%c ",P[i][j]);}
                else if(colour[i][j]%6 == 1){print_red(P[i][j]);}
                else if(colour[i][j]%6 == 2){print_green(P[i][j]);}
                else if(colour[i][j]%6 == 3){print_magenta(P[i][j]);}
                else if(colour[i][j]%6 == 4){print_cyan(P[i][j]);}
                else if(colour[i][j]%6 == 5){print_yellow(P[i][j]);}
                else if(colour[i][j]%6 == 0){print_blue(P[i][j]);}
        }
        printf("\n");
    }
}

int main(){
    Readinput();
    SetupColour();
    
    clock_t begin = clock();

    find();
    printcolour();

    clock_t end = clock();

    float time_spent = (float)(end - begin) / CLOCKS_PER_SEC;

    printf("\nStats: \n");
    printf("Execution Time: %f seconds\n",time_spent);
    printf("Comparisons Made: %d\n",comparisoncount);

}