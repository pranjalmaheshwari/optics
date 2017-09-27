#include "dimension.hpp"
#include "optics.hpp"

std::vector<value_t> optics::get_neighbours(point_t& p){
	std::vector<value_t> results;
	point_t v1;	change_value_t(v1, p, -eps)
	point_t v2;	change_value_t(v2, p, eps)
	box_t query_box(v1, v2);
	rtree_ptr->query(bgi::intersects(query_box), std::back_inserter(results));
	return results;
}

double optics::calc_core_dist(point_t& p, std::vector<value_t>& results, std::vector<double>& results_dist, unsigned int& elems){
	// heap to store top minPts dist vals
	boost::heap::binomial_heap< double > forCoreDist;
	for(auto it = results.begin();it!=results.end();++it){
		value_t& v = *it;
		double dist = bg::distance(p, v.first);
		if(dist <= eps){
			if(forCoreDist.size() < minPts)	forCoreDist.push(dist);
			else if(forCoreDist.top() > dist){	forCoreDist.pop();	forCoreDist.push(dist);}
			results_dist[elems] = dist;
			results[elems++] = v;
		}
	}
	results.resize(elems);
	results_dist.resize(elems);
	if(forCoreDist.size() > 0)	return forCoreDist.top();
	return -0.1;
}

void optics::update_neighbours(point_t& p, std::vector<value_t>& results, std::vector<double>& results_dist, boost::heap::fibonacci_heap< std::pair<double, unsigned int> >& fh, double& coreDist){
	for(unsigned int i = 0;i<results.size();++i){
		value_t& v = results[i];
		double newReachDist = std::max(coreDist, results_dist[i]);
		if(data[v.second] == std::numeric_limits<double>::max()){
			data[v.second] = newReachDist;
			handles[v.second] = fh.push(std::make_pair(-newReachDist,v.second));
		}
		else if(data[v.second] > -0.1 && newReachDist < data[v.second]){
			data[v.second] = newReachDist;
			(*handles[v.second]).first = -newReachDist;
			fh.increase(handles[v.second]);
		}
	}
}

optics::optics(std::string input_file, unsigned int minPts, double eps){
	read(input_file, minPts, eps);
}

bool optics::read(std::string input_file, unsigned int minPts, double eps){
	this->minPts = minPts;
	this->eps = eps;
	std::fstream fs(input_file, std::fstream::in);
	if(!fs.is_open()){
		return false;
	}

	std::string input;
	unsigned int count = 0;
	while(getline(fs,input)){
		values.push_back(value_t());
		value_t& dummy = values.back();
		std::array<double, __dim__> temp;
		double curr = 0.0;
		unsigned int i = 0;
		unsigned int t_i = 0;
		while(input[i] != 0){
			while(input[i] != '.' && input[i] != '\t'){
				curr *= 10;
				curr += (input[i]-'0');
				++i;
			}
			if(input[i] == '.'){
				++i;
				double temp = 0.0;
				double t = 1.0;
				while(input[i] != '\t' && input[i] != 0){
					temp *= 10;
					temp += (input[i]-'0');
					++i;
					t*=10.0;
				}
				temp /= t;
				curr += temp;
			}
			temp[t_i++] = curr;
			curr = 0.0;
			if(input[i] == 0)
				break;
			++i;
		}
		set_value_t(dummy.first, temp)
		dummy.second = count;
		++count;
	}
	fs.close();

	data.resize(count);
	ret.resize(count);
	handles.resize(count);

	for(double &n : data){
		n = std::numeric_limits<double>::max();
	}

	this->rtree = rtree_t(values, params_t(), indexable_t(), equal_to_t());
	rtree_ptr = &rtree;

	return true;
}

bool optics::run(){
	unsigned int processed = 0;
	for(value_t &n : values){
		if(data[n.second] > -0.1){
			point_t& p = n.first;//	set_value_t(p, n.first)
			std::vector<value_t> results = get_neighbours(p);
			// check if core-point or not
			if(results.size() >= minPts){
				// narrowing elements in the radius
				unsigned int elems = 0;
				std::vector<double> results_dist(results.size());
				double coreDist = calc_core_dist(p, results, results_dist, elems);
				if(elems >= minPts){
					data[n.second] = -1.0;
					ret[processed++] = data[n.second];
					boost::heap::fibonacci_heap< std::pair<double, unsigned int> > fh;
					update_neighbours(p, results, results_dist, fh, coreDist);
					while(!fh.empty()){
						ret[processed++] = -fh.top().first;
						point_t& q = values[fh.top().second].first;
						data[fh.top().second] = -1.0;
						fh.pop();
						std::vector<value_t> results_q = get_neighbours(q);
						// check if core-point or not
						if(results_q.size() > minPts){
							// narrowing elements in the radius
							unsigned int elems_q = 0;
							std::vector<double> results_dist_q(results_q.size());
							double coreDist_q = calc_core_dist(q, results_q, results_dist_q, elems_q);
							if(elems_q >= minPts){
								update_neighbours(q, results_q, results_dist_q, fh, coreDist_q);
							}
						}
					}
				}
			}
		}
	}
	for(unsigned int i = processed;i<ret.size();++i)	ret[i] = -1.0;
	return true;
}

bool optics::write_out(std::string output_file){
	std::fstream fs(output_file, std::fstream::out);
	if(!fs.is_open()){
		return false;
	}
	fs << std::setprecision(PRECISION);
	for(double& d : ret){
		fs << d << "\n";
	}
	fs.close();
	return true;
}