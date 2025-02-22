#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*  program: Lab1
	purpose: calculate expression (E-A)*C - B*(C-F) - D/E wish ASM language and check it using C
	date: 06.09.2024
	author: Derevyanko Ivan Aleksandrovich, group 3413
*/


int main(int argc, char *argv[]) {
	int a, b, c, d, e, f, resC, resASM;                    // declaration of variables
	printf("Input A, B, C, D, E, F values: ");             // prompt for input
	scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);    // input

	// assembler calculations
	asm("movl %5, %%eax;"     // eax -> E
		"movl %1, %%ebx;"     // ebx -> A
		"sub %%ebx, %%eax;"   // eax -> (E-A)
		
		"movl %3, %%ebx;"     // ebx -> C
		"imul %%ebx;"         // edx : eax -> (E-A) * C
		"movl %%eax, %%ecx;"  // ecx -> (E-A) * C
		
		"movl %6, %%eax;"     // eax -> F
		"sub %%eax, %%ebx;"   // ebx -> (C-F)
		
		"movl %2, %%eax;"     // eax -> B
		"imul %%ebx;"         // edx : eax -> (C-F) * B
		
		"sub %%eax, %%ecx;"   // ecx -> ((E-A) * C) - ((C-F) * B)
		
		"movl %5, %%ebx;"     // ebx -> E
		"movl %4, %%eax;"     // eax -> D
		"cdq;"                // eax -> edx : eax
		"idiv %%ebx;"         // eax -> (D/E)
		
		"sub %%eax, %%ecx;"   // ecx -> ((E-A) * C - (C-F) * B) - (D/E)
		"movl %%ecx, %0;"     // resASM -> ecx 
		
		//  0
		: "=r" (resASM)       // resASM -> output variable for assembler
		//     1        2        3        4        5        6
		: "r" (a), "r" (b), "r" (c), "r" (d), "r" (e), "r" (f)  // input variables
		: "%eax", "%ebx", "%ecx", "%edx"                        // used registers
		);
	
	printf("Result calculated with ASM language: (%d - %d) * %d - %d * (%d - %d) - %d / %d = %d ", e, a, c, b, c, f, d, e, resASM); // output for ASM calculations
	resC = (e - a) * c - b * (c - f) - d / e;            // same calculations to verify ASM results with C
	printf("\n");                                        // new line
	printf("Result calculated with C language: (%d - %d) * %d - %d * (%d - %d) - %d / %d = %d ", e, a, c, b, c, f, d, e, resC);    // output for C calculations
	printf("\n");                                        // new line
	system("PAUSE");									 // pause program in order not to close its window
	return 0;
}
