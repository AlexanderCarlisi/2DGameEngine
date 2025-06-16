#ifndef VECTOR_H
#define VECTOR_H

#include "stdlib.h"
#include <stdio.h>

#define DECLARE_VECTOR(vector_name, func_prefix, type)\
    typedef struct vector_name {\
        type* data;\
        size_t count;\
        size_t size;\
        float realloc_ratio;\
    } vector_name;\
\
    void func_prefix##_init(vector_name* arr);\
    void func_prefix##_free(vector_name* arr);\
    int func_prefix##_add(vector_name* arr, type item);\
    int func_prefix##_realloc(vector_name* arr);\
    int func_prefix##_realloc_set(vector_name* arr, size_t newSize);\
    void func_prefix##_pop_swap(vector_name* arr, int index);\


#define DEFINE_VECTOR(vector_name, func_prefix, type)\
    void func_prefix##_init(vector_name* arr) {\
        arr->count = 0;\
        arr->size = 1;\
        arr->realloc_ratio = 2.0f;\
        arr->data = (type*) calloc(arr->size, sizeof(type));\
    }\
\
    void func_prefix##_free(vector_name* arr) {\
        free(arr->data);\
        arr->data = NULL;\
        arr->count = 0;\
        arr->size = 0;\
        arr->realloc_ratio = 0;\
    }\
\
    int func_prefix##_realloc(vector_name* arr) {\
        arr->size *= arr->realloc_ratio;\
        type* reallocated = (type*) realloc(arr->data, arr->size * sizeof(type));\
        if (reallocated == NULL) {\
            printf("\n>>> Reallocation Failure <<<\n");\
            return 0;\
        }\
        arr->data = reallocated;\
        return 1;\
    }\
\
    int func_prefix##_realloc_set(vector_name* arr, size_t newSize) {\
        arr->size = newSize;\
        type* reallocated = (type*) realloc(arr->data, arr->size * sizeof(type));\
        if (reallocated == NULL) {\
            printf("\n>>> Reallocation Failure <<<\n");\
            return 0;\
        }\
        arr->data = reallocated;\
        return 1;\
    }\
\
    int func_prefix##_add(vector_name* arr, type item) {\
        arr->count++;\
        if (arr->count > arr->size) {\
            if(!func_prefix##_realloc(arr)) {\
                printf("\n>>> Add Failure, due to Reallocation Failure. <<<\n");\
                return 0;\
            }\
        }\
        arr->data[arr->count - 1] = item;\
        return 1;\
    }\
\
    void func_prefix##_pop_swap(vector_name* arr, int index) {\
        if (index < 0 || index >= arr->count) {\
            printf("\n>>> Pop-Swap Failure <<<\n...Index out of Bounds...");\
            return;\
        }\
\
        type pop = arr->data[index];\
        int lastIndex = arr->count - 1;\
        type swap = arr->data[lastIndex];\
\
        if (index != lastIndex) {\
            arr->data[index] = swap;\
        }\
        arr->count--;\
    }\



#define DECLARE_VECTOR_PTR(vector_name, func_prefix, type_ptr)\
    typedef struct vector_name {\
        type_ptr* data;\
        size_t count;\
        size_t size;\
        float realloc_ratio;\
    } vector_name;\
\
    void func_prefix##_init(vector_name* arr);\
    void func_prefix##_free(vector_name* arr);\
    int func_prefix##_add(vector_name* arr, type_ptr item);\
    int func_prefix##_realloc(vector_name* arr);\
    int func_prefix##_realloc_set(vector_name* arr, size_t newSize);\
    type_ptr func_prefix##_pop_swap(vector_name* arr, int index);\

    
#define DEFINE_VECTOR_PTR(vector_name, func_prefix, type_ptr)\
    void func_prefix##_init(vector_name* arr) {\
        arr->count = 0;\
        arr->size = 1;\
        arr->realloc_ratio = 2.0f;\
        arr->data = (type_ptr*) calloc(arr->size, sizeof(type_ptr));\
        if (arr->data == NULL) {\
            printf("\n>>> Initial Allocation of Vector Failed <<<\n");\
        }\
    }\
\
    void func_prefix##_free(vector_name* arr) {\
        for (size_t i = 0; i < arr->count; i++) {\
            free(arr->data[i]);\
        }\
        free(arr->data);\
        arr->data = NULL;\
        arr->count = 0;\
        arr->size = 0;\
        arr->realloc_ratio = 0;\
    }\
\
    int func_prefix##_realloc(vector_name* arr) {\
        arr->size *= arr->realloc_ratio;\
        type_ptr* reallocated = (type_ptr*) realloc(arr->data, arr->size * sizeof(type_ptr));\
        if (reallocated == NULL) {\
            printf("\n>>> Reallocation Failure <<<\n");\
            return 0;\
        }\
        arr->data = reallocated;\
        return 1;\
    }\
\
    int func_prefix##_realloc_set(vector_name* arr, size_t newSize) {\
        arr->size = newSize;\
        type_ptr* reallocated = (type_ptr*) realloc(arr->data, arr->size * sizeof(type_ptr));\
        if (reallocated == NULL) {\
            printf("\n>>> Reallocation Failure <<<\n");\
            return 0;\
        }\
        arr->data = reallocated;\
        return 1;\
    }\
\
    int func_prefix##_add(vector_name* arr, type_ptr item) {\
        arr->count++;\
        if (arr->count > arr->size) {\
            if(!func_prefix##_realloc(arr)) {\
                printf("\n>>> Add Failure, due to Reallocation Failure. <<<\n");\
                return 0;\
            }\
        }\
        arr->data[arr->count - 1] = item;\
        return 1;\
    }\
\
    type_ptr func_prefix##_pop_swap(vector_name* arr, int index) {\
        if (index < 0 || index >= arr->count) {\
            printf("\n>>> Pop-Swap Failure <<<\n...Index out of Bounds...");\
            return NULL;\
        }\
\
        type_ptr popped = arr->data[index];\
        int last = arr->count - 1;\
        arr->data[index] = arr->data[last];\
        arr->data[last] = NULL;\
        arr->count--;\
        return popped;
    }\

#endif // VECTOR_H