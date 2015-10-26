#ifndef BUTTON_INFO_HPP
#define BUTTON_INFO_HPP

#include "digital.hpp"

class ButtonInfo{
private:
	Digital *pin;
	int raw;			//チャタリングありのデータ
	int info;			//チャタリングなしのデータ
	int count;			//押した回数
	int upEdge;	//アップエッジフラグ
	int downEdge;	//ダウンエッジフラグ
	int state;			//一時的に保存しておくボタンデータ
	int timer;				//チャタリング回避カウント
	int old;				//一つ前のボタン情報
	int chatTime;
	unsigned int cycleTime;
	bool normalyClose;
public:
	ButtonInfo();
	ButtonInfo(Digital &digitalPin);
	int setup(bool normaly,int time);
	void cycle();
	int readValue(){return info;};
	int readDownEdge(){return downEdge;};
	int readUpEdge(){return upEdge;};
	int readCount(){return count;};
};

#endif
