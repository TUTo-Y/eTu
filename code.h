/*
*   程序名称 : 加密解密 
*   程序作者 : 时光催老人
*   修改时间 : 22-5-1
*   
*/
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include "control.h"

/**
 *  \brief 使用AES的cbc模式加密数据
 *
 *  \param inData   输入数据
 *  \param inSize   输入大小
 *  \param outData  输出数据
 *  \param outSize  输出大小
 *  \param key      秘钥
 *  \param iv       初始化向量
 * 
 *  \return 是否加密成功(0加密失败, 1加密成功)
 */
unsigned int En_Data_Aes_cbc(const unsigned char*inData, const unsigned int inSize,
            unsigned char**outData, unsigned int *outSize, 
            const unsigned char*key, const unsigned char*iv);

/**
 *  \brief 使用AES的cbc模式解密数据
 *
 *  \param inData   输入数据
 *  \param inSize   输入大小
 *  \param outData  输出数据
 *  \param outSize  输出大小
 *  \param key      秘钥
 *  \param iv       初始化向量
 * 
 *  \return 是否解密成功(0加密失败, 1加密成功)
 */
unsigned int De_Data_Aes_cbc(const unsigned char*inData, const unsigned int inSize,
            unsigned char**outData, unsigned int *outSize, 
            const unsigned char*key, const unsigned char*iv);