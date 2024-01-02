/**
 * @file img_utils.c
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-02
 * 
 * @copyright Copyright (c) 2021 - 2024 co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#include "img_utils.h"
#include <string.h>

#pragma pack(push, 1)
typedef struct {
    uint32_t width;
    uint32_t height;
    uint8_t bit_depth;
    uint8_t color_type;
    uint8_t compression;
    uint8_t filter;
    uint8_t interlace;
} IHDRChunk;
#pragma pack(pop)

#define SWAP_UINT32(x) (((x) >> 24) | \
                       (((x) & 0x00FF0000) >> 8) | \
                       (((x) & 0x0000FF00) << 8) | \
                       ((x) << 24))

/**
 * @brief 获取图片信息
 * 
 * @param src 图片数据
 * @param size 图片数据大小
 * @param header 图片信息
 * @return uint8_t 
 */
uint8_t img_png_get_info(const uint8_t * src, int size, img_header_t * header)
{
     if (size < 8) {
        return 0;
    }

    const uint8_t png_signature[8] = { 0x89, 'P', 'N', 'G', 0x0D, 0x0A, 0x1A, 0x0A };
    if (memcmp(src, png_signature, 8) != 0) {
        return 0; // 签名不匹配
    }

    src += 8;
    size -= 8;

    // 检查 IHDR 块
    if (size < 25) { // IHDR块的最小长度：4(长度) + 4(类型) + 13(IHDR数据) + 4(CRC)
        return 0; // 剩余数据太短，不足以包含完整的 IHDR 块
    }

    // 读取块长度
    uint32_t chunk_length = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];
    if (chunk_length != 13) {
        return 0; // IHDR块长度不正确
    }

    // 确认块类型是 "IHDR"
    if (src[4] != 'I' || src[5] != 'H' || src[6] != 'D' || src[7] != 'R') {
        return 0; // 块类型不是 IHDR
    }
    src += 8;
    IHDRChunk *ihdr;
    ihdr = (IHDRChunk *)src;
    // 大小端转换
    header->width = SWAP_UINT32(ihdr->width);
    header->height = SWAP_UINT32(ihdr->height);
    return 1;
}


