/*
 * leetcode 355: 设计推特 [中等]
 * 2022-04-26
 */
#include "common.h"

/***** 提交代码 ******************************************************************/
struct list_node {
    struct list_node *pre;
    struct list_node *next;
};

static void list_init(struct list_node *node)
{
    node->pre = node;
    node->next = node;
}

int list_empty(struct list_node *head)
{
    return head->next == head;
}

void list_add_tail(struct list_node *head, struct list_node *new)
{
    struct list_node *pre = head->pre;

    pre->next = new;
    new->pre = pre;
    new->next = head;
    head->pre = new;
}

void list_add_head(struct list_node *head, struct list_node *new)
{
    struct list_node *next = head->next;

    head->next = new;
    new->pre = head;
    new->next = next;
    next->pre = new;
}

void list_delete(struct list_node *node)
{
    struct list_node *pre = node->pre;
    struct list_node *next = node->next;

    pre->next = next;
    next->pre = pre;
}

#define container_of(ptr, type, member) ((type *)((uintptr_t)(ptr) - (uintptr_t)&(((type *)0)->member)))
#define list_entry(node, type, member) container_of(node, type, member)
#define list_first_entry(head, type, member) list_entry((head)->next, type, member)
#define list_next_entry(pos, type, member) list_entry((pos)->member.next, type, member)
#define list_for_each_entry(pos, head, type, member) \
        for (pos = list_first_entry(head, type, member); \
             &pos->member != head; \
             pos = list_next_entry(pos, type, member))
#define list_for_each_entry_safe(pos, n, head, type, member) \
        for (pos = list_first_entry(head, type, member); \
             &pos->member != head && (n = list_next_entry(pos, type, member), true); \
             pos = n)

int g_time = 0;

/* 用户 */
typedef struct {
    int id;
    struct list_node node;
    struct list_node tweet_head;
    struct list_node follow_head;
} User;

/* 推文 */
typedef struct {
    int tid;
    int time;
    User *user;
    struct list_node user_node;
    struct list_node global_node;
} Tweet;

/* 关注的人 */
typedef struct {
    User *user;
    struct list_node node;
} Follow;

/* 推特 */
typedef struct {
    struct list_node user_head;
    /* 所有的推文放在一个链表中，插入时插入头部，则推文在链表中按时间顺序排列 */
    struct list_node tweet_head;
} Twitter;

Twitter* twitterCreate() {
    Twitter *t = malloc(sizeof(Twitter));
    list_init(&t->user_head);
    list_init(&t->tweet_head);
    g_time = 0;
    return t;
}

User *CreateUser(Twitter *t, int id)
{
    User *u = malloc(sizeof(User));
    memset(u, 0, sizeof(User));
    u->id = id;
    list_init(&u->node);
    list_init(&u->tweet_head);
    list_init(&u->follow_head);
    list_add_tail(&t->user_head, &u->node);
    return u;
}

User *FindUser(Twitter *t, int id)
{
    User *u = NULL;

    list_for_each_entry(u, &t->user_head, User, node) {
        if (u->id == id) {
            return u;
        }
    }
    return CreateUser(t, id);
}

/* 创建推文 */
Tweet *CreateTweet(User *user, int tid)
{
    Tweet *t = malloc(sizeof(Tweet));
    t->user = user;
    t->tid = tid;
    t->time = g_time;
    g_time++;
    list_init(&t->user_node);
    list_init(&t->global_node);
    return t;
}

/* A创建推文 */
void twitterPostTweet(Twitter* obj, int userId, int tweetId) {
    User *u = NULL;
    Tweet *t = NULL;

    u = FindUser(obj, userId);
    t = CreateTweet(u, tweetId);
    list_add_tail(&u->tweet_head, &t->user_node);
    list_add_head(&obj->tweet_head, &t->global_node);
}

bool IsMyTweet(User *u, Tweet *t)
{
    Tweet *tmp = NULL;

    list_for_each_entry(tmp, &u->tweet_head, Tweet, user_node) {
        if (tmp->tid == t->tid) {
            return true;
        }
    }
    return false;
}

bool IsMyOrFollowTweet(User *u, Tweet *t)
{
    Follow *f = NULL;

    if (IsMyTweet(u, t)) {
        return true;
    }
    list_for_each_entry(f, &u->follow_head, Follow, node) {
        if (IsMyTweet(f->user, t)) {
            return true;
        }
    }
    return false;
}

/* 自己以及关注的人的最新10条推文id */
#define NEWS_NUM 10
int* twitterGetNewsFeed(Twitter* obj, int userId, int* retSize) {
    int count = 0;
    Tweet *t = NULL;
    User *u = FindUser(obj, userId);
    int *tweets = malloc(NEWS_NUM * sizeof(int));

    list_for_each_entry(t, &obj->tweet_head, Tweet, global_node) {
        if (IsMyOrFollowTweet(u, t)) {
            tweets[count] = t->tid;
            count++;
            if (count == NEWS_NUM) {
                break;
            }
        }
    }

    *retSize = count;
    return tweets;
}

Follow *CreateFollow(User *u2)
{
    Follow *f = malloc(sizeof(Follow));
    f->user = u2;
    return f;
}

Follow *FindFollow(User *u1, User *u2)
{
    Follow *f = NULL;

    list_for_each_entry(f, &u1->follow_head, Follow, node) {
        if (f->user->id == u2->id) {
            return f;
        }
    }
    return NULL;
}

/* A关注B */
void twitterFollow(Twitter* obj, int followerId, int followeeId) {
    User *u1 = NULL, *u2 = NULL;
    Follow  *f = NULL;

    /* 一个人可以被对个人关注, 关注后可以不再关注 */
    u1 = FindUser(obj, followerId);
    u2 = FindUser(obj, followeeId);
    f = FindFollow(u1, u2);
    if (f == NULL) {
        f = CreateFollow(u2);
        list_add_tail(&u1->follow_head, &f->node);
    }
}

/* A取消关注B */
void twitterUnfollow(Twitter* obj, int followerId, int followeeId) {
    User *u1 = NULL, *u2 = NULL;
    Follow *f = NULL;

    u1 = FindUser(obj, followerId);
    u2 = FindUser(obj, followeeId);
    f = FindFollow(u1, u2);
    if (f != NULL) {
        list_delete(&f->node);
        free(f);
    }
}

/* 释放关注的人 */
void FollowFree(User *u)
{
    Follow *pos = NULL, *n = NULL;

    list_for_each_entry_safe(pos, n, &u->follow_head, Follow, node) {
        list_delete(&pos->node);
        free(pos);
    }
}

/* 释放推文 */
void TweetFree(User *u)
{
    Tweet *pos = NULL, *n = NULL;

    list_for_each_entry_safe(pos, n, &u->tweet_head, Tweet, user_node) {
        list_delete(&pos->user_node);
        free(pos);
    }
}

void twitterFree(Twitter* obj) {
    User *pos = NULL, *n = NULL;

    list_for_each_entry_safe(pos, n, &obj->user_head, User, node) {
        FollowFree(pos);
        TweetFree(pos);
        list_delete(&pos->node);
        free(pos);
    }
    free(obj);
}

/***** 本地调试 ******************************************************************/
void TestCase1(void)
{
    int *tweets = NULL;
    int size;

    Twitter *t = twitterCreate();
    twitterPostTweet(t, 1, 5);
    tweets = twitterGetNewsFeed(t, 1, &size);
    PrintArray(tweets, size); //[5]
    free(tweets);
    twitterFollow(t, 1, 2);
    twitterPostTweet(t, 2, 6);
    tweets = twitterGetNewsFeed(t, 1, &size);
    PrintArray(tweets, size); //[6, 5]
    free(tweets);
    twitterUnfollow(t, 1, 2);
    tweets = twitterGetNewsFeed(t, 1, &size);
    PrintArray(tweets, size); //[5]
    free(tweets);
    twitterFree(t);
}

int main(void)
{
    TestCase1();
    return 0;
}