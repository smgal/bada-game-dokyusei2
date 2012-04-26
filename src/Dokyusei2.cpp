/**
 * Name        : Dokyusei2
 * Version     : 
 * Vendor      : 
 * Description : 
 */


#include "Dokyusei2.h"
#include "Form1.h"
#include <FBase.h>

////////////////////////////////////////////////////////////////////////////////

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::System;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

////////////////////////////////////////////////////////////////////////////////

namespace
{
	enum { TIME_OUT = 10 };

	Osp::Base::Runtime::Timer* s_p_timer = null;
	Osp::Ui::Controls::Form*   s_p_ref_form = null;
}

extern void* g_h_native_window;


#define CHECK_COND(cond) if ((cond) == 0) return false;
#define CHECK_RESULT(r)  if (IsFailed(r)) return false;

////////////////////////////////////////////////////////////////////////////////

Dokyusei2::Dokyusei2()
{
	s_p_timer = null;
}

Dokyusei2::~Dokyusei2()
{
	if (s_p_timer)
	{
		s_p_timer->Cancel();
		delete s_p_timer;
		s_p_timer = null;
	}

	s_p_ref_form = null;
}

Application*
Dokyusei2::CreateInstance(void)
{
	// Create the instance through the constructor.
	return new Dokyusei2();
}

bool
Dokyusei2::OnAppInitializing(AppRegistry& appRegistry)
{
	// TODO:
	// Initialize UI resources and application specific data.
	// The application's permanent data and context can be obtained from the appRegistry.
	//
	// If this method is successful, return true; otherwise, return false.
	// If this method returns false, the application will be terminated.

	// Uncomment the following statement to listen to the screen on/off events.
	//PowerManager::SetScreenEventListener(*this);

	// Create a form
	Form1 *pForm1 = new Form1();
	pForm1->Initialize();

	// Add the form to the frame
	Frame *pFrame = GetAppFrame()->GetFrame();
	pFrame->AddControl(*pForm1);

	pForm1->SetOrientation(ORIENTATION_LANDSCAPE);

	// Set the current form
	pFrame->SetCurrentForm(*pForm1);

	// Draw and Show the form
	pForm1->Draw();
	pForm1->Show();

	s_p_ref_form = pForm1;
	g_h_native_window = static_cast<void*>(pForm1);

	s_p_timer = new Osp::Base::Runtime::Timer;
	CHECK_COND(s_p_timer);

	result r = s_p_timer->Construct(*this);
	CHECK_RESULT(r);

	return true;
}

bool
Dokyusei2::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	// TODO:
	// Deallocate resources allocated by this application for termination.
	// The application's permanent data and context can be saved via appRegistry.
	return true;
}

void
Dokyusei2::OnForeground(void)
{
	if (s_p_timer)
	{
		s_p_timer->Start(TIME_OUT);
	}
}

void
Dokyusei2::OnBackground(void)
{
	if (s_p_timer)
	{
		s_p_timer->Cancel();
	}
}

void
Dokyusei2::OnTimerExpired(Osp::Base::Runtime::Timer& timer)
{
	if (!s_p_timer)
	{
		return;
	}

	s_p_timer->Start(TIME_OUT);

	s_p_ref_form->Draw();
	s_p_ref_form->Show();
}

void
Dokyusei2::OnLowMemory(void)
{
	// TODO:
	// Free unused resources or close the application.
}

void
Dokyusei2::OnBatteryLevelChanged(BatteryLevel batteryLevel)
{
	// TODO:
	// Handle any changes in battery level here.
	// Stop using multimedia features(camera, mp3 etc.) if the battery level is CRITICAL.
}

void
Dokyusei2::OnScreenOn (void)
{
	// TODO:
	// Get the released resources or resume the operations that were paused or stopped in OnScreenOff().
}

void
Dokyusei2::OnScreenOff (void)
{
	// TODO:
	//  Unless there is a strong reason to do otherwise, release resources (such as 3D, media, and sensors) to allow the device to enter the sleep mode to save the battery.
	// Invoking a lengthy asynchronous method within this listener method can be risky, because it is not guaranteed to invoke a callback before the device enters the sleep mode.
	// Similarly, do not perform lengthy operations in this listener method. Any operation must be a quick one.
}
