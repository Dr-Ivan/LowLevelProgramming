#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ProductModule.h"



// создание продукта заданного типа - возвращается указатель
Product* create_product(ProductType type)
{
    Product* product = (Product*) malloc(sizeof(Product));
    if (product == NULL)
    {
        printf("Недостаточно памяти!\n");
        exit(1);
    }

    product->type = type;
    product->flags = 0;
    
    printf("Ввод данных о продукте: \n");
    switch (type)
    {
    case CHRISTMAS_TREE_NUM:
    	do {
	        printf("Высота: ");
	        scanf("%f", &product->params.tree.height);
	        printf("Вес: ");
	        scanf("%f", &product->params.tree.weight);
	    }while (product->params.tree.height <= 0 || product->params.tree.weight <= 0);
        break;

    case CHRISTMAS_TREE_DECORATION_NUM:
    	printf("Цвет (не более 25 букв, без пробелов): ");
	    scanf("%s", &product->params.decoration.color);
    	do {
	        printf("Цена: ");
	        scanf("%f", &product->params.decoration.price);
	    }while (product->params.decoration.price <= 0);
        break;

    case NEW_YEAR_GIFT_NUM:
        printf("Производитель (бренд, не более 50 букв, без пробелов): ");
        scanf("%s", &product->params.gift.brand);
        do{
	        printf("Цена: ");
	        scanf("%f", &product->params.gift.price);
        }while (product->params.gift.price <= 0);
        break;

    default:
        printf("Неизвестный тип продукта. Операция отменена. \n");
        free(product);
        return NULL;
    };
    
    int property = false;
    unsigned int mask = 0;
    printf("Ввод свойств продукта: \n");
    printf("Продукт популярен? (0 - нет, 1 - да): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG5 : mask;
    
    printf("Продукт имеет хорошие отзывы? (0 - нет, 1 - да): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG4 : mask;
    
    printf("Продукт имеет быструю доставку? (0 - нет, 1 - да): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG3 : mask;
    
    printf("На продукт действует скидка? (0 - нет, 1 - да): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG2 : mask;
    
    printf("Продукт является товаром месяца? (0 - нет, 1 - да): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG1 : mask;
    
    product->flags = mask;

    return product;
}


// добавление продукта в масссив
void add_product(Product** data, int* size, Product* product)
{
    *data = (Product*)realloc(*data, (*size + 1) * sizeof(Product));
    if (data == NULL)
    {
        printf("Недостаточно памяти!\n");
        exit(1);
    }

    (*data)[*size] = *product;
    (*size)++;
}


// удаление продукта из масссива
void remove_product(Product** data, int* size, const int index)
{
    if (index < 0 || index >= *size)
    {
        printf("Неверный индекс!\n");
        return;
    }
	int i = index;
    for (; i < *size - 1; i++)
        (*data)[i] = (*data)[i + 1];

    *data = (Product*)realloc(*data, (*size - 1) * sizeof(Product));
    (*size)--;
    printf("Элемент удален из массива. Используйте команду 4 для просмотра.");
}

// обновить данные о продукте в масссиве
void update_product(Product* data, const int size, const int index)
{
     if (index < 0 || index >= size)
    {
        printf("Неверный индекс!\n");
        return;
    }
    
	Product* cur_product_ptr = &data[index];
    printf("Ввод данных о продукте: \n");
    switch (cur_product_ptr->type)
    {
    case CHRISTMAS_TREE_NUM:
    	do{
	        printf("Высота: ");
	        scanf("%f", &cur_product_ptr->params.tree.height);
	        printf("Вес: ");
	        scanf("%f", &cur_product_ptr->params.tree.weight);
	    }while (cur_product_ptr->params.tree.height <= 0 || cur_product_ptr->params.tree.weight <= 0);
        break;

    case CHRISTMAS_TREE_DECORATION_NUM:
    	printf("Цвет (не более 25 букв, без пробелов): ");
        scanf("%s", &cur_product_ptr->params.decoration.color);
	    do{
	        printf("Цена: ");
	        scanf("%f", &cur_product_ptr->params.decoration.price);
	    }while (cur_product_ptr->params.decoration.price <= 0);
        break;

    case NEW_YEAR_GIFT_NUM:
        printf("Производитель (бренд, не более 50 букв, без пробелов): ");
        scanf("%s", &cur_product_ptr->params.gift.brand);
        do{
	        printf("Цена: ");
	        scanf("%f", &cur_product_ptr->params.gift.price);
	    }while (cur_product_ptr->params.gift.price <= 0);
        break;

    default:
        printf("Неизвестный тип продукта. Операция отменена. \n");
        return;
    };
    
    int property = false;
    unsigned int mask = 0;
    printf("Ввод свойств продукта: \n");
    printf("Продукт популярен? (0 - нет, 1 - да): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG5 : mask;
    
    printf("Продукт имеет хорошие отзывы? (0 - нет, 1 - да): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG4 : mask;
    
    printf("Продукт имеет быструю доставку? (0 - нет, 1 - да): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG3 : mask;
    
    printf("На продукт действует скидка? (0 - нет, 1 - да): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG2 : mask;
    
    printf("Продукт является товаром месяца? (0 - нет, 1 - да): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG1 : mask;
    
    cur_product_ptr->flags = mask;

    
}

// вывод одного продукта
void print_product(const Product* product)
{
	ProductType type = product->type;
	char* type_string = NULL;
	switch (type)
    {
    case CHRISTMAS_TREE_NUM:
        type_string = "Это новогодняя елка.";
        break;

    case CHRISTMAS_TREE_DECORATION_NUM:
        type_string = "Это елочная игрушка.";
        break;

    case NEW_YEAR_GIFT_NUM:
        type_string = "Это новогодний подарок.";
        break;

    default:
        type_string = "Это неизвестный тип продукта.";
        return;
    };
		
    printf("Тип продукта: %d. %s\n", type, type_string);

    switch (type)
    {
    case CHRISTMAS_TREE_NUM:
        printf("Высота: %.2f \n", product->params.tree.height);
        printf("Вес: %.2f \n", product->params.tree.weight);
        break;

    case CHRISTMAS_TREE_DECORATION_NUM:
        printf("Цвет: %s \n", product->params.decoration.color);
        printf("Цена: %.2f \n", product->params.decoration.price);
        break;

    case NEW_YEAR_GIFT_NUM:
        printf("Производитель (бренд): %s \n", product->params.gift.brand);
        printf("Цена: %.2f \n", product->params.gift.price);
        break;

    default:
        printf("Неизвестный тип продукта. Операция отменена. \n");
        return;
    };

    printf("Особые свойства продукта. \n");
    if (product->flags & FLAG5)
        printf("\tТовар популярен.\n");
    if (product->flags & FLAG4)
        printf("\tТовар имеет хорошие отзывы.\n");
    if (product->flags & FLAG3)
        printf("\tТовар имеет быструю доставку.\n");
    if (product->flags & FLAG2)
        printf("\tНа товар действует скидка.\n");
    if (product->flags & FLAG1)
        printf("\tЭто товар месяца.\n");
}


// вывод всех элементов массива
void print_all_products(const Product* data, const int size)
{
    printf("Список всех продуктов:\n");
    int i = 0;
    for (; i < size; i++)
    {
        printf("Продукт номер: %d\n", i + 1);
        print_product(data+i);
        printf("\n\n");
    }
}


// вывод элементов массива с заданными свойствами (ввод маски происходит в самой функции)
void print_products_by_mask(const Product* data, const int size)
{
    printf("Для вывода продуктов по свойствам необходимо составтить маску.\nОтветьте на следующие вопросы:\n");
    
    int property = 0;
    unsigned int mask = 0;
    printf("Ввод свойств продукта: \n");
    printf("Продукт популярен? (0 - нет, 1 - да): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG5 : mask;
    
    printf("Продукт имеет хорошие отзывы? (0 - нет, 1 - да): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG4 : mask;
    
    printf("Продукт имеет быструю доставку? (0 - нет, 1 - да): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG3 : mask;
    
    printf("На продукт действует скидка? (0 - нет, 1 - да): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG2 : mask;
    
    printf("Продукт является товаром месяца? (0 - нет, 1 - да): ");
    scanf("%d", &property);
    mask = property ? mask|FLAG1 : mask;
    
    int i = 0;
    for (; i < size; i++)
    {
        if ((data[i].flags & mask) == mask)
        {
            printf("Продукт номер: %d\n", i + 1);
        	print_product(&data[i]);
        	printf("\n\n");
        }
    }
}
