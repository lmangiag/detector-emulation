#include <iostream>
#include <array>
#include "particle.h"

#define TIME_STEP 1e-9
// compiled with g++ main.cpp particle.cpp

int main()
{
	int maxEnergy = 500;
	const int numInputs = 10;

	double detectorSensitivity = 50;
	double detectorSaturation = 400;
	double readoutThreshold = 100;
	float readoutDeadtime = 2e-9;

	std::array<HepObject*, numInputs> ParticlesArray; //std::ParticlesArray

	Detector Detector1;
	// set detector parameters
	std::cout << "\nSet Detector parameters\n";
	Detector1.set(detectorSensitivity,detectorSaturation);

	ReadoutSystem Readout1;
	std::cout << "\nSet Readout parameters\n";
	Readout1.set(readoutThreshold, readoutDeadtime);

		// populate ParticlesArray with pointers to HepObject representing inputs
		std::cout << "\nGenerating input data for " << numInputs << " events\n";
		int i = 0;
		while (i < ParticlesArray.size())
		{
			ParticlesArray[i] = new HepObject;
			ParticlesArray[i] -> setValues(rand() % maxEnergy, i*TIME_STEP);
			i = i+1;
		}
		std::cout << "\nReading input data...\n";
		// Detector1 reads input from ParticlesArray
		// Readout1 reads from Detector1
		int k = 0;
		double InputE = 0;
		float InputT = 0;
		while (k < ParticlesArray.size()) //get size array
		{
			InputE = ParticlesArray[k] -> get_Energy();
			InputT = ParticlesArray[k] -> get_Time();

				std::cout << "\nEvent " << k << "--\n";
				std::cout << "\nInput:\n" << InputE << "\t" << InputT << "\n";

			Detector1.read(ParticlesArray[k]);
			Readout1.read(&Detector1);

				std::cout << "Detected:\n";
				std::cout << Detector1.get_Energy() << "\t" << Detector1.get_Time() << "\n";
				std::cout << "Acquired:\n";
				std::cout << Readout1.get_Energy() << "\t" << Readout1.get_Time() << "\n";
			delete ParticlesArray[k];
			k = k+1;
		}
		std::cout << "\nData acquisition completed\n";

	return 0;
}
