#include "Test.h"
#include "DS_Array.h"

int IntCmp(const void *l, const void *r) {
    return *((int*) l) - *((int*) r);
}

int ArrChk(struct DS_Array *arr, size_t size, int len, int hasCmp) {
    int failed = 0;
    if(!arr->compare != !hasCmp) failed++;
    if(arr->length != len) failed++;
    if(arr->size != size) failed++;
    return failed;
}

int NewDeleteZero() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 0, IntCmp);
    if(arr == 0) return ++failed;
    failed += ArrChk(arr, sizeof(int), 0, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int NewDeleteMany() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 4, IntCmp);
    if(arr == 0) return ++failed;
    failed += ArrChk(arr, sizeof(int), 4, 1);
    *((int*) arr->base + 0) = 0;
    *((int*) arr->base + 1) = 1;
    *((int*) arr->base + 2) = 2;
    *((int*) arr->base + 3) = 3;
    DS_ArrayDelete(arr);
    return failed;
}

int ResizeBigger() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 0, IntCmp);
    arr = DS_ArrayResize(arr, 4);
    if(arr == 0) return ++failed;
    failed += ArrChk(arr, sizeof(int), 4, 1);
    *((int*) arr->base + 0) = 0;
    *((int*) arr->base + 1) = 1;
    *((int*) arr->base + 2) = 2;
    *((int*) arr->base + 3) = 3;
    arr = DS_ArrayResize(arr, 8);
    if(arr == 0) return ++failed;
    failed += ArrChk(arr, sizeof(int), 8, 1);
    *((int*) arr->base + 4) = 4;
    *((int*) arr->base + 5) = 5;
    *((int*) arr->base + 6) = 6;
    *((int*) arr->base + 7) = 7;
    if(*((int*) arr->base + 0) != 0) failed++;
    if(*((int*) arr->base + 1) != 1) failed++;
    if(*((int*) arr->base + 2) != 2) failed++;
    if(*((int*) arr->base + 3) != 3) failed++;
    if(*((int*) arr->base + 4) != 4) failed++;
    if(*((int*) arr->base + 5) != 5) failed++;
    if(*((int*) arr->base + 6) != 6) failed++;
    if(*((int*) arr->base + 7) != 7) failed++;
    DS_ArrayDelete(arr);
    return failed;
}

int ResizeSmaller() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 8, IntCmp);
    *((int*) arr->base + 0) = 0;
    *((int*) arr->base + 1) = 1;
    *((int*) arr->base + 2) = 2;
    *((int*) arr->base + 3) = 3;
    *((int*) arr->base + 4) = 4;
    *((int*) arr->base + 5) = 5;
    *((int*) arr->base + 6) = 6;
    *((int*) arr->base + 7) = 7;
    arr = DS_ArrayResize(arr, 4);
    if(arr == 0) failed++;
    failed += ArrChk(arr, sizeof(int), 4, 1);
    if(*((int*) arr->base + 0) != 0) failed++;
    if(*((int*) arr->base + 1) != 1) failed++;
    if(*((int*) arr->base + 2) != 2) failed++;
    if(*((int*) arr->base + 3) != 3) failed++;
    arr = DS_ArrayResize(arr, 0);
    if(arr == 0) return ++failed;
    failed += ArrChk(arr, sizeof(int), 0, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int AtAll() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 4, IntCmp);
    *((int*) DS_ArrayAt(arr, 0)) = 0;
    *((int*) DS_ArrayAt(arr, 1)) = 1;
    *((int*) DS_ArrayAt(arr, 2)) = 2;
    *((int*) DS_ArrayAt(arr, 3)) = 3;
    if(*((int*) DS_ArrayAt(arr, 0)) != 0) failed++;
    if(*((int*) DS_ArrayAt(arr, 1)) != 1) failed++;
    if(*((int*) DS_ArrayAt(arr, 2)) != 2) failed++;
    if(*((int*) DS_ArrayAt(arr, 3)) != 3) failed++;
    failed += ArrChk(arr, sizeof(int), 4, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int CopyFromZero() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 0, IntCmp);
    int copy[0] = {};
    if(DS_ArrayCopyFrom(arr, 0, 0, copy) != arr) failed++;
    failed += ArrChk(arr, sizeof(int), 0, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int CopyFromFirstHalf() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 8, IntCmp);
    *((int*) arr->base + 0) = 0;
    *((int*) arr->base + 1) = 1;
    *((int*) arr->base + 2) = 2;
    *((int*) arr->base + 3) = 3;
    *((int*) arr->base + 4) = 4;
    *((int*) arr->base + 5) = 5;
    *((int*) arr->base + 6) = 6;
    *((int*) arr->base + 7) = 7;
    int copy[4] = {8, 9, 10, 11};
    if(DS_ArrayCopyFrom(arr, 0, 4, copy) != arr) failed++;
    if(*((int*) arr->base + 0) != 8) failed++;
    if(*((int*) arr->base + 1) != 9) failed++;
    if(*((int*) arr->base + 2) != 10) failed++;
    if(*((int*) arr->base + 3) != 11) failed++;
    if(*((int*) arr->base + 4) != 4) failed++;
    if(*((int*) arr->base + 5) != 5) failed++;
    if(*((int*) arr->base + 6) != 6) failed++;
    if(*((int*) arr->base + 7) != 7) failed++;
    failed += ArrChk(arr, sizeof(int), 8, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int CopyFromSecondHalf() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 8, IntCmp);
    *((int*) arr->base + 0) = 0;
    *((int*) arr->base + 1) = 1;
    *((int*) arr->base + 2) = 2;
    *((int*) arr->base + 3) = 3;
    *((int*) arr->base + 4) = 4;
    *((int*) arr->base + 5) = 5;
    *((int*) arr->base + 6) = 6;
    *((int*) arr->base + 7) = 7;
    int copy[4] = {8, 9, 10, 11};
    if(DS_ArrayCopyFrom(arr, 4, 8, copy) != arr) failed++;
    if(*((int*) arr->base + 0) != 0) failed++;
    if(*((int*) arr->base + 1) != 1) failed++;
    if(*((int*) arr->base + 2) != 2) failed++;
    if(*((int*) arr->base + 3) != 3) failed++;
    if(*((int*) arr->base + 4) != 8) failed++;
    if(*((int*) arr->base + 5) != 9) failed++;
    if(*((int*) arr->base + 6) != 10) failed++;
    if(*((int*) arr->base + 7) != 11) failed++;
    failed += ArrChk(arr, sizeof(int), 8, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int CopyFromMiddle() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 8, IntCmp);
    *((int*) arr->base + 0) = 0;
    *((int*) arr->base + 1) = 1;
    *((int*) arr->base + 2) = 2;
    *((int*) arr->base + 3) = 3;
    *((int*) arr->base + 4) = 4;
    *((int*) arr->base + 5) = 5;
    *((int*) arr->base + 6) = 6;
    *((int*) arr->base + 7) = 7;
    int copy[4] = {8, 9, 10, 11};
    if(DS_ArrayCopyFrom(arr, 2, 6, copy) != arr) failed++;
    if(*((int*) arr->base + 0) != 0) failed++;
    if(*((int*) arr->base + 1) != 1) failed++;
    if(*((int*) arr->base + 2) != 8) failed++;
    if(*((int*) arr->base + 3) != 9) failed++;
    if(*((int*) arr->base + 4) != 10) failed++;
    if(*((int*) arr->base + 5) != 11) failed++;
    if(*((int*) arr->base + 6) != 6) failed++;
    if(*((int*) arr->base + 7) != 7) failed++;
    failed += ArrChk(arr, sizeof(int), 8, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int CopyFromAll() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 8, IntCmp);
    *((int*) arr->base + 0) = 0;
    *((int*) arr->base + 1) = 1;
    *((int*) arr->base + 2) = 2;
    *((int*) arr->base + 3) = 3;
    *((int*) arr->base + 4) = 4;
    *((int*) arr->base + 5) = 5;
    *((int*) arr->base + 6) = 6;
    *((int*) arr->base + 7) = 7;
    int copy[8] = {8, 9, 10, 11, 12, 13, 14, 15};
    if(DS_ArrayCopyFrom(arr, 0, 8, copy) != arr) failed++;
    if(*((int*) arr->base + 0) != 8) failed++;
    if(*((int*) arr->base + 1) != 9) failed++;
    if(*((int*) arr->base + 2) != 10) failed++;
    if(*((int*) arr->base + 3) != 11) failed++;
    if(*((int*) arr->base + 4) != 12) failed++;
    if(*((int*) arr->base + 5) != 13) failed++;
    if(*((int*) arr->base + 6) != 14) failed++;
    if(*((int*) arr->base + 7) != 15) failed++;
    failed += ArrChk(arr, sizeof(int), 8, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int CopyToZero() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 0, IntCmp);
    int copy[0] = {};
    if(DS_ArrayCopyTo(arr, 0, 0, copy) != arr) failed++;
    failed += ArrChk(arr, sizeof(int), 0, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int CopyToFirstHalf() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 8, IntCmp);
    *((int*) arr->base + 0) = 0;
    *((int*) arr->base + 1) = 1;
    *((int*) arr->base + 2) = 2;
    *((int*) arr->base + 3) = 3;
    *((int*) arr->base + 4) = 4;
    *((int*) arr->base + 5) = 5;
    *((int*) arr->base + 6) = 6;
    *((int*) arr->base + 7) = 7;
    int copy[4] = {8, 9, 10, 11};
    if(DS_ArrayCopyTo(arr, 0, 4, copy) != arr) failed++;
    if(*((int*) arr->base + 0) != 0) failed++;
    if(*((int*) arr->base + 1) != 1) failed++;
    if(*((int*) arr->base + 2) != 2) failed++;
    if(*((int*) arr->base + 3) != 3) failed++;
    if(*((int*) arr->base + 4) != 4) failed++;
    if(*((int*) arr->base + 5) != 5) failed++;
    if(*((int*) arr->base + 6) != 6) failed++;
    if(*((int*) arr->base + 7) != 7) failed++;
    if(copy[0] != 0) failed++;
    if(copy[1] != 1) failed++;
    if(copy[2] != 2) failed++;
    if(copy[3] != 3) failed++;
    failed += ArrChk(arr, sizeof(int), 8, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int CopyToSecondHalf() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 8, IntCmp);
    *((int*) arr->base + 0) = 0;
    *((int*) arr->base + 1) = 1;
    *((int*) arr->base + 2) = 2;
    *((int*) arr->base + 3) = 3;
    *((int*) arr->base + 4) = 4;
    *((int*) arr->base + 5) = 5;
    *((int*) arr->base + 6) = 6;
    *((int*) arr->base + 7) = 7;
    int copy[4] = {8, 9, 10, 11};
    if(DS_ArrayCopyTo(arr, 4, 8, copy) != arr) failed++;
    if(*((int*) arr->base + 0) != 0) failed++;
    if(*((int*) arr->base + 1) != 1) failed++;
    if(*((int*) arr->base + 2) != 2) failed++;
    if(*((int*) arr->base + 3) != 3) failed++;
    if(*((int*) arr->base + 4) != 4) failed++;
    if(*((int*) arr->base + 5) != 5) failed++;
    if(*((int*) arr->base + 6) != 6) failed++;
    if(*((int*) arr->base + 7) != 7) failed++;
    if(copy[0] != 4) failed++;
    if(copy[1] != 5) failed++;
    if(copy[2] != 6) failed++;
    if(copy[3] != 7) failed++;
    failed += ArrChk(arr, sizeof(int), 8, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int CopyToMiddle() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 8, IntCmp);
    *((int*) arr->base + 0) = 0;
    *((int*) arr->base + 1) = 1;
    *((int*) arr->base + 2) = 2;
    *((int*) arr->base + 3) = 3;
    *((int*) arr->base + 4) = 4;
    *((int*) arr->base + 5) = 5;
    *((int*) arr->base + 6) = 6;
    *((int*) arr->base + 7) = 7;
    int copy[4] = {8, 9, 10, 11};
    if(DS_ArrayCopyTo(arr, 2, 6, copy) != arr) failed++;
    if(*((int*) arr->base + 0) != 0) failed++;
    if(*((int*) arr->base + 1) != 1) failed++;
    if(*((int*) arr->base + 2) != 2) failed++;
    if(*((int*) arr->base + 3) != 3) failed++;
    if(*((int*) arr->base + 4) != 4) failed++;
    if(*((int*) arr->base + 5) != 5) failed++;
    if(*((int*) arr->base + 6) != 6) failed++;
    if(*((int*) arr->base + 7) != 7) failed++;
    if(copy[0] != 2) failed++;
    if(copy[1] != 3) failed++;
    if(copy[2] != 4) failed++;
    if(copy[3] != 5) failed++;
    failed += ArrChk(arr, sizeof(int), 8, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int CopyToAll() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 8, IntCmp);
    *((int*) arr->base + 0) = 0;
    *((int*) arr->base + 1) = 1;
    *((int*) arr->base + 2) = 2;
    *((int*) arr->base + 3) = 3;
    *((int*) arr->base + 4) = 4;
    *((int*) arr->base + 5) = 5;
    *((int*) arr->base + 6) = 6;
    *((int*) arr->base + 7) = 7;
    int copy[8] = {8, 9, 10, 11, 12, 13, 14, 15};
    if(DS_ArrayCopyTo(arr, 0, 8, copy) != arr) failed++;
    if(*((int*) arr->base + 0) != 0) failed++;
    if(*((int*) arr->base + 1) != 1) failed++;
    if(*((int*) arr->base + 2) != 2) failed++;
    if(*((int*) arr->base + 3) != 3) failed++;
    if(*((int*) arr->base + 4) != 4) failed++;
    if(*((int*) arr->base + 5) != 5) failed++;
    if(*((int*) arr->base + 6) != 6) failed++;
    if(*((int*) arr->base + 7) != 7) failed++;
    if(copy[0] != 0) failed++;
    if(copy[1] != 1) failed++;
    if(copy[2] != 2) failed++;
    if(copy[3] != 3) failed++;
    if(copy[4] != 4) failed++;
    if(copy[5] != 5) failed++;
    if(copy[6] != 6) failed++;
    if(copy[7] != 7) failed++;
    failed += ArrChk(arr, sizeof(int), 8, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int CountZero() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 0, IntCmp);
    int val = 42;
    if(DS_ArrayCount(arr, 0, 0, &val) != 0) failed++;
    failed += ArrChk(arr, sizeof(int), 0, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int CountOneNone() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 1, IntCmp);
    *((int*) arr->base + 0) = 0;
    int val = 42;
    if(DS_ArrayCount(arr, 0, 1, &val) != 0) failed++;
    if(*((int*) arr->base + 0) != 0) failed++;
    failed += ArrChk(arr, sizeof(int), 1, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int CountOne() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 1, IntCmp);
    *((int*) arr->base + 0) = 42;
    int val = 42;
    if(DS_ArrayCount(arr, 0, 1, &val) != 1) failed++;
    if(*((int*) arr->base + 0) != 42) failed++;
    failed += ArrChk(arr, sizeof(int), 1, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int CountNone() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 8, IntCmp);
    *((int*) arr->base + 0) = 0;
    *((int*) arr->base + 1) = 1;
    *((int*) arr->base + 2) = 2;
    *((int*) arr->base + 3) = 3;
    *((int*) arr->base + 4) = 4;
    *((int*) arr->base + 5) = 5;
    *((int*) arr->base + 6) = 6;
    *((int*) arr->base + 7) = 7;
    int val = 42;
    if(DS_ArrayCount(arr, 0, 4, &val) != 0) failed++;
    if(DS_ArrayCount(arr, 2, 6, &val) != 0) failed++;
    if(DS_ArrayCount(arr, 4, 8, &val) != 0) failed++;
    if(DS_ArrayCount(arr, 0, 8, &val) != 0) failed++;
    if(*((int*) arr->base + 0) != 0) failed++;
    if(*((int*) arr->base + 1) != 1) failed++;
    if(*((int*) arr->base + 2) != 2) failed++;
    if(*((int*) arr->base + 3) != 3) failed++;
    if(*((int*) arr->base + 4) != 4) failed++;
    if(*((int*) arr->base + 5) != 5) failed++;
    if(*((int*) arr->base + 6) != 6) failed++;
    if(*((int*) arr->base + 7) != 7) failed++;
    failed += ArrChk(arr, sizeof(int), 8, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int Count() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 8, IntCmp);
    *((int*) arr->base + 0) = 42;
    *((int*) arr->base + 1) = 1;
    *((int*) arr->base + 2) = 2;
    *((int*) arr->base + 3) = 42;
    *((int*) arr->base + 4) = 4;
    *((int*) arr->base + 5) = 5;
    *((int*) arr->base + 6) = 6;
    *((int*) arr->base + 7) = 42;
    int val = 42;
    if(DS_ArrayCount(arr, 0, 4, &val) != 2) failed++;
    if(DS_ArrayCount(arr, 2, 6, &val) != 1) failed++;
    if(DS_ArrayCount(arr, 4, 8, &val) != 1) failed++;
    if(DS_ArrayCount(arr, 0, 8, &val) != 3) failed++;
    if(*((int*) arr->base + 0) != 42) failed++;
    if(*((int*) arr->base + 1) != 1) failed++;
    if(*((int*) arr->base + 2) != 2) failed++;
    if(*((int*) arr->base + 3) != 42) failed++;
    if(*((int*) arr->base + 4) != 4) failed++;
    if(*((int*) arr->base + 5) != 5) failed++;
    if(*((int*) arr->base + 6) != 6) failed++;
    if(*((int*) arr->base + 7) != 42) failed++;
    failed += ArrChk(arr, sizeof(int), 8, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int FillZero() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 0, IntCmp);
    int value = 0;
    if(DS_ArrayFill(arr, 0, 0, &value) != arr) failed++;
    failed += ArrChk(arr, sizeof(int), 0, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int FillFirstHalf() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 8, IntCmp);
    *((int*) arr->base + 0) = 0;
    *((int*) arr->base + 1) = 1;
    *((int*) arr->base + 2) = 2;
    *((int*) arr->base + 3) = 3;
    *((int*) arr->base + 4) = 4;
    *((int*) arr->base + 5) = 5;
    *((int*) arr->base + 6) = 6;
    *((int*) arr->base + 7) = 7;
    int value = 8;
    if(DS_ArrayFill(arr, 0, 4, &value) != arr) failed++;
    if(*((int*) arr->base + 0) != 8) failed++;
    if(*((int*) arr->base + 1) != 8) failed++;
    if(*((int*) arr->base + 2) != 8) failed++;
    if(*((int*) arr->base + 3) != 8) failed++;
    if(*((int*) arr->base + 4) != 4) failed++;
    if(*((int*) arr->base + 5) != 5) failed++;
    if(*((int*) arr->base + 6) != 6) failed++;
    if(*((int*) arr->base + 7) != 7) failed++;
    failed += ArrChk(arr, sizeof(int), 8, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int FillSecondHalf() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 8, IntCmp);
    *((int*) arr->base + 0) = 0;
    *((int*) arr->base + 1) = 1;
    *((int*) arr->base + 2) = 2;
    *((int*) arr->base + 3) = 3;
    *((int*) arr->base + 4) = 4;
    *((int*) arr->base + 5) = 5;
    *((int*) arr->base + 6) = 6;
    *((int*) arr->base + 7) = 7;
    int value = 8;
    if(DS_ArrayFill(arr, 4, 8, &value) != arr) failed++;
    if(*((int*) arr->base + 0) != 0) failed++;
    if(*((int*) arr->base + 1) != 1) failed++;
    if(*((int*) arr->base + 2) != 2) failed++;
    if(*((int*) arr->base + 3) != 3) failed++;
    if(*((int*) arr->base + 4) != 8) failed++;
    if(*((int*) arr->base + 5) != 8) failed++;
    if(*((int*) arr->base + 6) != 8) failed++;
    if(*((int*) arr->base + 7) != 8) failed++;
    failed += ArrChk(arr, sizeof(int), 8, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int FillMiddle() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 8, IntCmp);
    *((int*) arr->base + 0) = 0;
    *((int*) arr->base + 1) = 1;
    *((int*) arr->base + 2) = 2;
    *((int*) arr->base + 3) = 3;
    *((int*) arr->base + 4) = 4;
    *((int*) arr->base + 5) = 5;
    *((int*) arr->base + 6) = 6;
    *((int*) arr->base + 7) = 7;
    int value = 8;
    if(DS_ArrayFill(arr, 2, 6, &value) != arr) failed++;
    if(*((int*) arr->base + 0) != 0) failed++;
    if(*((int*) arr->base + 1) != 1) failed++;
    if(*((int*) arr->base + 2) != 8) failed++;
    if(*((int*) arr->base + 3) != 8) failed++;
    if(*((int*) arr->base + 4) != 8) failed++;
    if(*((int*) arr->base + 5) != 8) failed++;
    if(*((int*) arr->base + 6) != 6) failed++;
    if(*((int*) arr->base + 7) != 7) failed++;
    failed += ArrChk(arr, sizeof(int), 8, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int FillAll() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 8, IntCmp);
    *((int*) arr->base + 0) = 0;
    *((int*) arr->base + 1) = 1;
    *((int*) arr->base + 2) = 2;
    *((int*) arr->base + 3) = 3;
    *((int*) arr->base + 4) = 4;
    *((int*) arr->base + 5) = 5;
    *((int*) arr->base + 6) = 6;
    *((int*) arr->base + 7) = 7;
    int value = 8;
    if(DS_ArrayFill(arr, 0, 8, &value) != arr) failed++;
    if(*((int*) arr->base + 0) != 8) failed++;
    if(*((int*) arr->base + 1) != 8) failed++;
    if(*((int*) arr->base + 2) != 8) failed++;
    if(*((int*) arr->base + 3) != 8) failed++;
    if(*((int*) arr->base + 4) != 8) failed++;
    if(*((int*) arr->base + 5) != 8) failed++;
    if(*((int*) arr->base + 6) != 8) failed++;
    if(*((int*) arr->base + 7) != 8) failed++;
    failed += ArrChk(arr, sizeof(int), 8, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int IndexZero() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 0, IntCmp);
    int val = 42;
    if(DS_ArrayIndex(arr, 0, 0, &val) != -1) failed++;
    failed += ArrChk(arr, sizeof(int), 0, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int IndexOneNone() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 1, IntCmp);
    *((int*) arr->base + 0) = 0;
    int val = 42;
    if(DS_ArrayIndex(arr, 0, 1, &val) != -1) failed++;
    if(*((int*) arr->base + 0) != 0) failed++;
    failed += ArrChk(arr, sizeof(int), 1, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int IndexOne() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 1, IntCmp);
    *((int*) arr->base + 0) = 42;
    int val = 42;
    if(DS_ArrayIndex(arr, 0, 1, &val) != 0) failed++;
    if(*((int*) arr->base + 0) != 42) failed++;
    failed += ArrChk(arr, sizeof(int), 1, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int IndexNone() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 8, IntCmp);
    *((int*) arr->base + 0) = 0;
    *((int*) arr->base + 1) = 1;
    *((int*) arr->base + 2) = 2;
    *((int*) arr->base + 3) = 3;
    *((int*) arr->base + 4) = 4;
    *((int*) arr->base + 5) = 5;
    *((int*) arr->base + 6) = 6;
    *((int*) arr->base + 7) = 7;
    int val = 42;
    if(DS_ArrayIndex(arr, 0, 4, &val) != -1) failed++;
    if(DS_ArrayIndex(arr, 2, 6, &val) != -1) failed++;
    if(DS_ArrayIndex(arr, 4, 8, &val) != -1) failed++;
    if(DS_ArrayIndex(arr, 0, 8, &val) != -1) failed++;
    if(*((int*) arr->base + 0) != 0) failed++;
    if(*((int*) arr->base + 1) != 1) failed++;
    if(*((int*) arr->base + 2) != 2) failed++;
    if(*((int*) arr->base + 3) != 3) failed++;
    if(*((int*) arr->base + 4) != 4) failed++;
    if(*((int*) arr->base + 5) != 5) failed++;
    if(*((int*) arr->base + 6) != 6) failed++;
    if(*((int*) arr->base + 7) != 7) failed++;
    failed += ArrChk(arr, sizeof(int), 8, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int Index() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 8, IntCmp);
    *((int*) arr->base + 0) = 42;
    *((int*) arr->base + 1) = 1;
    *((int*) arr->base + 2) = 2;
    *((int*) arr->base + 3) = 42;
    *((int*) arr->base + 4) = 4;
    *((int*) arr->base + 5) = 5;
    *((int*) arr->base + 6) = 6;
    *((int*) arr->base + 7) = 42;
    int val = 42;
    if(DS_ArrayIndex(arr, 0, 4, &val) != 0) failed++;
    if(DS_ArrayIndex(arr, 2, 6, &val) != 3) failed++;
    if(DS_ArrayIndex(arr, 4, 8, &val) != 7) failed++;
    if(DS_ArrayIndex(arr, 0, 8, &val) != 0) failed++;
    if(*((int*) arr->base + 0) != 42) failed++;
    if(*((int*) arr->base + 1) != 1) failed++;
    if(*((int*) arr->base + 2) != 2) failed++;
    if(*((int*) arr->base + 3) != 42) failed++;
    if(*((int*) arr->base + 4) != 4) failed++;
    if(*((int*) arr->base + 5) != 5) failed++;
    if(*((int*) arr->base + 6) != 6) failed++;
    if(*((int*) arr->base + 7) != 42) failed++;
    failed += ArrChk(arr, sizeof(int), 8, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int length() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 0, IntCmp);
    if(DS_ArrayLength(arr) != 0) failed++;
    failed += ArrChk(arr, sizeof(int), 0, 1);
    arr = DS_ArrayResize(arr, 4);
    if(DS_ArrayLength(arr) != 4) failed++;
    failed += ArrChk(arr, sizeof(int), 4, 1);
    arr = DS_ArrayResize(arr, 8);
    if(DS_ArrayLength(arr) != 8) failed++;
    failed += ArrChk(arr, sizeof(int), 8, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int MaxZero() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 0, IntCmp);
    if(DS_ArrayMax(arr, 0, 0) != 0) failed++;
    failed += ArrChk(arr, sizeof(int), 0, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int MaxOneNone() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 1, IntCmp);
    *((int*) arr->base + 0) = 0;
    if(DS_ArrayMax(arr, 0, 0) != 0) failed++;
    if(*((int*) arr->base + 0) != 0) failed++;
    failed += ArrChk(arr, sizeof(int), 1, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int MaxOne() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 1, IntCmp);
    *((int*) arr->base + 0) = 0;
    if(*((int*) DS_ArrayMax(arr, 0, 1)) != 0) failed++;
    if(*((int*) arr->base + 0) != 0) failed++;
    failed += ArrChk(arr, sizeof(int), 1, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int MaxNone() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 4, IntCmp);
    *((int*) arr->base + 0) = 0;
    *((int*) arr->base + 1) = 1;
    *((int*) arr->base + 2) = 2;
    *((int*) arr->base + 3) = 3;
    if(DS_ArrayMax(arr, 2, 2) != 0) failed++;
    if(*((int*) arr->base + 0) != 0) failed++;
    if(*((int*) arr->base + 1) != 1) failed++;
    if(*((int*) arr->base + 2) != 2) failed++;
    if(*((int*) arr->base + 3) != 3) failed++;
    failed += ArrChk(arr, sizeof(int), 4, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int Max() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 8, IntCmp);
    *((int*) arr->base + 0) = 16;
    *((int*) arr->base + 1) = 0;
    *((int*) arr->base + 2) = 1;
    *((int*) arr->base + 3) = 2;
    *((int*) arr->base + 4) = 32;
    *((int*) arr->base + 5) = 4;
    *((int*) arr->base + 6) = 8;
    *((int*) arr->base + 7) = 64;
    if(*((int*) DS_ArrayMax(arr, 0, 4)) != 16) failed++;
    if(*((int*) DS_ArrayMax(arr, 4, 8)) != 64) failed++;
    if(*((int*) DS_ArrayMax(arr, 2, 6)) != 32) failed++;
    if(*((int*) DS_ArrayMax(arr, 0, 8)) != 64) failed++;
    if(*((int*) arr->base + 0) != 16) failed++;
    if(*((int*) arr->base + 1) != 0) failed++;
    if(*((int*) arr->base + 2) != 1) failed++;
    if(*((int*) arr->base + 3) != 2) failed++;
    if(*((int*) arr->base + 4) != 32) failed++;
    if(*((int*) arr->base + 5) != 4) failed++;
    if(*((int*) arr->base + 6) != 8) failed++;
    if(*((int*) arr->base + 7) != 64) failed++;
    failed += ArrChk(arr, sizeof(int), 8, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int MinZero() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 0, IntCmp);
    if(DS_ArrayMin(arr, 0, 0) != 0) failed++;
    failed += ArrChk(arr, sizeof(int), 0, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int MinOneNone() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 1, IntCmp);
    *((int*) arr->base + 0) = 0;
    if(DS_ArrayMin(arr, 0, 0) != 0) failed++;
    if(*((int*) arr->base + 0) != 0) failed++;
    failed += ArrChk(arr, sizeof(int), 1, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int MinOne() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 1, IntCmp);
    *((int*) arr->base + 0) = 0;
    if(*((int*) DS_ArrayMin(arr, 0, 1)) != 0) failed++;
    if(*((int*) arr->base + 0) != 0) failed++;
    failed += ArrChk(arr, sizeof(int), 1, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int MinNone() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 4, IntCmp);
    *((int*) arr->base + 0) = 0;
    *((int*) arr->base + 1) = 1;
    *((int*) arr->base + 2) = 2;
    *((int*) arr->base + 3) = 3;
    if(DS_ArrayMin(arr, 2, 2) != 0) failed++;
    if(*((int*) arr->base + 0) != 0) failed++;
    if(*((int*) arr->base + 1) != 1) failed++;
    if(*((int*) arr->base + 2) != 2) failed++;
    if(*((int*) arr->base + 3) != 3) failed++;
    failed += ArrChk(arr, sizeof(int), 4, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int Min() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 8, IntCmp);
    *((int*) arr->base + 0) = 2;
    *((int*) arr->base + 1) = 4;
    *((int*) arr->base + 2) = 8;
    *((int*) arr->base + 3) = 16;
    *((int*) arr->base + 4) = 1;
    *((int*) arr->base + 5) = 32;
    *((int*) arr->base + 6) = 64;
    *((int*) arr->base + 7) = 0;
    if(*((int*) DS_ArrayMin(arr, 0, 4)) != 2) failed++;
    if(*((int*) DS_ArrayMin(arr, 4, 8)) != 0) failed++;
    if(*((int*) DS_ArrayMin(arr, 2, 6)) != 1) failed++;
    if(*((int*) DS_ArrayMin(arr, 0, 8)) != 0) failed++;
    if(*((int*) arr->base + 0) != 2) failed++;
    if(*((int*) arr->base + 1) != 4) failed++;
    if(*((int*) arr->base + 2) != 8) failed++;
    if(*((int*) arr->base + 3) != 16) failed++;
    if(*((int*) arr->base + 4) != 1) failed++;
    if(*((int*) arr->base + 5) != 32) failed++;
    if(*((int*) arr->base + 6) != 64) failed++;
    if(*((int*) arr->base + 7) != 0) failed++;
    failed += ArrChk(arr, sizeof(int), 8, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int SortZero() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 0, IntCmp);
    if(DS_ArraySort(arr, 0, 0) != arr) failed++;
    failed += ArrChk(arr, sizeof(int), 0, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int SortOneNone() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 1, IntCmp);
    *((int*) arr->base + 0) = 0;
    if(DS_ArraySort(arr, 0, 0) != arr) failed++;
    if(*((int*) arr->base + 0) != 0) failed++;
    failed += ArrChk(arr, sizeof(int), 1, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int SortOne() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 1, IntCmp);
    *((int*) arr->base + 0) = 0;
    if(DS_ArraySort(arr, 0, 1) != arr) failed++;
    if(*((int*) arr->base + 0) != 0) failed++;
    failed += ArrChk(arr, sizeof(int), 1, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int SortNone() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 4, IntCmp);
    *((int*) arr->base + 0) = 0;
    *((int*) arr->base + 1) = 1;
    *((int*) arr->base + 2) = 2;
    *((int*) arr->base + 3) = 3;
    if(DS_ArraySort(arr, 2, 2) != arr) failed++;
    if(*((int*) arr->base + 0) != 0) failed++;
    if(*((int*) arr->base + 1) != 1) failed++;
    if(*((int*) arr->base + 2) != 2) failed++;
    if(*((int*) arr->base + 3) != 3) failed++;
    failed += ArrChk(arr, sizeof(int), 4, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int Sort() {
    int failed = 0;
    struct DS_Array *arr = DS_ArrayNew(sizeof(int), 8, IntCmp);
    *((int*) arr->base + 0) = 8;
    *((int*) arr->base + 1) = 4;
    *((int*) arr->base + 2) = 2;
    *((int*) arr->base + 3) = 16;
    *((int*) arr->base + 4) = 1;
    *((int*) arr->base + 5) = 64;
    *((int*) arr->base + 6) = 32;
    *((int*) arr->base + 7) = 0;
    if(DS_ArraySort(arr, 2, 6) != arr) failed++;
    if(*((int*) arr->base + 0) != 8) failed++;
    if(*((int*) arr->base + 1) != 4) failed++;
    if(*((int*) arr->base + 2) != 1) failed++;
    if(*((int*) arr->base + 3) != 2) failed++;
    if(*((int*) arr->base + 4) != 16) failed++;
    if(*((int*) arr->base + 5) != 64) failed++;
    if(*((int*) arr->base + 6) != 32) failed++;
    if(*((int*) arr->base + 7) != 0) failed++;
    if(DS_ArraySort(arr, 0, 4) != arr) failed++;
    if(*((int*) arr->base + 0) != 1) failed++;
    if(*((int*) arr->base + 1) != 2) failed++;
    if(*((int*) arr->base + 2) != 4) failed++;
    if(*((int*) arr->base + 3) != 8) failed++;
    if(*((int*) arr->base + 4) != 16) failed++;
    if(*((int*) arr->base + 5) != 64) failed++;
    if(*((int*) arr->base + 6) != 32) failed++;
    if(*((int*) arr->base + 7) != 0) failed++;
    if(DS_ArraySort(arr, 4, 8) != arr) failed++;
    if(*((int*) arr->base + 0) != 1) failed++;
    if(*((int*) arr->base + 1) != 2) failed++;
    if(*((int*) arr->base + 2) != 4) failed++;
    if(*((int*) arr->base + 3) != 8) failed++;
    if(*((int*) arr->base + 4) != 0) failed++;
    if(*((int*) arr->base + 5) != 16) failed++;
    if(*((int*) arr->base + 6) != 32) failed++;
    if(*((int*) arr->base + 7) != 64) failed++;
    if(DS_ArraySort(arr, 0, 8) != arr) failed++;
    if(*((int*) arr->base + 0) != 0) failed++;
    if(*((int*) arr->base + 1) != 1) failed++;
    if(*((int*) arr->base + 2) != 2) failed++;
    if(*((int*) arr->base + 3) != 4) failed++;
    if(*((int*) arr->base + 4) != 8) failed++;
    if(*((int*) arr->base + 5) != 16) failed++;
    if(*((int*) arr->base + 6) != 32) failed++;
    if(*((int*) arr->base + 7) != 64) failed++;
    failed += ArrChk(arr, sizeof(int), 8, 1);
    DS_ArrayDelete(arr);
    return failed;
}

int main() {
    RunTests(46, (struct Test[46]) {
        (struct Test) {NewDeleteZero, "NewDeleteZero"},
        (struct Test) {NewDeleteMany, "NewDeleteMany"},
        (struct Test) {ResizeBigger, "ResizeBigger"},
        (struct Test) {ResizeSmaller, "ResizeSmaller"},
        (struct Test) {AtAll, "AtAll"},
        (struct Test) {CopyFromZero, "CopyFromZero"},
        (struct Test) {CopyFromFirstHalf, "CopyFromFirstHalf"},
        (struct Test) {CopyFromSecondHalf, "CopyFromSecondHalf"},
        (struct Test) {CopyFromMiddle, "CopyFromMiddle"},
        (struct Test) {CopyFromAll, "CopyFromAll"},
        (struct Test) {CopyToZero, "CopyToZero"},
        (struct Test) {CopyToFirstHalf, "CopyToFirstHalf"},
        (struct Test) {CopyToSecondHalf, "CopyToSecondHalf"},
        (struct Test) {CopyToMiddle, "CopyToMiddle"},
        (struct Test) {CopyToAll, "CopyToAll"},
        (struct Test) {CountZero, "CountZero"},
        (struct Test) {CountOneNone, "CountOneNone"},
        (struct Test) {CountOne, "CountOne"},
        (struct Test) {CountNone, "CountNone"},
        (struct Test) {Count, "Count"},
        (struct Test) {FillZero, "FillZero"},
        (struct Test) {FillFirstHalf, "FillFirstHalf"},
        (struct Test) {FillSecondHalf, "FillSecondHalf"},
        (struct Test) {FillMiddle, "FillMiddle"},
        (struct Test) {FillAll, "FillAll"},
        (struct Test) {IndexZero, "IndexZero"},
        (struct Test) {IndexOneNone, "IndexOneNone"},
        (struct Test) {IndexOne, "IndexOne"},
        (struct Test) {IndexNone, "IndexNone"},
        (struct Test) {Index, "Index"},
        (struct Test) {length, "length"},
        (struct Test) {MaxZero, "MaxZero"},
        (struct Test) {MaxOneNone, "MaxOneNone"},
        (struct Test) {MaxOne, "MaxOne"},
        (struct Test) {MaxNone, "MaxNone"},
        (struct Test) {Max, "Max"},
        (struct Test) {MinZero, "MinZero"},
        (struct Test) {MinOneNone, "MinOneNone"},
        (struct Test) {MinOne, "MinOne"},
        (struct Test) {MinNone, "MinNone"},
        (struct Test) {Min, "Min"},
        (struct Test) {SortZero, "SortZero"},
        (struct Test) {SortOneNone, "SortOneNone"},
        (struct Test) {SortOne, "SortOne"},
        (struct Test) {SortNone, "SortNone"},
        (struct Test) {Sort, "Sort"},
    });
    return 0;
}
