#include "user.h"

/*
    dimage/dTUTo/f女生.jpeg*1232.data|f/txt\\dmusic|
*/
struct dir *UserLoadDir(char *Data)
{
    return NULL;
}

unsigned int UserLoad(struct user *user, const char*userName, const unsigned char*userKey)
{
    /* 用户文件 */
    FILE *File  = NULL;
    char dir_t[MAX_PATH] = { 0 };   // 合成目录
    char *user_src_data = NULL;     // 直接读取的用户数据
    char *user_data = NULL;         // 解密后的用户数据(去除第一段iv)
    unsigned int user_size = 0;              // 用户数据大小
    unsigned int i = 0;
    int t = 0;
    
    /* init */
    memset(user, 0, sizeof(struct user));
    /* 合成目录 */
    strcpy(dir_t, userName);
    strcat(dir_t, "/user");

    /* 打开用户文件 */
    if(!(File = fopen(dir_t, "rb")))
        return U_L_FLASE_U;
        
    /* 读取用户文件 */
    fseek(File, 0L, SEEK_END);
    user_size = ftell(File);
    rewind(File);
    user_src_data = (char*)malloc(user_size);
    fread(user_src_data, user_size, 1, File);        
    fclose(File);

    /* 解密iv */
    for(i = 0; i<16 ;i++)
        user->iv[i] = (unsigned char)userKey[i] ^ userKey[i + 16] ^ user_src_data[i];

    /* 通过解密的iv解密数据 */
    De_Data_Aes_cbc(user_src_data + 16, user_size - 16, (unsigned char**)&user_data, &user_size, userKey, user->iv);

    /* 效验半解密iv */
    t = user->iv[0] - (unsigned char)user_data[0];
    for(i = 1; i<16; i++)
        if(t != user->iv[i] - (unsigned char)user_data[i])
        {
            free(user_data);
            free(user_src_data);
            return U_L_FLASE_P;
        }
    /* 赋值密钥到结构体 */
    memcpy(user->Key, userKey, 16);

    /* 读取数据 */

    /* 释放缓存 */
    free(user_data);
    free(user_src_data);
    return U_L_TRUE;
}

unsigned int UserCreate(const char*userName, const unsigned char*userKey)
{
    FILE *File;
    char dir_t[MAX_PATH] = { 0 };   // 合成目录
    unsigned char iv[16] = {0};     // 初始化向量
    unsigned char oeiv[16] = {0};   // 半加密向量
    unsigned char *eiv = NULL;      // 加密后的半加密向量
    unsigned int i = 0;
    int t = 0;
    /* 合成目录 */
    strcpy(dir_t, userName);
    strcat(dir_t, "/user");

    /* 判断用户是否存在 */
    if(!access(dir_t, 0))
        return U_C_FLASE_UH;

    /* 创建用户文件 */
    mkdir(userName);
    if(!(File = fopen(dir_t, "wb")))
        return U_C_FLASE_UN;
    
    /* 生成iv和半加密iv加数 */
    t = rand()%10 - 5;
    /* 加密数据 */
    for(i = 0; i<16; i++)
    {
        iv[i] = (unsigned char)rand()%246 + 5;
        fputc(userKey[i] ^ userKey[i + 16] ^ iv[i], File);// 写入异或加密向量
        oeiv[i] = iv[i] + t;    //创建半加密向量
    }
    En_Data_Aes_cbc(oeiv, 16, &eiv, &i, userKey, iv);
    fwrite(eiv, i, 1, File);

    /* 清除数据退出 */
    free(eiv);
    fclose(File);
    return U_C_TRUE;
}