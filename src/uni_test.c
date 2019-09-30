#include "uni_test.h"
#include "sorts.h"
#include "vector.h"
#include "heap.h"
#include "hash.h"
#include "list.h"
#include "circular_queue.h"
#include "circular_safe_queue.h"
#include <stdio.h>

Compare_Result CompareSizeTPointers(void* _generalTypeA, void* _generalTypeB) {
    size_t** typeA = (size_t**) _generalTypeA;
    size_t** typeB = (size_t**) _generalTypeB;
    if (**typeA > **typeB) {
        return BIGGER;
    }

    return SMALLER;
}


void SwapToSizeTPointers(void* _generalTypeA, void* _generalTypeB) {
    size_t** typeA = (size_t**) _generalTypeA;
    size_t** typeB = (size_t**) _generalTypeB;
    size_t temp = **typeA;
    **typeA = **typeB;
    **typeB = temp; 
}

int CompareTwoArraysP(size_t** arrA, size_t* arrB, size_t sizeOfArrays) {
    size_t i = 0;
    for (; i < sizeOfArrays ; ++i) {
        if (*(arrA[i]) != arrB[i]) {
            return -1;
        }
    }

    return 0;
}

int CompareTwoArrays(size_t* arrA, size_t* arrB, size_t sizeOfArrays) {
    size_t i = 0;
    for (; i < sizeOfArrays ; ++i) {
        if (arrA[i] != arrB[i]) {
            return -1;
        }
    }

    return 0;
}

Compare_Result CompareSizeT(void* _generalTypeA, void* _generalTypeB) {
    size_t* typeA = (size_t*) _generalTypeA;
    size_t* typeB = (size_t*) _generalTypeB;
    if (*typeA > *typeB) {
        return BIGGER;
    }

    return SMALLER;
}


Heap_Data_Compare_Result CompareSizeTHeap(const void* _generalTypeA, const void* _generalTypeB) {
    const size_t* typeA = (const size_t*) _generalTypeA;
    const size_t* typeB = (const size_t*) _generalTypeB;
    if (*typeA > *typeB) {
        return HEAP_COMPARE_BIGGER;
    }

    return HEAP_COMPARE_SMALLER;
}

void SwapToSizeT(void* _generalTypeA, void* _generalTypeB) {
    size_t* typeA = (size_t*) _generalTypeA;
    size_t* typeB = (size_t*) _generalTypeB;
    size_t temp = *typeA;
    *typeA = *typeB;
    *typeB = temp; 
}


Heap_Data_Compare_Result Int_Heap(const void* _a, const void* _b) {
    const int* a = (const int*)_a;
    const int* b = (const int*)_b;
    if (a > b) {
        return HEAP_COMPARE_BIGGER;
    }

    return HEAP_COMPARE_SMALLER;
}

UNIT(basic_valid_size_t_pointer_bubble_sort_test)
    size_t one = 1;
    size_t two = 2;
    size_t three = 3;
    size_t four = 4;
    size_t arrFinalResult[4] = {1,2,3,4};
    size_t arrSize = 4;
    size_t* arr[4];
    arr[0] = &two;
    arr[1] = &one;
    arr[2] = &four;
    arr[3] = &three;
    ASSERT_THAT(SORT_SUCCESS == BubbleSortOnData((void*)&arr, sizeof(size_t*), sizeof(arr), CompareSizeTPointers, SwapToSizeTPointers));
    ASSERT_THAT(0 == CompareTwoArraysP(arr, arrFinalResult, arrSize));
END_UNIT

UNIT(basic_valid_size_t_bubble_sort_test)
    size_t arrFinalResult[4] = {1,2,3,4};
    size_t arr[4] = {2,1,4,3};
    size_t arrSize = 4;
    ASSERT_THAT(SORT_SUCCESS == BubbleSortOnData((void*)arr, sizeof(size_t*), sizeof(arr), CompareSizeT, SwapToSizeT));
    ASSERT_THAT(0 == CompareTwoArrays(arr, arrFinalResult, arrSize));
END_UNIT

UNIT(Allocate_Vector)
    Vector* newVector = VectorCreate(10, 5);
    ASSERT_THAT(NULL != newVector);
    VectorDestroy(&newVector, NULL);
    ASSERT_THAT(NULL == newVector); 
END_UNIT

UNIT(Append_To_Vector_Elements_Expect_No_Crash)
    size_t arr[] = {2,1,4,3};
    size_t i = 0;
    Vector* newVector = VectorCreate(10, 5);
    Vector_Result resultChecker = VECTOR_UNINITIALIZED_ERROR;
    ASSERT_THAT(NULL != newVector);
    ASSERT_THAT(VectorCapacity(newVector) == 10);
    for (i = 0; i < sizeof(arr)/sizeof(size_t) ; ++i) {
        resultChecker = VectorAppend(newVector, arr + i);
        ASSERT_THAT(VECTOR_SUCCESS == resultChecker);
    }

    ASSERT_THAT(VectorSize(newVector) == sizeof(arr)/sizeof(size_t));
    VectorDestroy(&newVector, NULL);
    ASSERT_THAT(NULL == newVector); 
END_UNIT

UNIT(Append_To_Vector_Elements_Expect_No_Crash_And_Then_Get_All)
    size_t arr[] = {2,1,4,3};
    size_t i = 0;
    size_t numOfElements = sizeof(arr) / sizeof(size_t);
    size_t* value = NULL;
    Vector* newVector = VectorCreate(10, 5);
    Vector_Result resultChecker = VECTOR_UNINITIALIZED_ERROR;
    ASSERT_THAT(NULL != newVector);
    for (i = 0; i < numOfElements; ++i) {
        resultChecker = VectorAppend(newVector, arr + i);
        ASSERT_THAT(VECTOR_SUCCESS == resultChecker);
    }

    for (i = 0; i < numOfElements; ++i) {
        resultChecker = VectorGet(newVector, i, (void**)&value);
        ASSERT_THAT(VECTOR_SUCCESS == resultChecker);
        ASSERT_THAT(*value == arr[i]);
    }

    for (i = numOfElements; i > 0; --i) {
        resultChecker = VectorRemove(newVector, (void**)&value);
        ASSERT_THAT(VECTOR_SUCCESS == resultChecker);
        ASSERT_THAT(*value == arr[i - 1]);
    }
    
    VectorDestroy(&newVector, NULL);
    ASSERT_THAT(NULL == newVector);
END_UNIT

UNIT(Vector_RemoveFrom)
    size_t arr[] = {2,1,4,3};
    size_t i = 0;
    size_t numOfElements = sizeof(arr) / sizeof(size_t);
    size_t* value = NULL;
    Vector* newVector = VectorCreate(10, 5);
    Vector_Result resultChecker = VECTOR_UNINITIALIZED_ERROR;
    ASSERT_THAT(NULL != newVector);
    for (i = 0; i < numOfElements; ++i) {
        resultChecker = VectorAppend(newVector, arr + i);
        ASSERT_THAT(VECTOR_SUCCESS == resultChecker);
    }

    resultChecker = VectorRemoveFrom(newVector, 1, (void**)&value);
    ASSERT_THAT(VECTOR_SUCCESS == resultChecker);
    ASSERT_THAT(*value == arr[1]);
    
    resultChecker = VectorRemoveFrom(newVector, 1, (void**)&value);
    ASSERT_THAT(VECTOR_SUCCESS == resultChecker);
    ASSERT_THAT(*value == arr[2]);

    resultChecker = VectorRemoveFrom(newVector, 1, (void**)&value);
    ASSERT_THAT(VECTOR_SUCCESS == resultChecker);
    ASSERT_THAT(*value == arr[3]);

    resultChecker = VectorRemoveFrom(newVector, 1, (void**)&value);
    ASSERT_THAT(VECTOR_INDEX_OUT_OF_BOUNDS_ERROR == resultChecker);

    resultChecker = VectorRemoveFrom(newVector, 0, (void**)&value);
    ASSERT_THAT(VECTOR_SUCCESS == resultChecker);
    ASSERT_THAT(*value == arr[0]);

    VectorDestroy(&newVector, NULL);
    ASSERT_THAT(NULL == newVector);
END_UNIT

UNIT(Allocate_Heap)
    Heap* newHeap = HeapCreate(10, HEAP_TYPE_MIN, Int_Heap);
    ASSERT_THAT(NULL != newHeap);
    HeapDestroy(&newHeap, NULL);
    ASSERT_THAT(NULL == newHeap); 
END_UNIT

UNIT(Append_To_Heap_Elements_Expect_No_Crash)
    size_t arr[] = {2,1,4,3};
    size_t i = 0;
    Heap* newData = HeapCreate(10, HEAP_TYPE_MIN, CompareSizeTHeap);
    Heap_Result resultChecker = HEAP_SUCCESS;
    ASSERT_THAT(NULL != newData);
/*  TODO:
    ASSERT_THAT(VectorCapacity(newVector) == 10); 
*/
    for (i = 0; i < sizeof(arr)/sizeof(size_t) ; ++i) {
        resultChecker = HeapInsert(newData, arr + i);
        ASSERT_THAT(HEAP_SUCCESS == resultChecker);
    }
/*  TODO: 
    ASSERT_THAT(VectorSize(newVector) == sizeof(arr)/sizeof(size_t));
*/
    HeapDestroy(&newData, NULL);
    ASSERT_THAT(NULL == newData); 
END_UNIT

UNIT(Allocate_Queue)
    CQueue* newDataS = CQueueCreate(10);
    ASSERT_THAT(NULL != newDataS);
    CQueueDestroy(&newDataS, NULL);
    ASSERT_THAT(NULL == newDataS); 
END_UNIT

UNIT(Allocate_SafeQueue)
    CSQueue* newDataS = CSQueueCreate(10);
    ASSERT_THAT(NULL != newDataS);
    CSQueueDestroy(&newDataS, NULL);
    ASSERT_THAT(NULL == newDataS); 
END_UNIT


UNIT(Allocate_List)
    List* newDataS = ListCreate();
    ASSERT_THAT(NULL != newDataS);
    ListDestroy(&newDataS, NULL);
    ASSERT_THAT(NULL == newDataS); 
END_UNIT


TEST_SUITE(Test DataStructures)
    /* bubble Sort Tests */
	TEST(basic_valid_size_t_pointer_bubble_sort_test)
    TEST(basic_valid_size_t_bubble_sort_test)

    /* Vector Tests */
    TEST(Allocate_Vector)
    TEST(Append_To_Vector_Elements_Expect_No_Crash)
    TEST(Append_To_Vector_Elements_Expect_No_Crash_And_Then_Get_All)
    TEST(Vector_RemoveFrom)

    /* Heap Tests */
    TEST(Allocate_Heap)
    TEST(Append_To_Heap_Elements_Expect_No_Crash)
    /* Queue Tests */
    TEST(Allocate_Queue)

    /* SafeQueue Tests */
    TEST(Allocate_SafeQueue)

    /* List Tests */
    TEST(Allocate_List)
END_SUITE
