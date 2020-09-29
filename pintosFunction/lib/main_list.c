#include "main_list.h"

void createList(struct list** l) {
    if (*l!=NULL)
        deleteList(l);
    *l = (struct list*)malloc(sizeof(struct list));
    list_init((*l));
}

void dumpdataList(struct list* l) {
    struct list_elem* iter;
    struct list_item* tempItem;
    if (l==NULL) return;
    bool flagDump = false;
    for (iter=l->head.next; iter!=&(l->tail); iter=iter->next) {
        flagDump = true;
        tempItem = list_entry(iter, struct list_item, elem);
        printf("%d ", tempItem->data);
    }
    if (flagDump) {
        printf("\n");
    }
}

void deleteList(struct list** l) {
    if (*l==NULL) return;
    struct list_elem *iter;
    struct list_item *tempItem;
    for (iter=list_begin(*l); iter!=&((*l)->tail); iter=iter->next) {
        tempItem = list_entry(iter, struct list_item, elem);
        tempItem->elem.next->prev = tempItem->elem.prev;
        tempItem->elem.prev->next = tempItem->elem.next;
        iter = iter->prev;
        free(tempItem);
    }
    free(*l);
    *l = NULL;
}

bool list_less(const struct list_elem* a, const struct list_elem* b, void*aux) {
    if (list_entry(a, struct list_item, elem)->data < list_entry(b,struct list_item, elem)->data)
        return true;
    else
        return false;
}

void listSwap(struct list* l, int idx_a, int idx_b) {
    if (l==NULL || idx_a == idx_b || list_rend(l)->next==list_end(l)) return;
    if (idx_a < 0) idx_a = 0;
    if (idx_b < 0) idx_b = 0;
    struct list_elem *a, *b, *tempN, *tempP;
    a=list_begin(l);
    b=a;
    for (int i = 0; i < idx_a && a->next != list_end(l); a=a->next, ++i);
    for (int i = 0; i < idx_b && b->next != list_end(l); b=b->next, ++i);
    if (a==b) return;
    else if (a->next==b || b->next==a) {
        if (b->next==a) {tempN=a;a=b;b=tempN;}
        a->prev->next = b;
        b->next->prev = a;
        tempN = b->next;
        b->next = a;    b->prev = a->prev;
        a->prev = b;    a->next = tempN;
    }
    else {
        a->next->prev = b;  a->prev->next = b;
        b->next->prev = a;  b->prev->next = a;
        tempP = a->prev;    tempN = a->next;
        a->next = b->next;  a->prev = b->prev;
        b->next = tempN;    b->prev = tempP;
    }
}

void listShuffle(struct list* l) {
    srand(time(NULL));
    int n = 0, size = list_size(l), s, e, SIZE;

    if (l==NULL || size==1 || list_rend(l)->next==list_end(l)) return;
    SIZE = 10*size;
    while (n++ <= SIZE) {
        s = (rand()*rand())%size;
        e = (rand()*rand())%size;
        listSwap(l, s, e);
    }
}

void otherListFuncs(struct list **l, char str[]) {
    int data, idx, idx1; char str2[10];
    if (strcmp(str, "list_push_back")==0) {
        scanf("%s %d", str, &data);
        struct list_item *tempItem = (struct list_item*)malloc(sizeof(struct list_item));
        tempItem->data = data;
        list_push_back(l[str[4]-'0'], &(tempItem->elem));
    }
    else if (strcmp(str, "list_push_front")==0) {
        scanf("%s %d", str, &data);
        struct list_item *tempItem = (struct list_item*)malloc(sizeof(struct list_item));
        tempItem->data = data;
        list_push_front(l[str[4]-'0'], &(tempItem->elem));
    }
    else if (strcmp(str, "list_front")==0) {
        scanf("%s", str);
        printf("%d\n", list_entry(list_front(l[str[4]-'0']), struct list_item, elem)->data);
    }
    else if (strcmp(str, "list_back")==0) {
        scanf("%s", str);
        printf("%d\n", list_entry(list_back(l[str[4]-'0']), struct list_item, elem)->data);
    }
    else if (strcmp(str, "list_pop_back")==0) {
        scanf("%s", str);
        free(list_entry(list_pop_back(l[str[4]-'0']), struct list_item, elem));
    }
    else if (strcmp(str, "list_pop_front")==0) {
        scanf("%s", str);
        free(list_entry(list_pop_front(l[str[4]-'0']), struct list_item, elem));
    }
    else if (strcmp(str, "list_insert")==0) {
        scanf("%s %d %d", str, &idx, &data);
        struct list_item* tempItem = (struct list_item*)malloc(sizeof(struct list_item));
        tempItem->data = data;
        struct list_elem* iter = &(l[str[4]-'0']->head);
        for (int i=0; i<=idx && iter!=&(l[str[4]-'0']->tail); iter=iter->next, ++i);
        list_insert(iter, &(tempItem->elem));
    }
    else if (strcmp(str, "list_insert_ordered")==0) {
        scanf("%s %d", str, &data);
        struct list_item* tempItem = (struct list_item*)malloc(sizeof(struct list_item));
        tempItem->data = data;
        list_insert_ordered(l[str[4]-'0'], &(tempItem->elem), list_less, NULL);
    }
    else if (strcmp(str, "list_empty")==0) {
        scanf("%s", str);
        if(list_empty(l[str[4]-'0'])) printf("true\n");
        else printf("false\n");
    }
    else if (strcmp(str, "list_size")==0) {
        scanf("%s", str);
        printf("%zu\n", list_size(l[str[4]-'0']));
    }
    else if (strcmp(str, "list_max")==0) {
        scanf("%s", str);
        printf("%d\n", list_entry(list_max(l[str[4]-'0'], list_less, NULL), struct list_item, elem)->data);
    }
    else if (strcmp(str, "list_min")==0) {
        scanf("%s", str);
        printf("%d\n", list_entry(list_min(l[str[4]-'0'], list_less, NULL), struct list_item, elem)->data);
    }
    else if (strcmp(str, "list_remove")==0) {
        scanf("%s %d", str, &idx);
        struct list_elem* iter = list_rend(l[str[4]-'0']);
        for (int i = 0; i <= idx && iter->next != list_end(l[str[4]-'0']); ++i, iter=iter->next);
        list_remove(iter);
        free(list_entry(iter, struct list_item, elem));
    }
    else if (strcmp(str, "list_reverse")==0) {
        scanf("%s", str);
        list_reverse(l[str[4]-'0']);
    }
    else if (strcmp(str, "list_shuffle")==0) {
        scanf("%s", str);
        listShuffle(l[str[4]-'0']);
    }
    else if (strcmp(str, "list_sort")==0) {
        scanf("%s", str);
        list_sort(l[str[4]-'0'], list_less, NULL);
    }
    else if (strcmp(str, "list_splice")==0) {
        scanf("%s %d %s %d %d", str, &idx, str2, &idx1, &data);
        struct list_elem *before, *first, *last;

        before = list_begin(l[str[4]-'0']);
        for (int i = 0; i < idx; ++i, before=before->next);

        first = list_begin(l[str2[4]-'0']);
        for (int i = 0; i < idx1; ++i, first=first->next);

        last = first;
        for (int i = 0; i < data-idx1; ++i, last=last->next);

        list_splice(before, first, last);           
    }
    else if (strcmp(str, "list_swap")==0) {
        scanf("%s %d %d", str, &idx, &idx1);
        listSwap(l[str[4]-'0'], idx, idx1);
    }
    else if (strcmp(str, "list_unique")==0) {
        char c;
        scanf("%s", str);
        c = getchar();
        while(c!='\n') {
            if ('0'<=c&&c<='9')
                break;
            c = getchar();
        }
        if (c!='\n')
            list_unique(l[str[4]-'0'], l[c-'0'], list_less, NULL);
        else
            list_unique(l[str[4]-'0'], NULL, list_less, NULL);
    }
}




// int listSizeFromTo(struct list_elem* s, struct list_elem* e) {
//     int i = 1;
//     for (; s!=e; s=s->next, ++i);
//     return i;
// }

// void binarySort(struct list* l, struct list_elem* s, struct list_elem *e){
//     int size = listSizeFromTo(s, e);
//     if (size <= 1) return;
//     size = (size-1)/2;

//     struct list_elem *mid = s, *tempEnd=e->next, *tempStart=s->prev;
//     for (int i=0; i<size; ++i, mid=mid->next);

//     binarySort(l,tempStart->next, mid);
//     binarySort(l,mid->next, tempEnd->prev);

//     int size1, size2, cnt1=0, cnt2=0;
//     struct list_elem *cur, *s1=tempStart->next, *s2=mid->next;
//     size1 = listSizeFromTo(s1, mid); size2 = listSizeFromTo(s2, tempEnd->prev);
//     cur = tempStart;
//     while(cnt1 < size1 && cnt2 < size2) {
//         if (list_entry(s1, struct list_item, elem)->data < list_entry(s2, struct list_item, elem)->data) {
//             cur->next = s1;
//             s1->prev = cur;
//             s1 = s1->next;
//             cnt1++;
//         }
//         else {
//             cur->next = s2;
//             s2->prev = cur;
//             s2 = s2->next;
//             cnt2++;
//         }
//         cur=cur->next;
//     }
//     if (cnt1 < size1) {
//         cur->next = s1;
//         s1->prev = cur;
//         mid->next = tempEnd;
//         tempEnd->prev = mid;
//     }
//     else if (cnt2 < size2) {
//         cur->next = s2;
//         s2->prev = cur;
//     }
// }

// void listSort(struct list* l) {
//     if (l==NULL || list_size(l) <= 1) return;
//     binarySort(l, list_begin(l), list_rbegin(l));
// }

// void listSplice(struct list* l0, int idx0, struct list* l1, int idx1, int len) {
//     if (len <= 0 || idx0 >= listSizeFromTo(list_begin(l0), list_rbegin(l0)) || idx1 >= listSizeFromTo(list_begin(l1), list_rbegin(l1))) return;
//     struct list_elem *subHead0, *subTail0, *subHead1, *subTail1;

//     subHead0 = list_rend(l0);
//     for (int i = 0; i < idx0; ++i, subHead0=subHead0->next);
//     subTail0 = subHead0->next;

//     subHead1 = list_rend(l1);
//     for (int i = 0; i < idx1; ++i, subHead1=subHead1->next);
//     subTail1 = subHead1->next;

//     for (int i = 0; i < len && subTail1 != list_rbegin(l1); subTail1=subTail1->next);

//     subHead0->next = subHead1->next;
//     subHead1->next->prev = subHead0;

//     subTail0->prev = subTail1->prev;
//     subTail1->prev->next = subTail0;

//     subHead1->next = subTail1;
//     subTail1->prev = subHead1;
// }
