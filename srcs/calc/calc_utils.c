#include "calc.h"

static double convert_radian(double angle)
{
	return ((angle * M_PI) / 180);
}

double cos_wrap(double angle)
{
	return (cos(convert_radian(angle)));
}

//0から180はプラス、181から359はマイナス
double sin_wrap(double angle)
{
	return (sin(convert_radian(angle)));
}

//91から179 & 271から359 はマイナス
double tan_wrap(double angle)
{
	return (tan(convert_radian(angle)));
}

//91から179 & 271から359 はマイナス
double cot_wrap(double angle)
{
	return (1.0 / tan_wrap(angle));
}
