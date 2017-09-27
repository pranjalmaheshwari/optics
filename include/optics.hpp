#ifndef OPTICS_H
#define OPTICS_H

#include <iostream>
#include <vector>
#include <array>
#include <limits>
#include <iomanip>
#include <fstream>

#include <boost/heap/fibonacci_heap.hpp>
#include <boost/heap/binomial_heap.hpp>
#include <boost/foreach.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/index/rtree.hpp>

#include "dimension.hpp"

#define PRECISION 12

namespace bg = boost::geometry;
namespace bgm = bg::model;
namespace bgi = bg::index;

typedef bgm::point<double, __dim__, bg::cs::cartesian> point_t;
typedef bg::model::box<point_t> box_t;
typedef std::pair<point_t, unsigned int> value_t;

typedef bgi::rstar<32, 8> params_t;
typedef bgi::indexable<value_t> indexable_t;
typedef bgi::equal_to<value_t> equal_to_t;
typedef bgi::rtree<value_t, params_t, indexable_t, equal_to_t> rtree_t;
typedef boost::heap::fibonacci_heap< std::pair<double, unsigned int> >::handle_type handle_t;

class optics
{
	std::vector< value_t > values;
	std::vector< double > data;
	std::vector< double > ret;
	rtree_t rtree;
	rtree_t* rtree_ptr;
	unsigned int minPts;
	double eps;
	std::vector<handle_t> handles;
	std::vector<value_t> get_neighbours(point_t& p);
	double calc_core_dist(point_t& p, std::vector<value_t>& results, std::vector<double>& results_dist, unsigned int& elems);
	void update_neighbours(point_t& p, std::vector<value_t>& results, std::vector<double>& results_dist, boost::heap::fibonacci_heap< std::pair<double, unsigned int> >& fh, double& coreDist);
public:
	optics(){}
	~optics(){}
	optics(std::string input_file, unsigned int minPts, double eps);
	bool read(std::string input_file, unsigned int minPts, double eps);
	bool run();
	bool write_out(std::string output_file);
};

#endif
