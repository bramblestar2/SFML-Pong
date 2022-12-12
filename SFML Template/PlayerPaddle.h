#pragma once
#include "Paddle.h"

class PlayerPaddle : public Paddle
{
public:
	PlayerPaddle();
	~PlayerPaddle();

	void update(const double _DT) override;
private:
};

