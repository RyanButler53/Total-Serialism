// Instrument base class. Other things will inherit from it. 
#ifndef INSTRUMENT_HPP_INCLUDED
#define INSTRUMENT_HPP_INCLUDED
#include "analysisMatrix.hpp"

#include <string>

class Instrument{
    private:
        /* data */
    protected:
        // All Inherited Instruments can use the Analysis Matrices and dynamics rows
        AnalysisMatrix* pitches_;
        AnalysisMatrix* rhythms_;
        AnalysisMatrix* articulations_;
        std::vector<short> dynamicsRow_;

        // Everything can access the pitch, articulation and dynamic mappings
        const std::vector<std::string> pitchMap_{"c","cs","d","ef","e","f","fs","g","af","a","bf","b"};
        const std::vector<std::string> articulationMap_{"->", "-^", "-_", "-!", "-.", "--", "->-.", "-^\\sfz", "", "->-!", "\\sfz", "-^-!"};
        const std::vector<std::string> dynamicMap_{"\\ppppp", "\\pppp", "\\ppp", "\\pp", "\\p", "\\mp", "\\mf", "\\f", "\\ff", "\\fff", "\\ffff", "\\fffff"};

        // Derived Classes specify a their own rows 
         // Generation Functions

    public:

        // Constructors
        Instrument(AnalysisMatrix* pitches, AnalysisMatrix* rhythms, AnalysisMatrix* articulations, std::vector<short> dynamics);
        virtual ~Instrument() = default;

        std::string rowToLilypond(Row r, short dynamic, short& leftover);
        virtual void generateCode(std::vector<std::string> &lilypondCode) = 0; // Pure Virtual?
        virtual std::string staffHeader(std::vector<std::string> &lilypondCode) = 0;
        
        // Utility Functions
        void clearSfz(std::string &str);
        std::string fullDuration(short duration, std::string jitter, std::string pitch, std::string articulation);
}; 

#endif // INSTRUMENT_HPP_INCLUDED