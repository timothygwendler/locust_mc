/*
 * LMCFreeFieldSignalGenerator.hh
 *
 *  Created on: Mar 12, 2014
 *      Author: nsoblath
 */

#ifndef LMCFREEFIELDSIGNALGENERATOR_HH_
#define LMCFREEFIELDSIGNALGENERATOR_HH_

#include <KThreeVector.hh>
#include "LMCGenerator.hh"

namespace locust
{

    /*!
     @class FreeFieldSignalGenerator
     @author N. S. Oblath

     @brief Generate signal in free space(without wave guide) for phase III

     @details
     Operates in time space

     Configuration name: "kass-signal"

     Available configuration options:
     - "param-name": type -- Description
     - "lo-frequency" : double -- the special value tuned down by the local oscillator, e.g., the 24.something giga hertz.
     - "xml-filename" : std::string -- the name of the xml locust config file.
     - "and-filename" : std::string -- the file of the hfss config file.
     

    */
    class FreeFieldSignalGenerator : public Generator
    {
        public:

            FreeFieldSignalGenerator( const std::string& aName = "freefield-signal" );
            virtual ~FreeFieldSignalGenerator();

            bool Configure( const scarab::param_node* aNode );

            void Accept( GeneratorVisitor* aVisitor ) const;


        private:
            std::vector<KGeoBag::KThreeVector > rReceiver; //Vector that contains 3D position of all points at which the fields are evaluated (ie. along receiver surface)
            std::vector<std::pair<int, double> > PreviousTimes; //Cache the results from previous iteration. [0] is previous index, [1] is corresponding retarded time of previous solution
            double fLO_Frequency;  // typically defined by a parameter in json file.

            std::string gxml_filename;

            std::vector<std::vector<std::array<std::array<double,2>, 3 > > > NFDElectricFieldFreq;  //Should use the KThreeVectors too.....
            std::vector<std::vector<std::array<std::array<double,2>, 3 > > > NFDMagneticFieldFreq;

            bool fWriteNFD;
            std::vector<double> NFDFrequencies;
            std::string fAND_filename;
            std::string fNFD_filename;

            bool DoGenerate( Signal* aSignal );
            void* DriveAntenna(int PreEventCounter, unsigned index, Signal* aSignal);

            void NFDWrite();

            int FindNode(double tNew, double dtStepSize, int IndexOld) const;

    };

} /* namespace locust */

#endif /* LMCFREEFIELDSIGNALGENERATOR_HH_ */
