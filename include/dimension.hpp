#ifndef DIMENSION_HPP
#define DIMENSION_HPP

#if DIM == 1
#define __dim__ 1

#define set_value_t(pt, p) bg::set<0>(pt, p[0]);

#define change_value_t(pt, p, offset) bg::set<0>(pt, bg::get<0>(p)+offset);

#elif DIM == 2
#define __dim__ 2

#define set_value_t(pt, p) bg::set<0>(pt, p[0]);	bg::set<1>(pt, p[1]);

#define change_value_t(pt, p, offset) bg::set<0>(pt, bg::get<0>(p)+offset);	bg::set<1>(pt, bg::get<1>(p)+offset);
#elif DIM == 3

#define __dim__ 3

#define set_value_t(pt, p) bg::set<0>(pt, p[0]);	bg::set<1>(pt, p[1]);	bg::set<2>(pt, p[2]);

#define change_value_t(pt, p, offset) bg::set<0>(pt, bg::get<0>(p)+offset);	bg::set<1>(pt, bg::get<1>(p)+offset);	bg::set<2>(pt, bg::get<2>(p)+offset);
#elif DIM == 4

#define __dim__ 4

#define set_value_t(pt, p) bg::set<0>(pt, p[0]);	bg::set<1>(pt, p[1]);	bg::set<2>(pt, p[2]);	bg::set<3>(pt, p[3]);

#define change_value_t(pt, p, offset) bg::set<0>(pt, bg::get<0>(p)+offset);	bg::set<1>(pt, bg::get<1>(p)+offset);	bg::set<2>(pt, bg::get<2>(p)+offset);	bg::set<3>(pt, bg::get<3>(p)+offset);
#elif DIM == 5

#define __dim__ 5

#define set_value_t(pt, p) bg::set<0>(pt, p[0]);	bg::set<1>(pt, p[1]);	bg::set<2>(pt, p[2]);	bg::set<3>(pt, p[3]);	bg::set<4>(pt, p[4]);

#define change_value_t(pt, p, offset) bg::set<0>(pt, bg::get<0>(p)+offset);	bg::set<1>(pt, bg::get<1>(p)+offset);	bg::set<2>(pt, bg::get<2>(p)+offset);	bg::set<3>(pt, bg::get<3>(p)+offset);	bg::set<4>(pt, bg::get<4>(p)+offset);
#endif

#endif
