#ifndef __MAIN_HASH_H
#define __MAIN_HASH_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
void createHash(struct hash **h);
// hashtable 생성
void dumpdataHash(struct hash *h);
// hashtable 출력
void deleteHash(struct hash **h);
// hasttable 삭제
void otherHashFuncs(struct hash **h, char str[]);
// dumpdata create delete 이외의 명령어에 대한 기능 수행
bool hash_less(const struct hash_elem *a, const struct hash_elem *b, void *aux);
void destructor(struct hash_elem *a, void *aux);
unsigned int hash_func(const struct hash_elem *a, void *aux);

/* Returns a hash of integer I. */
unsigned
hash_int_2 (int i);
#endif