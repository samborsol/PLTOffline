#ifndef GUARD_PLTBinaryFileReader_h
#define GUARD_PLTBinaryFileReader_h

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdint.h>
#include <set>

#include "PLTHit.h"
#include "PLTPlane.h"
#include "PLTGainCal.h"
#include "PLTError.h"

class PLTBinaryFileReader
{
  public:
    PLTBinaryFileReader ();
    PLTBinaryFileReader (std::string const, bool const IsText = false);
    ~PLTBinaryFileReader ();

    bool Open (std::string const);
    bool OpenBinary (std::string const);
    bool OpenTextFile (std::string const);
    void SetIsText (bool const);



    int  convPXL (int);
    bool DecodeSpyDataFifo (uint32_t, std::vector<PLTHit*>&, std::vector<PLTError>&, std::vector<int>&);
    int  ReadEventHits (std::vector<PLTHit*>&, std::vector<PLTError>&, unsigned long&, uint32_t&, uint32_t&, std::vector<int>&);
    int  ReadEventHits (std::ifstream&, std::vector<PLTHit*>&, std::vector<PLTError>&, unsigned long&, uint32_t&, uint32_t&, std::vector<int>&);
    int  ReadEventHitsText (std::ifstream&, std::vector<PLTHit*>&, unsigned long&, uint32_t&, uint32_t&);

    void ReadPixelMask (std::string const);
    void ReadOnlinePixelMask(const std::string maskFileName, const PLTGainCal& gainCal);
    bool IsPixelMasked (int const);

    void SetPlaneFiducialRegion (PLTPlane::FiducialRegion);

    PLTPlane::FiducialRegion fPlaneFiducialRegion;

  private:
    std::string fFileName;
    std::ifstream fInfile;
    bool fIsText;
    uint32_t fLastTime;
    int fTimeMult;
    int fFEDID;

    std::set<int> fPixelMask;
};



#endif
