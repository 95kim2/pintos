#include "main_list.h"
#include "main_bitmap.h"
#include "main_hash.h"

struct list* l[10];
struct bitmap* b[10];
struct hash* h[10];
char str[50];

int main(void) {
    for (int i = 0; i < 10; ++i) {
        l[i] = NULL;
        b[i] = NULL;
        h[i] = NULL;
    }
    
    scanf("%s", str);
    while(strcmp(str, "quit")!=0) {
        if (strcmp(str, "hash_int_2")==0) {
            int num;
            scanf("%d", &num);
            printf("NO.2: %u\n", hash_int_2(num));
            printf("NO.1: %u\n", hash_int(num));
        }
        else if (strcmp(str, "create")==0) {
            scanf("%s", str);
            if (strcmp(str, "list")==0) {
                scanf("%s", str);
                createList(l+(str[4]-'0'));
            }
            else if (strcmp(str, "hashtable")==0) {
                scanf("%s", str);
                createHash(h+(str[4]-'0'));
            }
            else if (strcmp(str, "bitmap")==0) {
                int size;
                scanf("%s %d", str, &size);
                b[str[2]-'0'] = bitmap_create((elem_type)size);
            }
        }
        else if (strcmp(str, "dumpdata")==0) {
            scanf("%s", str);
            if (strlen(str)==3)
                dumpdataBitmap(b[str[2]-'0']);
            else if (str[0] == 'l')
                dumpdataList(l[str[4]-'0']);
            else
                dumpdataHash(h[str[4]-'0']);
        }
        else if (strcmp(str, "delete")==0) {
            scanf("%s", str);
            if (str[0] == 'l')
                deleteList(l+(str[4]-'0'));
            else if (str[0] == 'b') 
                deleteBitmap(b+(str[2]-'0'));
            else if (str[0] == 'h')
                deleteHash(h+(str[4]-'0'));
        }
        else if (str[0] == 'l')
            otherListFuncs(l, str);
        else if (str[0] == 'b')
            otherBitmapFuncs(b, str);
        else if (str[0] == 'h') 
            otherHashFuncs(h, str);

        scanf("%s", str);
    }


    return 0;
}