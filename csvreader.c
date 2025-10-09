#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>



#define Max_Rooms_numb 50 //maximum number of rooms
#define Max_line_len 300 // It's a relatively smaller csv file
#define Scale 0.5 //scale for temperature of bar graph


// structure for room data (room name and temperature)
typedef struct {
    char name_room[Max_line_len];
    double temperature;
} room_data;

//function to convert a string into lowercase
void to_lower_case(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}
//function to print a bar graph based on room's temperature
void print_bar_graph(double temperature) {
    if (temperature < 0 || temperature > 30) {
        printf("X\n"); // if the temperature is out of range, print 'X'
    } else {
        int graph_length = (int)(temperature / Scale); // calculate number of '-' characters
        for (int i = 0; i < graph_length; i++) {
            printf("-");
        }
    }
}
// See if a room is currently available by checking it against our room list
int room_exists(const char available_rooms[Max_Rooms_numb][Max_line_len], int available_count, const char *room_name) {
    // Go through each room in the available rooms list from the file
    for (int j = 0; j < available_count; j++) {
        // Check if this room matches the one we're looking for
        if (strcmp(available_rooms[j], room_name) == 0) {
            return 1;  // the available room
        }
    }
    return 0;  // Sorry, couldn't find this room in the available list
}
// function to print the temperature and corresponding bar graph for given room
void room_temp_print(room_data rooms[], int room_count, const char *name_room) { //checks the room name against the available rooms and print the temperature if found
    printf("\nTemperature in %s:\n", name_room);

    int print_count = 0;
    for (int i = 0; i < room_count; i++) {  // check all rooms to find a matching room name
        char temp_room[Max_line_len];
        strcpy(temp_room, rooms[i].name_room);
        to_lower_case(temp_room); // convert room name to lowercase for comparison

        if (strcmp(temp_room, name_room) == 0) { // if room name matches,print its temperature
            printf("\n  %.1lf: ", rooms[i].temperature);
            print_bar_graph(rooms[i].temperature); // print the bar graph
            print_count++;
        }
    }

    if (print_count == 0) { // if no room is found,display an error message
        printf("\nError! Room '%s' is not found in the file.\n", name_room);
    }
}

// Display all unique available rooms from the room list
void display_available_rooms(room_data rooms[], int room_count) {
    char available_rooms[Max_Rooms_numb][Max_line_len];
    int available_count = 0;

    printf("\nHere are the available rooms:\n");

    // Check each room to build our unique list
    for (int i = 0; i < room_count; i++) {
        char room_name[Max_line_len];
        strcpy(room_name, rooms[i].name_room);

        // Skip if we've already added this room to the display
        if (room_exists(available_rooms, available_count, room_name)) {
            continue;
        }

        // Add this unique room to our display list
        strcpy(available_rooms[available_count], room_name);
        printf("  - %s\n", room_name);  // Print directly for clarity
        available_count++;
    }
}
// function to validate the user's input for the room name
int validate_input(char selected_room[], room_data rooms[], int room_count) { // returns 1 if valid input (room exists),2 if user types 'stop' and 0 if invalid
    to_lower_case(selected_room); // convert user input to lowercase

    if (strcmp(selected_room, "stop") == 0) {
        return 2;  //indicate the user wants to stop
    }

    if (strlen(selected_room) == 0) { // check for empty input
        printf("\nError! Room name cannot be empty. Please enter a valid input.\n");
        return 0;
    }

    for (int i = 0; i < room_count; i++) { // check all rooms and check if the input matches a room name
        char temp_room[Max_line_len];
        strcpy(temp_room, rooms[i].name_room);
        to_lower_case(temp_room);

        if (strcmp(temp_room, selected_room) == 0) {
            return 1;// indicate room is found(valid input)
        }
    }

    printf("\nError! Room '%s' does not exist. Please enter a valid room name.\n", selected_room); // if no room matches the input, display an error message
    return 0;
}


int main() {
    room_data rooms[Max_Rooms_numb];  // Array to store all room data
    FILE *file = fopen("Temperatures.csv", "r");  // Open the temperature data file
    
    // Check if file opened successfully
    if (file == NULL) {
        printf("\nError! Could not open the temperature data file.\n");
        return 1;
    }
    
    char line_buffer[100];
    int room_count = 0;
    
    // Skip the header line (first line) of the CSV file
    fgets(line_buffer, sizeof(line_buffer), file);

    // Read each line of the file and extract room data
    while (fgets(line_buffer, sizeof(line_buffer), file)) {
        // Parse temperature and room name from each line
        int parse_success = sscanf(line_buffer, "%lf,%49[^\n]", 
                                  &rooms[room_count].temperature, 
                                  rooms[room_count].name_room);
        
        if (parse_success == 2) {
            room_count++;
            
            // Safety check - don't exceed our room array capacity
            if (room_count >= Max_Rooms_numb) {
                printf("\nError! Maximum room capacity reached.\n");
                fclose(file);
                return 1;
            }
        } else {
            // Handle lines that don't match expected format
            printf("\nError! Found invalid data format in the file.\n");
            fclose(file);
            return 1;
        }
    }
    
    fclose(file);  // Done reading the file

    char user_room_choice[Max_line_len];
    int is_valid_input = 0;

    // Show user the list of available rooms
    display_available_rooms(rooms, room_count);

    // Main program loop - keep running until user types 'stop'
    do {
        printf("\nEnter a room name from the list that is displayed (or type 'stop' to exit): ");
        fgets(user_room_choice, Max_line_len, stdin);
        
        // Remove the newline character from user input
        user_room_choice[strcspn(user_room_choice, "\n")] = '\0';

        // Check if the user's input matches a real room
        is_valid_input = validate_input(user_room_choice, rooms, room_count);

        // If it's a valid room, show its temperature data
        if (is_valid_input == 1) {
            room_temp_print(rooms, room_count, user_room_choice);
        }

    } while (strcmp(user_room_choice, "stop") != 0);  // Exit when user types 'stop'

    printf("\nThank you and have a great day <:3 !\n");
    return 0;
}