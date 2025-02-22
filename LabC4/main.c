#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// ������� ��������� ��������� ������ ��������� � ��� ������ ����������� - ���������� �����,
// ��������� ������������ ��������� ��� �������
void arr_by_hand(float arr[][2], const int len){
	int i = 0;
	for(;i<len; i++){ 												// ���� �� ���� ������
		printf("������� ���������� X ����� ����� %d: ", i);
		scanf("%f", &arr[i][0]);									// ���� �
		
		printf("������� ���������� Y ����� ����� %d: ", i);
		scanf("%f", &arr[i][1]); 									// ���� Y

	};
}

// ������� ��������� ��������� ������ ��������� � ��� ������ ����������� - ���������� �����,
// ��������� ��������� ��� ���������� ������� �� ��������� ���������
void randomize_arr (float arr[][2], const int len){
	float mn, mx;
	printf("������� ������� � �������� ��� ��������� ���������: ");
	scanf("%f %f", &mn, &mx);										 // ���� ������ ��������� ��������� ���������
	printf("\n");
	
	if (mn > mx){													// ��� ������������� �������� ������� �������
		float t = mn;
		mn = mx;
		mx = t;
	};
	srand(time(0)); 												// ������������� ��������������� ������������������
	int i = 0;
	for(;i<len; i++){												// ���� �� ���� ������
		arr[i][0] = (float)rand() / RAND_MAX * (mx - mn) + mn;		// ��������� �
		arr[i][1] = (float)rand() / RAND_MAX * (mx - mn) + mn;		// ��������� Y

	};
}

// ������ ��������� ���������� �������������� ����� � �������� �������
// �� ���� ��������� ���������� ������ - ���������� ����� ����� � �������� �, �������� �������
bool belongs_to_area(float point[2], const float A){
	float x = point[0];											// ���������� � �����
	float y = point[1];											// ���������� Y �����
	
	bool left_half = (x <= 0) && (y >= x) && (y <= -x);			// ����� ����� ������� ��� � <= 0
	bool right_half = (x >= 0) && (y >= -x) && (y <= x);		// ����� ����� ������� ��� � >= 0
	bool in_parabola = (y <= -1 * x * x + A);					// ����� ������ ��������
	return (left_half || right_half) && in_parabola;			// ����������� �������
}

// ������� ��������� ��������� ������ ���������, ��� ������ ����������� - ���������� ����� � 
// �������� �, �������� ������� ��� ������ �������������� ����� � ������� ����� ������ �������
// ������� ������ ����� � ������� �� ��������� ������ � ������������ � ����������� � �������������� � �������
void print_arr(float arr[][2], const int len, const float A){
	int i = 0;
	for(;i<len; i++){																		// ���� �� ���� ������
		printf("����� %3d ����� ���������� (%10f, %10f). ", i+1, arr[i][0], arr[i][1]);		// ����� ���������
		bool belongs = belongs_to_area(arr[i], A);								// ������ ��������������
		
		if (belongs)															// ����� ���������� � ��������������
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
	int points_num;
	int arr_fill = 0;
	float A_parametr;
	
	// ���� ���������� �����
	printf("������� ���������� �������������� �����: ");
	scanf("%d", &points_num);
	printf("\n");
	
	// ����� ������� ���������� � ������� �� ������
	while (arr_fill != 1 && arr_fill != 2){
		printf("�������� ������ ���������� ������� ���������:\n\t1 - ������ ���� ���������,\n\t2 - ���������� ���������� �������.\n������� - ");
		scanf("%d", &arr_fill);
		printf("\n");
	};
	
	// ���������� ���������� �������
	float points[points_num][2];
	
	// ���������� ��� ��������� ��������
	if (arr_fill == 1)
		arr_by_hand(points, points_num);
	else
		randomize_arr(points, points_num);
		
	// ���� ��������� �, ��������� �������
	printf("������� �������� �, �������� �������: ");
	scanf("%f", &A_parametr);
	printf("\n");
				
	// ����� ������ �������������� � ������� ��� ����� ����� 
	print_arr(points, points_num, A_parametr);
	
	system("pause"); // �� ��������� ����
	return 0;
}
