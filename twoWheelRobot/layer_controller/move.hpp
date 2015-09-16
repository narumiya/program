#ifndef MOVE_HPP
#define MOVE_HPP

#include "layer_driver/circuit/mini_md_1.0/mini_md.hpp"
class Move{
private:
	MiniMD *md[2];
public:
	Move(MiniMD &l,MiniMD &r);
	int setup();
	void cycle();
	void setDuty(float value);
};
#endif
