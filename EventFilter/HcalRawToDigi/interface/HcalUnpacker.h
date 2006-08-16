/* -*- C++ -*- */
#ifndef HcalUnpacker_h_included
#define HcalUnpacker_h_included 1

#include "DataFormats/HcalDigi/interface/HBHEDataFrame.h"
#include "DataFormats/HcalDigi/interface/HODataFrame.h"
#include "DataFormats/HcalDigi/interface/HFDataFrame.h"
#include "DataFormats/HcalDigi/interface/ZDCDataFrame.h"
#include "DataFormats/HcalDigi/interface/HcalCalibDataFrame.h"
#include "DataFormats/HcalDigi/interface/HcalTriggerPrimitiveDigi.h"
#include "DataFormats/HcalDigi/interface/HcalHistogramDigi.h"
#include "DataFormats/FEDRawData/interface/FEDRawData.h"
#include "CondFormats/HcalObjects/interface/HcalElectronicsMap.h"
#include <set>

class HcalUnpacker {
public:

  struct Collections {
    Collections();
    std::vector<HBHEDataFrame>* hbheCont;
    std::vector<HODataFrame>* hoCont;
    std::vector<HFDataFrame>* hfCont;
    std::vector<HcalCalibDataFrame>* calibCont;
    std::vector<ZDCDataFrame>* zdcCont;
    std::vector<HcalTriggerPrimitiveDigi>* tpCont;
  };

  /// for normal data
  HcalUnpacker(int sourceIdOffset, int beg, int end) : sourceIdOffset_(sourceIdOffset), startSample_(beg), endSample_(end) { }
  /// For histograms, no begin and end
  HcalUnpacker(int sourceIdOffset) : sourceIdOffset_(sourceIdOffset), startSample_(-1), endSample_(-1) { }
  void unpack(const FEDRawData& raw, const HcalElectronicsMap& emap, std::vector<HcalHistogramDigi>& histoDigis);
  void unpack(const FEDRawData& raw, const HcalElectronicsMap& emap, Collections& conts);
  // Old -- deprecated
  void unpack(const FEDRawData& raw, const HcalElectronicsMap& emap, std::vector<HBHEDataFrame>& precision, std::vector<HcalTriggerPrimitiveDigi>& tp);
  // Old -- deprecated
  void unpack(const FEDRawData& raw, const HcalElectronicsMap& emap, std::vector<HODataFrame>& precision, std::vector<HcalTriggerPrimitiveDigi>& tp);
  // Old -- deprecated
  void unpack(const FEDRawData& raw, const HcalElectronicsMap& emap, std::vector<HFDataFrame>& precision, std::vector<HcalTriggerPrimitiveDigi>& tp);
private:
  int sourceIdOffset_; ///< number to subtract from the source id to get the dcc id
  int startSample_; ///< first sample from fed raw data to copy 
  int endSample_; ///< last sample from fed raw data to copy (if present)
  std::set<HcalElectronicsId> unknownIds_,unknownIdsTrig_; ///< Recorded to limit number of times a log message is generated
};

#endif // HcalUnpacker_h_included
