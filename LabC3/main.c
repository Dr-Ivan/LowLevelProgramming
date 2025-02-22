#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */


int main() {
	system("color F0");
	system("chcp 1251"); // ������� �������� �������� �����
	
	// ���������� ����������
	float x0, xh, xn;
	float y0, yh, yn;
	float x, y;
	double result;
	double max;
	double min;
	int nm1, nm2;
	
	// ���� ����������
	printf("������� [x0 (xh) xn]: ");
	scanf("%f %f %f", &x0, &xh, &xn);
	
	printf("������� [y0 (yh) yn]: ");
	scanf("%f %f %f", &y0, &yh, &yn);
	
	printf("������� ����� ��������: nm1, nm2: ");
	scanf("%d %d", &nm1, &nm2);
	
	// �������� 
	bool correctData = (nm1 >= 2.0f && nm1 <= 6.0f && nm2 >= 2.0f && nm2 <= 6.0f && x0 <= xn && y0 <= yn && yh > 0 && xh > 0);
	if (!correctData) {
		printf("������� �������� ������."); 	// ���� ������ �������
		return 1;	// ������� ��� ������ 1
	};
	
	// ����������
	x = x0; // ��������� �������� �
	result = 0; // ���������� ��� �������� ����������
	max = -2147483647; // ���������� ��� ��������� (�������� ����������� �������������)
	min = 2147483647; // ���������� ��� �������� (�������� ����������� �������������)
	
	// ����� ����� �������
	printf("|-------|-------|--------------|\n");
	printf("|   x   |   y   |    Result    |\n");
	printf("|-------|-------|--------------|\n");
	
	// ��������� ����� ��� ������������� ������� ���� ����������
	while(x < xn + xh/3) {
		y = y0;  // ����� �������� �
		while(y < yn + yh/3) {
			result = 0; 
			// ���������� �������� ������ � ������ �����
			{
				double result1 = 0; //��������� 1
				double result2 = 0; // ��������� 2
				int n = 1; //�������
				for (; n <= nm1; n++){ // ���� ���������� ����� ������� ����������
					double pw = pow(x, n);
					result1 += 1 + y * log(pw);
				};
				n = 1;	// ����� ��������
				for (; n <= nm2; n++){ // ���� ���������� ����� ������� ����������
					result2 += (7*x + pow(y, n-1)) / (sqrt(2*n + y));
				};
				result = result1 + ((x+1) / (3*y)) * result2; // �������� ���������
			};
			
			printf("| %5.2f | %5.2f | %.5le | \n", x, y, result); // ����� ������ �������
			printf("|-------|-------|--------------|\n"); // ����� ����������� ����� �������
			if (max < result) {	// ���������� ���������
				max = result;
			};
			
			if (min > result) {	// ���������� ��������
				min = result;
			};
				y += yh; // ��� �� �
			};
		x += xh; // ��� �� �
	};
	
	printf("����������� �������� = %le \n", min); // ����� ��������
	printf("������������ �������� = %le \n", max); // ����� ���������
	
	system("pause"); // �����, ����� ���� �� ����������� ����
	return 0;
}
