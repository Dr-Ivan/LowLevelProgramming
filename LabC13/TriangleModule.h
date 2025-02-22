#ifndef LAB11_HEADER
#define LAB11_HEADER

#define EPS 1e-6

// ��������� ��� ������������
typedef struct
{
	float ax;
	float ay;
	float bx;
	float by;
	float cx;
	float cy;
	bool equilateral;
} Triangle;

// �������� ����������� �� ����������� ������
Triangle create_triangle(float ax, float ay, float bx, float by, float cx, float cy);


// ��������� ������������
void move_triangle(Triangle* , float, float);


// ������ ��������� ���������� ������������
void center(const Triangle*, float*, float*);


// ������� ������������ �� �������� ���� � �������� ������ ���������
void rotate(Triangle*, float);


// ��������������� ������������ �� �������� �����������
void resize(Triangle*, float);


// �������� ��������������� ������������ � ���������� � ������ ���������
Triangle create_equilateral_triangle(float);


// �������� �������������� ������������
Triangle create_right_triangle(float, float);


// ����� ������������ � ������� �� ��������� �������
void print_triangle(const Triangle*);


#endif // LAB11_HEADER
