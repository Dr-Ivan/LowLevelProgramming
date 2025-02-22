#ifndef LAB12_HEADER
#define LAB12_HEADER

// ����� � �� ��������    	  16 = FLAG5		8 = FLAG4			    	4 = FLAG3				2 = FLAG2			1	= FLAG1	
//							  ��������� 	  ������� ������  			 ������� ��������	          ������			����� ������
typedef enum {
    FLAG1 = 1,		//0x01 		// 00001
    FLAG2 = 2,		//0x02 		// 00010
    FLAG3 = 4,		//0x04 		// 00100
    FLAG4 = 8,		//0x08 		// 01000
    FLAG5 = 16	    //0x16 		// 10000
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


// �������� �������� ��������� ���� - ������������ ���������
Product* create_product(ProductType type);


// ���������� �������� � �������
void add_product(Product** data, int* size, Product* product);


// �������� �������� �� ��������
void remove_product(Product** data, int* size, const int index);


// �������� ������ � �������� � ��������
void update_product(Product* data, const int size, const int index);


// ����� ������ ��������
void print_product(const Product* product);


// ����� ���� ��������� �������
void print_all_products(const Product* data, const int size);



// ����� ��������� ������� � ��������� ���������� (���� ����� ���������� � ����� �������)
void print_products_by_mask(const Product* data, const int size);

#endif // LAB12_HEADER


