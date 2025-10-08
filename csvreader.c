#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#define MAX_ROOMS 50 //maximum number of rooms
#define Max_line_len 300 // It's a relatively smaller csv file
#define Scale 0.5 //scale for temperature of bar graph



typedef struct 
{
    char name_room [Max_line_len];  // room name i.e a string 
    double temperature;  // temperature i.e a decimal number
}room_data;  //data type 


// creates a simple text-based bar graph to visualize temperature values.
void print_bar_graph(double temperature){
    if (temperature<0|| temperature>30 ){
        printf("X\n");
} else {
    int graph_len = (int) (temperature/ Scale ); //calculate the number of '_' characters 
    for (int i = 0; i < graph_len; i++)
    {
        printf("_");
    }
    }
}


//string conversion to lowercase

void lowercase(char * str){ //A pointer to the string (character array) you want to modify
    for (int i = 0; str[i]; i++)
    {
        str[i]=tolower(str[i]);
    }
    
}

// make sure if there is a room like that the user puts in
int room_exists(const char available_rooms[MAX_ROOMS][Max_line_len], int available_count, const char *room_name) { // check if a room name exists in the available_rooms list .returns 1 if found,0 if not
    for (int j = 0; j < available_count; j++) {
        if (strcmp(available_rooms[j], room_name) == 0) {
            return 1; // room exists in the list
        }
    }
    return 0;  //room does not exist in the list
}
