# CSV-reader-via-C
This is one of my project which is a csv reader that I am going to build with C

# Basic concept of what the project is going to be; The instruction is given in a long format but I will try to be as minimal as possible
CSV stands for (Comma-Separated Values); as it is a tabular data so, it can be used for interchangable between applications. 


typedef struct 
{
    char name_room [Max_line_len]; // Member 1: Room Name (a string)
    double temperature;            // Member 2: Temperature (a decimal number)
} room_data; // The name of your new data type
typedef struct { ... }: This is the syntax for defining a new structure and giving it a type name in one step.

What's inside the { ... }:

char name_room[Max_line_len];: This is the first "compartment" or member of the structure. It's a string (array of characters) that can hold the name of a room, like "Living Room" or "Kitchen". Its maximum length is defined by the constant Max_line_len.

double temperature;: This is the second member. It's a variable designed to hold a temperature value, which can be a decimal number like 22.5 or 18.75.

room_data;: This is the name you are giving to this new structure type. It's like a label for your custom blueprint.


#Function Purpose
#Takes a temperature and prints a visual representation using underscore characters.

How It Works
1. Range Check

if (temperature < 0 || temperature > 30) {
    printf("X\n");
}
If temperature is outside the 0-30 range, it prints X to indicate "invalid" or "out of range"

This acts as error handling for unexpected values

2. Bar Graph Creation

int graph_len = (int)(temperature / Scale);
Converts the temperature to a number of characters by dividing by Scale

Example: If Scale = 2 and temperature = 16, then graph_len = 8

The (int) cast truncates the decimal part

3. Printing the Graph

for (int i = 0; i < graph_len; i++) {
    printf("_");
}
Prints graph_len number of underscore characters

Creates a horizontal bar where length represents temperature

Example Output
If Scale = 3:

temperature = 15 → prints _____ (5 underscores)

temperature = 6 → prints __ (2 underscores)

temperature = -5 → prints X

temperature = 35 → prints X

Key Points
Visual scaling: The Scale variable controls how many degrees each _ character represents

Simple visualization: Longer bars = higher temperatures

Error handling: X marks values outside the expected range

This creates a quick, text-only way to see temperature trends at a glance!


