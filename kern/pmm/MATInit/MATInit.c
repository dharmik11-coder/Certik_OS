
#include <lib/debug.h>
#include <dev/mboot.h>
#include "import.h"

#define PAGESIZE  4096
#define VM_USERLO 0x40000000
#define VM_USERHI 0xF0000000
#define VM_USERLO_PI  (VM_USERLO / PAGESIZE)   // VM_USERLO page index
#define VM_USERHI_PI  (VM_USERHI / PAGESIZE)   // VM_USERHI page index


void
pmem_init(pmmap_list_type *pmmap_list_p)
{
    // : Define your local variables here.
    unsigned int nps;

    int row_count = get_size();

    nps = 0 ; 
    for( int i = 0;i < row_count;i++){
        if(nps < (get_mms(pmmap_list_p, i) + get_mml(pmmap_list_p, i))){
        nps = get_mms(pmmap_list_p, i) + get_mml(pmmap_list_p, i); 
        } 
	
    }

    if(nps % PAGESIZE == 0){
    nps = nps / PAGESIZE;
    }
    else{
    nps = nps / PAGESIZE + 1;
    }

    set_nps(nps); // Setting the value computed above to NUM_PAGES.

    // Reserved by the kernel
    for(int i = 0; i < VM_USERLO_PI; i++){
    set_accessibility(i, 1);
    }
    //set all default permission to 0
    for(int i = VM_USERLO_PI; i < VM_USERHI_PI; i++){
    set_accessibility(i, 0);
    }
}