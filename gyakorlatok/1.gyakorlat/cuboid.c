#include "cuboid.h"

void set_size(Cuboid* cuboid, double length, double width, double height)
{
	if (length > 0 && width > 0 && height > 0) {
		cuboid->length = length; //-> struktúra mezői
		cuboid->width = width;
		cuboid->height = height;
	} else {
		cuboid->length = cuboid->width = cuboid->height = -1; 
	}
}

double calc_volume(const Cuboid* cuboid)
{
	return cuboid->length * cuboid->width * cuboid->height;
}

double calc_surface(const Cuboid* cuboid)
{
	return 2 * (cuboid->length * cuboid->width + cuboid->width * cuboid->height + cuboid->height * cuboid->length);
}

int has_square_face(const Cuboid* cuboid)
{
	return (cuboid->length == cuboid->width || cuboid->width == cuboid->height || cuboid->height == cuboid->length);
}
