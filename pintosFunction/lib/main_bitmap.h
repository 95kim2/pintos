#ifndef __MAIN_BITMAP_H
#define __MAIN_BITMAP_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"
void dumpdataBitmap(struct bitmap *b);
// bitmap 출력
void deleteBitmap(struct bitmap **b);
// bitmap 삭제
void bitmap_expand(struct bitmap *b, size_t size);
// bitmap뒤에 size만큼 0을 붙인다.
void otherBitmapFuncs(struct bitmap **b, char str[]);
// dumpdata create delete 이외의 명령어에 대한 기능 수행
#endif