#include "command.h"
#include "post.h"
#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *input_function() // function for getting infinite size input
{
    int i = 2, j = 0;
    char *string;
    printf("Enter any command: \n");

    string = (char *)malloc(sizeof(char));
    while ((string[j] = getchar()) != '\n') // getting characters one by one and reallocating the string each time
    {
        string = (char *)realloc(string, sizeof(char) * i);
        i++;
        j++;
    }
    string = (char *)realloc(string, sizeof(char) * i);
    string[strlen(string)] = '\0'; // putting null character in the end of the string
    return string;
}
int parts_counter(char *input_cpy) // this function counts the number of words in a string
{
    int parts = 0;
    char *token = strtok(input_cpy, " ");
    while (token != NULL)
    {
        parts++;
        token = strtok(NULL, " ");
    }

    return parts;
}
void command_decipherer(char *input, int *logged_in_user, int *quit, Accounts *head, int *userCount)
{
    char *input_cpy = (char *)malloc((strlen(input)) * sizeof(char)); // this part counts the number of words in input string
    if (input_cpy == NULL)
    {
        printf("Failed to allocate memory\n");
        exit(0);
    }
    strcpy(input_cpy, input); // strtok alters the main string so we have to use a copy of it for this part
    int parts = parts_counter(input_cpy);
    free(input_cpy);
    // this part stores the first word of input in command string
    const char devide[3] = {' ', '\n', '\0'}; // used for deviding the input when we reach these characters
    const char post_devide[2] = {'\n', '\0'};
    char *command = strtok(input, devide);
    if (strcmp(command, "signup") == 0) // the following if statements decide what operation should be done
    {                                   // depending on the command the user gave
        if (parts != 3)
        {
            printf("Too few or too many arguments!!\nThe format should be: signup <username> <password>\n");
            return;
        }
        char *signup_username = strtok(NULL, devide); // getting the remaining two parts from input string
        char *signup_password = strtok(NULL, devide);

        signup_func(head, signup_username, signup_password, userCount);
    }
    else if (strcmp(command, "login") == 0)
    {
        if (*logged_in_user != 0)
        {
            printf("you have to logout before you login to another account!\n");
            return;
        }
        if (parts != 3)
        {
            printf("Too few or too many arguments!!\nThe format should be: login <username> <password>\n");
            return;
        }
        char *login_username = strtok(NULL, devide); // getting the remaining two parts from input string
        char *login_password = strtok(NULL, devide);
        login_func(head, login_username, login_password, logged_in_user);
    }
    else if (strcmp(command, "post") == 0)
    {
        if (*logged_in_user == 0)
        {
            printf("You have to login to be able to post\n");
            return;
        }
        if (parts < 2)
        {
            printf("Too few arguments!!\nThe format should be: post <text>\n");
            return;
        }
        // getting the post text from input string
        char *post_text = strtok(NULL, post_devide);
        post_func(head, *logged_in_user, post_text);
    }
    else if (strcmp(command, "like") == 0)
    {
        char *like_username = strtok(NULL, devide); // getting the remaining two parts from input string
        char *like_post_ID = strtok(NULL, devide);
        int like_postID = atoi(like_post_ID);
        like_func(head, like_username, like_postID, *logged_in_user);
    }
    else if (strcmp(command, "logout") == 0)
    {
        if (*logged_in_user == 0)
        {
            printf("You must be logged in to use logout!\n");
            return;
        }
        if (parts != 1)
        {
            printf("Too many arguments!!\nThe format should be: logout\n");
            return;
        }
        logout_func(logged_in_user);
    }
    else if (strcmp(command, "delete") == 0)
    {
        if (*logged_in_user == 0)
        {
            printf("You have to login first\n");
            return;
        }
        /*if (parts != 2)
        {
            printf("You command had %d parts\nToo few or too many arguments!!\nThe format should be: delete <post ID>\n", parts);
            return;
        }*/
        char *delete_postID = strtok(NULL, devide);
        int del_postID_num = atoi(delete_postID);
        delete_func(head, *logged_in_user, del_postID_num); // needs username and post ID as arguments
    }
    else if (strcmp(command, "info") == 0)
    {
        if (parts != 1)
        {
            printf("Too many arguments!!\nThe format should be: info\n");
            return;
        }
        info_func(head, *logged_in_user);
    }
    else if (strcmp(command, "find_user") == 0)
    {
        if (parts != 2)
        {
            printf("Too few or too many arguments!!\nThe format should be: find_user <username>\n");
            return;
        }
        char *find_username = strtok(NULL, devide);
        find_user(head, find_username);
    }
    else if (strcmp(command, "quit") == 0)
    {
        if (parts != 1)
        {
            printf("Too many arguments!!\nThe format should be: quit\n");
            return;
        }
        printf("You quit UT-Tooti.\n");
        *quit = 0;
    }
    else
    {
        printf("This command is not defined!\n");
        return;
    }
    free(command);
}
