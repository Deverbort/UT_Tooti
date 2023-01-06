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
#define ACCOUNTS_FILE_ADDRESS "./accounts.txt"
#define POSTS_FILE_ADDRESS "./posts.txt"
#endif // STRUCTURES
void accounts_file(Accounts *head);
void posts_file(Accounts *head);
