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
void free_all_data(Accounts *head);