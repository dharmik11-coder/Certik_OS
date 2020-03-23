#include <lib/debug.h>
#include "import.h"

/** TASK 1:
  * Allocation of a physical page.
  *
  * 1. - First, implement a naive page allocator that scans the data-structure
  *      you implemented in MATIntro.
  *
  *    Hint 1: (Q: Do you have to scan the physical pages from index 0?
  *    Recall how you have initialized the table in pmem_init.)
  *
  *    - Then mark the page as allocated in the data-structure and return the
  *      page index of the page found.
  *      In the case when there is no available page found, return 0.
  * 2. Optimize the code with the memorization techniques so that you do not
  *    have to scan the data-structure from scratch every time.
  */

#define PAGESIZE  4096
#define VM_USERLO  0x40000000
#define VM_USERHI  0xF0000000
#define VM_USERLO_PI  (VM_USERLO / PAGESIZE)
#define VM_USERHI_PI  (VM_USERHI / PAGESIZE)

//set a next pointer to remember the last allocated page index
static unsigned int next = VM_USERLO_PI; 

unsigned int
palloc()
{
  // TODO
  // physical pages not available
  if (get_nps() == 0) {
    return 0;
  }

  
  unsigned int begin = next;
  do {
    
    if (is_accessible(next) && is_allocated(next) == 0) {
      update_allocation(next, 1);
      return next;
    }
    next++;
      if (next == VM_USERHI_PI) {
   	   next = VM_USERLO_PI;
  	  }
    } while (next != begin);

  //all pages allocated
  return 0;
}


/** TASK 2:
  * Free of a physical page.
  *
  * This function marks the page with given index as unallocated in your
  * data-structure.
  *
  * Hint: Simple. Check if a page is allocated and to set the allocation status
  *       of a page index.
  */
void
pfree(unsigned int pfree_index)
{
  // TODO
  update_allocation(pfree_index, 0);
}
