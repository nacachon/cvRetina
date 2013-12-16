// -*- C++ -*-
/*!
* @file  cvRetina.h
* @brief ModuleDescription
* @date  $Date$
*
* $Id$
*/

#ifndef CVRETINA_H
#define CVRETINA_H

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>
#include <iostream>
#include <cstring>
#include "opencv2\opencv.hpp"

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">

// </rtc-template>

using namespace RTC;

/*!
* @class cvRetina
* @brief ModuleDescription
*
*/
class cvRetina
	: public RTC::DataFlowComponentBase
{
public:
	/*!
	* @brief constructor
	* @param manager Maneger Object
	*/
	cvRetina(RTC::Manager* manager);

	/*!
	* @brief destructor
	*/
	~cvRetina();

	// <rtc-template block="public_attribute">

	// </rtc-template>

	// <rtc-template block="public_operation">

	// </rtc-template>

	/***
	*
	* The initialize action (on CREATED->ALIVE transition)
	* formaer rtc_init_entry() 
	*
	* @return RTC::ReturnCode_t
	* 
	* 
	*/
	virtual RTC::ReturnCode_t onInitialize();

	/***
	*
	* The finalize action (on ALIVE->END transition)
	* formaer rtc_exiting_entry()
	*
	* @return RTC::ReturnCode_t
	* 
	* 
	*/
	// virtual RTC::ReturnCode_t onFinalize();

	/***
	*
	* The startup action when ExecutionContext startup
	* former rtc_starting_entry()
	*
	* @param ec_id target ExecutionContext Id
	*
	* @return RTC::ReturnCode_t
	* 
	* 
	*/
	// virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

	/***
	*
	* The shutdown action when ExecutionContext stop
	* former rtc_stopping_entry()
	*
	* @param ec_id target ExecutionContext Id
	*
	* @return RTC::ReturnCode_t
	* 
	* 
	*/
	// virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

	/***
	*
	* The activated action (Active state entry action)
	* former rtc_active_entry()
	*
	* @param ec_id target ExecutionContext Id
	*
	* @return RTC::ReturnCode_t
	* 
	* 
	*/
	virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

	/***
	*
	* The deactivated action (Active state exit action)
	* former rtc_active_exit()
	*
	* @param ec_id target ExecutionContext Id
	*
	* @return RTC::ReturnCode_t
	* 
	* 
	*/
	virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

	/***
	*
	* The execution action that is invoked periodically
	* former rtc_active_do()
	*
	* @param ec_id target ExecutionContext Id
	*
	* @return RTC::ReturnCode_t
	* 
	* 
	*/
	virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

	/***
	*
	* The aborting action when main logic error occurred.
	* former rtc_aborting_entry()
	*
	* @param ec_id target ExecutionContext Id
	*
	* @return RTC::ReturnCode_t
	* 
	* 
	*/
	// virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

	/***
	*
	* The error action in ERROR state
	* former rtc_error_do()
	*
	* @param ec_id target ExecutionContext Id
	*
	* @return RTC::ReturnCode_t
	* 
	* 
	*/
	// virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

	/***
	*
	* The reset action that is invoked resetting
	* This is same but different the former rtc_init_entry()
	*
	* @param ec_id target ExecutionContext Id
	*
	* @return RTC::ReturnCode_t
	* 
	* 
	*/
	// virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);

	/***
	*
	* The state update action that is invoked after onExecute() action
	* no corresponding operation exists in OpenRTm-aist-0.2.0
	*
	* @param ec_id target ExecutionContext Id
	*
	* @return RTC::ReturnCode_t
	* 
	* 
	*/
	// virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

	/***
	*
	* The action that is invoked when execution context's rate is changed
	* no corresponding operation exists in OpenRTm-aist-0.2.0
	*
	* @param ec_id target ExecutionContext Id
	*
	* @return RTC::ReturnCode_t
	* 
	* 
	*/
	// virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);


protected:
	// <rtc-template block="protected_attribute">

	// </rtc-template>

	// <rtc-template block="protected_operation">

	// </rtc-template>

	// Configuration variable declaration
	// <rtc-template block="config_declare">
	/*!
	* 
	* - Name:  log_sampling
	* - DefaultValue: OFF
	*/
	std::string m_log_sampling;
	/*!
	* 
	* - Name:  parvo_view
	* - DefaultValue: OFF
	*/
	std::string m_parvo_view;
	/*!
	* 
	* - Name:  magno_view
	* - DefaultValue: OFF
	*/
	std::string m_magno_view;

	// </rtc-template>

	// DataInPort declaration
	// <rtc-template block="inport_declare">
	RTC::CameraImage m_input;
	/*!
	*/
	InPort<RTC::CameraImage> m_inputIn;

	// </rtc-template>


	// DataOutPort declaration
	// <rtc-template block="outport_declare">
	RTC::CameraImage m_parvo;
	/*!
	*/
	OutPort<RTC::CameraImage> m_parvoOut;
	RTC::CameraImage m_magno;
	/*!
	*/
	OutPort<RTC::CameraImage> m_magnoOut;

	// </rtc-template>

	// CORBA Port declaration
	// <rtc-template block="corbaport_declare">

	// </rtc-template>

	// Service declaration
	// <rtc-template block="service_declare">

	// </rtc-template>

	// Consumer declaration
	// <rtc-template block="consumer_declare">

	// </rtc-template>

private:
	// <rtc-template block="private_attribute">

	// </rtc-template>

	// <rtc-template block="private_operation">

	// </rtc-template>
	cv::Ptr<cv::Retina> retina_image;
	cv::Mat inputFrame;
	cv::Mat magnoFrame;
	cv::Mat parvoFrame;
	bool isCFGChanged();
	int old_width;
	int old_height;
	int old_bpp;
	int old_length;
	int len_p;
	int len_m;
	bool fflg;
	//std::string log_flg;
	bool p_viewflg;
	std::string p_prevflg;
	bool m_viewflg;
	std::string m_prevflg;
};


extern "C"
{
	DLL_EXPORT void cvRetinaInit(RTC::Manager* manager);
};

#endif // CVRETINA_H
