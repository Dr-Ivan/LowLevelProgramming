#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*  ���: Lab5
	����: 
				x1 = 4/3, xk = x_(k�1) ^ ((2*k^2) / (4*k^2 - 1))
				����� ������ xn, ����� ��� (x_(n)�x_(n�1)) < eps
	����: 12.10.2024
	�����: ��������� ���� �������������, ������ 3413
*/


// ����������� ������� ��� ���������� ������� ����� ������������������
double recursive_solution(double cur, int k, const double eps){
	float power = (2*k*k) / (float)(4*k*k - 1); // ����� �������
	double nxt = pow(cur, power);				// �������� � ��� �������
	double res = 0;
	if (cur - nxt >= eps)						// ���� ���� ���� ������������������ ������ ���������� �� �����������
		res = recursive_solution(nxt, ++k, eps); // ����������� ����� ��� ���������� ����� ������������������
	else										// ����� - ������ ������ ���� ������������������
		res = nxt;								// ���������� ��� ��������
	return res;					
};


// ����������� ������� ��� ���������� ������� ����� ������������������
double iterative_solution(const double x1, const double eps){
	double cur = x1;		// ������� ���� ������������������
	float k = 2.0f;			// ��� �����
	float power; 			// ����� �������
	double nxt = cur;		// ��������� ���� ������������������
	do {
		cur = nxt;							  // ������������ ������� ���� ������������������
		power = (2*k*k) / (float)(4*k*k - 1); // ���������� ����� �������
		nxt = pow(cur, power);				  // ���������� ����� ����� ������������������
		k++;								  // ��������� ������� - ����� �������� ����� ������������������
	} while (cur - nxt >= eps);				  // ������, ���� ����� ���� ������������������ ������ ���������� �� �����������
	return nxt;								  // ����� - ������ ������ ���� ������������������ -> ���������� ��� ��������
};

int main(int argc, char *argv[]) {
	system("color F0");   	//	����� ��� �������
	system("chcp 1251");	// ������� ����
	
	// ���������� ����������
	float eps;
	double res_iterative, res_recursive;
	// ����, ���� �� ����� ������, ��������������� ��� (eps > 0)
	do {
		printf("������� �������� ����������� ������� ����� ������� ������������������: ");
		scanf("%f", &eps);
		printf("\n");
	} while (eps <= 0);
	
	const double x1 = 4.0f/3.0f; 					// ������ ���� ������������������ - ���������
	res_iterative = iterative_solution(x1, eps);	// ����������� �������
	printf("��������, ���������� ��� ����������� �������: %17.15f \n", res_iterative); // ����� ����������

	res_recursive = recursive_solution(x1, 2, eps);	// ����������� �������
	printf("��������, ���������� ��� ����������� �������: %17.15f \n", res_recursive); // ����� ����������

	system("pause"); // �� ��������� ����
	return 0;
}
