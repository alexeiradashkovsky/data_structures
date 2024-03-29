#ifndef __DATA_STRUCTURE_DEFENITIONS_H_
#define __DATA_STRUCTURE_DEFENITIONS_H_

#define MAX(a,b)  (a < b ? b : a)

typedef enum _aps_ds_error {
	DS_SUCCESS,
	DS_INVALID_PARAM_ERROR,
	DS_UNINITIALIZED_ERROR,				/*< Uninitialized vector error >*/
	DS_OUT_OF_BOUNDS_ERROR,		        /*< Trying to get value in out of bounds >*/
	DS_UNINITIALIZED_ITEM_ERROR,		/*< Uninitialized item error >*/
	DS_REALLOCATION_ERROR,				/*< realloc error on grow/shrink >*/
	DS_ALLOCATION_ERROR,
	DS_OVERFLOW_ERROR,					/*< There is no space to insert items and no reallocte >*/
	DS_UNDERFLOW_ERROR,					/*< There is no items in vector >*/
    DS_ELEMENT_NOT_FOUND_ERROR,
	DS_EMPTY_ERROR,
	DS_KEY_EXISTS_ERROR,
	DS_GENERAL_ERROR
} aps_ds_error;

typedef enum Compare_Result {
    BIGGER  = 0xFFF,
    SMALLER = 0xEFD,
    EQUAL = 0xDEF
} Compare_Result;


typedef enum TravelType {
    IN_ORDER,
    POST_ORDER,
    PRE_ORDER
} TravelType;

typedef Compare_Result (*CompareFunc)(const void*, const void*);

typedef void (*ElementDestroy)(void* _item);
typedef void (*ElementAction)(void* _item, void* _context);

#endif /* __DATA_STRUCTURE_DEFENITIONS_H_ */