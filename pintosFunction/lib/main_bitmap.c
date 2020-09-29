#include "main_bitmap.h"

void dumpdataBitmap(struct bitmap *b) {
    if (b==NULL) return;
    int *bits = (int*)malloc(sizeof(int) * b->bit_cnt);
    elem_type size = *(b->bits);
    for (int i = 0; i < b->bit_cnt; ++i) {
        bits[i] = size%2;
        size/=2;
    }
    for (int i = 0; i < b->bit_cnt; ++i) {
        printf("%d", bits[i]);
    }
    free(bits);
    printf("\n");
}

void deleteBitmap(struct bitmap **b) {
    if (*b==NULL) return;
    free((*b)->bits);
    free(*b);
    *b=NULL;
}

void bitmap_expand(struct bitmap *b, size_t size) {
    int *bits = (int*)malloc(sizeof(int) * (b->bit_cnt));
    size_t len = b->bit_cnt;
    for (int i = 0; i < len; ++i) {
        if (bitmap_all(b, i, 1)) bits[i] = 1;
        else bits[i] = 0;
    }
    free(b->bits);
    free(b);
    b = bitmap_create(len+size);
    for (int i = 0; i < len; ++i) {
        if (bits[i] == 1)
            bitmap_mark(b, i);
    }
    free(bits);
}

void otherBitmapFuncs(struct bitmap **b, char str[]) {
    size_t idx, len;
    if (strcmp(str, "bitmap_mark")==0) {
        scanf("%s %zu", str, &idx);
        bitmap_mark(b[str[2]-'0'], idx);
    }
    else if (strcmp(str, "bitmap_all")==0) {
        scanf("%s %zu %zu", str, &idx, &len);
        if(bitmap_all(b[str[2]-'0'], idx, len)) printf("true\n");
        else printf("false\n");
    }
    else if (strcmp(str, "bitmap_any")==0) {
        scanf("%s %zu %zu", str, &idx, &len);
        if (bitmap_any(b[str[2]-'0'], idx, len)) printf("true\n");
        else printf("false\n");
    }
    else if (strcmp(str, "bitmap_contains")==0) {
        char str1[6]; bool tf = false;
        scanf("%s %zu %zu %s", str, &idx, &len, str1);
        if (strcmp(str1, "true")==0) tf = true;
        if (bitmap_contains(b[str[2]-'0'], idx, len, tf)) printf("true\n");
        else printf("false\n");
    }
    else if (strcmp(str, "bitmap_count")==0) {
        char str1[6]; bool tf = false;
        scanf("%s %zu %zu %s", str, &idx, &len, str1);
        if (strcmp(str1, "true")==0) tf = true;
        printf("%zu\n", bitmap_count(b[str[2]-'0'], idx, len, tf));
    }
    else if (strcmp(str, "bitmap_dump")==0) {
        scanf("%s", str);
        bitmap_dump(b[str[2]-'0']);
    }
    else if (strcmp(str, "bitmap_expand")==0) {
        scanf("%s %zu", str, &len);
        bitmap_expand(b[str[2]-'0'], len);
    }
    else if (strcmp(str, "bitmap_flip")==0) {
        scanf("%s %zu", str, &idx);
        bitmap_flip(b[str[2]-'0'], idx);
    }
    else if (strcmp(str, "bitmap_none")==0) {
        scanf("%s %zu %zu", str, &idx, &len);
        if (bitmap_none(b[str[2]-'0'], idx, len)) printf("true\n");
        else printf("false\n");
    }
    else if (strcmp(str, "bitmap_reset")==0) {
        scanf("%s %zu", str, &idx);
        bitmap_reset(b[str[2]-'0'], idx);
    }
    else if (strcmp(str, "bitmap_scan")==0) {
        char str1[6]; bool tf = false;
        scanf("%s %zu %zu %s", str, &idx, &len, str1);
        if (strcmp(str1, "true")==0) tf = true;
        printf("%zu\n", bitmap_scan(b[str[2]-'0'], idx, len, tf));
    }
    else if (strcmp(str, "bitmap_scan_and_flip")==0) {
        char str1[6]; bool tf = false;
        scanf("%s %zu %zu %s", str, &idx, &len, str1);
        if (strcmp(str1, "true")==0) tf = true;
        printf("%zu\n", bitmap_scan_and_flip(b[str[2]-'0'], idx, len, tf));
    }
    else if (strcmp(str, "bitmap_set")==0) {
        char str1[6]; bool tf = false;
        scanf("%s %zu %s", str, &idx, str1);
        if (strcmp(str1, "true")==0) tf = true;
        bitmap_set(b[str[2]-'0'], idx, tf);
    }
    else if (strcmp(str, "bitmap_set_all")==0) {
        char str1[6]; bool tf = false;
        scanf("%s %s", str, str1);
        if (strcmp(str1, "true")==0) tf = true;
        bitmap_set_all(b[str[2]-'0'], tf);
    }
    else if (strcmp(str, "bitmap_set_multiple")==0) {
        char str1[6]; bool tf = false;
        scanf("%s %zu %zu %s", str, &idx, &len, str1);
        if (strcmp(str1, "true")==0) tf = true;
        bitmap_set_multiple(b[str[2]-'0'], idx, len, tf);
    }
    else if (strcmp(str, "bitmap_size")==0) {
        char str1[6];
        scanf("%s", str);
        printf("%zu\n", bitmap_size(b[str[2]-'0']));
    }
    else if (strcmp(str, "bitmap_test")==0) {
        scanf("%s %zu", str, &idx);
        if (bitmap_test(b[str[2]-'0'], idx)) printf("true\n");
        else printf("false\n");
    }
}