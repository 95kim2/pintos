#include "main_hash.h"
#include "list.h"
#define FNV_32_PRIME 1073676287u
#define FNV_32_BASIS 2166136261u

/* Returns a hash of integer I. */
unsigned
hash_int_2 (int i) 
{   
    int size = sizeof(i) * 8;
    unsigned int temp = (unsigned int)i;
    int hash = FNV_32_BASIS;
    while(size--) {
        hash = (hash*FNV_32_PRIME) ^ (++temp * temp++);
    }
    return hash;
}

bool hash_less(const struct hash_elem *a, const struct hash_elem *b, void *aux) {
    if (a->value < b->value) return true;
    else return false;
}

void destructor(struct hash_elem *a, void *aux) {
    free(a);
}

void deleteHash(struct hash **h) {
    hash_destroy(*h,destructor);
    free(*h);
    *h = NULL;
}

unsigned int hash_func(const struct hash_elem *a, void *aux) {
    hash_int(a->value);
}

void createHash(struct hash **h) {
    if (*h != NULL) deleteHash(h);

    *h = (struct hash*)malloc(sizeof(struct hash));
    hash_init(*h, hash_func, hash_less, NULL);
    struct list *tempBucket;
    for (int i = 0; i < (*h)->bucket_cnt; ++i) {
        tempBucket = (*h)->buckets + i;
        list_init(tempBucket);
    }
}

void dumpdataHash(struct hash *h) {
    if (h==NULL) return;
    struct list *bucket;
    struct list_elem *iter;
    bool flag = false;
    for (int i = 0; i < h->bucket_cnt; ++i) {
        bucket = (h->buckets) + i;
        for (iter=list_begin(bucket); iter != list_end(bucket); iter=iter->next) {
            flag = true;
            printf("%d ", list_entry(iter, struct hash_elem, list_elem)->value);
        }
    }
    if (flag) printf("\n");
}

void square(struct hash_elem *a, void *aux) {
    a->value *= (a->value);
}

void triple(struct hash_elem *a, void *aux) {
    a->value *= (a->value)*(a->value);
}

void otherHashFuncs(struct hash **h, char str[]) {
    if (strcmp(str, "hash_insert")==0) {
        int val;
        scanf("%s %d", str, &val);
        struct hash_elem* hashElem = (struct hash_elem*)malloc(sizeof(struct hash_elem));
        hashElem->value = val;
        hash_insert(h[str[4]-'0'], hashElem);
    }
    else if (strcmp(str, "hash_apply")==0) {
        char str2[20];
        scanf("%s %s", str, str2);
        if (strcmp(str2, "square")==0) 
            hash_apply(h[str[4]-'0'], square);
        else if (strcmp(str2, "triple")==0)
            hash_apply(h[str[4]-'0'], triple);
    }
    else if (strcmp(str, "hash_delete")==0) {
        int val;
        scanf("%s %d", str, &val);
        struct hash_elem temp;
        temp.value = val;
        struct hash_elem *tempFree = hash_delete(h[str[4]-'0'], &temp);
        free(tempFree);
    }
    else if (strcmp(str, "hash_empty")==0) {
        scanf("%s", str);
        if (hash_empty(h[str[4]-'0'])) printf("true\n");
        else printf("false\n");
    }
    else if (strcmp(str, "hash_size")==0) {
        scanf("%s", str);
        printf("%zu\n", hash_size(h[str[4]-'0']));
    }
    else if (strcmp(str, "hash_clear")==0) {
        scanf("%s", str);
        hash_clear(h[str[4]-'0'], destructor);
    }
    else if (strcmp(str, "hash_find")==0) {
        int val;
        scanf("%s %d", str, &val);
        struct hash_elem temp, *tempFound;
        temp.value = val;
        tempFound = hash_find(h[str[4]-'0'], &temp);
        if (tempFound!=NULL)
            printf("%d\n", tempFound->value);
    }
    else if (strcmp(str, "hash_replace")==0) {
        int val;
        scanf("%s %d", str, &val);
        struct hash_elem *newElem = (struct hash_elem*)malloc(sizeof(struct hash_elem));
        newElem->value = val;
        newElem = hash_replace(h[str[4]-'0'], newElem);
        if (newElem!=NULL) free(newElem);
    }
}