#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

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

typedef struct
{
    int operation_number;
    float dx;
    float dy;
    float alpha;
    float k;
    float side;
	float X;
	float Y;
    Triangle t;
} OperationData;

typedef struct
{
    int operation_number;
    Triangle t;
    Triangle result;
} OperationResult;


// �������� ��������� ������������ �����
bool equal_float(float a, float b){
	return (abs(a - b) < EPS);
}


// �������� ����������� �� ����������� ������
Triangle create_triangle(float ax, float ay, float bx, float by, float cx, float cy){
	Triangle t;
	t.ax = ax;
	t.ay = ay;
	t.bx = bx;
	t.by = by;
	t.cx = cx;
	t.cy = cy;
	t.equilateral = (bool) (equal_float(pow((bx-ax), 2) + pow((by-ay), 2), pow((cx-ax), 2) + pow((cy-ay), 2)) &&
							equal_float(pow((bx-cx), 2) + pow((by-cy), 2), pow((cx-ax), 2) + pow((cy-ay), 2)));                     
	return t;
};


// ��������� ������������
void move_triangle(Triangle* t, float dx, float dy){
	t->ax += dx;
	t->ay += dy;
	t->bx += dx;
	t->by += dy;
	t->cx += dx;
	t->cy += dy;
};


// ������ ��������� ���������� ������������
void center(const Triangle* t, float* resx, float* resy){
	*resx = (float)(t->ax + t->bx + t->cx)/3;
	*resy = (float)(t->ay + t->by + t->cy)/3;
};


// ������� ������������ �� �������� ���� � �������� ������ ���������
void rotate(Triangle* t, float alpha_deg){
	float center_x, center_y;
	center(t, &center_x, &center_y);
	
	float alpha_rad = alpha_deg * M_PI / 180;
	
	float ax = center_x + (t->ax - center_x) * cos(alpha_rad) - (t->ay - center_y) * sin(alpha_rad);
	float ay = center_y + (t->ax - center_x) * sin(alpha_rad) + (t->ay - center_y) * cos(alpha_rad);
	float bx = center_x + (t->bx - center_x) * cos(alpha_rad) - (t->by - center_y) * sin(alpha_rad);
	float by = center_y + (t->bx - center_x) * sin(alpha_rad) + (t->by - center_y) * cos(alpha_rad);
	float cx = center_x + (t->cx - center_x) * cos(alpha_rad) - (t->cy - center_y) * sin(alpha_rad);
	float cy = center_y + (t->cx - center_x) * sin(alpha_rad) + (t->cy - center_y) * cos(alpha_rad);
	
	t->ax = ax;
	t->ay = ay;
	t->bx = bx;
	t->by = by;
	t->cx = cx;
	t->cy = cy;	
};


// ��������������� ������������ �� �������� �����������
void resize(Triangle* t, float k){
	t->ax *= k;
	t->ay *= k;
	t->bx *= k;
	t->by *= k;
	t->cx *= k;
	t->cy *= k;
};


// �������� ��������������� ������������ � ���������� � ������ ���������
Triangle create_equilateral_triangle(float side){
	Triangle t; 
	float ax = -side/2;
	float ay = -side*sqrt(3)/6;
	float bx = side/2;
	float by = -side*sqrt(3)/6;
	float cx = 0;
	float cy = side*sqrt(3)/3;
	
	t.ax = ax;
	t.ay = ay;
	t.bx = bx;
	t.by = by;
	t.cx = cx;
	t.cy = cy;
	
	t.equilateral = true;
	return t;
};


// �������� �������������� ������������
Triangle create_right_triangle(float sidex, float sidey){
	Triangle t;
	t.ax = 0;
	t.ay = 0;
	t.bx = sidex;
	t.by = 0;
	t.cx = 0;
	t.cy = sidey;
	t.equilateral = false; 
	return t;
};


// ����� ������������ � ������� �� ��������� �������
void print_triangle(const Triangle* t){
	float px1, py1, px2, py2, px3, py3;
	
	if (t->ay > t->by){
		if (t->ay > t->cy){
			px1 = t->ax;
			py1 = t->ay;
			if (t->bx < t->cx){
				px2 = t->bx;
				py2 = t->by;
				px3 = t->cx;
				py3 = t->cy;
			} else{
				px2 = t->cx;
				py2 = t->cy;
				px3 = t->bx;
				py3 = t->by;
			};
		} else {
			px1 = t->cx;
			py1 = t->cy;
			
			if (t->bx < t->ax){
				px2 = t->bx;
				py2 = t->by;
				px3 = t->ax;
				py3 = t->ay;
			} else{
				px2 = t->ax;
				py2 = t->ay;
				px3 = t->bx;
				py3 = t->by;
			};
			
		};	
	}else{
		if (t->by > t->cy){
			px1 = t->bx;
			py1 = t->by;
			if (t->ax < t->cx){
				px2 = t->ax;
				py2 = t->ay;
				px3 = t->cx;
				py3 = t->cy;
			} else{
				px2 = t->cx;
				py2 = t->cy;
				px3 = t->ax;
				py3 = t->ay;	
			};
		} else {
			px1 = t->cx;
			py1 = t->cy;
			
			if (t->bx < t->ax){
				px2 = t->bx;
				py2 = t->by;
				px3 = t->ax;
				py3 = t->ay;
			} else{
				px2 = t->ax;
				py2 = t->ay;
				px3 = t->bx;
				py3 = t->by;	
			};
			
		};	
		
	}
	
	
	printf("\t(%.2f, %.2f)\n", px1, py1);
	printf("(%.2f, %.2f)\t(%.2f, %.2f)\n", px2, py2,px3, py3);
	printf("[%s]", t->equilateral? "��������������": "����������������");
	printf("\n\n");
}


void write_to_binary_file()
{
    FILE *file = fopen("operations.dat", "wb");
    if (file == NULL)
    {
        printf("������ ��� �������� ����� ��� ������.\n");
        return;
    }
    
	float ax, ay, bx, by, cx, cy;
	printf("������� ������� (������ �����):\
					\n\t2 - ����������� ������������ �� �������� �������� ������������ ���� X � Y.\
					\n\t3 - ������ ��������� ��������� ������������.\
					\n\t4 - ������� ������������ �� �������� ���� ������ ��� ���������.\
					\n\t5 - ��������� ������� ������������ �� �������� ����������� �������� ������������ ��� ���������.\
					\n\t6 - �������� ��������������� ������������ �� ��������� ������� �������, �������� �������� ��������� � ������ (0,0).\
					\n\t7 - �������� �������������� ������������ �� ���� �������� ������ �������, ����������� � �������������� ��������� X � Y.\n\n");
	
    int more = 1;
    while (more)
    {
        OperationData opData;
        printf("�������� ������� (2 - 7, ������� 1 - �������� ������������ ����������� � ����� ������): ");
        scanf("%d", &opData.operation_number);

        if (opData.operation_number < 2 || opData.operation_number > 8)
        {
            printf("����������� �������!\n");
            continue;
        }
        
        printf("������� ���������� ����� �����������\n� �������� ������� ax, ay, bx, by, cx, cy: ");
	    scanf("%f %f %f %f %f %f", &ax, &ay, &bx, &by, &cx, &cy);
	    opData.t = create_triangle(ax, ay, bx, by, cx, cy);

		switch (opData.operation_number)
        {
        case 2:
            printf("������� �������� dx, dy: ");
	    	scanf("%f %f", &opData.dx, &opData.dy);
            break;

        case 3:
            break;

        case 4:
            printf("������� ���� �������� � ��������: ");
	    	scanf("%f", &opData.alpha);
            break;

        case 5:
        	printf("������� ����������� �������� k: ");
	    	scanf("%f", &opData.k);
            break;

        case 6:
            printf("������� ����� ������� ��������������� ������������ � ���������� � ����� (0, 0): ");
	    	scanf("%f", &opData.side);
            break;

        case 7:
            printf("������� ������ X � Y: ");
	    	scanf("%f %f", &opData.X, &opData.Y);
            break;

        default:
            printf("����������� �������!\n\n");
            continue;
        }

        fwrite(&opData, sizeof(OperationData), 1, file);

        printf("�������� ��� ���� ��������? (1 - ��, 0 - ���): ");
        scanf("%d", &more);
    }

    fclose(file);
}

void process_binary_file()
{
    FILE *inputFile = fopen("operations.dat", "rb");
    if (inputFile == NULL)
    {
        printf("������ ��� �������� ����� ��� ������.\n");
        return;
    }

    FILE *outputFile = fopen("results.dat", "wb");
    if (outputFile == NULL)
    {
        printf("������ ��� �������� ����� ��� ������.\n");
        fclose(inputFile);
        return;
    }

    OperationData opData;
    while (fread(&opData, sizeof(OperationData), 1, inputFile) == 1)
    {
        OperationResult opResult;
        opResult.operation_number = opData.operation_number;
        opResult.t = opData.t;

        switch (opData.operation_number)
        {
        case 2:
        	opResult.result = opResult.t;
        	move_triangle(&opResult.result, opData.dx, opData.dy);
            break;

        case 3:
        	center(&opResult.t, &opResult.result.ax, &opResult.result.ay);
            break;

        case 4:
        	opResult.result = opResult.t;
            rotate(&opResult.result, opData.alpha);
            break;

        case 5:
        	opResult.result = opResult.t;
            resize(&opResult.result, opData.k);
            break;

        case 6:
            opResult.result = create_equilateral_triangle(opData.side);
            break;

        case 7:
            opResult.result = create_right_triangle(opData.X,opData.Y);
            break;

        default:
            printf("����������� ������� %d!\n", opData.operation_number);
            continue;
        }

        fwrite(&opResult, sizeof(OperationResult), 1, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);
}

void read_binary_file()
{
    FILE *file = fopen("results.dat", "rb");
    if (file == NULL)
    {
        printf("������ ��� �������� ����� ��� ������.\n");
        return;
    }

    OperationResult opResult;
    while (fread(&opResult, sizeof(OperationResult), 1, file) == 1)
    {
        printf("�������� ����� %d\n", opResult.operation_number);
        printf("��� �������������: \n");
        print_triangle(&opResult.t);
        printf("\n");
        

        if (opResult.operation_number >= 2 && opResult.operation_number <= 7 && opResult.operation_number != 3)
        {
            printf("���������: \n");
            print_triangle(&opResult.result);
            printf("\n");
        }
        else if (opResult.operation_number == 3)
        {
           	printf("�������� ������� ������������ ��������� � ����� (%.2f, %.2f).\n\n", opResult.result.ax, opResult.result.ay);	
            printf("\n");
        }
        else
        {
            printf("����������� �������!\n");
        }
        printf("\n");
    }

    fclose(file);
}

int main()
{
	system("color F0");
	system("chcp 1251");
	
    int choice;
    do
    {
        printf("����:\n");
        printf("1. �������� ������ � �������� ����\n");
        printf("2. ���������� �������� ���� � �������� ����������\n");
        printf("3. ��������� ���������� �� ��������� �����\n");
        printf("4. ����� �� ���������\n");
        printf("��� �����: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            write_to_binary_file();
            break;
        case 2:
            process_binary_file();
            break;
        case 3:
            read_binary_file();
            break;
        case 4:
            printf("����� �� ���������...\n");
            break;
        default:
            printf("���������� �������!\n");
        }
    } while (choice != 4);

    return 0;
}

