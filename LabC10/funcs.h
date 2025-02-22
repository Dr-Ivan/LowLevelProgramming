#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mem.h>


#define LEN(array) array[0] 
#define ELEM(array, i) array[i+1]
#define ELEM_TYPE int


// ������� ��������� ������,
// ��������� ��������� ��� ���������� ������� �� ��������� ���������
void randomize_arr (ELEM_TYPE* arr, float mn, float mx){
	ELEM_TYPE len = LEN(arr);   											// ����� ��������� �������
	int i;
	for(i = 0; i<len; i++){													// ���� �� ���� ���������
		ELEM(arr, i) = (ELEM_TYPE) ((float)rand() / RAND_MAX * (mx - mn) + mn);	// ��������� ������� � �������� ���������
	};
};

// ������� ��������� ������ � �������� ��� ���,
// ����� �� ������� ������ �� ��������, �������� �� �������� ��� ������ �������� � ����������� �� define-� DELETE_ODD_INDEXES
ELEM_TYPE* delete_indexes(ELEM_TYPE* arr){
	ELEM_TYPE len = LEN(arr); 							// ����� ��������� �������
	int i, j;
	ELEM_TYPE new_size = len;							// �������, �� ������� ������������ ����� ��������������� �������� ��� ������
		
	for (i = len; i >= 1; i--){  						// ���� �� ���� ��������
	#ifdef DELETE_ODD_INDEXES
		if (i % 2 != 0)
		{												// �� ������ �������� �������
			for (j = i; j < new_size; j++){				// �������� ��� �������� �� ���� �����
				ELEM(arr, j-1) = ELEM(arr, j);
			};
			new_size--;									// �� ������������� ����� ������ ��������
			LEN(arr)--;									// ��������� ������� ������, ������� �������� ������ �������
		};	
	#else
		if (i % 2 == 0)
		{												// �� ������ ������ �������
			for (j = i; j < new_size; j++){				// �������� ��� �������� �� ���� �����
				ELEM(arr, j-1) = ELEM(arr, j);
			};
			new_size--;									// �� ������������� ����� ������ ��������
			LEN(arr)--;									// ��������� ������� ������, ������� �������� ������ �������
		};	
	#endif
    }
    arr = (ELEM_TYPE*) realloc(arr, (LEN(arr))*sizeof(ELEM_TYPE));	// ����������� ������� - ���������� ���������� ������
	if (!arr) exit(1);												// �������� �� ��, ��� ������ ���� ��������
	return arr;
};

// ������� ��������� ������, ������� �������� �
// ��������� ������� ����� � ������
ELEM_TYPE* add_zeros(ELEM_TYPE* arr){
	ELEM_TYPE len = LEN(arr), mx = ELEM(arr, 0); 						// ����� ��������� �������
	int i, j = 1;
	for(i = 0; i<len; i++){												// ���� �� ���� ���������
		mx = mx > ELEM(arr, i) ? mx : ELEM(arr, i);						// ����� ���������
	};
	mx = abs(mx); 														// ������ ���������
	arr = (ELEM_TYPE*) realloc(arr, (len+mx)*sizeof(ELEM_TYPE));		// ����������� ������
	if (!arr) exit(1);						    						// �������� �� ��, ��� ������ ���� ��������
	LEN(arr) = len+mx; 			 										// ����� ������ �������
	
	for(i = len-1; i >= 0; i--){										// ����������� ��� �������� �� mx �������� ������
		ELEM(arr, i+mx) = ELEM(arr, i);
	};
	
	memset(arr+1, 0, (size_t)(mx * sizeof(ELEM_TYPE))); 				// �������� ������ mx ���������
	 
	return arr;
};

// ������� ��������� ������, � ������������ ��� ���� � ������ 
ELEM_TYPE* relocate_zeros(ELEM_TYPE* arr){
	ELEM_TYPE len = LEN(arr);  							// ����� ��������� �������
	int zero_count = 0, i = 1;  						// ������� �����
	for(i = 0; i<len; i++){								// ���� �� ���� ���������
		zero_count += ELEM(arr, i) == 0 ? 1 : 0;		// ������� �����
	};
	int j = (int) len-1;	
	for (i = len-1; i >= 0; i--){						// ����������� ��� ��������� �������� � �����
		if (ELEM(arr, i) != 0){
			ELEM(arr, j) = ELEM(arr, i);
			j--;
		}
	}
	memset(arr+1, 0, (size_t)(zero_count * sizeof(ELEM_TYPE))); // �������� ������� ������ ���������, ������� ���� ������� ����� � �������� �������
	return arr;
};

// ������� ��������� ������ � �������� ��� ��������, ������ �, ��
// ��������, ������� ��� ������� �������������� ���� ��������� ������� � ����������� �� define-�� REPLACE_WITH_MAX, REPLACE_WITH_MIN
ELEM_TYPE* replace(ELEM_TYPE* arr, const int x){
	ELEM_TYPE len = LEN(arr);			// ����� ��������� �������
	ELEM_TYPE replacement = ELEM(arr, 0);		// ��������, �� ������� ����� ����� ��������
	int i;
	
	#if REPLACE_WITH_MIN == 1
	for(i = 1; i<len; i++){				// ���� �� ���� ���������
		replacement = ELEM(arr, i) < replacement? ELEM(arr, i) : replacement ;	// ����� ��������
	};
	
	#elif REPLACE_WITH_MAX == 1
	for(i = 1; i<len; i++){				// ���� �� ���� ���������
		replacement = ELEM(arr, i) > replacement? ELEM(arr, i) : replacement ;	// ����� ���������
	};
	
	#else
	for(i = 1; i<len; i++){				// ���� �� ���� ���������
		replacement += ELEM(arr, i);	// ������� �����
	};
	replacement /= len;  				// ������� �������� ���������������
	
	#endif
	
	for(i = 0; i<len; i++){				// ���� �� ���� ���������
		if (ELEM(arr, i) == x)			// ������ ��������� ���������
			ELEM(arr, i) = replacement;			// �� ������� ��������������
	};
	return arr;
};


