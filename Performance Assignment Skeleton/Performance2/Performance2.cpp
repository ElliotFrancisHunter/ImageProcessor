// Visual Studio 2017 version.

#include "stdafx.h"
#include "Performance2.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <concurrent_vector.h>
#include <ppl.h>
#include <filesystem>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



const std::string mSourcePath = "./Source/";
const std::string mDestPath = "./Destination/";

// Timer - used to established precise timings for code.
class TIMER
{
	LARGE_INTEGER t_;

	__int64 current_time_;

	public:
		TIMER()	// Default constructor. Initialises this timer with the current value of the hi-res CPU timer.
		{
			QueryPerformanceCounter(&t_);
			current_time_ = t_.QuadPart;
		}

		TIMER(const TIMER &ct)	// Copy constructor.
		{
			current_time_ = ct.current_time_;
		}

		TIMER& operator=(const TIMER &ct)	// Copy assignment.
		{
			current_time_ = ct.current_time_;
			return *this;
		}

		TIMER& operator=(const __int64 &n)	// Overloaded copy assignment.
		{
			current_time_ = n;
			return *this;
		}

		~TIMER() {}		// Destructor.

		static __int64 get_frequency()
		{
			LARGE_INTEGER frequency;
			QueryPerformanceFrequency(&frequency); 
			return frequency.QuadPart;
		}

		__int64 get_time() const
		{
			return current_time_;
		}

		void get_current_time()
		{
			QueryPerformanceCounter(&t_);
			current_time_ = t_.QuadPart;
		}

		inline bool operator==(const TIMER &ct) const
		{
			return current_time_ == ct.current_time_;
		}

		inline bool operator!=(const TIMER &ct) const
		{
			return current_time_ != ct.current_time_;
		}

		__int64 operator-(const TIMER &ct) const		// Subtract a TIMER from this one - return the result.
		{
			return current_time_ - ct.current_time_;
		}

		inline bool operator>(const TIMER &ct) const
		{
			return current_time_ > ct.current_time_;
		}

		inline bool operator<(const TIMER &ct) const
		{
			return current_time_ < ct.current_time_;
		}

		inline bool operator<=(const TIMER &ct) const
		{
			return current_time_ <= ct.current_time_;
		}

		inline bool operator>=(const TIMER &ct) const
		{
			return current_time_ >= ct.current_time_;
		}
};

CWinApp theApp;  // The one and only application object

//using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize Microsoft Foundation Classes, and print an error if failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		// Application starts here...

		// Time the application's execution time.
		TIMER start;	// DO NOT CHANGE THIS LINE. Timing will start here.

		//--------------------------------------------------------------------------------------
		// Insert your code from here...

		Concurrency::concurrent_vector<std::pair<cv::Mat, std::string>> matV;
		for (const auto& file : std::filesystem::directory_iterator(mSourcePath))
		{
			matV.push_back(std::make_pair(cv::imread(file.path().string(), cv::ImreadModes::IMREAD_GRAYSCALE), file.path().filename().stem().string()));
		}

		Concurrency::parallel_for_each(matV.begin(), matV.end(), [&](std::pair<cv::Mat, std::string> image) {

			cv::Mat dest;	
			cv::transpose(image.first, dest); 
			cv::flip(dest, dest, 1);
			dest.convertTo(dest, -1, 1, 20); // Increase brightness by 20%
			
			cv::resize(dest, dest, cv::Size(dest.rows * 2, dest.cols * 2), 2, 2, cv::InterpolationFlags::INTER_LINEAR); // Bilinear scaling
			cv::imwrite(mDestPath  + image.second + ".png", dest); // Save as png
			}, concurrency::auto_partitioner());

		//-------------------------------------------------------------------------------------------------------
		// How long did it take?...   DO NOT CHANGE FROM HERE...
		
		TIMER end;

		TIMER elapsed;
		
		elapsed = end - start;

		__int64 ticks_per_second = start.get_frequency();

		// Display the resulting time...

		double elapsed_seconds = (double)elapsed.get_time() / (double)ticks_per_second;

		std::cout << "Elapsed time (seconds): " << elapsed_seconds;
		std::cout << std::endl;
		std::cout << "Press a key to continue" << std::endl;

		char c;
		std::cin >> c;
	}

	return nRetCode;
}
