#include <stdio.h>
#include <stdint.h>


#define Max_line_len 300 // It's a relatively smaller csv file

int main(){
    FILE *file= fopen("Temperatures.csv", "r");  /*Reads the csv file and path to it aswell*/

    if (file=NULL)   
    {
        printf("Error: there was no csv file");
    }
    


}