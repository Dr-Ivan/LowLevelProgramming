#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


//#define FLAG1 1		//0x01 		// 00001
//#define FLAG2 2		//0x02 		// 00010
//#define FLAG3 4		//0x04 		// 00100
//#define FLAG4 8		//0x08 		// 01000
//#define FLAG5 16	//0x16 		// 10000


typedef enum {
    FLAG1 = 1,		//0x01 		// 00001
    FLAG2 = 2,		//0x02 		// 00010
    FLAG3 = 4,		//0x04 		// 00100
    FLAG4 = 8,		//0x08 		// 01000
    FLAG5 = 16	    //0x16 		//
} Flags;



// ������������ ��� ����� ��������
typedef enum {
    CHRISTMAS_TREE_NUM = 1,
    CHRISTMAS_TREE_DECORATION_NUM,
    NEW_YEAR_GIFT_NUM
} ProductType;

// ��������� ��� ��������� ����������
struct CHRISTMAS_TREE {
	float height;
    float weight;
};

struct CHRISTMAS_TREE_DECORATION {
    char color[26];
    float price;
};

struct NEW_YEAR_GIFT {
    char brand[51];
    float price;
};

// ����������� ��� ��������� ���������� � ����������� �� ���� ��������
union ProductParameters {
    struct CHRISTMAS_TREE tree;
    struct CHRISTMAS_TREE_DECORATION decoration;
    struct NEW_YEAR_GIFT gift;
};

// ��������� Product (�������� ���������, �������� ������� ����� � �������)
typedef struct  {
    ProductType type;         			// ��� ��������
    union ProductParameters params; 	// ��������� ��������
    unsigned int flags : 5;           	// 5 ������ � ������� ����
} Product;

// ����� � �� ��������    	  16 = FLAG5		8 = FLAG4			    	4 = FLAG3				2 = FLAG2			1	= FLAG1	
//							  ��������� 	  ������� ������  			 ������� ��������	          ������			����� ������


// �������� �������� ��������� ���� - ������������ ���������
Product* create_product(ProductType type)
{
    Product* product = (Product*) malloc(sizeof(Product));
    if (product == NULL)
    {
        printf("������������ ������!\n");
        exit(1);
    }

    product->type = type;
    product->flags = 0;
    
    printf("���� ������ � ��������: \n");
    switch (type)
    {
    case CHRISTMAS_TREE_NUM:
    	do {
	        printf("������: ");
	        scanf("%f", &product->params.tree.height);
	        printf("���: ");
	        scanf("%f", &product->params.tree.weight);
	    }while (product->params.tree.height <= 0 || product->params.tree.weight <= 0);
        break;

    case CHRISTMAS_TREE_DECORATION_NUM:
    	printf("���� (�� ����� 25 ����, ��� ��������): ");
	    scanf("%s", &product->params.decoration.color);
    	do {
	        printf("����: ");
	        scanf("%f", &product->params.decoration.price);
	    }while (product->params.decoration.price <= 0);
        break;

    case NEW_YEAR_GIFT_NUM:
        printf("������������� (�����, �� ����� 50 ����, ��� ��������): ");
        scanf("%s", &product->params.gift.brand);
        do{
	        printf("����: ");
	        scanf("%f", &product->params.gift.price);
        }while (product->params.gift.price <= 0);
        break;

    default:
        printf("����������� ��� ��������. �������� ��������. \n");
        free(product);
        return NULL;
    };
    
    int property = false;
    unsigned int mask = 0;
    printf("���� ������� ��������: \n");
    printf("������� ���������? (0 - ���, 1 - ��): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG5 : mask;
    
    printf("������� ����� ������� ������? (0 - ���, 1 - ��): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG4 : mask;
    
    printf("������� ����� ������� ��������? (0 - ���, 1 - ��): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG3 : mask;
    
    printf("�� ������� ��������� ������? (0 - ���, 1 - ��): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG2 : mask;
    
    printf("������� �������� ������� ������? (0 - ���, 1 - ��): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG1 : mask;
    
    product->flags = mask;

    return product;
}


// ���������� �������� � �������
void add_product(Product** data, int* size, Product* product)
{
    *data = (Product*)realloc(*data, (*size + 1) * sizeof(Product));
    if (data == NULL)
    {
        printf("������������ ������!\n");
        exit(1);
    }

    (*data)[*size] = *product;
    (*size)++;
}


// �������� �������� �� ��������
void remove_product(Product** data, int* size, const int index)
{
    if (index < 0 || index >= *size)
    {
        printf("�������� ������!\n");
        return;
    }
	int i = index;
    for (; i < *size - 1; i++)
        (*data)[i] = (*data)[i + 1];

    *data = (Product*)realloc(*data, (*size - 1) * sizeof(Product));
    (*size)--;
    printf("������� ������ �� �������. ����������� ������� 4 ��� ���������.");
}

// �������� ������ � �������� � ��������
void update_product(Product* data, const int size, const int index)
{
     if (index < 0 || index >= size)
    {
        printf("�������� ������!\n");
        return;
    }
    
	Product* cur_product_ptr = &data[index];
    printf("���� ������ � ��������: \n");
    switch (cur_product_ptr->type)
    {
    case CHRISTMAS_TREE_NUM:
    	do{
	        printf("������: ");
	        scanf("%f", &cur_product_ptr->params.tree.height);
	        printf("���: ");
	        scanf("%f", &cur_product_ptr->params.tree.weight);
	    }while (cur_product_ptr->params.tree.height <= 0 || cur_product_ptr->params.tree.weight <= 0);
        break;

    case CHRISTMAS_TREE_DECORATION_NUM:
    	printf("���� (�� ����� 25 ����, ��� ��������): ");
        scanf("%s", &cur_product_ptr->params.decoration.color);
	    do{
	        printf("����: ");
	        scanf("%f", &cur_product_ptr->params.decoration.price);
	    }while (cur_product_ptr->params.decoration.price <= 0);
        break;

    case NEW_YEAR_GIFT_NUM:
        printf("������������� (�����, �� ����� 50 ����, ��� ��������): ");
        scanf("%s", &cur_product_ptr->params.gift.brand);
        do{
	        printf("����: ");
	        scanf("%f", &cur_product_ptr->params.gift.price);
	    }while (cur_product_ptr->params.gift.price <= 0);
        break;

    default:
        printf("����������� ��� ��������. �������� ��������. \n");
        return;
    };
    
    int property = false;
    unsigned int mask = 0;
    printf("���� ������� ��������: \n");
    printf("������� ���������? (0 - ���, 1 - ��): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG5 : mask;
    
    printf("������� ����� ������� ������? (0 - ���, 1 - ��): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG4 : mask;
    
    printf("������� ����� ������� ��������? (0 - ���, 1 - ��): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG3 : mask;
    
    printf("�� ������� ��������� ������? (0 - ���, 1 - ��): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG2 : mask;
    
    printf("������� �������� ������� ������? (0 - ���, 1 - ��): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG1 : mask;
    
    cur_product_ptr->flags = mask;

    
}

// ����� ������ ��������
void print_product(const Product* product)
{
	ProductType type = product->type;
	char* type_string = NULL;
	switch (type)
    {
    case CHRISTMAS_TREE_NUM:
        type_string = "��� ���������� ����.";
        break;

    case CHRISTMAS_TREE_DECORATION_NUM:
        type_string = "��� ������� �������.";
        break;

    case NEW_YEAR_GIFT_NUM:
        type_string = "��� ���������� �������.";
        break;

    default:
        type_string = "��� ����������� ��� ��������.";
        return;
    };
		
    printf("��� ��������: %d. %s\n", type, type_string);

    switch (type)
    {
    case CHRISTMAS_TREE_NUM:
        printf("������: %.2f \n", product->params.tree.height);
        printf("���: %.2f \n", product->params.tree.weight);
        break;

    case CHRISTMAS_TREE_DECORATION_NUM:
        printf("����: %s \n", product->params.decoration.color);
        printf("����: %.2f \n", product->params.decoration.price);
        break;

    case NEW_YEAR_GIFT_NUM:
        printf("������������� (�����): %s \n", product->params.gift.brand);
        printf("����: %.2f \n", product->params.gift.price);
        break;

    default:
        printf("����������� ��� ��������. �������� ��������. \n");
        return;
    };

    printf("������ �������� ��������. \n");
    if (product->flags & FLAG5)
        printf("\t����� ���������.\n");
    if (product->flags & FLAG4)
        printf("\t����� ����� ������� ������.\n");
    if (product->flags & FLAG3)
        printf("\t����� ����� ������� ��������.\n");
    if (product->flags & FLAG2)
        printf("\t�� ����� ��������� ������.\n");
    if (product->flags & FLAG1)
        printf("\t��� ����� ������.\n");
}


// ����� ���� ��������� �������
void print_all_products(const Product* data, const int size)
{
    printf("������ ���� ���������:\n");
    int i = 0;
    for (; i < size; i++)
    {
        printf("������� �����: %d\n", i + 1);
        print_product(data+i);
        printf("\n\n");
    }
}


// ����� ��������� ������� � ��������� ���������� (���� ����� ���������� � ����� �������)
void print_products_by_mask(const Product* data, const int size)
{
    printf("��� ������ ��������� �� ��������� ���������� ���������� �����.\n�������� �� ��������� �������:\n");
    
    int property = 0;
    unsigned int mask = 0;
    printf("���� ������� ��������: \n");
    printf("������� ���������? (0 - ���, 1 - ��): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG5 : mask;
    
    printf("������� ����� ������� ������? (0 - ���, 1 - ��): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG4 : mask;
    
    printf("������� ����� ������� ��������? (0 - ���, 1 - ��): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG3 : mask;
    
    printf("�� ������� ��������� ������? (0 - ���, 1 - ��): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG2 : mask;
    
    printf("������� �������� ������� ������? (0 - ���, 1 - ��): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG1 : mask;
    
    int i = 0;
    for (; i < size; i++)
    {
        if ((data[i].flags & mask) == mask)
        {
            printf("������� �����: %d\n", i + 1);
        	print_product(&data[i]);
        	printf("\n\n");
        }
    }
}



int main() {
	system("color F0");  	// ����� ���� �������
	system("chcp 1251");	// ������� �������� �������� �����
	
	// ���������� ����������
    Product* products = NULL;
    int size = 0;
	int command;
	int type;
	int index;

    while (true) // �������� ���� ��������� ��� ����� ������ ������������
    {
        printf("\n\n����:\n");
        printf("1. �������� �������.\n");
        printf("2. ������� �������.\n");
        printf("3. �������� ���������� � ������������ ��������.\n");
        printf("4. ������� �� ����� ���������� ��� ���� ���������.\n");
        printf("5. ������� �� ����� ������ ���������� � ��������� � ���������� ����������.\n");
        printf("6. ����� �� ���������.\n");
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
            printf("����� �� ���������...\n");
            free(products);
            products = NULL;
            return 0;

        default:
            printf("����������� �������!\n");
        }
    }

    return 0;
}
