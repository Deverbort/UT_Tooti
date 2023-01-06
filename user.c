#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Post *initiazlize_post()
{
    Post *head = (Post *)malloc(sizeof(Post));
    head->text = head->username = NULL;
    head->next_post = NULL;
    head->likers = NULL;
    head->post_ID = head->likes = -1;
}
Accounts *initiazlize_accounts()
{
    Accounts *head = (Accounts *)malloc(sizeof(Accounts));
    head->username = head->password = NULL;
    head->next_acc = NULL;
    head->userpost = NULL;
    head->userNum = head->postsNum = -1;
    return head;
}
void signup_func(Accounts *head, char *signup_username, char *signup_password, int *userCount)
{
    Accounts *current = head;
    Accounts *new_acc = (Accounts *)malloc(sizeof(Accounts)); //malloc a new acc
    while (current->next_acc != NULL) //surfing until we find the last account node
    {
        current = current->next_acc;
        if ((strcmp(current->username, signup_username)) == 0)
        {
            printf("This username already exists!\n");
            printf("%s\n%s\n", current->username, signup_username);
            return;
        }
    }
    current->next_acc = new_acc; // doing mallocs and giving values to every variable of the new acc
    new_acc->username = (char *)malloc(strlen(signup_username) * sizeof(char));
    new_acc->password = (char *)malloc(strlen(signup_password) * sizeof(char));
    if (new_acc->username == NULL || new_acc->password == NULL)
    {
        printf("Failed to allocate memory\n");
        exit(0);
    }
    strcpy(new_acc->username, signup_username);
    strcpy(new_acc->password, signup_password);
    new_acc->userNum = *userCount + 1;
    (*userCount)++;
    new_acc->postsNum = 0;
    new_acc->userpost = NULL;
    new_acc->next_acc = NULL;
    new_acc->userpost = initiazlize_post();
    printf("Signup was a success\n");
    return;
}
void login_func(Accounts *head, char *login_username, char *login_password, int *logged_in_user)
{
    Accounts *current = head;
    Accounts *new_acc = (Accounts *)malloc(sizeof(Accounts));
    if (new_acc == NULL)
    {
        printf("Failed to allocate memory\n");
        exit(0);
    }
    int success = 0;
    while (current->next_acc != NULL) // navigate through the linked list until we find the username
    {
        current = current->next_acc;
        if ((strcmp(current->username, login_username)) == 0) // i fthe username was found break out of the loop
        {
            success = 1;
            break;
        }
    }
    if (success != 1) // if the username was not found print error and return
    {
        printf("username not found!\n");
        return;
    }
    if ((strcmp(current->password, login_password) == 0)) // check if the password is correct
    {
        *logged_in_user = current->userNum;
        printf("Successfully logged in to %s\n", current->username);
    }
    else // if the password is incorrect print error
    {
        printf("The username and password do not match\n");
    }
}
void logout_func(int *logged_in_user)
{
    printf("Successfully logged out.\n"); // simply changes the value of logged in user to a non-user value
    *logged_in_user = 0;
}
