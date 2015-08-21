//--------------------------------------------------------------------
//
//	my_standard_io.h
//										ver.2.00
//
//										作成・編集日：2014/11/5
//										作成・編集者：桐生
//--------------------------------------------------------------------

//Warning:
//	このファイルの文字送信関数では一文字送信の関数を中心にして全ての文字送信を行っています。
//	そのため、マイコン、通信形式に合わせた一文字送信を次のような関数にしてください。
//		void 関数名(char 送信する文字)
//	そして、その関数のアドレスを引数として使用してください。
//	マクロで定義しておくとより使いやすくなります。

#ifndef my_standard_io_h
#define my_standard_io_h
#include <math.h>

//----------------------------------------------------------
//別名定義

//recive_order_c等の文字解析および格納データの使用
#define USE_RECEIVE_VALUE

//最大文字数
#define WORD_MAX 128

//通信データの終端文字
#define ORDERS_C_END '#'				//receive_orders_c,receive_order_cの終端文字
#define ORDERS_ST_END '\0'				//receive_orders_stの終端文字

//----------------------------------------------------------
//	typedef

//recrive_orders_c関数のデータ保存用構造体(内部データの変更禁止)
typedef struct{
	char			front_c;				//格納場所
	float			num_data;				//数値データ
	unsigned int	point_ct;				//小数点位置
	unsigned int	f_minus;				//数値データのマイナス判断用フラグ
	unsigned int	f_front_char;			//前回入力データの判断(文字かどうか)
}orders_c_t;

//----------------------------------------------------------
//					画面表示用関数
//------------------------------------------------
// title: 	一文字送信の関数
// return:	なし
// argument:void (*)(char)	1文字送信
//			char			送信データ
// coders:	桐生
void put_c(void (*put_char)(char c),char data);
//------------------------------------------------
// title: 	自然数の文字列送信
// return:	なし
// argument:void (*)(char)	1文字送信
//			unsigned long	送信用整数データ
// coders:	桐生
void put_i(void (*put_char)(char c),unsigned long data);
//------------------------------------------------
// title:	整数の文字列送信
// return:	なし
// argument:void (*)(char)	1文字送信
//			signed long		送信データ
// coders:	桐生
void put_si(void (*put_char)(char c),signed long data);
//------------------------------------------------
// title:	実数の文字列送信(小数点以下3桁)
// return:	なし
// argument:void (*)(char)	1文字送信
//			float			送信データ
// coders:	桐生
void put_f(void (*put_char)(char c),float data);
//------------------------------------------------
// title:	文字列送信
// return:	なし
// argument:void (*)(char)	1文字送信
//			char*			送信データ
// coders:	桐生
void put_st(void (*put_char)(char c),char *st);
//------------------------------------------------
// title:	改行の送信
// return:	なし
// argument:void (*)(char)	1文字送信
// coders:	桐生
void put_enter(void (*put_char)(char c));
//------------------------------------------------
// title:	文字列と数字(int)の送信
// return:	なし
// argument:void (*)(char)	1文字送信
//			char*			送信データ
//			int				送信データ
// coders:	桐生
void i_print(void (*put_char)(char c),char *st,int num);
//------------------------------------------------
// title:	文字列と数字(float)の送信
// return:	なし
// argument:void (*)(char)	1文字送信
//			char*			送信データ
//			float			送信データ
// coders:	桐生
void f_print(void (*put_char)(char c),char *st,float num);
//------------------------------------------------
// title:	文字列と数字(float)x2の送信
// return:	なし
// argument:void (*)(char)	1文字送信
//			char*			送信データ(文字)
//			float			送信データ(数字1)
//			float			送信データ(数字2)
// coders:	桐生
void f2_print(void (*put_char)(char c),char *st,float num1,float num2);

//------------------------------------------------
// title:	数字(unsigned int,0b)の送信
// return:	なし
// argument:void (*)(char)	1文字送信
//			char*			送信データ(文字)
//			unsigned int	送信データ(数字)
// coders:	桐生
void put_ib(void (*put_char)(char c),unsigned int data);
//------------------------------------------------
// title:	数字(unsigned int,0x)の送信
// return:	なし
// argument:void (*)(char)	1文字送信
//			char*			送信データ(文字)
//			unsigned int	送信データ(数字)
// coders:	桐生
void put_ix(void (*put_char)(char c),unsigned int data);

//--------------------------------------------------------------------
// 格納データの保存
#ifdef USE_RECEIVE_VALUE
//------------------------------------------------
// title:	格納データを変更する関数
// return:	なし
// argument:char 	データ格納場選択
//			float	格納用データ
// coders:	桐生
void write_value(char c,float num);

//------------------------------------------------
// title:	格納データを読み取る関数
// return:	なし
// argument:char 	データ格納場選択
//			float	格納用データ
// coders:	桐生
float read_value(char c);

//------------------------------------------------
// title:	受信データを保存する関数
// return:	unsigned int	設定されてない文字の検出
// argument:char			受信データ
// coders:	桐生
unsigned int receive_orders_c(orders_c_t *data,char c);
//受信データ方式
//	1.文字(a-z,A-Z)
//	2.データ(float型)
//	3.ORDERS_C_END(ヘッダーファイルで定義)
//	この順のデータをこの関数では処理します。

//------------------------------------------------
// title:	受信データを保存する関数
// return:	unsigned int	設定されてない文字の検出
// argument:char 	受信データ
// coders:	桐生
unsigned int receive_order_c(char c);
//受信データ方式
//	1.文字(a-z,A-Z)
//	2.データ(float型)
//	3.ORDERS_C_END(ヘッダーファイルで定義)
//	この順のデータをこの関数では処理します。

//------------------------------------------------
// title:	受信データを保存する関数
// return:	unsigned int	設定されてない文字の検出
// argument:char*			受信データ
// coders:	桐生
unsigned int recive_order_st(char *st);
//受信データ方式
//	1.文字(a-z,A-Z)
//	2.データ(float型)
//	3.ORDERS_C_END(ヘッダーファイルで定義)
//	この順のデータをこの関数では処理します。
//	データが一部のみの時、そのデータは破棄されます。
#endif

#endif
