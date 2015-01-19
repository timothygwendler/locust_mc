/*
 * LMCGenerator.cc
 *
 *  Created on: Feb 4, 2014
 *      Author: nsoblath
 */

#include "LMCGenerator.hh"

#include "LMCLogger.hh"
#include "LMCSignal.hh"

namespace locust
{
    LMCLOGGER( lmclog, "Generator" );

    Generator::Generator( const std::string& aName ) :
            fName( aName ),
            fRequiredSignalState( Signal::kFreq ),  // pls confused here.
            fRNG( NULL ),
            fNext( NULL )
    {
    }

    Generator::~Generator()
    {
    }

    Signal* Generator::Run( unsigned aTimeSize ) const
    {
        Signal* newSignal = new Signal();
        newSignal->Initialize( aTimeSize );
        if( ! Run( newSignal ) )
        {
            delete newSignal;
            return NULL;
        }
        return newSignal;
    }

    bool Generator::Run( Signal* aSignal ) const
    {
        if(! Generate( aSignal ) )
        {
            LMCERROR( lmclog, "Signal generation failed" );
            return false;
        }
        if( fNext != NULL ) fNext->Run( aSignal );
        return true;
    }

    bool Generator::Generate( Signal* aSignal ) const
    {
        if( ! aSignal->ToState( fRequiredSignalState ) )
        {
            LMCERROR( lmclog, "Unable to convert signal to state <" << fRequiredSignalState << ">" );
            return false;
        }
        return DoGenerate( aSignal );
    }

    const std::string& Generator::GetName() const
    {
        return fName;
    }

    void Generator::SetName( const std::string& aName )
    {
        fName = aName;
        return;
    }

    Signal::State Generator::GetRequiredSignalState() const
    {
        return fRequiredSignalState;
    }

    void Generator::SetRequiredSignalState( Signal::State state )
    {
        fRequiredSignalState = state;
        return;
    }

    void Generator::SetRNG( RandomLib::Random* aRNG )
    {
        fRNG = aRNG;
        return;
    }

    RandomLib::Random* Generator::GetRNG() const
    {
        return fRNG;
    }

    Generator* Generator::GetNextGenerator() const
    {
        return fNext;
    }

    void Generator::SetNextGenerator( Generator* aGenerator )
    {
        fNext = aGenerator;
        return;
    }


} /* namespace locust */
