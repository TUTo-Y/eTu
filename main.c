#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "control.h"
#include "code.h"
#include "user.h"

#if 0
int main()
{
    srand(time(NULL));

    for(;;)
    {
        unsigned int i = 0;
        i = rand()%246 + 5;
        if(i<5 || i>250)
        {
            printf("错误aaaaaaaaa\n");
            Sleep(10000);
        }
        else
            printf("OK\n");
    }
    return 0;
}
#endif

#if 1
int main()
{
    srand((unsigned int)time(NULL));
    
    char name[MAX_PATH] = {0};
    unsigned char key[32] = {0};

    printf("输入名字 : ");
    scanf("%s", name);
    printf("输入密码 : ");
    scanf("%s", key);

    switch(UserCreate(name, key))
    {
        case U_C_TRUE:
            printf("用户创建成功\n\n");
        break;

        case U_C_FLASE_UH:
            printf("用户已存在\n\n");
        break;
        
        case U_C_FLASE_UN:
            printf("用户无法创建\n\n");
        break;
    }

    printf("输入名字 : ");
    scanf("%s", name);
    printf("输入密码 : ");
    scanf("%s", key);
    /* 读取用户文件 */
    struct user user;
    switch(UserLoad(&user, name, key))
    {
        case U_L_TRUE:
            printf("读取成功!\n");
        break;
        case U_L_FLASE_U:
            printf("用户不存在!\n");
        break;
        case U_L_FLASE_P:
            printf("密码错误!\n");
        break;
    }

    system("pause");
    return 0;
}
#endif
