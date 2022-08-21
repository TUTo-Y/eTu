/*
    用户数据 : user/user
    16字节 : 异或加密的iv
    16字节 : aes加密后的半加密向量 : iv[i] += x;
    其余 : 用户目录数据
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "control.h"
#include "code.h"

#define U_L_TRUE     0      // 读取成功
#define U_L_FLASE_U  0x01   // 用户读取失败
#define U_L_FLASE_P  0x02   // 密码错误

#define U_C_TRUE     0      // 用户创建成功
#define U_C_FLASE_UH 0x01   // 用户已存在
#define U_C_FLASE_UN 0x02   // 用户无法创建

/* 文件 */
struct file
{
    /* 文件名 */
    char file_name[MAX_PATH];
    /* 对应的磁盘文件 */
    char file[MAX_PATH];

    /* 上下文件 */
    struct file *file_old;
    struct file *file_next;
};

/* 文件夹 */
struct dir
{
    /* 文件夹名 */
    char dir_name[MAX_PATH];

    /* 包含文件 */
    struct file *file;
    /* 包含文件夹 */
    struct dir *dir;

    /* 上下文件夹 */
    struct dir *dir_old;
    struct dir *dir_next;
};

/* 用户文件 */
struct user
{
    char *User;
    unsigned char Key[32];
    unsigned char iv[16];

    /* 文件目录 */
    struct dir *dir;
};


/**
 *  \brief 读取用户文件夹数据
 *
 *  \param Data 文件信息存储数据
 * 
 *  \return 读取的文件夹
 */
struct dir *UserLoadDir(char *Data);

/**
 *  \brief 读取用户数据
 *
 *  \param user     存储用户信息
 *  \param userName 用户名
 *  \param userKey  密码
 * 
 *  \return 是否读取成功
 */
unsigned int UserLoad(struct user *user, const char*userName, const unsigned char*userKey);


/**
 *  \brief 创建用户文件
 *
 *  \param userName 用户名
 *  \param userKey  密码
 * 
 *  \return 是否创建成功
 */
unsigned int UserCreate(const char*userName, const unsigned char*userKey);
