/**
 * Takashi Michikawa
 */
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
std::mutex mtx;

void worker (const int id ) {
	std::lock_guard<std::mutex> lock (mtx);
	std::cerr<<id <<":"<< std::this_thread::get_id()<<std::endl;
}

int main (int argc, char** argv) {
	size_t nt = std::thread::hardware_concurrency();
	std::cerr<<"#nt"<<nt<<std::endl;
	if ( nt == 0 ) nt = 1;

	std::vector<std::thread> ths (nt);
	
	int count = 0;
	for ( std::thread& th : ths ) {
		th = std::thread( worker , count );
		++count;
	}
	
	for ( std::thread& th : ths ) {
		th.join();
	}
	
	return 0;
}



