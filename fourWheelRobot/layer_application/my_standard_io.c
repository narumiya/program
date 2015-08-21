//--------------------------------------------------------------------
//
//	my_standard_io.c
//										ver.2.02
//
//										作成・編集日：2014/11/5
//										作成・編集者：桐生
//--------------------------------------------------------------------

//Warning:
//	このファイルの文字送信関数では一文字送信の関数を中心にして全ての文字送信を行っています。
//	そのため、マイコン、通信形式に合わせた一文字送信を次のような関数にしてください。
//		void 関数名(char 送信する文字)
//	そして、その関数のアドレスを引数として使用してください。

#include "my_standard_io.h"
#include <math.h>

#define READ_MODE	0
#define WRITE_MODE	1
#define USE_RECEIVE_VALUE

//----------------------------------------------------------
//					画面表示用関数
//------------------------------------------------
// title: 	一文字送信の関数
// return:	なし
// argument:void (*)(char)	1文字送信
//			char			送信データ
// coders:	桐生
void put_c(void (*put_char)(char c),char data){
	put_char(data);
}

//------------------------------------------------
// title: 	自然数の文字列送信
// return:	なし
// argument:void (*)(char)	1文字送信
//			unsigned long	送信用整数データ
// coders:	桐生
void put_i(void (*put_char)(char c),unsigned long data){
	short i=0;
	char out[WORD_MAX] = {0};

	if(data == 0){
		put_char('0');
	}else{
		for(i=0;(data>0)&(i<WORD_MAX);i++){
			out[i] = data%10;
			data *= 0.1;
		}
		for(i=i-1;i>=0;i--){
			put_char(out[i] + '0');
		}
	}
}

//------------------------------------------------
// title:	整数の文字列送信
// return:	なし
// argument:void (*)(char)	1文字送信
//			signed long		送信データ
// coders:	桐生
void put_si(void (*put_char)(char c),signed long data){
	if(data < 0){
		put_char('-');
		put_i(put_char,(-1)*data);
	}else{
		put_char(' ');
		put_i(put_char,data);
	}
}

//------------------------------------------------
// title:	実数の文字列送信(小数点以下3桁)
// return:	なし
// argument:void (*)(char)	1文字送信
//			float			送信データ
// coders:	桐生
void put_f(void put_char(char),float data){
	const short few_below = 3;		//最大10桁
	int
		i=0,
		i_data = 0;
	float
		i_part = 0,
		f_part = 0;

	data += (data >= 0)? 0.5*powf(0.1,few_below):(-1)*0.5*powf(0.1,few_below);
	f_part = modff(data,&i_part);
	put_si(put_char,(int)i_part);
	put_char('.');
	i_data = (int)(fabsf(f_part)*powf(10,few_below));
	for(i=1;pow(10,few_below-i)>i_data && i<few_below;i++){
		put_char('0');
	}
	put_i(put_char,(int)(i_data));
}

//------------------------------------------------
// title:	文字列送信
// return:	なし
// argument:void (*)(char)	1文字送信
//			char*			送信データ
// coders:	桐生
void put_st(void (*put_char)(char c),char *st){
	short n=0;

	for(n=0;(((*(st+n))!='\0') && (n<WORD_MAX));n++){
		put_char(*(st+n));
	}
}

//------------------------------------------------
// title:	改行の送信
// return:	なし
// argument:void (*)(char)	1文字送信
// coders:	桐生
void put_enter(void (*put_char)(char c)){
	put_char(0x0d);
	put_char(0x0a);
}

//------------------------------------------------
// title:	文字列と数字(int)の送信
// return:	なし
// argument:void (*)(char)	1文字送信
//			char*			送信データ
//			int				送信データ
// coders:	桐生
void i_print(void (*put_char)(char c),char *st,int num){
	put_st(put_char,st);
	put_char(',');

	put_si(put_char,num);
	put_char(',');
}

//------------------------------------------------
// title:	文字列と数字(float)の送信
// return:	なし
// argument:void (*)(char)	1文字送信
//			char*			送信データ
//			float			送信データ
// coders:	桐生
void f_print(void (*put_char)(char c),char *st,float num){
	put_st(put_char,st);
	put_char(',');

	put_f(put_char,num);
	put_char(',');
}
//------------------------------------------------
// title:	文字列と数字(float)x2の送信
// return:	なし
// argument:void (*)(char)	1文字送信
//			char*			送信データ(文字)
//			float			送信データ(数字1)
//			float			送信データ(数字2)
// coders:	桐生
void f2_print(void (*put_char)(char c),char *st,float num1,float num2){
	f_print(put_char,st,num1);
	put_f(put_char,num2);
	put_char(',');
}
//------------------------------------------------
// title:	数字(unsigned int,0b)の送信
// return:	なし
// argument:void (*)(char)	1文字送信
//			char*			送信データ(文字)
//			unsigned int	送信データ(数字)
// coders:	桐生
void put_ib(void (*put_char)(char c),unsigned int data){
	unsigned long b=0;
	unsigned short ct=0;

	do{
		ct++;
		b = b << 1;
		b |= data & 0x1;
		data = data >> 1;
	}while(data != 0 && ct <= 16);
	put_char('0');
	put_char('b');
	for(;ct != 0;ct--){
		put_i(put_char,b&1);
		b = b >> 1;
	}
}

//------------------------------------------------
// title:	数字(unsigned int,0x)の送信
// return:	なし
// argument:void (*)(char)	1文字送信
//			char*			送信データ(文字)
//			unsigned int	送信データ(数字)
// coders:	桐生
void put_ix(void (*put_char)(char c),unsigned int data){
	unsigned long x=0;
	unsigned short ct=0;

	do{
		ct++;
		x = x << 4;
		x |= data & 0xf;
		data = data >> 4;
	}while(data != 0 && ct <= 8);
	put_char('0');
	put_char('x');
	for(;ct != 0;ct--){
		if((x & 0xf) <= 9)	put_i(put_char,(x&0xf));
		else				put_char('A' + (x&0xf)-10);
		x = x >> 4;
	}
}

#ifdef USE_RECEIVE_VALUE
//--------------------------------------------------------------------
// 格納データの保存
//------------------------------------------------
// title:	格納データ関数
// return:	読み込みデータ
// argument:char 	データ格納場選択
//			float	書き込み時のデータ
//			int		読み書きのモード選択
// coders:	桐生
static float value_data(char c,float num,int mode){
	float ans=0;
	static float atoz_value[26] = {0};
	static float AtoZ_value[26] = {0};

	if( (c >= 'a') && (c <= 'z') ){
		if(mode == WRITE_MODE)		{atoz_value[(int)(c - 'a')] = num;}
		else if(mode == READ_MODE)	{ans = atoz_value[(int)(c - 'a')];}
	}else if( (c >= 'A') && (c <= 'Z') ){
		if(mode == WRITE_MODE)		{AtoZ_value[(int)(c - 'A')] = num;}
		else if(mode == READ_MODE)	{ans = AtoZ_value[(int)(c - 'A')];}
    }

	return ans;
}
//------------------------------------------------
// title:	格納データを変更する関数
// return:	なし
// argument:char 	データ格納場選択
//			float	格納用データ
// coders:	桐生
void write_value(char c,float num){
	value_data(c,num,WRITE_MODE);
}

//------------------------------------------------
// title:	格納データを読み取る関数
// return:	なし
// argument:char 	データ格納場選択
//			float	格納用データ
// coders:	桐生
float read_value(char c){
	return (value_data(c,0,READ_MODE));
}
//------------------------------------------------
// title:	受信データを保存する関数
// return:	unsigned int	設定されてない文字の検出
// argument:char			受信データ
// coders:	桐生
unsigned int receive_orders_c(orders_c_t *data,char c){
//受信データ方式
//	1.文字(a-z,A-Z)
//	2.データ(float型)
//	3.ORDERS_C_END(ヘッダーファイルで定義)
//	この順のデータをこの関数では処理します。
	short f_reset = 0,									//処理のリセットフラグ
		  f = 0;										//設定されてない文字の検出

	if(c == ORDERS_C_END){
		if(data->f_minus == 1)	data->num_data = data->num_data * (-1);
		write_value(data->front_c,data->num_data);
		f_reset = 1;
		data->front_c=0;
	}else{
		if((c >= '0') && (c <= '9')){
			data->f_front_char = 0;
			if(data->point_ct == 0)	data->num_data = data->num_data*10 + (c-'0');
			else{
				data->num_data = data->num_data + (c-'0')*pow(0.1,data->point_ct);
				data->point_ct = data->point_ct + 1;
			}
		}else if(((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'))){
			f_reset = 1;
			data->front_c = c;
			data->f_front_char = 1;
		}else if(c == '-' && data->f_front_char == 1){
			data->f_minus = data->f_minus ^ 1;
		}else if(c == '.'){
			data->f_front_char = 0;
			data->point_ct = 1;
		}
		else{
			f = 1;
		}
    }

	if(f_reset == 1){
		data->num_data = 0;
		data->point_ct = 0;
		data->f_minus = 0;
	}
	return (f);
}


//------------------------------------------------
// title:	受信データを保存する関数
// return:	unsigned int	設定されてない文字の検出
// argument:char 	受信データ
// coders:	桐生
unsigned int receive_order_c(char c){
//受信データ方式
//	1.文字(a-z,A-Z)
//	2.データ(float型)
//	3.ORDERS_C_END(ヘッダーファイルで定義)
//	この順のデータをこの関数では処理します。
	static orders_c_t data = {0};
	return(receive_orders_c(&data,c));
}
//------------------------------------------------
// title:	受信データを保存する関数
// return:	unsigned int	設定されてない文字の検出
// argument:char*			受信データ
// coders:	桐生
unsigned int recive_order_st(char *st){
//受信データ方式
//	1.文字(a-z,A-Z)
//	2.データ(float型)
//	3.ORDERS_C_END(ヘッダーファイルで定義)
//	この順のデータをこの関数では処理します。
//	データが一部のみの時、そのデータは破棄されます。
	orders_c_t data = {0};
	short f=0,i=0;
	const short max_word = 20;

	for(i=0;max_word <= max_word;i++){
		if(st[i] == ORDERS_ST_END){
			st[i] = ORDERS_C_END;
			for(i=0;st[i] != ORDERS_C_END;i++)	f |= receive_orders_c(&data,st[i]);
			return f;
		}
	}
	return 1;
}
#endif
