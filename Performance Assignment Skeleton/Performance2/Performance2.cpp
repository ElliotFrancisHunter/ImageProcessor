// Visual Studio 2017 version.

#include "stdafx.h"
#include "Performance2.h"
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <concurrent_vector.h>
#include <ppl.h>

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

//ImageManager im;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	Gdiplus::GdiplusStartupInput input;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &input, NULL);

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

		Concurrency::concurrent_vector<cv::Mat> matV;
		//--------------------------------------------------------------------------------------
		// Insert your code from here...
		for (const auto& file : std::filesystem::directory_iterator(mSourcePath))
		{

		}
		cv::Mat sourceMat, destMat;
		sourceMat = cv::imread("./Source/IMG_1.jpg", cv::ImreadModes::IMREAD_GRAYSCALE);
		cv::transpose(sourceMat, destMat); 
		cv::flip(destMat, destMat, 1);
		destMat.convertTo(destMat, -1, 1, 50); // Increase all pixel values by 50 to increase brightness
		
		cv::resize(destMat, destMat, cv::Size(destMat.rows * 2, destMat.cols * 2), 2, 2, cv::InterpolationFlags::INTER_LINEAR);

		imwrite("Test2.png", destMat);


		//-------------------------------------------------------------------------------------------------------
		// How long did it take?...   DO NOT CHANGE FROM HERE...
		
		TIMER end;

		TIMER elapsed;
		
		elapsed = end - start;

		__int64 ticks_per_second = start.get_frequency();

		// Display the resulting time...

		double elapsed_seconds = (double)elapsed.get_time() / (double)ticks_per_second;

		Gdiplus::GdiplusShutdown(gdiplusToken);

		std::cout << "Elapsed time (seconds): " << elapsed_seconds;
		std::cout << std::endl;
		std::cout << "Press a key to continue" << std::endl;

		char c;
		std::cin >> c;
	}

	return nRetCode;
}
