#include "hooke.h"

//Actual data starts at data+1 ------------> data+0 = data size info
void	hooke_reset(t_hooke *h, float k, float m, float t, float x0, float v0)
{
	h->k = k;
	h->m = m;
	h->t = t;
	h->d_t = h->t / (float)h->steps;
	h->x0 = x0;
	h->v0 = v0;

	h->data[1].y = h->x0;
	h->data[1].x = h->d_t * 0;

	h->data[2].y = (h->x0) +
					(h->d_t * h->x0) -
					(1.0f/2.0f * h->k/h->m * h->x0 * (h->d_t*h->d_t));
	h->data[2].x = h->d_t * 1;

	h->x = h->data[1].y;
	for (int i = 3; i < h->steps; i++)
	{
		h->data[i].y = (-h->d_t*h->d_t * h->k * h->data[i-1].y + 2 * h->m * h->data[i-1].y - h->m * h->data[i-2].y)/h->m;
		h->data[i].x = h->d_t * (float)i;
	}
}

void	hooke_vel_data(t_hooke *h)
{
	h->vel_data[1].y = h->v0;
	h->vel_data[1].x = 0;
	for (int i = 2; i < h->steps; i++)
	{
		h->vel_data[i].y = (h->data[i + 1].y - h->data[i - 1].y) / (2 * h->d_t);
		h->vel_data[i].x = h->d_t * (float)i;
	}
}

void	hooke_init(t_hooke *h, int steps)
{
	h->steps = steps;
	h->data = (Vector2 *)malloc(sizeof(Vector2) * (h->steps + 1));
	h->vel_data = (Vector2 *)malloc(sizeof(Vector2) * (h->steps + 1));
}
void	hooke_destroy(t_hooke *h)
{
	free(h->data);
}

void	hooke_set_k(t_hooke *h, float k)
{
	hooke_reset(h, k, h->m, h->t, h->x0, h->v0);
}
void	hooke_set_m(t_hooke *h, float m)
{
	hooke_reset(h, h->k, m, h->t, h->x0, h->v0);
}
void	hooke_set_x0(t_hooke *h, float x0)
{
	hooke_reset(h, h->k, h->m, h->t, x0, h->v0);
}

float	hooke_get_period(t_hooke h)
{
	int	start = 2;
	float	t[2];
	for (int k = 0; k < 2; k++)
		for (int i = start; i < h.steps - 1; i++)
			if (h.data[i - 1].x < h.data[i].x && h.data[i].x > h.data[i + 1].x)
			{
				t[k] = h.data[i].y;
				start = i + 1;
				break;
			}
	return (t[1] - t[0]);
}
