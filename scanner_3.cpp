//sample rate 증가, 모터에 맞춰서 촬영 시간 변화, 조립 각도 제한에 따른 각도 조정, 촬영 종료 후 모터 속도 조절 삭제

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

	double x = 0, y = 0, z = 0;
	int R = 0, G = 0, B = 0;

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
		device.set_sample_rate(1000);

		device.start_scanning();

		std::cout << "start" << "\n";

		while(duration <= 84){

			start = clock();

			const sweep::scan scan = device.get_scan();

			for (const sweep::sample& sample : scan.samples) {
				e1 = clock();
				x = cos((float)(sample.angle-90000) / 1000 /180 * 3.141592) * sample.distance * cos(360 / 168 * duration * 3.141592 / 180);
				y = cos((float)(sample.angle-90000) / 1000 /180 * 3.141592) * sample.distance* sin(360 / 168 * duration * 3.141592 / 180);
				z = sin((float)(sample.angle-90000) / 1000 /180 * 3.141592) * sample.distance;
				if (sample.distance < 20) { R = 255, G = 0; }
				else if (sample.distance < 40) { R = 255, G = 50; }
				else if (sample.distance < 60) { R = 255, G = 100; }
				else if (sample.distance < 80) { R = 255, G = 150; }
				else if (sample.distance < 100) { R = 255, G = 200; }
				else if (sample.distance < 120) { R = 255, G = 255; }
				else if (sample.distance < 140) { R = 200, G = 255; }
				else if (sample.distance < 160) { R = 150, G = 255; }
				else if (sample.distance < 180) { R = 100, G = 200; }
				else if (sample.distance < 200) { R = 50, G = 200; }
				else { R = 0, G = 200; }
				
				out << x << " " << y << " "<< z << " " << R << " " << G << " " << B <<"\n";
			}
			end = clock();
			duration += (double)(end - start) / (CLOCKS_PER_SEC);
		}
		device.stop_scanning(); 
		out.close();
		std::cout << "end" << "\n";
	}
	catch (const sweep::device_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}