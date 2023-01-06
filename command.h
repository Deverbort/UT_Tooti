#ifndef STRUCTURES
#define STRUCTURES
typedef struct Post Post;
typedef struct Accounts Accounts;
struct Post
{
    char *username;
    int post_ID;
    int likes;
    int *likers; // to avoid multiple likes from the same account
    char *text;
    Post *next_post;
};
struct Accounts
{
    char *username;
    char *password;
    int userNum; // to avoid multiple likes from the same account
    int postsNum;
    Post *userpost;
    Accounts *next_acc;
};
#endif                              // STRUCTURES
char *input_function();             // function for getting infinite size input
int parts_counter(char *input_cpy); // this function counts the number of words in a string
void command_decipherer(char *input, int *logged_in_user, int *quit, Accounts *head, int *userCount);
