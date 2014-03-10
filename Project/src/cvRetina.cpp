// -*- C++ -*-
/*!
* @file  cvRetina.cpp
* @brief ModuleDescription
* @date $Date$
*
* $Id$
*/

#include "cvRetina.h"
using namespace std;
// Module specification
// <rtc-template block="module_spec">
static const char* cvretina_spec[] =
{
	"implementation_id", "cvRetina",
	"type_name",         "cvRetina",
	"description",       "ModuleDescription",
	"version",           "1.0.0",
	"vendor",            "Kazuki Urabe",
	"category",          "Category",
	"activity_type",     "PERIODIC",
	"kind",              "DataFlowComponent",
	"max_instance",      "1",
	"language",          "C++",
	"lang_type",         "compile",
	// Configuration variables
	"conf.default.log_sampling", "OFF",
	"conf.default.parvo_view", "OFF",
	"conf.default.magno_view", "OFF",
	// Widget
	"conf.__widget__.log_sampling", "radio",
	"conf.__widget__.parvo_view", "radio",
	"conf.__widget__.magno_view", "radio",
	// Constraints
	"conf.__constraints__.log_sampling", "(ON, OFF)",
	"conf.__constraints__.parvo_view", "(ON, OFF)",
	"conf.__constraints__.magno_view", "(ON, OFF)",
	""
};
// </rtc-template>

/*!
* @brief constructor
* @param manager Maneger Object
*/
cvRetina::cvRetina(RTC::Manager* manager)
	// <rtc-template block="initializer">
	: RTC::DataFlowComponentBase(manager),
	m_inputIn("input", m_input),
	m_parvoOut("parvo", m_parvo),
	m_magnoOut("magno", m_magno)

	// </rtc-template>
{
}

/*!
* @brief destructor
*/
cvRetina::~cvRetina()
{
}



RTC::ReturnCode_t cvRetina::onInitialize()
{
	// Registration: InPort/OutPort/Service
	// <rtc-template block="registration">
	// Set InPort buffers
	addInPort("input", m_inputIn);

	// Set OutPort buffer
	addOutPort("parvo", m_parvoOut);
	addOutPort("magno", m_magnoOut);

	// Set service provider to Ports

	// Set service consumers to Ports

	// Set CORBA Service Ports

	// </rtc-template>

	// <rtc-template block="bind_config">
	// Bind variables and configuration variable
	bindParameter("log_sampling", m_log_sampling, "OFF");
	bindParameter("parvo_view", m_parvo_view, "OFF");
	bindParameter("magno_view", m_magno_view, "OFF");
	// </rtc-template>

	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t cvRetina::onFinalize()
{
return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t cvRetina::onStartup(RTC::UniqueId ec_id)
{
return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t cvRetina::onShutdown(RTC::UniqueId ec_id)
{
return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t cvRetina::onActivated(RTC::UniqueId ec_id)
{
	inputFrame.release();
	parvoFrame.release();
	magnoFrame.release();
	old_width = 0;
	old_height = 0;
	old_bpp = 0;
	old_length = 0;
	len_p = 0;
	len_m = 0;
	fflg = false;
	//	log_flg = m_log_sampling;
	//viewer flag
	p_viewflg = false;
	p_prevflg = "OFF";
	m_viewflg = false;
	m_prevflg = "OFF";
	if(m_parvo_view=="ON")
	{
		p_viewflg = true;
		p_prevflg = "ON";
		cout<<m_parvoOut.getName()<<" viewer ON"<<endl;
		cv::namedWindow(m_parvoOut.getName(), CV_WINDOW_AUTOSIZE);
	}
	if(m_magno_view=="ON")
	{
		m_viewflg = true;
		m_prevflg = "ON";
		cout<<m_magnoOut.getName()<<" viewer ON"<<endl;
		cv::namedWindow(m_magnoOut.getName(), CV_WINDOW_AUTOSIZE);
	}
	return RTC::RTC_OK;
}


RTC::ReturnCode_t cvRetina::onDeactivated(RTC::UniqueId ec_id)
{
	inputFrame.release();
	parvoFrame.release();
	magnoFrame.release();
	fflg = false;
	//	log_flg = m_log_sampling;
	//バッファの初期化
	while(m_inputIn.isNew()) m_inputIn.read();

	if(p_viewflg == true)
		cv::destroyWindow(m_parvoOut.getName());
	if(m_viewflg == true)
		cv::destroyWindow(m_magnoOut.getName());
	return RTC::RTC_OK;
}


RTC::ReturnCode_t cvRetina::onExecute(RTC::UniqueId ec_id)
{
	// Check input image is new
	if (!m_inputIn.isNew())
	{	
		return RTC::RTC_OK;
	}
	m_inputIn.read();

	//画像が空、または画像のサイズ、チャンネルが変化
	if(inputFrame.empty() || isCFGChanged())
	{
		if(!inputFrame.empty())
		{
			inputFrame.release();
			parvoFrame.release();
			magnoFrame.release();
		}	
		inputFrame.create(cvSize(m_input.width,m_input.height),m_input.bpp);
		old_height = m_input.height;
		old_width = m_input.width;
		old_bpp = m_input.bpp;
		old_length = m_input.pixels.length();
	}
	memcpy(inputFrame.data,(void *)&(m_input.pixels[0]),m_input.pixels.length());

	//input -> retina -> magno, parvo
	if(fflg == false)
	{
		retina_image.release();
		parvoFrame.release();
		magnoFrame.release();
		//OFF
		if(m_log_sampling == "OFF"){
			retina_image = new cv::Retina(inputFrame.size());
			//			log_flg = "OFF";
		}
		else{
			retina_image = new cv::Retina(inputFrame.size(), true, cv::RETINA_COLOR_BAYER, true, 2.0, 10.0);
			//			log_flg = "ON";
		}
		fflg = true;
	}

	retina_image->run(inputFrame);
	retina_image->getParvo(parvoFrame);
	retina_image->getMagno(magnoFrame);


	//	len_p = parvoFrame.size().height * parvoFrame.size().width * parvoFrame.channels();
	len_p = parvoFrame.size().height * parvoFrame.size().width * parvoFrame.elemSize();
	m_parvo.pixels.length(len_p);
	m_parvo.height	= parvoFrame.size().height;
	m_parvo.width	= parvoFrame.size().width;
	m_parvo.bpp		= parvoFrame.type();
	memcpy((void *)&(m_parvo.pixels[0]),parvoFrame.data,len_p);

	//	len_m = magnoFrame.size().height * magnoFrame.size().width * magnoFrame.channels();
	len_m = magnoFrame.size().height * magnoFrame.size().width * magnoFrame.elemSize1();
	m_magno.pixels.length(len_m);
	m_magno.height	= magnoFrame.size().height;
	m_magno.width	= magnoFrame.size().width;
	m_magno.bpp		= magnoFrame.type();
	memcpy((void *)&(m_magno.pixels[0]),magnoFrame.data,len_m);

	//viwer
	if(m_parvo_view!=p_prevflg)	//parvo changed
	{
	if(p_prevflg == "ON")
	{		
	p_prevflg = "OFF";
	p_viewflg = false;
	cout<<m_parvoOut.getName()<<" viewer OFF"<<endl;
	cv::destroyWindow(m_parvoOut.getName());
	}
	else
	{		
	p_prevflg = "ON";
	p_viewflg = true;
	cout<<m_parvoOut.getName()<<" viewer ON"<<endl;
	cv::namedWindow(m_parvoOut.getName(), CV_WINDOW_AUTOSIZE);
	}
	}
	if(m_magno_view!=m_prevflg)	//magno changed
	{
	if(m_prevflg == "ON")
	{		
	m_prevflg = "OFF";
	m_viewflg = false;
	cout<<m_magnoOut.getName()<<" viewer OFF"<<endl;
	cv::destroyWindow(m_magnoOut.getName());
	}
	else
	{		
	m_prevflg = "ON";
	m_viewflg = true;
	cout<<m_magnoOut.getName()<<" viewer ON"<<endl;
	cv::namedWindow(m_magnoOut.getName(), CV_WINDOW_AUTOSIZE);
	}
	}
	if(p_viewflg == true){
	#if (!defined WIN32) || (!defined WIN64)
	cvStartWindowThread();
	#endif
	cv::imshow(m_parvoOut.getName(),parvoFrame);
	cv::waitKey(1);
	}
	if(m_viewflg == true){
	#if (!defined WIN32) || (!defined WIN64)
	cvStartWindowThread();
	#endif
	cv::imshow(m_magnoOut.getName(),magnoFrame);
	cv::waitKey(1);
	}
	m_parvoOut.write();
	m_magnoOut.write();

	
	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t cvRetina::onAborting(RTC::UniqueId ec_id)
{
return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t cvRetina::onError(RTC::UniqueId ec_id)
{
return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t cvRetina::onReset(RTC::UniqueId ec_id)
{
return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t cvRetina::onStateUpdate(RTC::UniqueId ec_id)
{
return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t cvRetina::onRateChanged(RTC::UniqueId ec_id)
{
return RTC::RTC_OK;
}
*/

bool cvRetina::isCFGChanged()
{
	if(old_height != m_input.height || old_width != m_input.width || old_bpp != m_input.bpp || old_length != (int)m_input.pixels.length())
		return true;

	return false;
}

extern "C"
{

	void cvRetinaInit(RTC::Manager* manager)
	{
		coil::Properties profile(cvretina_spec);
		manager->registerFactory(profile,
			RTC::Create<cvRetina>,
			RTC::Delete<cvRetina>);
	}

};


