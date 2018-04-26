//스캐너 동작 기본 코드 / 거리, 각도, 시간값 텍스트에 저장

#include <cstdlib>
#include <iostream>
#include <string.h>
#include <sweep/sweep.hpp>
#include <fstream>
#include<ctime>
#include <time.h>
#include<math.h>
using namespace std;

int main(int argc, char* argv[]) {

	ofstream out;
	clock_t start, end, e1;
	double duration = 0;

	out.open("output.txt");

	try {
		if (argc != 2) {
			std::cerr << "Usage: ./example-c++ device\n";
			return EXIT_FAILURE;
		}
		std::string a = "COM3";

		std::cout << "Constructing sweep device..." << std::endl;
		sweep::sweep device{ argv[1] };

		device.set_motor_speed(5);
		device.set_sample_rate(500);

		device.start_scanning();

		while(duration <= 90){

			start = clock();

			const sweep::scan scan = device.get_scan();

			for (const sweep::sample& sample : scan.samples) {
				e1 = clock();
				out << ((float)sample.angle / 1000) << " " << sample.distance <<" " << duration << "\n";
			}
			end = clock();
			duration += (double)(end - start) / (CLOCKS_PER_SEC);
		}
		device.stop_scanning();
		device.set_motor_speed(0);
		out.close();
	}
	catch (const sweep::device_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}