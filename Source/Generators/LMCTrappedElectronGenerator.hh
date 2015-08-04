/*
 * LMCTRAPPEDELECTRONGENERATOR.hh
 *
 *  Created on: Mar 6, 2015
 *      Author: plslocum after nsoblath
 */

#ifndef LMCTRAPPEDELECTRONGENERATOR_HH_
#define LMCTRAPPEDELECTRONGENERATOR_HH_

#include "../Core/LMCGenerator.hh"
#include "../Core/LMCRunLengthCalculator.hh"
#define LO_FREQUENCY 26.385015e9 // Hz
//#define LO_FREQUENCY 26.385 // Hz  This is where it was for collaboration meeting in April 2015.
#define PI 3.1415926
#define Z1 -2.5 // z-offset (cm) of lower coil.
#define Z2 2.5  // z-offset (cm) of upper coil.
#define RCOIL 2.0 // radius (cm) of both coils.
#define CENTER_TO_ANTENNA 10.1// distance from antenna to center of trap (cm).
#define CENTER_TO_SHORT 10.1 // distance from short to center of trap (cm).
#define C 2.99792458e10 // speed of light in cm/s.
#define MU0 1.256637e-4 // magnetic constant in T*cm/A.

// solenoid geometry
#define ZBOTTOM -5.0 // cm
#define ZTOP 5.0 // cm
#define RSOLENOID 0.63 // cm
#define NCOILS 100 // = 2 for pinch coils, = ~100 for solenoid.
#define CURRENT_SOLENOID -1.7 // -1.7 amps for solenoid, +2.0 amps for pinch coils.


// field grid
#define SPACE_DIMENSION 20.0 // cm in x y and z.
#define SPACE_RESOLUTION 0.2 // cm



namespace locust
{

    /*!
     @class TrappedElectronGenerator
     @author P. L. Slocum after N. S. Oblath

     @brief  Step an electron through a magnetic trap and generate its Doppler-shifted cyclotron radiation.

     @details
     Operates in time space

     Configuration name: "trapped-electron"

     Available configuration options:

    */
    class TrappedElectronGenerator : public Generator
    {
        public:
            TrappedElectronGenerator( const std::string& aName = "trapped-electron" );
            virtual ~TrappedElectronGenerator();

            bool Configure( const ParamNode* aNode );

            void Accept( GeneratorVisitor* aVisitor ) const;

            Signal::State GetDomain() const;
            void SetDomain( Signal::State aDomain );
            
 
        private:
            bool DoGenerate( Signal* aSignal ) const;

            bool DoGenerateTime( Signal* aSignal ) const;
            bool DoGenerateFreq( Signal* aSignal ) const;
            bool (TrappedElectronGenerator::*fDoGenerateFunc)( Signal* aSignal ) const;

            double GetBMagExact(double x0, double y0, double z0) const;
            double GetBz( double x0, double y0, double z0 ) const;
            double GetBx( double x0, double y0, double z0 ) const;
            double GetBy( double x0, double y0, double z0 ) const;
            double GetSpeed(double KineticEnergy) const;
            double GetKineticEnergy(double Velocity) const;
            double CalculateGamma( double KineticEnergy ) const;
            double *StepElectron(double *OldPosition, double KineticEnergy, double mu, double dt) const;
            double *StartElectron(double KineticEnergy, double PitchAngle) const;
            bool StopElectron(double *position) const;
            double GetMu(double *position, double KineticEnergy, double PitchAngle) const;
            double CalculateLarmorPower( double gamma, double B) const;  
            double CalculateCyclotronFrequency( double Gamma , double *position) const;
            double CalculateBasebandFrequency( double CyclotronFrequency ) const;
            double GetVoltagePhase( double Freq, double dt ) const;
            double GetVoltagePhaseFromShort( double Freq, double dt ) const;
            double GetCyclotronFreqAntennaFrame( double RFFreq, double Vparallel) const;
            void BuildFieldMaps();
            double *GetBzMap() const;
            double *GetBxMap() const;
            double *GetByMap() const;
            double InterpolateB(double x0, double y0, double z0, double *fieldmap) const;
            double GetBMag(double x0, double y0, double z0) const;
            
            double *BzMap;
            double *BxMap;
            double *ByMap;



    };

} /* namespace locust */

#endif /* LMCTRAPPEDELECTRONGENERATOR_HH_ */
