#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// 縦
#define VIRTICAL 5
// 横
#define HORIZONTAL 5

// 数字の最小値・最大値
#define NUMMIN 1
#define NUMMAX 99

// 人数の最大値
#define PLAYERMAX 4

#define STRSIZE 256
#define INPUTSIZE 16
#define LINELEN 64

#define CARD_DUP -1
#define CARD_OK 0

#define SUCCESS 0
#define ERR_POINTER_NULL -1
#define ERR_INVALID_VALUE -2

#define BINGO 2
#define REACH 1
#define NOBINGO 0
#define ERR -1

#define EXIST 1
#define NOEXIST 0

typedef struct {
	int num[VIRTICAL][HORIZONTAL];
	int status;
} BingoCard;

typedef struct {
	int isExist;
	int v;
	int h;
} Result;

typedef struct {
	int list[NUMMAX - NUMMIN + 1];
} NumList;

int randomList[NUMMAX - NUMMIN + 1];

int initNum(NumList*, int, int, int);
int makeFree(NumList*, int);
int shuffle(NumList*, int, int);
int checkDup(NumList*, int);
int initCard(BingoCard*, int);
int search(BingoCard*, int, int, Result*);
void showCard(BingoCard);
int getNum(int*, char*);
int start(BingoCard*, int);
int isBingo(BingoCard, Result);
void showAll(BingoCard*, int);
void show(BingoCard*, int);
void showLine(void);
void printNum(int, int, int, Result*);
int getRandom(int);
void initRandom(void);
int _shuffle(int*, int);


int main(void) {
	BingoCard card[PLAYERMAX];
	int player, i;
	
	/* 乱数初期化 */
	srand((unsigned int)time(NULL));
	
	/* 人数設定 */
	/* 1〜4の範囲外ならエラー終了 */
	getNum(&player, "player: ");
	if (player < 1 || player > PLAYERMAX) {
		return ERR_INVALID_VALUE;
	}
	
	/* ビンゴカード初期化 */
	initCard(card, player);
	
	/* ビンゴゲーム開始 */
	start(card, player);
	
	return SUCCESS;
}

int getNum(int *num, char *str) {
	char input[INPUTSIZE];

	if (num == NULL) return ERR_POINTER_NULL;

	// 入力を受け付ける前にstrを出力
	if (str == NULL) {
		printf("->");
	} else {
		printf("%s", str);
	}
	
	// 入力を受け取り、整数へ変換、引数numで返す
	fgets(input, INPUTSIZE, stdin);
	*num = strtol(input, NULL, 0);
	printf("\n");
	return SUCCESS;
}

int initNum(NumList *num, int ele, int min, int max) {
	int i;

	if (max < min) return ERR_INVALID_VALUE;
	if (num == NULL) return ERR_POINTER_NULL;

	// minからmaxまでの値が一つづつ入った配列
	// num[ele].list[]を作る
	for (i = 0; i < max - min + 1; i++) {
		num[ele].list[i] = min + i;
	}
	return SUCCESS;
}

int _shuffle(int* num, int size) {
	int i, r, tmp;
	
	if (size < 1) return ERR_INVALID_VALUE;
	if (num == NULL) return ERR_POINTER_NULL;
	
	// 配列num[]をシャッフルする
	// 一番後ろと一番後ろ以外の何かを交換
	// 後ろから2番目と後ろから2番目より前の何かを交換
	// これを繰り返す
	i = size;
	while (i > 1) {
		r = rand() % i;
		i--;
		tmp = num[i];
		num[i] = num[r];
		num[r] = tmp;
	}
	return SUCCESS;
}

int shuffle(NumList *num, int ele, int size) {
	if (size < 1) return ERR_INVALID_VALUE;
	if (num == NULL) return ERR_POINTER_NULL;
	
	return _shuffle(num[ele].list, size);
}

int makeFree(NumList *num, int ele) {
	int pos;
	int v, h;

	if (num == NULL) return ERR_POINTER_NULL;
	
	// 真ん中を0にする
	v = (VIRTICAL + 1) / 2;
	h = (HORIZONTAL + 1) / 2;
	pos = (v - 1) * 5 + (h - 1);
	num[ele].list[pos] = 0;
	return SUCCESS;
}

int checkDup(NumList* buf, int num) {
	int i, j, cnt;
	
	if (num < 0) return ERR_INVALID_VALUE;
	if (buf == NULL) return ERR_POINTER_NULL;
	if (num == 0) return CARD_OK;
	
	// 0番目〜VIRTICAL * HORIZONTAL-1番目までが全く同じになっていないか
	for (j = 0; j < num; j++) {
		cnt = 0;
		for (i = 0; i < VIRTICAL * HORIZONTAL; i++) {
			if (buf[j].list[i] == buf[num].list[i])
				cnt++;
		}
		if (cnt >= VIRTICAL * HORIZONTAL) return CARD_DUP;
	}
	return CARD_OK;
}

int initCard(BingoCard* card, int player) {
	NumList buf[PLAYERMAX];
	int i, j, k;
	
	if (player < 1) return ERR_INVALID_VALUE;
	if (player > PLAYERMAX) return ERR_INVALID_VALUE;
	if (card == NULL) return ERR_POINTER_NULL;
	
	// 人数分のカードを用意する
	for (k = 0; k < player; k++) {
		do {
			// 最小値から最大値まで1つずつ入った配列を用意
			initNum(buf, k, NUMMIN, NUMMAX);
			// 配列をシャッフル
			shuffle(buf, k, NUMMAX - NUMMIN + 1);
			// （VIRTICAL * HORIZONTAL個の要素の）真ん中を0
			makeFree(buf, k);
			// 配列にダブりがないか（=カードの中身が1人1人異なるか）
		} while (checkDup(buf, k) == CARD_DUP);
		
		// 配列の内容を扱いやすい形にする
		for (i = 0; i < VIRTICAL; i++) {
			for (j = 0; j < HORIZONTAL; j++) {
				card[k].num[i][j] = buf[k].list[i * 5 + j];
			}
		}
		
		// ビンゴしていない
		card[k].status = NOBINGO;
	}
	
	return SUCCESS;
}

int search(BingoCard *card, int value, int player, Result* res) {
	int i, j, k;
	
	if (player < 1) return ERR_INVALID_VALUE;
	if (player > PLAYERMAX) return ERR_INVALID_VALUE;
	if (card == NULL) return ERR_POINTER_NULL;
	if (res == NULL) return ERR_POINTER_NULL;
	
	// 人数分のカードを調べ、valueがカードの中にあれば0にする
	// resにはその値があったかどうか（isExist）と、あった位置（v、h）を記録
	for (k = 0; k < player; k++) {
		res[k].isExist = NOEXIST;
		res[k].v = -1;
		res[k].h = -1;
		for (i = 0; i < VIRTICAL; i++) {
			for (j = 0; j < HORIZONTAL; j++) {
				if (card[k].num[i][j] == value) {
					card[k].num[i][j] = 0;
					res[k].isExist = EXIST;
					res[k].v = i;
					res[k].h = j;
				}
			}
		}
	}
	return SUCCESS;
}

int isBingo(BingoCard card, Result res) {
	int i, cnt;
	// card.statusがREACHなら必ずREACH以上
	int ret = card.status;

	// 今回の数字がカードにないのなら、状態が変化していないので調べる必要はない
	if (res.isExist != EXIST) {
		return ret;
	}
	
	// たて、よこが全て0ならBINGO、あと一つならREACH
	// 開けた場所に関わる行、列のみ調べる
	cnt = 0;
	for (i = 0; i < VIRTICAL; i++) {
		if (card.num[i][res.h] == 0) cnt++; 
	}
	if (cnt == VIRTICAL) {
		return BINGO;
	} else if (cnt == VIRTICAL - 1) {
		ret = REACH;
	}
	cnt = 0;
	for (i = 0; i < HORIZONTAL; i++) {
		if (card.num[res.v][i] == 0) cnt++; 
	}
	if (cnt == HORIZONTAL) {
		return BINGO;
	} else if (cnt == HORIZONTAL - 1) {
		ret = REACH;
	}
	
	// 斜めはVIRTICAL == HORIZONTALの時のみ定義
	// 開けた場所に関わるものを調べる
	if (VIRTICAL == HORIZONTAL) {
		// 左上から右下
		if (res.v == res.h) {
			cnt = 0;
			for (i = 0; i < VIRTICAL; i++) {
				if (card.num[i][i] == 0) cnt++;
			}
			if (cnt == VIRTICAL) {
				return BINGO;
			} else if (cnt == VIRTICAL - 1) {
				ret = REACH;
			}
		// 右上から左下
		} else if (res.v == VIRTICAL - res.h - 1) {
			cnt = 0;
			for (i = 0; i < VIRTICAL; i++) {
				if (card.num[i][VIRTICAL - i - 1] == 0) cnt++;
			}
			if (cnt == VIRTICAL) {
				return BINGO;
			} else if (cnt == VIRTICAL - 1) {
				ret = REACH;
			}
		}
	}
	return ret;
}

void showLine(void) {
	char str[LINELEN + 1];
	
	// 線を引く
	memset(str, '-', LINELEN);
	memset(str + LINELEN, '\0', 1);
	printf("%s\n", str);
}

void initRandom(void) {
	int i;
	for (i = 0; i < (NUMMAX - NUMMIN + 1); i++) {
		randomList[i] = i + NUMMIN;
	}
	
	_shuffle(randomList, NUMMAX - NUMMIN + 1);
}

int getRandom(int count) {
	return randomList[count];
}

int start(BingoCard *card, int player) {
	int i, r;
	int status = NOBINGO;
	int count = 0;
	Result res[PLAYERMAX];
	
	if (player < 1) return ERR_INVALID_VALUE;
	if (player > PLAYERMAX) return ERR_INVALID_VALUE;
	if (card == NULL) return ERR_POINTER_NULL;
	
	// 乱数列初期化
	initRandom();
	
	// 全てのカードを表示
	showAll(card, player);
	showLine();
	
	do {
		// ENTER入力待ち
		getchar();

		// 開ける数字を決める
		r = getRandom(count);

		// その数字がカードにあるか
		search(card, r, player, res);
		
		// 番号表示、番号がカードにあるかを表示
		printNum(r, count, player, res);
		for (i = 0; i < player; i++) {
			
			// カードにあったら
			if (res[i].isExist == EXIST) {
				// BINGOか調べる
				card[i].status = isBingo(card[i], res[i]);
				
				if (card[i].status == BINGO) {
					status = BINGO;
				}
				// カードを表示
				show(card, i);
			}
		}
		if (status == NOBINGO) showLine();
		count++;

	// BINGOになったら終了
	} while (status == NOBINGO);
	
	return SUCCESS;
}

char* statusString(int status) {
	char* res;
	switch (status) {
		case BINGO:
			res = "Bingo!";
			break;
		case REACH:
			res = "Reach!";
			break;
		case NOBINGO:
			res = "";
			break;
		default:
			res = "Error";
			break;
	}
	return res;
}

void printNum(int num, int count, int player, Result* res) {
	int i;
	
	printf("Count: %d\n", count);
	printf("Number: %d\n", num);
	
	// 番号がカードにあったら
	for (i = 0; i < player; i++) {
		if (res[i].isExist == EXIST) {
			printf("Exist\n");
			break;
		}
	}
	printf("\n");
}

void showAll(BingoCard* card, int player) {
	int i;
	
	for (i = 0; i < player; i++) {
		show(card, i);
	}
}

void show(BingoCard* card, int player) {
	printf("Player%d\n", (player + 1));
	printf("Status:%s \n", statusString(card[player].status));
	printf("\nCard:\n");
	showCard(card[player]);
	printf("\n\n");
}

void showCard(BingoCard card) {
	int i, j;
	char str[STRSIZE] = "";
	
	for (j = 0; j < HORIZONTAL; j++) {
		snprintf(str, STRSIZE, "%s+----", str);
	}
	printf("%s+\n", str);
	for (i = 0; i < VIRTICAL; i++) {
		memset(str, '\0', STRSIZE);
		for (j = 0; j < HORIZONTAL; j++) {
			snprintf(str, STRSIZE, "%s| %2d ", str, card.num[i][j]);
		}
		printf("%s|\n", str);
		memset(str, '\0', STRSIZE);
		for (j = 0; j < HORIZONTAL; j++) {
			snprintf(str, STRSIZE, "%s+----", str);
		}
		printf("%s+\n", str);
	}
}
