#ifndef LAB12_HEADER
#define LAB12_HEADER

// флаги и их значени¤    	  16 = FLAG5		8 = FLAG4			    	4 = FLAG3				2 = FLAG2			1	= FLAG1	
//							  попул¤рен 	  хорошие отзывы  			 быстра¤ доставка	          скидка			товар мес¤ца
typedef enum {
    FLAG1 = 1,		//0x01 		// 00001
    FLAG2 = 2,		//0x02 		// 00010
    FLAG3 = 4,		//0x04 		// 00100
    FLAG4 = 8,		//0x08 		// 01000
    FLAG5 = 16	    //0x16 		// 10000
} Flags;

// ѕеречисление дл¤ типов продукта
typedef enum {
    CHRISTMAS_TREE_NUM = 1,
    CHRISTMAS_TREE_DECORATION_NUM,
    NEW_YEAR_GIFT_NUM
} ProductType;

// —труктуры дл¤ различных параметров
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

// ќбъединение дл¤ различных параметров в зависимости от типа продукта
union ProductParameters {
    struct CHRISTMAS_TREE tree;
    struct CHRISTMAS_TREE_DECORATION decoration;
    struct NEW_YEAR_GIFT gift;
};

// —труктура Product (основна¤ структура, элементы которой будут в массиве)
typedef struct  {
    ProductType type;         			// “ип продукта
    union ProductParameters params; 	// ѕараметры продукта
    unsigned int flags : 5;           	// 5 флагов в битовом поле
} Product;


// создание продукта заданного типа - возвращаетс¤ указатель
Product* create_product(ProductType type);


// добавление продукта в масссив
void add_product(Product** data, int* size, Product* product);


// удаление продукта из масссива
void remove_product(Product** data, int* size, const int index);


// обновить данные о продукте в масссиве
void update_product(Product* data, const int size, const int index);


// вывод одного продукта
void print_product(const Product* product);


// вывод всех элементов массива
void print_all_products(const Product* data, const int size);



// вывод элементов массива с заданными свойствами (ввод маски происходит в самой функции)
void print_products_by_mask(const Product* data, const int size);

#endif // LAB12_HEADER


