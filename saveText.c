#include "saveText.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void accounts_file(Accounts *head)
{
    FILE *accounts = fopen(ACCOUNTS_FILE_ADDRESS, "w");
    Accounts *temp = head;
    while (temp->next_acc != NULL)
    {
        temp = temp->next_acc;
        fprintf(accounts, "%s %s %d\n", temp->username, temp->password, temp->postsNum);
    }
    fclose(accounts);
}
void posts_file(Accounts *head)
{
    FILE *posts_txt = fopen(POSTS_FILE_ADDRESS, "w");
    Accounts *temp = head;
    while (temp->next_acc != NULL)
    {
        temp = temp->next_acc;
        Post *temp_post = temp->userpost;
        while (temp_post->next_post != NULL)
        {
            temp_post = temp_post->next_post;
            fprintf(posts_txt, "%s %s %d\n", temp_post->text, temp_post->username, temp_post->likes);
        }
    }
    fclose(posts_txt);
}
