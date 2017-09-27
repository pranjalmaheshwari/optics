#include "optics.hpp"

int main(int argc, char const *argv[])
{
	unsigned int minPts = atoi(argv[3]);
	double eps = atof(argv[4]);
	optics a(argv[1], minPts, eps);
	a.run();
	a.write_out(argv[2]);
	return 0;
}