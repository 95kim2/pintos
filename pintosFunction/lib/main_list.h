#ifndef __MAIN_LIST_H
#define __MAIN_LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "list.h"

void createList(struct list** l);
//List 생성
void dumpdataList(struct list* l);
//List 데이터 순서대로 모두 출력
bool list_less(const struct list_elem* a, const struct list_elem* b, void*aux);
//List 비교 함수 a data < b data -> true 아니면 false
void deleteList(struct list** l);
//List 데이터 모두 해제
void listSwap(struct list* l, int idx_a, int idx_b);
//swap btween index idx_a, idx_b each other
void listShuffle(struct list* l);
//List를 무작위로 섞는다.
void otherListFuncs(struct list **l, char str[]);
//dumpdata delete create 이외의 명령어에 대한 기능 수행
#endif