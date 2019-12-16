#pragma  once

#define MY_CVECTOR

#include <stdlib.h>
#include <stdio.h>

// C言語による簡易vectorもどき
typedef struct cvector_t {
	void* value_;	// 要素の格納領域
	int capacity_;	// 格納可能な最大要素数
	int size_;		// 格納されている要素数
} cvector;

// 初期化
#define INIT(CVECTOR) CVECTOR.value_ = 0; CVECTOR.capacity_ = 0; CVECTOR.size_ = 0;

// 配列への参照(汎用)
#define ARRAY_AT(T, V, N) (((T*)V)[N])

// 要素への参照(cvector)
#define AT(T, CVECTOR, N) ARRAY_AT(T, CVECTOR.value_, N)

// 要素数を追加する(private)
#define SECURE_ADD(T, CVECTOR) {\
	CVECTOR.capacity_ += 10;\
	void* tmp;\
	tmp = (T*)malloc(sizeof(T) * CVECTOR.capacity_);\
	if (tmp == NULL) { printf("memory secure error\n"); exit(1); }\
	for (int i = 0; i < CVECTOR.size_; ++i)\
		ARRAY_AT(T, tmp, i) = AT(T, CVECTOR, i);\
	FREE(CVECTOR);\
	CVECTOR.value_ = tmp;\
}

// 要素の任意の位置にデータを追加
#define INSERT(T, CVECTOR, POS, ITEM)\
{\
	if (CVECTOR.size_ == CVECTOR.capacity_) {\
		SECURE_ADD(T, CVECTOR)\
	}\
	for (int i = CVECTOR.size_; i > POS; i--) {\
		AT(T, CVECTOR, i) = AT(T, CVECTOR, i - 1);\
	}\
	AT(T, CVECTOR, POS) = ITEM;\
	CVECTOR.size_++;\
}

// 要素の末尾にデータを追加
#define PUSH_BACK(T, CVECTOR, ITEM)\
{\
	if (CVECTOR.size_ == CVECTOR.capacity_) {\
		SECURE_ADD(T, CVECTOR)\
	}\
	AT(T, CVECTOR, CVECTOR.size_) = ITEM;\
	CVECTOR.size_++;\
}

// 要素の末尾のデータを消去
#define POP_BACK(T, CVECTOR)\
{\
	if (!EMPTY(CVECTOR)) {\
		CVECTOR.size_--;\
		void* tmp;\
		tmp = (T*)malloc(sizeof(T) * CVECTOR.size_);\
		if (tmp == NULL) { printf("memory secure error\n"); exit(1); }\
		for (int i = 0; i < CVECTOR.size_; ++i)\
			ARRAY_AT(T, tmp, i) = AT(T, CVECTOR, i);\
		FREE(CVECTOR);\
		CVECTOR.value_ = tmp;\
	}\
}

// 指定した要素を消去する
#define ERASE(T, CVECTOR, POS) {\
	if (POS < 0 || POS >= CVECTOR.size_) {\
		AT(T, CVECTOR, CVECTOR.size_ - 1);\
	}\
	else {\
		for (int i = POS; i < CVECTOR.size_ - 1; i++)\
			AT(T, CVECTOR, i) = AT(T, CVECTOR, i + 1);\
		CVECTOR.size_--;\
	}\
}

// 格納されている要素数
#define SIZE(CVECTOR) CVECTOR.size_

// 要素数変更
#define RESIZE(T, CVECTOR, SIZE)\
{\
	int min_size = SIZE < CVECTOR.size_ ? SIZE : CVECTOR.size_;\
	CVECTOR.capacity_ = SIZE;\
	CVECTOR.size_ = SIZE;\
	void* tmp;\
	tmp = (T*)malloc(sizeof(T) * SIZE);\
	if (tmp == NULL) { printf("memory secure error\n"); exit(1); }\
		for (int i = 0; i < min_size; ++i)\
			ARRAY_AT(T, tmp, i) = AT(T, CVECTOR, i);\
	FREE(CVECTOR);\
	CVECTOR.value_ = tmp;\
}

// 空かどうか
#define EMPTY(CVECTOR) (!CVECTOR.value_ ? 1 : 0)

// value_のみを消去する
#define FREE(CVECTOR) free(CVECTOR.value_); CVECTOR.value_ = 0;

// 全ての要素を消去する
#define CLEAR(CVECTOR) FREE(CVECTOR) CVECTOR.capacity_ = 0; CVECTOR.size_ = 0;