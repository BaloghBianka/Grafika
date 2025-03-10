#include "cuboid.h"
#include <stdio.h>

int main()
{
	Cuboid cuboid;
	set_size(&cuboid, 5, 9, 13);

	printf("Cuboid volume: %lf\n", calc_volume(&cuboid));
	printf("Cuboid surface: %lf\n", calc_surface(&cuboid));

	if (has_square_face(&cuboid))
	{
		printf("The cuboid has at least one square face.\n");
	}
	else
	{
		printf("The cuboid has no square faces.\n");
	}

	return 0;
}
