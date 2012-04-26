
#include "Form1.h"
#include <FGraphics.h>

////////////////////////////////////////////////////////////////////////////////

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;

////////////////////////////////////////////////////////////////////////////////

namespace dokyu
{
	struct TBufferDesc
	{
		void* p_start_address;
		int   width;
		int   height;
		int   bytes_per_line;
		int   bits_per_pixel;
	};

	void Init();
	void Done();
	bool Do(const TBufferDesc& buffer_desc);
}

////////////////////////////////////////////////////////////////////////////////

Form1::Form1(void)
{
}

Form1::~Form1(void)
{
}

bool
Form1::Initialize()
{
	Construct(FORM_STYLE_NORMAL);

	return true;
}

result
Form1::OnInitializing(void)
{
	result r = E_SUCCESS;

	dokyu::Init();

	return r;
}

result
Form1::OnTerminating(void)
{
	result r = E_SUCCESS;

	dokyu::Done();

	return r;
}

result
Form1::OnDraw(void)
{
	Canvas* p_canvas = GetCanvasN();

	p_canvas->SetBackgroundColor(Color(0xFF000000));
	p_canvas->Clear();

	{
		BufferInfo buffer_info;

		if (p_canvas->Lock(buffer_info) == E_SUCCESS)
		{
			dokyu::TBufferDesc buffer_desc;

			buffer_desc.p_start_address = buffer_info.pPixels;
			buffer_desc.width           = buffer_info.width;
			buffer_desc.height          = buffer_info.height;
			buffer_desc.bytes_per_line  = buffer_info.pitch;
			buffer_desc.bits_per_pixel  = buffer_info.bitsPerPixel;

			dokyu::Do(buffer_desc);
		}
		p_canvas->Unlock();
	}

	delete p_canvas;

	return E_SUCCESS;
}
