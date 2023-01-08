#include "free.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void free_all_data(Accounts *head)
{
    if (head == NULL || head->next_acc == NULL)
        return;
    while (head != NULL)
    {
        free(head->password);
        free(head->username);
        Post *head_post = head->userpost;
        while(head_post != NULL)
        {
            free(head_post->likers);
            free(head_post->text);
            free(head_post->username);
            head_post = head_post->next_post;
        }
        head = head->next_acc;
    }
}