#include "code.h"

unsigned int En_Data_Aes_cbc(const unsigned char*inData, const unsigned int inSize,
            unsigned char**outData, unsigned int *outSize, 
            const unsigned char*key, const unsigned char*iv)
{
    int temp;
    /* ctx结构体 */
    EVP_CIPHER_CTX *ctx;

    /* 初始化ctx */
    if(!EVP_CIPHER_CTX_init(ctx = EVP_CIPHER_CTX_new()))
        return 0;

    /* 计算加密后空间 */
    *outSize = inSize + AES_BLOCK_SIZE - inSize%AES_BLOCK_SIZE;
    /* 分配加密后的空间 */
    *outData = (unsigned char*)malloc(*outSize);

    /* 初始化加密 */
    if(!EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        return 0;
    /* 加密数据 */
    if(!EVP_EncryptUpdate(ctx, *outData, &temp, inData, inSize))
        return 0;
    /* 加密最后一段 */
    if(!EVP_EncryptFinal_ex(ctx, *outData + temp, &temp))
        return 0;
        
    /* 释放数据 */
    EVP_CIPHER_CTX_cleanup(ctx);
    EVP_CIPHER_CTX_free(ctx);
    return 1;
}

unsigned int De_Data_Aes_cbc(const unsigned char*inData, const unsigned int inSize,
            unsigned char**outData, unsigned int *outSize, 
            const unsigned char*key, const unsigned char*iv)
{
    int temp = 0;
    /* ctx结构体 */
    EVP_CIPHER_CTX *ctx;

    /* 初始化ctx */
    if(!EVP_CIPHER_CTX_init(ctx = EVP_CIPHER_CTX_new()))
        return 0;
    /* 分配加密后的空间 */
    *outData = (unsigned char*)malloc(*outSize = inSize);

    /* 初始化加密 */
    if(!EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        return 0;
    /* 加密数据 */
    if(!EVP_DecryptUpdate(ctx, *outData, outSize, inData, inSize))
        return 0;
    /* 加密最后一段 */
    if(!EVP_DecryptFinal_ex(ctx, *outData + *outSize, &temp))
        return 0;
        
    /* 调整空间大小 */
    *outSize += temp;
    if(_msize(*outData) != *outSize)
        *outData = realloc(*outData, *outSize);

    /* 释放数据 */
    EVP_CIPHER_CTX_cleanup(ctx);
    EVP_CIPHER_CTX_free(ctx);
    return 1;
}