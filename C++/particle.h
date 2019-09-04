class HepObject {
	protected:
		double m_Energy;
		float m_Time;
	public:
		void setValues(double Energy, float Time);
		double get_Energy() const {return m_Energy;};
		double get_Time() const {return m_Time;};
};

class Detector : public HepObject {
	private:
		double m_minInput;
		double m_maxInput;
	public:
		void set(double minIn, double maxIn);
		void read(const HepObject * p);
};

class ReadoutSystem : public HepObject {
	private:
		double m_Threshold;		// threshold for event detection
		float m_deadTime;			// readout dead time after detection
	public:
		void set(double Threshold, float deadTime);
		void read(const Detector * p);
};
