#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "post.h"
#include "command.h"
#include "saveText.h"
int main(void)
{
    int logged_in_user = 0;
    int quit = 1, userCount = 0;
    Accounts *accounts_head = initiazlize_accounts();
    while (quit)
    {
        char *input = input_function();
        command_decipherer(input, &logged_in_user, &quit, accounts_head, &userCount);
        printf("%s\n", accounts_head->username);
        free(input);
        accounts_file(accounts_head);
        posts_file(accounts_head);
    }
    free(accounts_head);
}