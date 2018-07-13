#ifndef SEGYTRACEHEADER_H
#define SEGYTRACEHEADER_H

#include "iheader.h"
#include <map>

class SegyTraceHeader : public IHeader
{
public:
	SegyTraceHeader();
    virtual boost::any get(const std::string& fieldName)const;
    virtual void set(const std::string& fieldName, boost::any value);
	const std::vector<std::string>& getFieldNames()const;
	static const std::vector<std::string> fieldNames;
	static const FieldMapper mapperInfo;
	static const std::map < std::string, FieldDetailInfo> detailInfo;

    static const std::string traceNumberLine,traceNumberReel,originalFieldRecordNumber,traceSeqNumberFR,sourceNumber,cdpNumber,traceSeqNumberCDP,traceIdCode,numVerticalSumTraces,numHorizontalStackedTraces,dataUse,distSrcRecv,recvElevation,surfElevation,depthBelowSurf,datumElevationRecv,datumElevationSrc,waterDepthSrc,waterDepthGroup,elevScalar,coordScalar,srcCoordX,srcCoordY,recvGroupCoordX,recvGroupCoordY,coordUnit,weatheringVelocity,subWeatheringVelocity,upholeTimeSrc,upholeTimeRsvGroup,srcStatCorrection,rcvGroupStatCorrection,totalStaticApplied,lagTimeA,lagTimeB,delayRecTime,muteTimeStart,muteTimeEnd,sampleCount,sampleInterval,gainType,instrGainCons,instrInitGain,correlated,sweepFrStart,sweepFrEnd,sweepLength,sweepType,sweepTraceTaperLengthStart,sweepTraceTaperLengthEnd,taperType,aliasFilterFr,aliasFilterSlope,notchFilterFr,notchFilterSlope,lowCutFr,highCutFr,lowCutSlope,highCutSlope,year,dayOfYear,hour,min,sec,timeCode,traceWeightFactor,geophoneRoll,geophoneFirstTrace,geophoneLastTrace,gapSize,travel,cdpX,cdpY,inlineNumber,xlineNumber,shotpointNumber,shotpointScalar,traceMeasurementUnit,transductionConstant,transductionUnit,devId,timeScalar,srcType,srcEnergyDirection,srcMeasurement,srcMeasurementUnit;

private:
	std::map<std::string, int> fieldValue;
};

#endif // SEGYTRACEHEADER_H
