#include <iostream>
#include <mutex>
#include <random>
#include <time.h>
#include "Meliskudat_Kudat_Melis_hw7_HW7DynIntQueue.h"
#include <thread>
#include <ctime>
#include <chrono>
#include <iomanip>
using namespace std;



int countpackage = 0 ; // to reach the total_box_count at the end of packaging
int countf = 0; // to reach the total_box_count at the end of filling
int total_box_count ; // size of the queue
int min_production , max_production ; // random duration for a box creation
int min_filling_time ,max_filling_time ; // filling duration for box filling
int min_packaging_time, max_packaging_time ; // packaging duration for a box packaging
HW7DynIntQueue FillingQueue ; // filling queue
HW7DynIntQueue PackagingQueue ; // packaging queue
mutex Mutex1 , Mutex2 , Mutex3; // mutex1 is used FillingQueue , mutex2 is used PackagingQueue and mutex3 is used for cout


int random_range(const int & min, const int & max) // to have random values
{ 
	static mt19937 generator(time(0));
	uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

void producer()
{
   for( int i = 1 ; i <= total_box_count ; i++)
   {
     this_thread::sleep_for(chrono::seconds(random_range(min_production,max_production))) ; // time spent for production
	 Mutex1.lock() ;
	 FillingQueue.enqueue(i) ; // enqueue boxes to filling queue
	 int current_size = FillingQueue.getCurrentSize() ;
	 Mutex1.unlock() ;
	 Mutex3.lock() ;
	 time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());  // to get current time
     struct tm *ptm = new struct tm; 
     localtime_s(ptm, &tt);
     cout << "Producer has enqueued a new box " << i << " to filling queue (filling queue size is " << current_size << "): " << put_time(ptm,"%X") << endl;
	 //delete ptm ;
     Mutex3.unlock() ;
	 
   }
}

void filler( int id)
{
  
	while( countf != total_box_count ) // to be sure that all of the boxes are filled
	{
		int a ;
		Mutex1.lock() ;
		if( !FillingQueue.isEmpty() )
		{
			FillingQueue.dequeue(a) ; // take the box from the filling queue
			countf += 1 ;
			int current_size_2 = FillingQueue.getCurrentSize() ;
			Mutex1.unlock() ;
			Mutex3.lock() ;
		    time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
            struct tm *ptm = new struct tm; 
	        localtime_s(ptm, &tt); 
	        cout << "Filler " << id << " started filling the box " << a << " (filling queue size is " << current_size_2 << "): " << put_time(ptm,"%X") << endl;
			Mutex3.unlock() ;

			this_thread::sleep_for(chrono::seconds(random_range(min_filling_time,max_filling_time))) ; // time spent for filling

			 
			Mutex3.lock() ;
			time_t bb = chrono::system_clock::to_time_t(chrono::system_clock::now());  // to get  the current time
            struct tm *pinter = new struct tm; 
	        localtime_s(pinter, &bb); 
	        cout << "Filler " << id << " finished filling the box " << a <<  " : " << put_time(pinter,"%X") << endl; 
            Mutex3.unlock() ;
			
			Mutex2.lock() ; 
			PackagingQueue.enqueue(a) ; // put the previously dequeued box to packaging queue
			int package_size = PackagingQueue.getCurrentSize() ;
			Mutex2.unlock() ;
			
			Mutex3.lock() ;
			time_t cc = chrono::system_clock::to_time_t(chrono::system_clock::now()); // to get the current time
            struct tm *pinto = new struct tm; 
	        localtime_s(pinto, &cc); 
	        cout << "Filler " << id << " put box " <<  a << " into packaging queue (packaging queue size is " << package_size <<"):" << put_time(pinto,"%X") << endl;
			//delete pinter ;
			//delete pinto ;
            Mutex3.unlock() ;
			
			
		}
		else
		{
			Mutex1.unlock() ; // to unlock mutex1
		}


	}

}


void packager( int id)
{
    int b ;
	while( countpackage != total_box_count ) // to be sure that all boxes are packaged
	{
		Mutex2.lock() ;
		if( !PackagingQueue.isEmpty() ) // if queue is not empty
		{
			PackagingQueue.dequeue(b) ; // take the box from packaging queue
			countpackage += 1 ; // increase the number of box that are packaged
			Mutex2.unlock() ;
			Mutex3.lock() ;
		    time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
            struct tm *ptm = new struct tm; 
	        localtime_s(ptm, &tt); 
	        cout << "Packager " << id << " started packaging the box " << b << " (packaging queue size is " << PackagingQueue.getCurrentSize() << "): " << put_time(ptm,"%X") << endl;
			Mutex3.unlock() ;
			
			this_thread::sleep_for(chrono::seconds(random_range(min_packaging_time,max_packaging_time))) ; // time spent for packaging

			Mutex3.lock() ;
			tt = chrono::system_clock::to_time_t(chrono::system_clock::now());  
	        localtime_s(ptm, &tt); 
	        cout << "Packager " << id << " finished packaging the box " << b <<  " : " << put_time(ptm,"%X") << endl;
			//delete ptm ;
            Mutex3.unlock() ;
			

		}
		else
		{
			Mutex2.unlock() ;
		}

	}


}





int main()
{
	
	cout << "Please enter the total number of items:" ;
	cin >> total_box_count ;
	cout << "Please enter the min-max waiting time range of producer:" << endl;
	cout << "Min: " ;
	cin >> min_production ;
	cout <<	"Max: " ;
	cin >> max_production ;
	cout << "Please enter the min-max waiting time range of filler workers:" << endl ;
	cout << "Min: " ;
	cin >> min_filling_time ;
	cout <<	"Max: " ;
	cin >> max_filling_time ;
	cout << "Please enter the min-max waiting time range of packager workers:" << endl ;
	cout << "Min: " ;
	cin >> min_packaging_time ;
	cout <<	"Max: " ;
	cin >> max_packaging_time ;

	time_t ss = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
    struct tm *pist = new struct tm; 
	localtime_s(pist, &ss); 
	cout << "Simulation starts " << put_time(pist,"%X") << endl;
    thread thr1(producer);
	thread thr2(filler, 1);
	thread thr3(filler, 2);
	thread thr4(packager, 1);
	thread thr5(packager, 2);

	thr1.join();
	thr2.join();
	thr3.join();
	thr4.join() ;
	thr5.join() ;

	time_t dd = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
    struct tm *pintr = new struct tm; 
	localtime_s(pintr, &dd); 
	cout << "End of the simulation ends " << put_time(pintr,"%X") << endl;
	//delete pintr ;
	return 0;
}


