#include <lib/x86.h>

#include "import.h"


/** TASK 1:
  * * 1. Allocate a page (with container_alloc) for the page table,
  * * 2. Check if the page was allocated and register the allocated page in page directory for the given virtual address.
  * * 3. Clear (set to 0) all the page table entries for this newly mapped page table.
  * * 4. Return the page index of the newly allocated physical page.
  *    In the case when there's no physical page available, it returns 0.
  */
unsigned int alloc_ptbl(unsigned int proc_index, unsigned int vadr)
	{
	  // TODO
	  unsigned int addr;
	  unsigned int page_index;
	  page_index = container_alloc(proc_index);
	  if(page_index == 0) return 0;//physical page not vailable
	  
	  // register it in page table directory
	  set_pdir_entry_by_va(proc_index, vadr, page_index);
	  
	  // clear the whole page table entry and addr increases 4 per step, since entry is 4 bytes
	  for(addr = page_index << 12; addr < (page_index + 1) << 12; addr += 4){
	    *(unsigned int *)addr &= 0x00000000; 
	  }
	  return page_index;
	  
	}

/** TASK 2:
  * * Reverse operation of alloc_ptbl.
  *   - Remove corresponding page directory entry
  *   - Free the page for the page table entries (with container_free).
  * Hint 1: Find the pde corresponding to vadr (MPTOp layer)
  * Hint 2: Remove the pde (MPTOp layer)
  * Hint 3: Use container free
  */
void free_ptbl(unsigned int proc_index, unsigned int vadr)
{
  // TODO
  unsigned int pdir_entry;
  unsigned int page_index;
  pdir_entry = get_pdir_entry_by_va(proc_index, vadr);
  page_index = pdir_entry >> 12;
  // remove page directory entry
  rmv_pdir_entry_by_va(proc_index, vadr);

  //free the page for the page table entities
  container_free(proc_index, page_index);
}
