#ifndef __QUEUE_H__
#define __QUEUE_H__


/**
 *  @file queue.h
 *  @brief
 *
 *  @details
 *
 *
 *  @author Author Alexei Radashkovsky (alexeirada@gmail.com)
 *  @Update by Alexei Radashkovsky on 08/20/17
 *  @bug no bugs known.
 */


#include <stddef.h> /*< size_t >*/

typedef struct Queue Queue;

typedef enum Queue_Result
{
    QUEUE_SUCCESS = 0xFE91,
    QUEUE_UNITIALIZED_ERROR = 1,
    QUEUE_OVERFLOW_ERROR,
	QUEUE_EMPTY_ERROR,
    QUEUE_ELEMENT_UNITIALIZED_ERROR
}Queue_Result;

typedef int	(*QueueElementAction)(void* _element, void* _context);

 /**
  * @brief Create a new queue with given initialize size.
  * @param[in] _initSize - initial capacity, number of elements that can be stored initially.
  * @return Queue* - on success / NULL on fail
  */
Queue* QueueCreate(size_t _initSize);

/**
 * @brief : free SQueue.
 * @details : free SQueue if _desFunc is NULL.
 *
 * @param[in] _squeue 	- safe queue.
 * @param[in] _desFunc 	- a pointer to a function to destroy elements.
 * 						  If destruction function do not provided user have to
 * 						  delete all elements by him self.
 */
void QueueDestroy(Queue** _queue,void (*_elementDestroy)(void* _item));

/**
 * @brief : Inserts a new element to tail of queue .
 *
 * @param[in] _queue 	- queue.
 * @param[in] _element 	- a new element to insert.
 *
 * @return[success] : SQUEUE_SUCCESS
 * @return[failure] : SQUEUE_UNINITIALIZED_ERROR
 * @return[failure] : SQUEUE_ELEMENT_UNINITIALIZED_ERROR
 */
Queue_Result QueueInsert(Queue* _queue, void* _element);


/**
 * @brief : Removes an element from the head of the queue.
 *
 * @param[in] _queue 			- queue.
 * @param[out] _returnElement 	- return the element that removed.
 * 								  if _returnElement NULL just remove from queue do not free
 * @return[success] : SQUEUE_SUCCESS
 * @return[failure] : SQUEUE_UNINITIALIZED_ERROR
 */
Queue_Result QueueRemove(Queue* _queue, void** _returnElement);

/**
 * @brief : check if Queue is empty
 *
 * @param[in] _queue - queue.
 *
 * @return[success] : 1 if empty
 * @return[success] : 0 if not empty
 */
int QueueIsEmpty(const Queue* _queue);


/**
 * @brief : run on all elements and perform SQueueElementAction function.
 *
 * @param[in]  _queue - queue.
 * @param[in] _action - function to perform on safe queue elements
 * @param[in] _context - context for action function.
 *
 * @return[success] : SQUEUE_SUCCESS
 * @return[failure] : SQUEUE_UNINITIALIZED_ERROR
 */
Queue_Result QueueForEach(const Queue* _queue,QueueElementAction _action, void* _context);


#endif /* __QUEUECFUNC_H__ */
