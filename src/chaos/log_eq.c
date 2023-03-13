#include "chaos.h"

/*-------------------------------------------------------*/
/*       Local variables (LOCAL TO THIS MODULE)          */
/*       (module variables ~~> class variables)          */
/*-------------------------------------------------------*/
static t_ds_1D	logEq;

double	log_func(double x)
{
	return (logEq.ctrl_param * x * (1 - x));
}

float	*rec_func(float *x, t_func f, int size)
{
	for (int i = 1; i < size; i++)
		x[i] = f(x[i - 1]);
	return (x);
}

void	InitLogisticEq(void)
{
	logEq.x0 = 0.1f;
	logEq.x_data[0] = logEq.x0;
	logEq.ctrl_param = 2.5f;
	logEq.steps = IT;
	logEq.f = log_func;
}

void	SetLogEq_x0(float x0) {logEq.x0 = x0; }

void	SetLogEq_ctrl_param(float ctrl_param) { logEq.ctrl_param = ctrl_param; }

void	UpdateLogisticEq(void)
{
	rec_func(logEq.x_data, logEq.f, logEq.steps);
}
