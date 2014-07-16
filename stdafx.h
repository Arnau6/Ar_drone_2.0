// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define ARDRONE_SESSION_ID          "ad1efdac"      // SessionID
#define ARDRONE_PROFILE_ID          "992f7f4f"      // Profile ID
#define ARDRONE_APPLOCATION_ID      "510acf97"      // Application ID



#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
#include <sstream>      // std::ostringstream
#include <string>
#include <ctime>

#include "Xinput.h"// manette Xbox
#pragma comment(lib, "Xinput.lib") 
//#pragma comment(lib, "Xinput9_1_0.lib") 


#pragma comment(lib, "WS2_32.lib") // socket
#include <sys/wstat.inl>

#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv/cv.h>
//#include <opencv2/objdetect/objdetect.hpp>

//Leap Motion
#include <Leap.h>
#include <LeapMath.h>


// WinINet
#include <wininet.h>
#pragma comment(lib, "wininet.lib") 

#include <vcclr.h>//winForm

#include <msclr/marshal.h> // used to convert		System::String^ to std::string
#include <msclr/marshal_cppstd.h>

using namespace Leap;
using namespace cv;
using namespace std;

