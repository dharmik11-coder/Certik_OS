/*
 * Filename: boot0.S
 * Description:
 *  - Sets up the machine registers (including the stack pointers) properly
 *    for execution in 16-bit mode.
 *  - Utilizes the BIOS interrupt mechanism to output messages to the screen.
 *  - Reads the second stage bootloader from the disk into appropriate location.
 *    (boot1 is put just after MBR and before the first partition, i.e. from
 *    sector 2 to sector 63.)
 *  - Correctly transfers execution to the loaded second stage bootloader.
 */

	

    .globl start
start:
    /* assemble the file in 16-bit mode *

    /**
      * Clear the interrupts flag, disabling the interrupts.
      * Clear the direction flag, to configure auto-increment mode.
      */
    cli
    cld


    .code16
/*******************************************************************************
*   YOUR 16-bit CODE
*******************************************************************************/
/*clear segment register*/

	movw $0x0000, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movw %ax, %ss


/*******************************************************************************
*   DATA STRUCTURES
*******************************************************************************/
/*setup stack*/

	movw $0x7c00,%bp
	movw $0x7c00,%sp

// setting video mode 

	mov $0,%ah
	mov $0x03,%al
	int $0x10




/* print starting msg*/

	movw $STARTUP_MSG, %si
	call printstr


	/*DAP setup */
	
	pushl $0x0          	//set start
	pushl $0x1		//LBA addr
	pushw %es		//set buffer
	pushw $0x7e00		// to boot1 addr
	pushw $62 		// no. of sector
	//pushw $0x0000		//unused
	pushw $16		// size of DAP
	movw %sp, %si 		//set DAP addr
	mov $0x42, %ah
	mov $0x00, %al	 	
	int $0x13 		//read sector
	jc fail_msg		//encounter err
	
	jmp 0x7e00 		//pass control to boot1 start addr


		

fail_msg:
	movw	$LOAD_FAIL_MSG, %si
	call printstr



printstr:
	
	movb	$14,%ah

printstr.1:
	lodsb
	cmp $0,%al
	je printstr.2
	int $0x10
	jmp printstr.1

printstr.2:
	ret


STARTUP_MSG:
    .ascii    "Start boot0 ...\r\n\0"

LOAD_FAIL_MSG:
    .ascii    "Error during loading boot1.\r\n\0"

