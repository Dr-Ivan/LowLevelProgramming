#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/*  name: Lab2
	purpose: 	Z = A / B - C
				if Z<0, then calculate (A – B) * C + A
				else calculate product of all even nums in [A, B]
	date: 09.09.2024
	author: Derevyanko Ivan Aleksandrovich, group 3413
	*/


int main(int argc, char *argv[]) {
	int a, b, c, resC, resASM;			// declaration of variables
	printf("Input A, B, C values: "); 	// prompt for input
	scanf("%d %d %d", &a, &b, &c);		// input
	const int two = 2;					// it will be used as a constant for division in ASM calculations

	asm("movl %1, %%eax;"       	// eax -> A
		"movl %2, %%ebx;"			// ebx -> B
		"cdq;"						// eax -> edx : eax
		"idiv %%ebx;"            	// eax -> (A / B)
		
		"movl %3, %%ebx;"       	// ebx -> C
		"sub %%ebx, %%eax;"			// eax -> (A / B) - C
		
		"movl $0, %%ebx;"			// ebx -> 0;
		"cmp %%ebx, %%eax;"			// eax <=> 0 ?
		"jl if_less;"				// if A / B - C < 0
		"jge else_block;"			// if A / B - C >= 0
	
	
		"if_less:"					// if A / B - C < 0
			"movl %1, %%eax;"       // eax -> A
			"movl %2, %%ebx;"		// ebx -> B
			"sub %%ebx, %%eax;"		// eax -> (A - B)
			
			"movl %3, %%ecx;"  		// ecx -> C
			"imul %%ecx;"			// edx : eax -> ((A - B) * C)
			
			"movl %1, %%ecx;"		// ecx -> A
			"add %%ecx, %%eax;"     // eax -> ((A - B) * C) + A
			
			"jmp end_asm;"			// return value from EAX to resASM
		
		
		"else_block:"			  	// if A / B - C >= 0
			"movl %1, %%eax;"       // eax -> A
			"movl %2, %%ebx;"		// ebx -> B
			"cmp %%eax, %%ebx;"		// eax <=> ebx ?
		// if B < A
			"jl err_data;"		
		// else:
			"movl %1, %%ecx;"		// ecx -> A  - current num
			"movl $1, %%ebx;"		// ebx -> 1	 - product
			"jmp prod_start;"  		// begin product loop
			
		"prod_start:"				// loop for calculating product of even integers
			"movl %%ecx, %%eax;"	// eax -> current num
			"cdq;"					// eax -> edx : eax
			"idiv %4;"				// divide current num by 2
			"cmp $0, %%edx;"		// if mod == 0
			"je add_to_product;"	// add this num to product
			"jne check_edge;"		// increase cur num by 1 and check if cur num exceeds B
			
			
		"check_edge:"
			"add $1, %%ecx;"		// increase cur num by 1
			"cmp %2, %%ecx;"		// if cur num exceeds B
			"jg end_asm1;"			// return result from ECX
			"jle prod_start;"  		// else do one more iteration
		
		"add_to_product:"			// adds num from ECX to product in EBX
			"movl %%ebx, %%eax;"	// preparation for multiplication
			"imul %%ecx;"			// edx : eax -> cur num * product
			"movl %%eax, %%ebx;"	// return back in EBX
			"jmp check_edge;"		// increase cur num by 1 and check if cur num exceeds B
		
		"err_data:"	            	// if B <= A
			"movl $1, %%eax;"		// eax -> 0;
			"jmp end_asm;"			// return value from EAX to resASM
		
		
		"end_asm1:"					// returns value from EBX to resASM
			"movl %%ebx, %%eax;"	// eax = ebx
			"jmp end_asm;"			// return value from EAX to resASM
		
		"end_asm:"					// returns value from EAX to resASM
			"movl %%eax, %0;"		// resASM -> eax
	
	//      0
	:"=r"(resASM)						// output variable
	//   1       2       3        4
	:"r"(a), "r"(b), "r"(c), "r"(two)	// input variables
	:"%eax", "%ebx", "%ecx", "%edx"		// used registers
	);
	
	
	
	printf("Result calculated with ASM language: %d", resASM);  // output for ASM calculations
	printf("\n");												// new line
	

	if (a / b - c < 0){					// check condition for Z
		resC = (a-b)*c+a;				// if z<0 -> output this value
	} else {							// else start accumulating product of even integers
		resC = 1;						// product accumulator
		int i = a;						// begin with A
		for ( ; i <= b; i++){			// i -> current number
			if (i%2 == 0){				// if i is even
				resC = resC*i;			// add it to product
			};
		};
	};
	
	printf("Result calculated with C language: %d", resC);	// output for C result
	if (resC == 1){											// if result is 1
		printf("\nResult is 1 because B <= A, so there are no integers in [A, B]."); // it means B <= A -> no integers in product
	};
	
	return 0;
}
