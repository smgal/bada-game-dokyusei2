#ifndef _FORM1_H_
#define _FORM1_H_

#include <FBase.h>
#include <FUi.h>

class Form1 :
	public Osp::Ui::Controls::Form
{

// Construction
public:
	Form1(void);
	virtual ~Form1(void);
	bool Initialize(void);

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual result OnDraw(void);
};

#endif	//_FORM1_H_
