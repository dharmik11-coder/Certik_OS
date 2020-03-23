 #include <lib/gcc.h>

/** ASSIGNMENT OVERVIEW:
  * ASSIGNMENT INFO:
  * - In this section, you will design and implement data-structure
  *   that performs bookkeeping for each physical page. You are
  *   free to design the data-structure to keep track of as many or
  *   as few pieces of information that you believe are essential.
  */

/** The highest available physical physical page number
  * available in the machine.
  */
static unsigned int NUM_PAGES;

/**
 * TODO: Data-Structure representing information for one physical page.
 */
struct ph_page {
  unsigned int access; 
  unsigned int pallocated; 
};

static struct ph_page AccTable[1048576];  

/** The getter function for NUM_PAGES. */
unsigned int
get_nps(void)
{
  return NUM_PAGES;
}

/** The setter function for NUM_PAGES. */
void
set_nps(unsigned int nps)
{
  NUM_PAGES = nps;
}


// functions for updating access table 
unsigned int is_accessible(unsigned int page_index)
{
  if(AccTable[page_index].access > 1)
    return 1;
  return 0;
}

void set_accessibility(unsigned int page_index, unsigned int norm_val)
{
  AccTable[page_index].access = norm_val;
  AccTable[page_index].pallocated = 0;
}

unsigned int is_allocated(unsigned int page_index)
{
  if(AccTable[page_index].pallocated > 0)
    return 1;
  return 0;
}

void update_allocation(unsigned int page_index, unsigned int allocated)
{
  AccTable[page_index].pallocated = allocated;
}