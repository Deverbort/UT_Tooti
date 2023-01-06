#include "post.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void info_func(Accounts *head, int logged_in_user)
{
    if (logged_in_user == 0) // check if the user has logged in
    {
        printf("You need to login to use this function\n");
        return;
    }
    Accounts *current = head;
    while (current->userNum != logged_in_user) // navigating to find the account
        current = current->next_acc;
    printf("username: %s\npassword: %s\n", current->username, current->password);
    Post *post_curr = (Post *)malloc(sizeof(Post)); // to avoid ruining the linked list
    post_curr = current->userpost;
    while (post_curr->next_post != NULL) // print each element of each post
    {
        post_curr = post_curr->next_post;
        printf("\npost_ID: %d\npost text: %s\nlikes: %d\n\n", post_curr->post_ID, post_curr->text, post_curr->likes);
    }
    printf("End of posts\n");
    free(post_curr);
}
void like_func(Accounts *head, char *uploader_username, int like_postID, int logged_in_user)
{
    Accounts *current = head;
    int success = 0;
    while (current->next_acc != NULL) // navigating to find the account
    {
        current = current->next_acc;
        if (strcmp(current->username, uploader_username) == 0) // if we reached the username we wanted break out of the loop
        {
            success++;
            break;
        }
    }
    if (success == 0)
    {
        printf("user was not found!\n");
        return;
    }

    Post *post_cur = current->userpost->next_post;
    success = 0;             // will be used to see if we have found the mentioned post
    while (post_cur != NULL) // navigate through the posts to find the post with the entered post id
    {
        if ((post_cur->post_ID) == like_postID)
        {
            success++;
            break;
        }
        post_cur = post_cur->next_post;
    }
    if (success == 0)
    {
        printf("no post with this post_ID exists!\n");
        return;
    }
    // now we check to see if the post has been liked by the logged in user before this or not
    post_cur->likers = (int *)realloc(post_cur->likers, (post_cur->likes + 1) * sizeof(int));
    for (int i = 0; i <= (post_cur->likes); i++)
        if (post_cur->likers[i] == logged_in_user)
        {
            printf("You have already liked this post\n");
            return;
        }
    post_cur->likers[post_cur->likes] = logged_in_user; // storing the current user as someone who liked the post
    (post_cur->likes)++;
    free(post_cur);
    printf("You liked post %d from user %s\n", like_postID, uploader_username);
}
void delete_func(Accounts *head, int logged_in_user, int post_ID)
{
    Accounts *current = head;
    while (current->userNum != logged_in_user) // navigating to find the account
        current = current->next_acc;
    Post *post_cur, *post_prev;
    post_prev = current->userpost;
    post_cur = post_prev->next_post;
    int success = 0;         // will be used to see if we have found the mentioned post
    while (post_cur != NULL) // navigate through the posts to find the post with the entered post id
    {
        if ((post_cur->post_ID) == post_ID)
        {
            success++;
            break;
        }
        post_cur = post_cur->next_post;
        post_prev = post_prev->next_post;
    }
    if (success == 0)
    {
        printf("no post with this post_ID exists!\n");
        return;
    }
    post_prev->next_post = post_cur->next_post; // form a new link
    free(post_cur);                             // free the deleted node
    (current->postsNum)--;                      // decrementing the number of posts by user
    printf("The post has been successfully deleted\n");
}
void find_user(Accounts *head, char *find_username)
{
    Accounts *current = head;
    int success = 0;
    while (current->next_acc != NULL) // navigating to find the account
    {
        current = current->next_acc;
        if (strcmp(current->username, find_username) == 0) // if we reached the username we wanted break out of the loop
        {
            success++;
            break;
        }
    }
    if (success == 0)
    {
        printf("user was not found!\n");
        return;
    }
    Post *post_curr = (Post *)malloc(sizeof(Post)); // to avoid ruining the linked list
    post_curr = current->userpost;
    while (post_curr->next_post != NULL) // printing the information of posts
    {
        post_curr = post_curr->next_post;
        printf("\npost_ID: %d\npost text: %s\nlikes: %d\n\n", post_curr->post_ID, post_curr->text, post_curr->likes);
    }
    printf("End of posts\n");
    free(post_curr);
}
void post_func(Accounts *head, int logged_in_user, char *post_text)
{
    Accounts *current = head;
    while (current->userNum != logged_in_user) // navigating to find the account
        current = current->next_acc;
    Post *newpost = (Post *)malloc(sizeof(Post));
    if (newpost == NULL)
    {
        printf("Failed to allocate memory\n");
        exit(0);
    }
    Post *post_cur = current->userpost;
    int counter = 0;
    while (post_cur->next_post != NULL) // navigating to find the last post
    {
        post_cur = post_cur->next_post;
        counter++;
    }
    post_cur->next_post = newpost; // doing mallocs and giving value to every variable in newpost
    newpost->likes = 0;
    newpost->likers = (int *)malloc(sizeof(int));
    if (newpost->likers == NULL)
    {
        printf("Failed to allocate memory\n");
        exit(0);
    }
    newpost->next_post = NULL;
    if (counter == 0) // if this is the first post (so we wouldn't have repetitive post ids.)
        newpost->post_ID = 1;
    else
        newpost->post_ID = post_cur->post_ID + 1;
    newpost->text = (char *)malloc(strlen(post_text) * sizeof(char));
    if (newpost->text == NULL)
    {
        printf("Failed to allocate memory\n");
        exit(0);
    }
    strcpy(newpost->text, post_text);

    newpost->username = (char *)malloc(strlen(current->username) * sizeof(char));
    if (newpost->username == NULL)
    {
        printf("Failed to allocate memory\n");
        exit(0);
    }
    strcpy(newpost->username, current->username);
    (current->postsNum)++;
    printf("Successfully posted\n");
    return;
}
