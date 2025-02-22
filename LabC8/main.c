#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <mem.h>


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// ������� ��������� ������,
// ��������� ��������� ��� ���������� ������� �� ��������� ���������
void randomize_arr (int* arr, float mn, float mx){
	int len = arr[0];   	// ����� ��������� �������
	int i;
	for(i = 1; i<=len; i++){										// ���� �� ���� ���������
		arr[i] = (int) ((float)rand() / RAND_MAX * (mx - mn) + mn);	// ��������� ������� � �������� ���������
	};
};

// ������� ��������� ������ � �������� ��� ���,
// ����� �� ������� ������ �� ��������, �������� �� �������� ��������
int* delete_even_indexes(int* arr){
	int len = arr[0]; 			// ����� ��������� �������
	int i, j;
	int new_size = len;			// �������, �� ������� ������������ ����� ��������������� �������� ��� ������
		
	for (i = len; i >= 1; i--){  				// ���� �� ���� ��������
		if (i % 2 == 0){						// �� ������ ������ �������
			for (j = i; j < new_size; j++){		// �������� ��� �������� �� ���� �����
				arr[j] = arr[j+1];
			};
			new_size--;							// �� ������������� ����� ������ ��������
			arr[0]--;							// ��������� ������� ������, ������� �������� ������ �������
		};
		
//		// ���������� ������ ������� �� ������ ��������
//		int k = 1;
//		for (k =1;k<=len;k++){
//			printf(" %d ", arr[k]);
//		};
//		printf("\n");
		
    }
    arr = (int*) realloc(arr, (arr[0])*sizeof(int));	// ����������� ������� - ���������� ���������� ������
	if (!arr) exit(1);									// �������� �� ��, ��� ������ ���� ��������
	return arr;
};

// ������� ��������� ������, ������� �������� �
// ��������� ������� ����� � ������
int* add_zeros(int* arr){
	int len = arr[0], mx = arr[1]; 						// ����� ��������� �������
	int i, j = 1;
	for(i = 1; i<=len; i++){							// ���� �� ���� ���������
		mx = mx > arr[i] ? mx : arr[i];					// ����� ���������
	};
	mx = abs(mx); 										// ������ ���������
	arr = (int*) realloc(arr, (len+mx)*sizeof(int));	// ����������� ������
	if (!arr) exit(1);						    		// �������� �� ��, ��� ������ ���� ��������
	arr[0] = len+mx; 			 						// ����� ������ �������
	
	for(i = len; i >= 1; i--){							// ����������� ��� �������� �� mx �������� ������
		arr[i+mx] = arr[i];
	};
	
	memset(arr+1, 0, (size_t)(mx * sizeof(int))); 		// �������� ������ mx ���������
	 
	return arr;
};

// ������� ��������� ������, � ������������ ��� ���� � ������ 
int* relocate_zeros(int* arr){
	int len = arr[0];  						// ����� ��������� �������
	int zero_count = 0, i = 1;  			// ������� �����
	for(i = 1; i<=len; i++){				// ���� �� ���� ���������
		zero_count += arr[i] == 0 ? 1 : 0;	// ������� �����
	};
	int j = len;	
	for (i = len; i >= 1; i--){				// ����������� ��� ��������� �������� � �����
		if (arr[i] != 0){
			arr[j--] = arr[i];
		}
	}
	memset(arr+1, 0, (size_t)(zero_count * sizeof(int))); // �������� ������� ������ ���������, ������� ���� ������� ����� � �������� �������
	return arr;
};

// ������� ��������� ������ � �������� ��� ��������, ������ �, ��
// ������� �������������� ���� ��������� �������
int* replace_with_average(int* arr, const int x){
	int len = arr[0];	// ����� ��������� �������
	int avg = 0;		// ������� ��������������
	int i;
	for(i = 1; i<=len; i++){	// ���� �� ���� ���������
		avg += arr[i];			// ������� �����
	};
	avg /= len;  				// ������� �������� ���������������
	for(i = 1; i<=len; i++){	// ���� �� ���� ���������
		if (arr[i] == x)		// ������ ��������� ���������
			arr[i] = avg;		// �� ������� ��������������
	};
	return arr;
};


int main(int argc, char *argv[]) {
	
	system("color F0");  // ����� ���� �������
	system("chcp 1251"); // ������� �������� �������� �����
	srand(time(0)); 	 // ������������� ��������������� ������������������
	
	// ���������� ����������
	int A_len = 11111;
	int B_len = 11111;
	int max_len = 10000;
	int i, j;
	int** A = NULL;

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
	
    A = (int**) malloc(A_len * sizeof(int*));		// ��������� ������ ��� ��������� ������ �
	if (!A) exit(1);								// �������� �� ��, ��� ������ ���� ��������
	
 	//��� ������� ��������-��������� �������� ���� ������
    for (i = 0; i < A_len; ++i){
        A[i] = (int*) calloc(B_len+1, sizeof(int)); // ��������� ������ ��� ����������
		if (!A[i]) exit(1);							// �������� �� ��, ��� ������ ���� ��������
		A[i][0] = B_len;							// ��������� �����
 		randomize_arr(A[i], mn, mx);				// ���������� ������� ���������� �������
	};
	
	printf("�������� ������: \n");
	
	// ����� ���������� �������
	for (i = 0; i < A_len; ++i) 
    {
    	int line_len = A[i][0];
        for (j = 1; j <= line_len; ++j) 
            printf("%6d ", A[i][j]);
        printf("\n");
    };
    
    printf("\n\n");
    
    // ���������� ���������� �������� ��� ������������
    for (i = 0; i < A_len; ++i) 
    {
    	if (i % 4 == 0)
    		A[i] = delete_even_indexes(A[i]);
    	if (i % 4 == 1)
        	A[i] = add_zeros(A[i]);
        if (i % 4 == 2)
        	A[i] = relocate_zeros(A[i]);
        if (i % 4 == 3){
	        int x;
			printf("������� �����, ������� ����� �������� �� ������� � ������ ����� %d: ", i+1);
			scanf("%d", &x);
        	A[i] = replace_with_average(A[i], x);
		};
    };
    
    
    printf("���������� ������: \n");
    
    // ����� ���������� �������
	for (i = 0; i < A_len; ++i) 
    {
    	int line_len = A[i][0];
        for (j = 1; j <= line_len; ++j) 
            printf("%6d ", A[i][j]);
        printf("\n");
    };
    
    // ������� ����������
    for (i = 0; i < A_len; ++i)  
		free(A[i]);
    
    // ������� �������� ������
	free(A); 
	A = NULL;
	
	return 0;
}
