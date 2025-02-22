#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mem.h>


#define LEN(array) array[0] 
#define ELEM(array, i) array[i+1]
#define ELEM_TYPE int


// ôóíęöč˙ ďđčíčěŕĺň ěŕńńčâ,
// ďîçâîë˙ĺň çŕďîëíčňü ĺăî ńëó÷ŕéíűěč ÷čńëŕěč čç çŕäŕííîăî äčŕďŕçîíŕ
void randomize_arr (ELEM_TYPE* arr, float mn, float mx){
	ELEM_TYPE len = LEN(arr);   											// äëčíŕ ďîäŕííîăî ěŕńńčâŕ
	int i;
	for(i = 0; i<len; i++){													// öčęë ďî âńĺě ýëĺěĺíňŕě
		ELEM(arr, i) = (ELEM_TYPE) ((float)rand() / RAND_MAX * (mx - mn) + mn);	// ńëó÷ŕéíűé ýëĺěĺíň â çŕäŕííîě äčŕďŕçîíĺ
	};
};

// ôóíęöč˙ ďđčíčěŕĺň ěŕńńčâ č čçěĺí˙ĺň ĺăî ňŕę,
// ÷ňîáű îí ńîńňî˙ë ňîëüęî čç ýëĺěĺňîâ, ńňî˙âřčő íŕ íĺ÷ĺňíűő čëč ÷ĺňíűő číäĺęńŕő â çŕâčńčěîńňč îň define-ŕ DELETE_ODD_INDEXES
ELEM_TYPE* delete_indexes(ELEM_TYPE* arr){
	ELEM_TYPE len = LEN(arr); 							// äëčíŕ ďîäŕííîăî ěŕńńčâŕ
	int i, j;
	ELEM_TYPE new_size = len;							// ăđŕíčöŕ, äî ęîňîđîé âęëţ÷čňĺëüíî áóäóň đŕńńěŕňđčâŕňüń˙ ýëĺěĺíňű ďđč ńäâčăĺ
		
	for (i = len; i >= 1; i--){  						// öčęë ďî âńĺě číäĺęńŕě
	#ifdef DELETE_ODD_INDEXES
		if (i % 2 != 0)
		{												// íŕ ęŕćäîě íĺ÷ĺňíîě číäĺęńĺ
			for (j = i; j < new_size; j++){				// ńäâčíóňü âńĺ ýëĺěĺíňű íŕ îäčí âëĺâî
				ELEM(arr, j-1) = ELEM(arr, j);
			};
			new_size--;									// íĺ đŕńńěŕňđčâŕňü äŕëĺĺ ëčříčĺ ýëĺěĺíňű
			LEN(arr)--;									// óěĺíüřčňü íóëĺâîé číäĺęń, ęîňîđűé îçíŕ÷ŕĺň đŕçěĺđ ěŕńńčâŕ
		};	
	#else
		if (i % 2 == 0)
		{												// íŕ ęŕćäîě ÷ĺňíîě číäĺęńĺ
			for (j = i; j < new_size; j++){				// ńäâčíóňü âńĺ ýëĺěĺíňű íŕ îäčí âëĺâî
				ELEM(arr, j-1) = ELEM(arr, j);
			};
			new_size--;									// íĺ đŕńńěŕňđčâŕňü äŕëĺĺ ëčříčĺ ýëĺěĺíňű
			LEN(arr)--;									// óěĺíüřčňü íóëĺâîé číäĺęń, ęîňîđűé îçíŕ÷ŕĺň đŕçěĺđ ěŕńńčâŕ
		};	
	#endif
    }
    arr = (ELEM_TYPE*) realloc(arr, (LEN(arr))*sizeof(ELEM_TYPE));	// đĺŕëëîęŕöč˙ ěŕńńčâŕ - óěĺíüřĺíčĺ çŕíčěŕĺěîé ďŕě˙ňč
	if (!arr) exit(1);												// ďđîâĺđęŕ íŕ ňî, ÷ňî ďŕě˙ňü áűëŕ âűäĺëĺíŕ
	return arr;
};

// ôóíęöč˙ ďđčíčěŕĺň ěŕńńčâ, íŕőîäčň ěŕęńčěóě č
// äîáŕâë˙ĺň ńňîëüęî íóëĺé â íŕ÷ŕëî
ELEM_TYPE* add_zeros(ELEM_TYPE* arr){
	ELEM_TYPE len = LEN(arr), mx = ELEM(arr, 0); 						// äëčíŕ ďîäŕííîăî ěŕńńčâŕ
	int i, j = 1;
	for(i = 0; i<len; i++){												// öčęë ďî âńĺě ýëĺěĺíňŕě
		mx = mx > ELEM(arr, i) ? mx : ELEM(arr, i);						// ďîčńę ěŕęńčěóěŕ
	};
	mx = abs(mx); 														// ěîäóëü ěŕęńčěóěŕ
	arr = (ELEM_TYPE*) realloc(arr, (len+mx)*sizeof(ELEM_TYPE));		// đĺŕëëîęŕöč˙ ďŕě˙ňč
	if (!arr) exit(1);						    						// ďđîâĺđęŕ íŕ ňî, ÷ňî ďŕě˙ňü áűëŕ âűäĺëĺíŕ
	LEN(arr) = len+mx; 			 										// äëčíŕ íîâîăî ěŕńńčâŕ
	
	for(i = len-1; i >= 0; i--){										// ďĺđĺäâčíóňü âńĺ ýëĺěĺíňű íŕ mx číäĺęńîâ âďđŕâî
		ELEM(arr, i+mx) = ELEM(arr, i);
	};
	
	memset(arr+1, 0, (size_t)(mx * sizeof(ELEM_TYPE))); 				// çŕíóëčňü ďĺđâűĺ mx ýëĺěĺíňîâ
	 
	return arr;
};

// ôóíęöč˙ ďđčíčěŕĺň ěŕńńčâ, č ďĺđĺńňŕâë˙ĺň âńĺ íóëč â íŕ÷ŕëî 
ELEM_TYPE* relocate_zeros(ELEM_TYPE* arr){
	ELEM_TYPE len = LEN(arr);  							// äëčíŕ ďîäŕííîăî ěŕńńčâŕ
	int zero_count = 0, i = 1;  						// ń÷ĺň÷čę íóëĺé
	for(i = 0; i<len; i++){								// öčęë ďî âńĺě ýëĺěĺíňŕě
		zero_count += ELEM(arr, i) == 0 ? 1 : 0;		// ďîäń÷ĺň íóëĺé
	};
	int j = (int) len-1;	
	for (i = len-1; i >= 0; i--){						// ďĺđĺäâčíóňü âńĺ íĺíóëĺâűĺ ýëĺěĺíňű â ęîíĺö
		if (ELEM(arr, i) != 0){
			ELEM(arr, j) = ELEM(arr, i);
			j--;
		}
	}
	memset(arr+1, 0, (size_t)(zero_count * sizeof(ELEM_TYPE))); // çŕíóëčňü ńňîëüęî ďĺđâűő ýëĺěĺíňîâ, ńęîëüęî áűëî íŕéäĺíî íóëĺé â čńőîäíîě ěŕńńčâĺ
	return arr;
};

// ôóíęöč˙ ďđčíčěŕĺň ěŕńńčâ č çŕěĺí˙ĺň âńĺ ýëĺěĺíňű, đŕâíűĺ Ő, íŕ
// ěŕęńčěóě, ěčíčěóě čëč ńđĺäíĺĺ ŕđčôěĺňč÷ĺńęîĺ âńĺő ýëĺěĺíňîâ ěŕńńčâŕ â çŕâčńčěîńňč îň define-îâ REPLACE_WITH_MAX, REPLACE_WITH_MIN
ELEM_TYPE* replace(ELEM_TYPE* arr, const int x){
	ELEM_TYPE len = LEN(arr);			// äëčíŕ ďîäŕííîăî ěŕńńčâŕ
	ELEM_TYPE replacement = ELEM(arr, 0);		// çíŕ÷ĺíčĺ, íŕ ęîňîđîĺ íóćíî áóäĺň çŕěĺíčňü
	int i;
	
	#if REPLACE_WITH_MIN == 1
	for(i = 1; i<len; i++){				// öčęë ďî âńĺě ýëĺěĺíňŕě
		replacement = ELEM(arr, i) < replacement? ELEM(arr, i) : replacement ;	// ďîčńę ěčíčěóěŕ
	};
	
	#elif REPLACE_WITH_MAX == 1
	for(i = 1; i<len; i++){				// öčęë ďî âńĺě ýëĺěĺíňŕě
		replacement = ELEM(arr, i) > replacement? ELEM(arr, i) : replacement ;	// ďîčńę ěŕęńčěóěŕ
	};
	
	#else
	for(i = 1; i<len; i++){				// öčęë ďî âńĺě ýëĺěĺíňŕě
		replacement += ELEM(arr, i);	// ďîäń÷ĺň ńóěěű
	};
	replacement /= len;  				// ďîäń÷ĺň ńđĺäíĺăî ŕđčôěĺňč÷ĺńęîăî
	
	#endif
	
	for(i = 0; i<len; i++){				// öčęë ďî âńĺě ýëĺěĺíňŕě
		if (ELEM(arr, i) == x)			// çŕěĺíŕ ňđĺáóĺěűő ýëĺěĺíňîâ
			ELEM(arr, i) = replacement;			// íŕ ńđĺäíĺĺ ŕđčôěĺňč÷ĺńęîĺ
	};
	return arr;
};


