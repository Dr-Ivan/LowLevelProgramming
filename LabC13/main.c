#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "TriangleModule.h"
#include "ProductModule.h"


int main(int argc, char *argv[]) {
	system("color F0");  	// ����� ���� �������
	system("chcp 1251"); 	// ������� �������� �������� �����
	
	// ���������� ����������
	float ax, ay, bx, by, cx, cy;
	float dx, dy;
	float centx, centy;
	float angle;
	float k;
	float side;
	float X,Y;
	int cont = false;
	Triangle t;	
	Product* products = NULL;
    int size = 0;
	int type;
	int index;
	int command = 0;	  // ������� ������������
	
	while (true){	// �������� ���� ��������� ��� ����� ������ ������������
        printf("\n����:\n");
        printf("1. ������������ 11: ������ �� ����������-�������������\n");
        printf("2. ������������ 12: ������ � �������� ��������-���������\n");
        printf("3. ����� �� ���������\n");
		printf("�������� �������� (������� ������ �����): ");

        int choice;
        scanf("%d", &choice);
        
    	bool created = false; // ������ �� �����������
		bool run = true;	  // ����������� ������ � ������ ������

        switch (choice) 	
        {
        case 1: // ������������ 11: ������ �� ����������-�������������
			while (run){
				printf("������� ������� (������ �����):\
							\n\t1 - �������� ������������ �� ����������� ��� ������.\
							\n\t2 - ����������� ������������ �� �������� �������� ������������ ���� X � Y.\
							\n\t3 - ������ ��������� ��������� ������������.\
							\n\t4 - ������� ������������ �� �������� ���� ������ ��� ���������.\
							\n\t5 - ��������� ������� ������������ �� �������� ����������� �������� ������������ ��� ���������.\
							\n\t6 - �������� ��������������� ������������ �� ��������� ������� �������, �������� �������� ��������� � ������ (0,0).\
							\n\t7 - �������� �������������� ������������ �� ���� �������� ������ �������, ����������� � �������������� ��������� X � Y.\
							\n\t8 - ����� ������������ � �������.\
							\n\t9 - ����� �� ����� ������ ������. \n\n");
							
				printf("�������� �������: ");
				scanf("%d", &command);
				printf("\n\n");
				
				switch (command)
			    {
			    case 1:  // �������� ����������� �� ����������� ������
			    	printf("������� ���������� ����� �����������\n� �������� ������� ax, ay, bx, by, cx, cy: ");
			    	scanf("%f %f %f %f %f %f", &ax, &ay, &bx, &by, &cx, &cy);
			    	Triangle t = create_triangle(ax, ay, bx, by, cx, cy);
			    	created = true;
			    	printf("������ ����� �����������. ��� ��������� ����������� ������� 8.\n\n");
			    	break;
			    	
			    case 2:	// ��������� ������������
			    	if (!created) {
						printf("����������� ��� �� ������!\n\n");
						break;
					};
			        printf("������� �������� dx, dy: ");
			    	scanf("%f %f", &dx, &dy);
			    	move_triangle(&t, dx, dy);
			    	printf("����������� ���������. ��� ��������� ����������� ������� 8.\n\n");
			    	break;
			
			    case 3:	// ������ ��������� ���������� ������������
			    	if (!created) {
						printf("����������� ��� �� ������!\n\n");
						break;
					};
			    	center(&t, &centx, &centy);
			    	printf("\n\n");
			    	printf("�������� ������� ������������ ��������� � ����� (%.2f, %.2f).\n\n", centx, centy);	
			        break;
			
			    case 4:	// ������� ������������ ������ ��������� �� �������� ���� � �������� 
			    	if (!created) {
						printf("����������� ��� �� ������!\n\n");
						break;
					};
			        printf("������� ���� �������� � ��������: ");
			    	scanf("%f", &angle);
			    	rotate(&t, angle);
			    	printf("����������� �������. ��� ��������� ����������� ������� 8.\n\n");
			    	break;
			
			    case 5:	// ��������������� ������������ �� �������� �����������
			    	if (!created) {
						printf("����������� ��� �� ������!\n\n");
						break;
					};
			        printf("������� ����������� �������� k: ");
			    	scanf("%f", &k);
			    	resize(&t, k);
			    	printf("����������� ���������������. ��� ��������� ����������� ������� 8.\n\n");
			    	break;
			
			    case 6:	// �������� ��������������� ������������ � ���������� � ������ ���������
			        printf("������� ����� ������� ��������������� ������������ � ���������� � ����� (0, 0): ");
			    	scanf("%f", &side);
			    	t = create_equilateral_triangle(side);
			    	created = true;
			    	printf("������ ����� �����������. ��� ��������� ����������� ������� 8.\n\n");
			    	break;
			
			    case 7: // �������� �������������� ������������
			        printf("������� ������ X � Y: ");
			    	scanf("%f %f", &X, &Y);
			    	t = create_right_triangle(X,Y);
			    	created = true;
			    	printf("������ ����� �����������. ��� ��������� ����������� ������� 8.\n\n");
			    	break;
			    	
			    case 8:	// ����� ������������ � ������� �� ��������� �������
			    	if (!created) {
						printf("����������� ��� �� ������!\n\n");
						break;
					};
			    	print_triangle(&t);
			    	break;
			    	
			    case 9: // ���������� ������
			    	printf("���������� ������ �� ����������-�������������...\n\n");
			    	run = false;
			    	break;
			
			    default:
			        printf("����������� �������!\n\n");
			        break;
			    };
			    
			if (run){ // ������ � �����������, ����� �� �������� ����� ����� ���������� ������� ����
				printf("����������? \n\t0 - ���, �����.\n\t1 - ��, ����������.\n");
				printf("�������� �������: ");
				scanf("%d", &cont);
				printf("\n\n");
				if (!cont) run = false;
			};		
			};
			break;
			
        case 2: // ������������ 12: ������ � �������� ��������-���������
		        
			while (run) { 
		        printf("\n\n����:\n");
		        printf("1. �������� �������.\n");
		        printf("2. ������� �������.\n");
		        printf("3. �������� ���������� � ������������ ��������.\n");
		        printf("4. ������� �� ����� ���������� ��� ���� ���������.\n");
		        printf("5. ������� �� ����� ������ ���������� � ��������� � ���������� ����������.\n");
		        printf("6. ����� �� ����� ������ ������.\n");
		        printf("�������� �������� (������� ������ �����): ");
		
		        scanf("%d", &command);
		
		        switch (command)
		        {
		        case 1:
		            printf("������� ��� ���������\n(%d - ���������� ����,\n%d - ������� �������,\n%d - ���������� �������)\n��� �����: ",  CHRISTMAS_TREE_NUM, CHRISTMAS_TREE_DECORATION_NUM, NEW_YEAR_GIFT_NUM);
		            scanf("%d", &type);
		            ProductType new_porduct_type = (ProductType)type;
		            Product* new_product = create_product(new_porduct_type);
		            if (!new_product) break;            
		            add_product(&products, &size, new_product);
		            printf("����� ������� �������� � ������. ����������� ������� 4 ��� ���������.");
		            break;
		
		        case 2:
		            if (size == 0)
		            {
		                printf("������ ����.\n");
		                break;
		            }
		
		            printf("������� ����� ��������, ������� ���������� ������� (��������� � �������): ");
		            scanf("%d", &index);
		            remove_product(&products, &size, index - 1);
		            break;
		
		        case 3:
		            if (size == 0)
		            {
		                printf("������ ����.\n");
		                break;
		            }
		
		            printf("������� ������ ��������, ������� ���������� �������� (��������� � �������): ");
		            scanf("%d", &index);
		            update_product(products, size, index - 1);
		            printf("������� ��������. ����������� ������� 4 ��� ���������.");
		            break;
		
		        case 4:
		            if (size == 0)
		            {
		                printf("������ ����.\n");
		                break;
		            }
		            print_all_products(products, size);
		            break;
		
		        case 5:
		            if (size == 0)
		            {
		                printf("������ ����.\n");
		                break;
		            }
		            print_products_by_mask(products, size);
		            break;
		
		        case 6:
		            printf("���������� ������ � �������� ��������-���������...\n\n");
		            free(products);
		            products = NULL;
		            run = false;
		            break;
		
		        default:
		            printf("����������� �������!\n");
		        };
		    };
		    break;
		    
        case 3:
            printf("����� �� ���������...\n");
            return 0;

        default:
            printf("����������� �������!\n");
        }
    };
		
	system("pause");
	return 0;
}

