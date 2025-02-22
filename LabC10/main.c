
// ����������� ���� define'� ������ ��������� ������� �� ����� funcs.h, �� �������� ���� ��� �������� ���������
// ��������� ������� LEN, ELEM, ELEM_TYPE � ������������� ��������� ������������ ����� ������� � ����� funcs.h

// ���� ������ ��� define'a ����, �� �� ��������� ����� ������ �� ������� �������������� (�� ����� else)
// ���� �������� ���, �� ������������ � REPLACE_WITH_MIN - �� ����������� ������
#define REPLACE_WITH_MAX 1
//#define REPLACE_WITH_MIN 1


#define DELETE_ODD_INDEXES // ������ ��������� ������� delete_indexes - � ��� ��������� �������� �������, ��� ���� - ������

#include "funcs.h"



int main(int argc, char *argv[]) {
	
	system("color F0");  	// ����� ���� �������
	system("chcp 1251"); 	// ������� �������� �������� �����
	srand(time(0)); 	 	// ������������� ��������������� ������������������
	
	// ���������� ����������
	int A_len = 11111;
	int B_len = 11111;
	int max_len = 10000;
	int i, j;
	ELEM_TYPE** A = NULL;

	// ���� �������� �������
	while (A_len < 1 || A_len >= max_len || B_len < 1 || B_len >= max_len){
		printf("������� ������� �������: \n");
		printf("\t������� ���������� ����� �: ");
		scanf("%d", &A_len);
		printf("\t������� ���������� �������� B: ");
		scanf("%d", &B_len);
		printf("\n");
	};
	
	// ���� ������ ��������� ��������� �����
	float mn, mx;
	printf("������� ������� � �������� ��� ��������� �����: ");
	scanf("%f %f", &mn, &mx);							
	printf("\n");
	
	// ��� ������������� �������� ������� �������
	if (mn > mx){										
		float t = mn;
		mn = mx;
		mx = t;
	};
	
    A = (ELEM_TYPE**) malloc(A_len * sizeof(ELEM_TYPE*));		// ��������� ������ ��� ��������� ������ �
	if (!A) exit(1);											// �������� �� ��, ��� ������ ���� ��������
	
 	//��� ������� ��������-��������� �������� ���� ������
    for (i = 0; i < A_len; ++i){
        A[i] = (ELEM_TYPE*) calloc(B_len+1, sizeof(ELEM_TYPE)); // ��������� ������ ��� ����������
		if (!A[i]) exit(1);										// �������� �� ��, ��� ������ ���� ��������
		A[i][0] = B_len;										// ��������� �����
 		randomize_arr(A[i], mn, mx);							// ���������� ������� ���������� �������
	};
	
	printf("�������� ������: \n");
	
	// ����� ���������� �������
	for (i = 0; i < A_len; ++i) 
    {
    	ELEM_TYPE line_len = A[i][0];
        for (j = 1; j <= line_len; ++j) 
            printf("%6d ", A[i][j]);
        printf("\n");
    };
    
    printf("\n\n");
    
    // ���������� ���������� �������� ��� ������������
    for (i = 0; i < A_len; ++i) 
    {
    	if (i % 4 == 0)
    		A[i] = delete_indexes(A[i]);
    	if (i % 4 == 1)
        	A[i] = add_zeros(A[i]);
        if (i % 4 == 2)
        	A[i] = relocate_zeros(A[i]);
        if (i % 4 == 3){
	        int x;
	        
	        #if REPLACE_WITH_MIN == 1
	        printf("������� �����, ������� ����� �������� �� ������� � ������ ����� %d: ", i+1);
			#elif REPLACE_WITH_MAX == 1
			printf("������� �����, ������� ����� �������� �� �������� � ������ ����� %d: ", i+1);
			#else
			printf("������� �����, ������� ����� �������� �� ������� � ������ ����� %d: ", i+1);
			#endif
	        
			scanf("%d", &x);
        	A[i] = replace(A[i], x);
		};
    };
    
    
    printf("\n���������� ������: \n");
    
    // ����� ���������� �������
	for (i = 0; i < A_len; ++i) 
    {
    	ELEM_TYPE line_len = LEN(A[i]);
        for (j = 0; j < line_len; ++j) 
            printf("%6d ", ELEM(A[i], j));
        printf("\n");
    };
    printf("\n");
    
    // ������� ����������
    for (i = 0; i < A_len; i++)  
		free(A[i]);
    
    // ������� �������� ������
	free(A); 
	A = NULL;
	
	system("pause");
	return 0;
};
