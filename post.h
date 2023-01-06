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
#endif // STRUCTURES
void info_func(Accounts *head, int logged_in_user);
void like_func(Accounts *head, char *uploader_username, int like_postID, int logged_in_user);
void delete_func(Accounts *head, int logged_in_user, int post_ID);
void find_user(Accounts *head, char *find_username);
void post_func(Accounts *head, int logged_in_user, char *post_text);
