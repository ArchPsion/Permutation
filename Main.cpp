// Standard Libraries
#include <iostream>

// Custom Libraries
#include "HexPermutation.hpp"

int main(void)
{
	const std::vector<u32> u1 = { 1u, 2u };
	const std::vector<u32> u2 = { 3u, 4u };
	
	const std::vector<u32> u3 = { 1u, 3u };
	const std::vector<u32> u4 = { 2u, 4u };
	
	const std::vector<u32> u5 = { 1u, 4u };
	const std::vector<u32> u6 = { 2u, 3u };
	
	const std::vector<u32> v1 = { 1u, 2u, 3u };
	const std::vector<u32> v2 = { 2u, 3u, 4u };
	const std::vector<u32> v3 = { 3u, 4u, 1u };
	const std::vector<u32> v4 = { 4u, 1u, 2u };
	
	const auto t1 = HexPermutation(u1, u2);
	const auto t2 = HexPermutation(u3, u4);
	const auto t3 = HexPermutation(u5, u6);
	
	const auto s1 = HexPermutation(v1);
	const auto ss1 = s1*s1;
	
	const auto s2 = HexPermutation(v2);
	const auto ss2 = s2*s2;
	
	const auto s3 = HexPermutation(v3);
	const auto ss3 = s3*s3;
	
	const auto s4 = HexPermutation(v4);
	const auto ss4 = s4*s4;
	
	const auto& h = ss3;
	
	const auto x = h*t1*h.inverse()*t1;
	const auto y = h*t2*h.inverse()*t2;
	const auto z = h*t3*h.inverse()*t3;
	
	const auto a = h*s1*h.inverse()*s1.inverse();
	const auto b = h*ss1*h.inverse()*ss1.inverse();
	const auto c = h*s2*h.inverse()*s2.inverse();
	const auto d = h*ss2*h.inverse()*ss2.inverse();
	
	const auto m = h*s3*h.inverse()*s3.inverse();
	const auto n = h*ss3*h.inverse()*ss3.inverse();
	const auto o = h*s4*h.inverse()*s4.inverse();
	const auto p = h*ss4*h.inverse()*ss4.inverse();
	
	std::cout << x.info() << std::endl;
	std::cout << y.info() << std::endl;
	std::cout << z.info() << std::endl;
	
	std::cout << a.info() << std::endl;
	std::cout << b.info() << std::endl;
	std::cout << c.info() << std::endl;
	std::cout << d.info() << std::endl;
	
	std::cout << m.info() << std::endl;
	std::cout << n.info() << std::endl;
	std::cout << o.info() << std::endl;
	std::cout << p.info() << std::endl;
	
	return 0;
}
