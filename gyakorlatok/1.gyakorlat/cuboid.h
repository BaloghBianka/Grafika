#ifndef CUBOID_H
#define CUBOID_H

typedef struct Cuboid
{
	double length;
	double width;
	double height;
} Cuboid;

//Definiáljunk egy függvényt, amellyel ellenőrzött módon be lehet állítani egyszerre a 3 él hosszát (például set_size néven)!
void set_size(Cuboid* cuboid, double length, double width, double height);


//Definiáljunk egy függvényt, amelyik kiszámítja a téglatest térfogatát (például calc_volume), és egy másikat amelyik a felszínét (például calc_surface)!
double calc_volume(const Cuboid* cuboid);

double calc_surface(const Cuboid* cuboid);

//Definiáljunk egy függvényt, amelyik a téglalapot megvizsgálja, hogy van-e négyzet alakú lapja!
int has_square_face(const Cuboid* cuboid);

#endif 
