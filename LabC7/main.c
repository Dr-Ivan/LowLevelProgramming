#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */



// ������� ��������� ������ � ���������� ��� ���������,
// ��������� ��������� ��� ���������� ������� �� ��������� ���������
void randomize_arr (int* arr, const int len){
	float mn, mx;
	printf("������� ������� � �������� ��� ��������� �����: ");
	scanf("%f %f", &mn, &mx);									// ���� ������ ��������� ��������� �����
	printf("\n");
	
	if (mn > mx){												// ��� ������������� �������� ������� �������
		float t = mn;
		mn = mx;
		mx = t;
	};
	srand(time(0)); 											// ������������� ��������������� ������������������
	int i;
	for(i = 0;i<len; i++){										// ���� �� ���� ���������
		arr[i] = (int) ((float)rand() / RAND_MAX * (mx - mn) + mn);		// ��������� ������� � �������� ���������
	};
}

// ������� ��������� ������ � ���������� ��� ���������, ������� ��� �� �����
void print_arr(const int* const arr, const int len){
	if (len == 0)
		printf("������ ����. \n");
	int i;
	for(i = 0;i<len; i++){												// ���� �� ���� ���������
		printf("������� ������� ����� %4d ����� %5d. ", i+1, arr[i]);	// ����� ��������
		printf("\n");		// ����� ������
	};
}

// ������� ��������� ������ � ���������� ��� ���������, ��������� ��� �� ����� (� ������� �����������)
void sort_arr(int* arr, const int len){
	int i = 0;
	int j;
	for (; i < len; i++){  	// ���������� ������� �������
		// ����� ������� ������������ �������� ����������������� �����
		int min_ind = i;	
		for (j = i+1; j < len; j++){
			min_ind = arr[min_ind] > arr[j] ? j : min_ind;
		};
		
		// ��������� ������ ������ � ������ ����������������� �����
		int temp = arr[i];
		arr[i] = arr[min_ind];
		arr[min_ind] = temp;
	};
}

// ������� ������� � ������� ������ � �� ������� � �� ������� ������
void make_arr_B(const int* const arr_A, const int A_len){
	int len_B = 0;						// ���������� ���������� �����
	int i;
	for(i = 0;i<A_len; i++){
		int current = arr_A[i];			// ���� �� ���� ���������
		if ((current%3 == 0) || (current%5 == 0)){
			len_B++;					// ������� ���������� ���������� �����
		};
	};
	
	// ��������� ������ ��� ������ �
	int* arr_B = (int*) malloc(sizeof(int) * len_B);
	if (!arr_B) exit(1);				// �������� �� ��, ��� ������ ���� ��������
	int k = 0;
	for(i = 0;i<A_len; i++){
		int current = arr_A[i];			// ���� �� ���� ��������� ������� �
		if ((current%3 == 0) || (current%5 == 0)){
			arr_B[k++] = current; 		// ���������� ������� � ������� �������
		};

	};

	printf("\n���������� ��������������� ������ B: \n");
	sort_arr(arr_B, len_B); 	// ���������� ������� �
	print_arr(arr_B, len_B);	// ����� ������� �
	free(arr_B);				// ���������� ������, ���������� �������� �
	arr_B = NULL;
}


int main(int argc, char *argv[]) {
	system("color F0");  // ����� ���� �������
	system("chcp 1251"); // ������� �������� �������� �����
	
	// ���������� ����������
	int A_len = 11111;
	int max_len = 10000;
	int* A = NULL;

	
	while (A_len <= 1 || A_len >= max_len){
		// ���� ���������� �����
		printf("������� ���������� ����� � ������� �: ");
		scanf("%d", &A_len);
		printf("\n");
	};
	
	A = (int*) malloc(sizeof(int) * A_len); 	// ��������� ������ ��� ������ �
	if (!A) exit(1);							// �������� �� ��, ��� ������ ���� ��������
	randomize_arr(A, A_len);					// ���������� ������� � ���������� �������
	
	
	printf("\n�������� ������ �: \n"); 			// ����� ������� �
	print_arr(A, A_len);

	make_arr_B(A, A_len); 						// ��� ���������� ��������, ��������� � �������� �
	
	free(A); 									// ���������� ������, ���������� �������� �
	A = NULL;
	system("pause");							// �� ��������� ����
	return 0;
}
