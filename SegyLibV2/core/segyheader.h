#ifndef SEGYHEADER_H
#define SEGYHEADER_H

#include "iheader.h"
#include <map>

class SegyHeader : public IHeader
{

public:
    SegyHeader();
    virtual boost::any get(const std::string& fieldName)const;
    virtual void set(const std::string& fieldName, boost::any value);
    const std::vector<std::string>& getFieldNames()const;
    static const std::string jobId,lineNumber,reelNumber,numTracesPerRecord,numOfAxualiryTracesPerRecord,sampleInterval,sampleIntervalOrigin,sampleCount,sampleCountOrigin,type,cdpFold,traceSorting,verticalSum,sweepFrStart,sweepFrEnd,sweepLength,sweepType,traceNumOfSweepChannel,sweepTaperLengthStart,sweepTaperLengthEnd,taperType,corrDataTraces,binGainRecovery,ampRecoveryMethod,measurementSys,impSignal,polarityCode,segyFormat,fixedLength;
    static const std::vector<std::string> fieldNames;
    static const FieldMapper mapperInfo;
    static const std::map < std::string, FieldDetailInfo> detailInfo;
private:
    std::map<std::string, int> fieldValue;
};

#endif // SEGYHEADER_H
