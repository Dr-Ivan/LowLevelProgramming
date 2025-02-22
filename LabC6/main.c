#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// ������� ��������� ��������� ������ ��������� � ��� ������ ����������� - ���������� �����,
// ��������� ������������ ��������� ��� �������
void arr_by_hand(float* arr, const int number_of_points){
	int i;
	for(i = 0;i<number_of_points*2; i+=2){ 						// ���� �� ���� ������
		printf("������� ���������� X ����� ����� %d: ", (i/2)+1);
		scanf("%f", arr+i+0);									// ���� �
		
		printf("������� ���������� Y ����� ����� %d: ", (i/2)+1);
		scanf("%f", arr+i+1); 									// ���� Y

	};
}

// ������� ��������� ��������� ������ ��������� � ��� ������ ����������� - ���������� �����,
// ��������� ��������� ��� ���������� ������� �� ��������� ���������
void randomize_arr (float* arr, const int number_of_points){
	float mn, mx;
	printf("������� ������� � �������� ��� ��������� ���������: ");
	scanf("%f %f", &mn, &mx);									// ���� ������ ��������� ��������� ���������
	printf("\n");
	
	if (mn > mx){												// ��� ������������� �������� ������� �������
		float t = mn;
		mn = mx;
		mx = t;
	};
	srand(time(0)); 											// ������������� ��������������� ������������������
	int i;
	for(i = 0;i<number_of_points*2; i+=2){							// ���� �� ���� ������
		*(arr+i) = (float)rand() / RAND_MAX * (mx - mn) + mn;		// ��������� �
		*(arr+i+1) = (float)rand() / RAND_MAX * (mx - mn) + mn;		// ��������� Y

	};
}

// ������ ��������� ���������� �������������� ����� � �������� �������
// �� ���� ��������� ���������� ������ - ���������� ����� ����� � �������� �, �������� �������
bool belongs_to_area(const float x, const float y, const float A){
	bool left_half = (x <= 0) && (y >= x) && (y <= -x);			// ����� ����� ������� ��� � <= 0
	bool right_half = (x >= 0) && (y >= -x) && (y <= x);		// ����� ����� ������� ��� � >= 0
	bool in_parabola = (y <= -1 * x * x + A);					// ����� ������ ��������
	return (left_half || right_half) && in_parabola;			// ����������� �������
}

// ������� ��������� ��������� ������ ���������, ��� ������ ����������� - ���������� ����� � 
// �������� �, �������� ������� ��� ������ �������������� ����� � ������� ����� ������ �������
// ������� ������ ����� � ������� �� ��������� ������ � ������������ � ����������� � �������������� � �������
void print_arr(const float* const arr, const int number_of_points, const float A){
	int i;
	for(i = 0;i<number_of_points*2; i+=2){													// ���� �� ���� ������
		printf("����� %3d ����� ���������� (%10f, %10f). ", (i/2)+1, *(arr+i), *(arr+i+1));	// ����� ���������
		bool belongs = belongs_to_area(*(arr+i), *(arr+i+1), A);								// ������ ��������������
		
		if (belongs)														// ����� ���������� � ��������������
			printf("��� ����������� �������� �������. ");
		else
			printf("��� �� ����������� �������� �������. ");
		
		printf("\n");		// ����� ������
	};
}

int main(int argc, char *argv[]) {
	system("color F0");  // ����� ���� �������
	system("chcp 1251"); // ������� �������� �������� �����
	
	// ���������� ����������
	int points_num = 111;
	int arr_fill = 0;
	int max_len = 110;
	float A_parametr;
	// ��������� �� ������� ����������� �������
	void (*input_arr_func_ptr)(float*, const int);  
	// ��������� �� ������� ������ �������
	void (*print_arr_func_ptr)(const float* const, const int, const float) = print_arr; 
	
	// ���������� ���������� �������
	float points[110][2];
	
	while (points_num <= 1 || points_num >= max_len){
		// ���� ���������� �����
		printf("������� ���������� ��������������� �����: ");
		scanf("%d", &points_num);
		printf("\n");
	};
	
	// ����� ������� ���������� � ������� �� ������
	while (arr_fill != 1 && arr_fill != 2){
		printf("�������� ������ ���������� ������� ���������:\n\t1 - ������ ���� ���������,\n\t2 - ���������� ���������� �������.\n������� - ");
		scanf("%d", &arr_fill);
		printf("\n");
	};
	
	// ������������� ��������� ��������� ��������
	if (arr_fill == 1)
		input_arr_func_ptr = arr_by_hand;
	else
		input_arr_func_ptr = randomize_arr;
	
		
	// ����������� ������� ��� ���������� ��������
	float* points_ptr = &points;
		
	// ���������� ������� ��������� ��������
	input_arr_func_ptr(points_ptr, points_num);	

	// ���� ��������� �, ��������� �������
	printf("������� �������� �, �������� �������: ");
	scanf("%f", &A_parametr);
	printf("\n");
	
	// ����� ������ �������������� � ������� ��� ����� ����� 
	print_arr_func_ptr(points_ptr, points_num, A_parametr);
	
	system("pause"); // �� ��������� ����
	return 0;
}
