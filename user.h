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
#endif //STRUCTURES
Post *initiazlize_post();
Accounts *initiazlize_accounts();
void signup_func(Accounts *head, char *signup_username, char *signup_password, int *userCount);
void login_func(Accounts *head, char *login_username, char *login_password, int *logged_in_user);
void logout_func(int *logged_in_user);
