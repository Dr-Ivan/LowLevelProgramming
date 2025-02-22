#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <mem.h>

bool is_number(char* s){
	if (!strlen(s))
		return false;
	int i = 0;
	bool flag = true;
	for (; i < strlen(s); i++){
		if (!isdigit(tolower(s[i]))) // && s[i] != '.' && s[i] != '!' &&s[i] != '?')
			flag = false;
	};
	return flag;	
};

int* all_last_numbers(char* str, int* len){
	int count = 0;
    int i = 1;
    int string_len = strlen(str);
    for (; i <= string_len; i++){
        if ((str[i] == '.' || str[i] == '!' || str[i] == '?' || str[i] == '\0'))
            count++;
    };
    char* temp = malloc(string_len*sizeof(char));
    
    if (temp == NULL) {
		printf("Ошибка! Недостаточно памяти. \n");
		exit(1);
	};
    
    memset(temp, '\0', (string_len)*sizeof(char));
	int* nums = (int*) calloc(count, sizeof(int));
	
	if (nums == NULL) {
		printf("Ошибка! Недостаточно памяти. \n");
		exit(1);
	};
	
	
	int j = 0, n = 0;
	i = 0;
	int res = 0;
	while (j <= string_len){
		char current = str[j++];
		if (isdigit(current))
			temp[i++] = current;	
		else if ( current == ' ' || current == ',' || current == '\0' ) {
			if (is_number(temp)) nums[n] = atoi(temp);
			// printf("%d ", nums[n-1]);
			memset(temp, '\0', (string_len)*sizeof(char));
			i = 0;}
		else if ((current == '.' || current == '!' || current == '?' )&&nums[n]==0) {
			if (is_number(temp)) nums[n] = atoi(temp);
			memset(temp, '\0', (string_len)*sizeof(char));
			i = 0;}
		else if ((current == '.' || current == '!' || current == '?' )&&nums[n]!=0) {
			n++;
			if (is_number(temp)) nums[n++] = atoi(temp);
			memset(temp, '\0', (string_len)*sizeof(char));
			i = 0;
		} else{
			memset(temp, '\0', (string_len)*sizeof(char));
			i = 0;
		};
	};
	if (isdigit(temp[0]))
		nums[n] = atoi(temp);
	res = n+1;
	*len = res;
	free(temp);
	temp = NULL;
	return nums;
};


bool is_word(char* s){
	if (!strlen(s))
		return false;
	int i = 0;
	for (; i < strlen(s); i++){
		if (!isalpha(tolower(s[i])) && s[i] != '.' && s[i] != ',' && s[i] != '!' && s[i] != '?')
			return false;
	};
	return true;	
};

char** short_words(char* str, int k, int* result_len){
	int string_len = strlen(str);
    int count = string_len;
    char** result = (char**) calloc((count + 1), sizeof(char*));
    if (result == NULL) {
    	printf("Ошибка! Недостаточно памяти. \n");
        exit(1);
    };
    int i;
    for (i = 0; i < count; i++){
    	result[i] = (char*) malloc((string_len + 1) * sizeof(char));
    	if (result[i] == NULL) {
			printf("Ошибка! Недостаточно памяти. \n");
			exit(1);
		}
    	memset(result[i], '\0', (string_len + 1)*sizeof(char));
	};

    i = 0;
	int j = 0, current = 0;
    while (j <= string_len){
    	if (str[j] == ' ' || str[j] == '.' || str[j] == ',' || str[j] == '!' || str[j] == '?' || str[j] == '\0'){
    		//puts(result[i]);
    		if ((strlen(result[i]) <= k && is_word(result[i])) || (!is_number(result[i]) && !is_word(result[i])) || is_number(result[i])){
    			// result[i][current++] = str[j];
    			// i++;
    			
    			result[++i][0] = str[j];
    			result[i++][1] = '\0';
    			//  printf("%c ", str[j]);
			}
    		else{
    			memset(result[i], '\0', (string_len + 1)*sizeof(char));
    			result[i][0] = str[j];
    			result[i++][1] = '\0';
			}	
			j++;
			current = 0;
		}else{
			result[i][current++] = str[j++];
		};
		// puts(result[i]);
	};
	*result_len = i+1;
    return result;
};


char** words(char* str, int* result_len){
	int count = 1;
    int i = 0;
    int string_len = strlen(str);
    for (; i < string_len; i++){
        if (str[i] == ' ' || str[i] == '.' || str[i] == ',' || str[i] == '!' || str[i] == '?')
            count++;
    }
    
    char** result = (char**) calloc((count + 1), sizeof(char*));
    if (result == NULL) {
    	printf("Ошибка! Недостаточно памяти. \n");
        exit(1);
    };
    for (i = 0; i < count; i++){
    	result[i] = (char*) malloc((string_len + 1) * sizeof(char));
    	if (result[i] == NULL) {
			printf("Ошибка! Недостаточно памяти. \n");
			exit(1);
		}
    	memset(result[i], '\0', (string_len + 1)*sizeof(char));
	};

    i = 0;
	int j = 0, current = 0;
    while (j <= string_len){
    	if (str[j] == ' ' || str[j] == '.' || str[j] == ',' || str[j] == '!' || str[j] == '?' || str[j] == '\0'){
    		if (is_word(result[i]))
    			i++;
    		else
    			memset(result[i], '\0', (string_len + 1)*sizeof(char));
			j++;
			current = 0;
			*result_len = i+1;
		}else{
			result[i][current++] = str[j++];
		};
	};
	
	if (i == *result_len)
		*result_len++;
	else
		memset(result[i], '\0', (string_len + 1)*sizeof(char));
	
    return result;
};

 
bool equal_letters(char* s1, char* s2){
	if (strlen(s1) != strlen(s2))
		return false;
	int i = 0;
	for (; i < strlen(s2); i++){
		if (tolower(s1[i]) != tolower(s2[i]))
			return false;
	};
	return true;
};

int count_substring(char* str, char* s){
	int size;
	char** w = words(str, &size);
	int result = 0;
	int substr_len = strlen(s);
	char* temp = calloc(substr_len+1, sizeof(char));
	int i = 0;
	for (; i < size; i++){
		// printf(" %s ", w[i]);
		int j = 0;
		for (;j <= size; j++){
			temp = strncpy(temp, w[i]+j, substr_len);
			temp[substr_len] = '\0';		
			if (equal_letters(temp, s))
				result++;
		};
	};
	
	free(temp);
	temp = NULL;
	return result;
};


int main(int argc, char *argv[]) {
	system("color F0");  // белый цвет консоли
	system("chcp 1251"); // кодовая страница русского языка
	
	if ((!strcmp(argv[2], "-delete") && argc <= 3) || (!strcmp(argv[2], "-info") && argc <= 3) || argc <= 2) {
		printf("Ошибка! Введено неверное количество аргументов для данной команды. \n");
		return 1;
	}
	
	if (strlen(argv[1]) >= 1000) {
		printf("Ошибка! Сторка слишком длинная. \n");
		return 1;
	}
	
	char* command = argv[2];
	
	char* str = (char*) calloc(strlen(argv[1])+1, sizeof(char));
	if (str == NULL) {
		printf("Ошибка! Недостаточно памяти. \n");
		return 1;
	}
	
	str = argv[1];
	str[strlen(argv[1])] = '\0';
	printf("\n");
	if(!strcmp(command, "-create")) {
		int count = 0;
		int* arr = all_last_numbers(str, &count);
		printf("Найдено %d чисел, завершающих предолжение. \n", count);
		int i = 0;
		for (;i < count; i++){
			printf("Число номер %d = %d \n", i+1, arr[i]);
		};
		free(arr);
		arr = NULL;
	} else if (!strcmp(command, "-info")) {
		char* s = argv[3];
		int count = count_substring(str, s);
		printf("Заданное слово %s встречается в сторке %d раз. \n", s, count);
	} else if (!strcmp(command, "-delete")) {
		int count;
		int max_len = atoi(argv[3]);
		char** words = short_words(str, max_len, &count);
		int i = 0;
		printf("Все слова длиннее %d букв были удалены. Резульат: \n", max_len);
		for(;i < count; i++){
			printf("%s", words[i]);
			free(words[i]);
		};
		free(words);
  		words = NULL;
	}else{
		printf("Введена несуществующая команда %s. \nДоступные команды: \n\t-info \n\t-create \n\t-delete", command);
	};
	
	free(str);
	str = NULL;
	
	printf("\n\n");
	system("pause");
	return 0;
}
