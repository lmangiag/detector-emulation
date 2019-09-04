#include "particle.h"

// HepObject Constructor
void HepObject::setValues(double Energy, float Time)
{
	m_Energy = Energy;
	m_Time = Time;
}

// set parameters of Detector object
void Detector::set(double minIn, double maxIn)
{
	m_minInput = minIn;
	m_maxInput = maxIn;
}

// read operation on input data
void Detector::read(const HepObject * p)
{
	m_Time = p -> get_Time();
	double inputEnergy = p -> get_Energy();
		if (inputEnergy >= m_minInput) // is this signal detectable?
		{
			if (inputEnergy < m_maxInput) // is it saturating the detector?
			{
				m_Energy = inputEnergy;			// no
			}
			else {m_Energy = m_maxInput;}	// yes
		}
		else {m_Energy = 0;}
}

// Set parameters for ReadoutSystem
void ReadoutSystem::set(double Threshold, float deadTime)
{
	m_Threshold = Threshold;
	m_deadTime = deadTime;
	m_Energy = 0;
	m_Time = 0;
}

// ReadoutSystem read data from Detector
void ReadoutSystem::read(const Detector * p)
{
	float inputTime = p -> get_Time();
	double inputEnergy = p -> get_Energy();
	if ( inputEnergy > m_Threshold )
	{
		if ((inputTime - m_Time) > m_deadTime)
		{
			m_Energy = inputEnergy;
			m_Time = inputTime;
		}
	}
	else
	{
		m_Energy = 0;
		m_Time = inputTime;
	}
}
