#include "segytraceheader.h"


SegyTraceHeader::SegyTraceHeader(){
    for (std::map < std::string, FieldDetailInfo>::const_iterator it = detailInfo.begin(); it != detailInfo.end(); ++it){
        fieldValue[it->first] = 0;
    }
}

boost::any SegyTraceHeader::get(const std::string &fieldName) const{
    if (fieldValue.count(fieldName) < 1)
        throw;
    return fieldValue.find(fieldName)->second;
}

void SegyTraceHeader::set(const std::string &fieldName, boost::any value){
    fieldValue[fieldName]=boost::any_cast<int>(value);
}


const std::vector<std::string>& SegyTraceHeader::getFieldNames()const{
    return fieldNames;
}

const std::string SegyTraceHeader::traceNumberLine="traceNumberLine";
const std::string SegyTraceHeader::traceNumberReel="traceNumberReel";
const std::string SegyTraceHeader::originalFieldRecordNumber="originalFieldRecordNumber";
const std::string SegyTraceHeader::traceSeqNumberFR="traceSeqNumberFR";
const std::string SegyTraceHeader::sourceNumber="sourceNumber";
const std::string SegyTraceHeader::cdpNumber="cdpNumber";
const std::string SegyTraceHeader::traceSeqNumberCDP="traceSeqNumberCDP";
const std::string SegyTraceHeader::traceIdCode="traceIdCode";
const std::string SegyTraceHeader::numVerticalSumTraces="numVerticalSumTraces";
const std::string SegyTraceHeader::numHorizontalStackedTraces="numHorizontalStackedTraces";
const std::string SegyTraceHeader::dataUse="dataUse";
const std::string SegyTraceHeader::distSrcRecv="distSrcRecv";
const std::string SegyTraceHeader::recvElevation="recvElevation";
const std::string SegyTraceHeader::surfElevation="surfElevation";
const std::string SegyTraceHeader::depthBelowSurf="depthBelowSurf";
const std::string SegyTraceHeader::datumElevationRecv="datumElevationRecv";
const std::string SegyTraceHeader::datumElevationSrc="datumElevationSrc";
const std::string SegyTraceHeader::waterDepthSrc="waterDepthSrc";
const std::string SegyTraceHeader::waterDepthGroup="waterDepthGroup";
const std::string SegyTraceHeader::elevScalar="elevScalar";
const std::string SegyTraceHeader::coordScalar="coordScalar";
const std::string SegyTraceHeader::srcCoordX="srcCoordX";
const std::string SegyTraceHeader::srcCoordY="srcCoordY";
const std::string SegyTraceHeader::recvGroupCoordX="recvGroupCoordX";
const std::string SegyTraceHeader::recvGroupCoordY="recvGroupCoordY";
const std::string SegyTraceHeader::coordUnit="coordUnit";
const std::string SegyTraceHeader::weatheringVelocity="weatheringVelocity";
const std::string SegyTraceHeader::subWeatheringVelocity="subWeatheringVelocity";
const std::string SegyTraceHeader::upholeTimeSrc="upholeTimeSrc";
const std::string SegyTraceHeader::upholeTimeRsvGroup="upholeTimeRsvGroup";
const std::string SegyTraceHeader::srcStatCorrection="srcStatCorrection";
const std::string SegyTraceHeader::rcvGroupStatCorrection="rcvGroupStatCorrection";
const std::string SegyTraceHeader::totalStaticApplied="totalStaticApplied";
const std::string SegyTraceHeader::lagTimeA="lagTimeA";
const std::string SegyTraceHeader::lagTimeB="lagTimeB";
const std::string SegyTraceHeader::delayRecTime="delayRecTime";
const std::string SegyTraceHeader::muteTimeStart="muteTimeStart";
const std::string SegyTraceHeader::muteTimeEnd="muteTimeEnd";
const std::string SegyTraceHeader::sampleCount="sampleCount";
const std::string SegyTraceHeader::sampleInterval="sampleInterval";
const std::string SegyTraceHeader::gainType="gainType";
const std::string SegyTraceHeader::instrGainCons="instrGainCons";
const std::string SegyTraceHeader::instrInitGain="instrInitGain";
const std::string SegyTraceHeader::correlated="correlated";
const std::string SegyTraceHeader::sweepFrStart="sweepFrStart";
const std::string SegyTraceHeader::sweepFrEnd="sweepFrEnd";
const std::string SegyTraceHeader::sweepLength="sweepLength";
const std::string SegyTraceHeader::sweepType="sweepType";
const std::string SegyTraceHeader::sweepTraceTaperLengthStart="sweepTraceTaperLengthStart";
const std::string SegyTraceHeader::sweepTraceTaperLengthEnd="sweepTraceTaperLengthEnd";
const std::string SegyTraceHeader::taperType="taperType";
const std::string SegyTraceHeader::aliasFilterFr="aliasFilterFr";
const std::string SegyTraceHeader::aliasFilterSlope="aliasFilterSlope";
const std::string SegyTraceHeader::notchFilterFr="notchFilterFr";
const std::string SegyTraceHeader::notchFilterSlope="notchFilterSlope";
const std::string SegyTraceHeader::lowCutFr="lowCutFr";
const std::string SegyTraceHeader::highCutFr="highCutFr";
const std::string SegyTraceHeader::lowCutSlope="lowCutSlope";
const std::string SegyTraceHeader::highCutSlope="highCutSlope";
const std::string SegyTraceHeader::year="year";
const std::string SegyTraceHeader::dayOfYear="dayOfYear";
const std::string SegyTraceHeader::hour="hour";
const std::string SegyTraceHeader::min="min";
const std::string SegyTraceHeader::sec="sec";
const std::string SegyTraceHeader::timeCode="timeCode";
const std::string SegyTraceHeader::traceWeightFactor="traceWeightFactor";
const std::string SegyTraceHeader::geophoneRoll="geophoneRoll";
const std::string SegyTraceHeader::geophoneFirstTrace="geophoneFirstTrace";
const std::string SegyTraceHeader::geophoneLastTrace="geophoneLastTrace";
const std::string SegyTraceHeader::gapSize="gapSize";
const std::string SegyTraceHeader::travel="travel";
const std::string SegyTraceHeader::cdpX="cdpX";
const std::string SegyTraceHeader::cdpY="cdpY";
const std::string SegyTraceHeader::inlineNumber="inlineNumber";
const std::string SegyTraceHeader::xlineNumber="xlineNumber";
const std::string SegyTraceHeader::shotpointNumber="shotpointNumber";
const std::string SegyTraceHeader::shotpointScalar="shotpointScalar";
const std::string SegyTraceHeader::traceMeasurementUnit="traceMeasurementUnit";
const std::string SegyTraceHeader::transductionConstant="transductionConstant";
const std::string SegyTraceHeader::transductionUnit="transductionUnit";
const std::string SegyTraceHeader::devId="devId";
const std::string SegyTraceHeader::timeScalar="timeScalar";
const std::string SegyTraceHeader::srcType="srcType";
const std::string SegyTraceHeader::srcEnergyDirection="srcEnergyDirection";
const std::string SegyTraceHeader::srcMeasurement="srcMeasurement";
const std::string SegyTraceHeader::srcMeasurementUnit="srcMeasurementUnit";

static std::map < std::string, FieldMappingInfo> initMapperInfo(){
    std::map<std::string, FieldMappingInfo> mmap;
    mmap[SegyTraceHeader::traceNumberLine] = FieldMappingInfo(0, 4);
    mmap[SegyTraceHeader::traceNumberReel] = FieldMappingInfo(4, 4);
    mmap[SegyTraceHeader::originalFieldRecordNumber] = FieldMappingInfo(8, 4);
    mmap[SegyTraceHeader::traceSeqNumberFR] = FieldMappingInfo(12, 4);
    mmap[SegyTraceHeader::sourceNumber] = FieldMappingInfo(16, 4);
    mmap[SegyTraceHeader::cdpNumber] = FieldMappingInfo(20, 4);
    mmap[SegyTraceHeader::traceSeqNumberCDP] = FieldMappingInfo(24, 4);
    mmap[SegyTraceHeader::traceIdCode] = FieldMappingInfo(28, 2);
    mmap[SegyTraceHeader::numVerticalSumTraces] = FieldMappingInfo(30, 2);
    mmap[SegyTraceHeader::numHorizontalStackedTraces] = FieldMappingInfo(32, 2);
    mmap[SegyTraceHeader::dataUse] = FieldMappingInfo(34, 2);
    mmap[SegyTraceHeader::distSrcRecv] = FieldMappingInfo(36, 4);
    mmap[SegyTraceHeader::recvElevation] = FieldMappingInfo(40, 4);
    mmap[SegyTraceHeader::surfElevation] = FieldMappingInfo(44, 4);
    mmap[SegyTraceHeader::depthBelowSurf] = FieldMappingInfo(48, 4);
    mmap[SegyTraceHeader::datumElevationRecv] = FieldMappingInfo(52, 4);
    mmap[SegyTraceHeader::datumElevationSrc] = FieldMappingInfo(56, 4);
    mmap[SegyTraceHeader::waterDepthSrc] = FieldMappingInfo(60, 4);
    mmap[SegyTraceHeader::waterDepthGroup] = FieldMappingInfo(64, 4);
    mmap[SegyTraceHeader::elevScalar] = FieldMappingInfo(68, 2);
    mmap[SegyTraceHeader::coordScalar] = FieldMappingInfo(70, 2);
    mmap[SegyTraceHeader::srcCoordX] = FieldMappingInfo(72, 4);
    mmap[SegyTraceHeader::srcCoordY] = FieldMappingInfo(76, 4);
    mmap[SegyTraceHeader::recvGroupCoordX] = FieldMappingInfo(80, 4);
    mmap[SegyTraceHeader::recvGroupCoordY] = FieldMappingInfo(84, 4);
    mmap[SegyTraceHeader::coordUnit] = FieldMappingInfo(88, 2);
    mmap[SegyTraceHeader::weatheringVelocity] = FieldMappingInfo(90, 2);
    mmap[SegyTraceHeader::subWeatheringVelocity] = FieldMappingInfo(92, 2);
    mmap[SegyTraceHeader::upholeTimeSrc] = FieldMappingInfo(94, 2);
    mmap[SegyTraceHeader::upholeTimeRsvGroup] = FieldMappingInfo(96, 2);
    mmap[SegyTraceHeader::srcStatCorrection] = FieldMappingInfo(98, 2);
    mmap[SegyTraceHeader::rcvGroupStatCorrection] = FieldMappingInfo(100, 2);
    mmap[SegyTraceHeader::totalStaticApplied] = FieldMappingInfo(102, 2);
    mmap[SegyTraceHeader::lagTimeA] = FieldMappingInfo(104, 2);
    mmap[SegyTraceHeader::lagTimeB] = FieldMappingInfo(106, 2);
    mmap[SegyTraceHeader::delayRecTime] = FieldMappingInfo(108, 2);
    mmap[SegyTraceHeader::muteTimeStart] = FieldMappingInfo(110, 2);
    mmap[SegyTraceHeader::muteTimeEnd] = FieldMappingInfo(112, 2);
    mmap[SegyTraceHeader::sampleCount] = FieldMappingInfo(114, 2);
    mmap[SegyTraceHeader::sampleInterval] = FieldMappingInfo(116, 2);
    mmap[SegyTraceHeader::gainType] = FieldMappingInfo(118, 2);
    mmap[SegyTraceHeader::instrGainCons] = FieldMappingInfo(120, 2);
    mmap[SegyTraceHeader::instrInitGain] = FieldMappingInfo(122, 2);
    mmap[SegyTraceHeader::correlated] = FieldMappingInfo(124, 2);
    mmap[SegyTraceHeader::sweepFrStart] = FieldMappingInfo(126, 2);
    mmap[SegyTraceHeader::sweepFrEnd] = FieldMappingInfo(128, 2);
    mmap[SegyTraceHeader::sweepLength] = FieldMappingInfo(130, 2);
    mmap[SegyTraceHeader::sweepType] = FieldMappingInfo(132, 2);
    mmap[SegyTraceHeader::sweepTraceTaperLengthStart] = FieldMappingInfo(134, 2);
    mmap[SegyTraceHeader::sweepTraceTaperLengthEnd] = FieldMappingInfo(136, 2);
    mmap[SegyTraceHeader::taperType] = FieldMappingInfo(138, 2);
    mmap[SegyTraceHeader::aliasFilterFr] = FieldMappingInfo(140, 2);
    mmap[SegyTraceHeader::aliasFilterSlope] = FieldMappingInfo(142, 2);
    mmap[SegyTraceHeader::notchFilterFr] = FieldMappingInfo(144, 2);
    mmap[SegyTraceHeader::notchFilterSlope] = FieldMappingInfo(146, 2);
    mmap[SegyTraceHeader::lowCutFr] = FieldMappingInfo(148, 2);
    mmap[SegyTraceHeader::highCutFr] = FieldMappingInfo(150, 2);
    mmap[SegyTraceHeader::lowCutSlope] = FieldMappingInfo(152, 2);
    mmap[SegyTraceHeader::highCutSlope] = FieldMappingInfo(154, 2);
    mmap[SegyTraceHeader::year] = FieldMappingInfo(156, 2);
    mmap[SegyTraceHeader::dayOfYear] = FieldMappingInfo(158, 2);
    mmap[SegyTraceHeader::hour] = FieldMappingInfo(160, 2);
    mmap[SegyTraceHeader::min] = FieldMappingInfo(162, 2);
    mmap[SegyTraceHeader::sec] = FieldMappingInfo(164, 2);
    mmap[SegyTraceHeader::timeCode] = FieldMappingInfo(166, 2);
    mmap[SegyTraceHeader::traceWeightFactor] = FieldMappingInfo(168, 2);
    mmap[SegyTraceHeader::geophoneRoll] = FieldMappingInfo(170, 2);
    mmap[SegyTraceHeader::geophoneFirstTrace] = FieldMappingInfo(172, 2);
    mmap[SegyTraceHeader::geophoneLastTrace] = FieldMappingInfo(174, 2);
    mmap[SegyTraceHeader::gapSize] = FieldMappingInfo(176, 2);
    mmap[SegyTraceHeader::travel] = FieldMappingInfo(178, 2);
    mmap[SegyTraceHeader::cdpX] = FieldMappingInfo(180, 4);
    mmap[SegyTraceHeader::cdpY] = FieldMappingInfo(184, 4);
    mmap[SegyTraceHeader::inlineNumber] = FieldMappingInfo(188, 4);
    mmap[SegyTraceHeader::xlineNumber] = FieldMappingInfo(192, 4);
    mmap[SegyTraceHeader::shotpointNumber] = FieldMappingInfo(196, 4);
    mmap[SegyTraceHeader::shotpointScalar] = FieldMappingInfo(200, 2);
    mmap[SegyTraceHeader::traceMeasurementUnit] = FieldMappingInfo(202, 2);
    mmap[SegyTraceHeader::transductionConstant] = FieldMappingInfo(204, 6);
    mmap[SegyTraceHeader::transductionUnit] = FieldMappingInfo(210, 2);
    mmap[SegyTraceHeader::devId] = FieldMappingInfo(212, 2);
    mmap[SegyTraceHeader::timeScalar] = FieldMappingInfo(214, 2);
    mmap[SegyTraceHeader::srcType] = FieldMappingInfo(216, 2);
    mmap[SegyTraceHeader::srcEnergyDirection] = FieldMappingInfo(218, 6);
    mmap[SegyTraceHeader::srcMeasurement] = FieldMappingInfo(224, 6);
    mmap[SegyTraceHeader::srcMeasurementUnit] = FieldMappingInfo(230, 2);
    return mmap;
}

const std::map < std::string, FieldMappingInfo> SegyTraceHeader::mapperInfo = initMapperInfo();

static std::map < std::string, FieldDetailInfo> initDetailInfo(){
    std::map<std::string, FieldDetailInfo> mmap;
    mmap[SegyTraceHeader::traceNumberLine] = FieldDetailInfo("Trace sequence within line","Numbers continue to increase if the same line continues across multiple SEGY files (Highly recommended for all types of data)");
    mmap[SegyTraceHeader::traceNumberReel] = FieldDetailInfo("Trace sequence number within SEGY file","Each file starts with trace sequence one");
    mmap[SegyTraceHeader::originalFieldRecordNumber] = FieldDetailInfo("Original field record number");
    mmap[SegyTraceHeader::traceSeqNumberFR] = FieldDetailInfo("Trace number within the origina field record");
    mmap[SegyTraceHeader::sourceNumber] = FieldDetailInfo("Energy source point number","Used when more than one record occurs at the same effective surface location. It is recommended that the new entry defined in Trace Header bytes 197-202 be used for shotpoint number.");
    mmap[SegyTraceHeader::cdpNumber] = FieldDetailInfo("Ensemble number","Ensemble number (i.e. CDP, CMP, CRP, etc)");
    mmap[SegyTraceHeader::traceSeqNumberCDP] = FieldDetailInfo("Trace number within the ensemble","Each ensemble starts with trace number one");
    mmap[SegyTraceHeader::traceIdCode] = FieldDetailInfo("Trace identification code","-1=Other\n0=Unknown\n1=Seismic data\n2=Dead\n3=Dummy\n4=Time break\n5=Uphole\n6=Sweep\n7=Timing\n8=Waterbreak\n9=Near-field hun signature\n10=Far-field gun signature\n11=Seismic pressure sensor\n12=Multicomponent seismic sensor - Vertical component\n13=Multicomponent seismic sensor - Cross-line component\n14=Multicomponent seismic sensor - In-line component\n15=Rotated multicomponent seismic sensor - Vertical component\n16=Rotated multicomponent seismic sensor - Transverse component\n17=Rotated multicomponent seismic sensor - Radial component\n18=Vibrator reaction mass\n19=Vibrator baseplate\n20=Vibrator estimated ground force\n21=Vibrator reference\n22=Time-velocity pairs");
    mmap[SegyTraceHeader::numVerticalSumTraces] = FieldDetailInfo("Number of vertically summed traces","Number of vertically summed traces yielding this trace (1 is one trace, 2 is two summed traces, etc.)");
    mmap[SegyTraceHeader::numHorizontalStackedTraces] = FieldDetailInfo("Number of horizontally stacked traces","Number of horizontally stacked traces yielding this trace (1 is one trace, 2 is two stacked traces, etc.)");
    mmap[SegyTraceHeader::dataUse] = FieldDetailInfo("Data use","1=Production\n2=Test");
    mmap[SegyTraceHeader::distSrcRecv] = FieldDetailInfo("","Distance from center of the source point to the center of the receiver group (negative if opposite to direction in which line is shot)");
    mmap[SegyTraceHeader::recvElevation] = FieldDetailInfo("Receiver group elevation","All elevations above the Vertucal datum are positive and below are negative");
    mmap[SegyTraceHeader::surfElevation] = FieldDetailInfo("Surface elevation at source");
    mmap[SegyTraceHeader::depthBelowSurf] = FieldDetailInfo("Source depth below surface");
    mmap[SegyTraceHeader::datumElevationRecv] = FieldDetailInfo("Datum elevation at receiver group");
    mmap[SegyTraceHeader::datumElevationSrc] = FieldDetailInfo("Datum elevation at source");
    mmap[SegyTraceHeader::waterDepthSrc] = FieldDetailInfo("Water depth at source");
    mmap[SegyTraceHeader::waterDepthGroup] = FieldDetailInfo("Water depth at group");
    mmap[SegyTraceHeader::elevScalar] = FieldDetailInfo("Elevation scalar","Scalar to be applied to all elevations and depths specified in Trace Header bytes 41-68 to give the real value. Scalar=1,+10,+100,+1000, or +10000. If positive, scalar is used as a multiplier; if negative, scalar is used as a divisor.");
    mmap[SegyTraceHeader::coordScalar] = FieldDetailInfo("Coordinate scalar","Scalar to be applied to all coordinates specified in Trace Header bytes 73-88 and to bytes Trace Header 181-188 to give the real value. Scalar=1,+10,+100,+1000, or +10000. If positive, scalar is used as a multiplier; if negative, scalar is used as divisor.");
    mmap[SegyTraceHeader::srcCoordX] = FieldDetailInfo("Source coordinate - X");
    mmap[SegyTraceHeader::srcCoordY] = FieldDetailInfo("Source coordinate - Y");
    mmap[SegyTraceHeader::recvGroupCoordX] = FieldDetailInfo("Group coordinate - X");
    mmap[SegyTraceHeader::recvGroupCoordY] = FieldDetailInfo("Group coordinate - Y");
    mmap[SegyTraceHeader::coordUnit] = FieldDetailInfo("Coordinate units","1=Length (meters or feet)\n2=Seconds of arc\n3=Decimal degrees\n4=Degrees, minutes, seconds (DMS)");
    mmap[SegyTraceHeader::weatheringVelocity] = FieldDetailInfo("Weathering velocity");
    mmap[SegyTraceHeader::subWeatheringVelocity] = FieldDetailInfo("Subweathering velocity");
    mmap[SegyTraceHeader::upholeTimeSrc] = FieldDetailInfo("Uphole time at source in milliseconds");
    mmap[SegyTraceHeader::upholeTimeRsvGroup] = FieldDetailInfo("Uphole time at group in milliseconds");
    mmap[SegyTraceHeader::srcStatCorrection] = FieldDetailInfo("Source static correction in milliseconds");
    mmap[SegyTraceHeader::rcvGroupStatCorrection] = FieldDetailInfo("Group static correction in milliseconds");
    mmap[SegyTraceHeader::totalStaticApplied] = FieldDetailInfo("Total static applied in milliseconds","Zero if no static has been applied");
    mmap[SegyTraceHeader::lagTimeA] = FieldDetailInfo("Lag time A","Time in milliseconds beween end of 240-byte trace identification header and time break. The value is positive if time break occurs after the end of header; negative if time break occurs before the end of header. Time break is defined as the intiation pulse that may be recorded on an auxiliary trace of as otherwise specified by the recording system.");
    mmap[SegyTraceHeader::lagTimeB] = FieldDetailInfo("Lag time B","Time in milliseconds between time break and the initiation time of the energy source. May be positive or negative");
    mmap[SegyTraceHeader::delayRecTime] = FieldDetailInfo("Delay recording time","Time in milliseconds beween initiation time of energy source and the time when recording of data samples begins. In SEGY rev 0 this entry was intended for deep-water work if data recording does not start at zero time. The entry can be negative to accommodate negative start times (i.e. data recorded before time zero, presumably as a result of static application to the data trace). If a non-zero value (negative or positive) is recorded in this entry, a comment to that effect should appear in the Textul File Header.");
    mmap[SegyTraceHeader::muteTimeStart] = FieldDetailInfo("Start mute time","Start mute time in milliseconds");
    mmap[SegyTraceHeader::muteTimeEnd] = FieldDetailInfo("End mute time","End mute time in milliseconds");
    mmap[SegyTraceHeader::sampleCount] = FieldDetailInfo("Number of samples in this trace");
    mmap[SegyTraceHeader::sampleInterval] = FieldDetailInfo("Sample interval","Sample interval in microseconds for this trace. The number of bytes in a trace record must be consistent with the number of samples written in the trace header. This is important for all recording media; but it is particularly crucial for the correct processing of SEGY data in disk files.\nIf the fixed length trace flag in bytes 3503-3504 of the Binary File Header is set, the sample interval and number of samples in every trace in the SEGY file must be the save as the values recorded in the Binary File Header. If the fixed length trace flag is not set, the sample interval and number of samples may vary from trace to trace.");
    mmap[SegyTraceHeader::gainType] = FieldDetailInfo("Gain type of field instrumets","1=fixed\n2=binary\n3=floating point\n4...N=optional use");
    mmap[SegyTraceHeader::instrGainCons] = FieldDetailInfo("Instrument gain constant","Instrument gain constant in dB");
    mmap[SegyTraceHeader::instrInitGain] = FieldDetailInfo("Instrument early or initial gain","Instrument early or initial gain in dB");
    mmap[SegyTraceHeader::correlated] = FieldDetailInfo("Correlated","1=no\n2=yes");
    mmap[SegyTraceHeader::sweepFrStart] = FieldDetailInfo("Seep frequency at start","Seep frequency at start in Hz");
    mmap[SegyTraceHeader::sweepFrEnd] = FieldDetailInfo("Seep frequency at end","Seep frequency at start in Hz");
    mmap[SegyTraceHeader::sweepLength] = FieldDetailInfo("Sweep length","Sweep length in milliseconds");
    mmap[SegyTraceHeader::sweepType] = FieldDetailInfo("Sweep type","1=linear\n2=parabolic\n3=exponential\4=other");
    mmap[SegyTraceHeader::sweepTraceTaperLengthStart] = FieldDetailInfo("Sweep trace taper length at start","Sweep trace taper length at start in milliseconds");
    mmap[SegyTraceHeader::sweepTraceTaperLengthEnd] = FieldDetailInfo("Sweep trace taper length at end","Sweep trace taper length at end in milliseconds");
    mmap[SegyTraceHeader::taperType] = FieldDetailInfo("Taper type","1=linear\n2=cos^2\n3=other");
    mmap[SegyTraceHeader::aliasFilterFr] = FieldDetailInfo("Alias filter frequency","Alias filter frequency (Hz), if used");
    mmap[SegyTraceHeader::aliasFilterSlope] = FieldDetailInfo("Alias filter slope","Alias filter slope (dB/octave)");
    mmap[SegyTraceHeader::notchFilterFr] = FieldDetailInfo("Notch filter frequency","Notch filter frequency (Hz), if used");
    mmap[SegyTraceHeader::notchFilterSlope] = FieldDetailInfo("Notch fileter slope","Notch fileter slope (dB/octave)");
    mmap[SegyTraceHeader::lowCutFr] = FieldDetailInfo("Low-cut frequency","Low-cut frequency (Hz), if used");
    mmap[SegyTraceHeader::highCutFr] = FieldDetailInfo("High-cut frequency","High-cut frequency (Hz), if used");
    mmap[SegyTraceHeader::lowCutSlope] = FieldDetailInfo("Low-cut slope","Low-cut slope (db/octave)");
    mmap[SegyTraceHeader::highCutSlope] = FieldDetailInfo("High-cut slope","High-cut slope (db/octave)");
    mmap[SegyTraceHeader::year] = FieldDetailInfo("Year data recorded","The 1975 standard is unclear as to whether this sould be recorded as a 2-digit or a 4-digit year and both have been used. For SEGY revisions beyond rev 0, the year should be recorded as the complete 4-digit Gregorian calendar year (i.e. the year 2001 should be recorded as 2001_10 (7D1_16))");
    mmap[SegyTraceHeader::dayOfYear] = FieldDetailInfo("Day of year","Julian day for GMT and UTC time basis");
    mmap[SegyTraceHeader::hour] = FieldDetailInfo("Hour of daty","24 hour clock");
    mmap[SegyTraceHeader::min] = FieldDetailInfo("Minute of hour");
    mmap[SegyTraceHeader::sec] = FieldDetailInfo("Second of minute");
    mmap[SegyTraceHeader::timeCode] = FieldDetailInfo("Time basis code","1=Local\n2=GMT (Greenwich Mean Time)\n3=Other, should be explained in a user defined stanza in the Extended Textual File Header\n4=UTC (Coordinated Universal Time)");
    mmap[SegyTraceHeader::traceWeightFactor] = FieldDetailInfo("Trace weighting factor","Defined as 2^(-N) volts for the least significant bit");
    mmap[SegyTraceHeader::geophoneRoll] = FieldDetailInfo("Geophone group number of roll switch position one");
    mmap[SegyTraceHeader::geophoneFirstTrace] = FieldDetailInfo("Geophone group number of trace number one within origianl field record");
    mmap[SegyTraceHeader::geophoneLastTrace] = FieldDetailInfo("Grophone group number of last trace within original field record");
    mmap[SegyTraceHeader::gapSize] = FieldDetailInfo("Gap size","Total number of groups dropped");
    mmap[SegyTraceHeader::travel] = FieldDetailInfo("Over travel associated with tape at beginning or end of line","1=down (or behind)\n2=up (or ahead)");
    mmap[SegyTraceHeader::cdpX] = FieldDetailInfo("X coordinate of ensemble position", "X coordinate of ensemble (CDP) position of this trace (scalar in Trace Header bytes 71-72 applies). The coordinate reference system should be identified through an extended header Location Data stanza");
    mmap[SegyTraceHeader::cdpY] = FieldDetailInfo("Y coordinate of ensemble position", "X coordinate of ensemble (CDP) position of this trace (scalar in Trace Header bytes 71-72 applies). The coordinate reference system should be identified through an extended header Location Data stanza");
    mmap[SegyTraceHeader::inlineNumber] = FieldDetailInfo("Inline number","For 3-D poststack data, this field should be used for the in-line number. If one in-line per SEGY file is being recorded, this value should be the same for all traces in the file and the same value will be recorded in bytes 3205-3208 of the Binary File Header.");
    mmap[SegyTraceHeader::xlineNumber] = FieldDetailInfo("Cross-line number","For 3-D poststack data, this field should be used for the cross-line number. This weill typically be the same value as the ensemble (CDP) number in Trace Header bytes 21-24, but this does not have to be the case.");
    mmap[SegyTraceHeader::shotpointNumber] = FieldDetailInfo("Shotpoint number","This is probably only applicable to 2-D poststack data. Note that it is assumed that the shotpoint number refers to the source location nearest to the ensemble (CDP) location for a particular trace . If this is not the case, there should be a commnet in the Textual File Header explaining what the shotpoint number actually refers to.");
    mmap[SegyTraceHeader::shotpointScalar] = FieldDetailInfo("Shotpoint scalar","Scalar to be applied to the shotpoint number in Trace Header bytes 197-200 to give the real value. If positive, scalar is used as a multiplier; if negative as a divisor; if zero the shotpoint number is not scaled (i.e. it is an integer. A typical value will be -10,allowing shotpoint numbers with one decimal digit to the right of the decimal point)");
    mmap[SegyTraceHeader::traceMeasurementUnit] = FieldDetailInfo("Trace value measurement unit","-1=Other (should be described in Data Sample Measurement Units Stanza)\n0=Unknown\n1=Padcal (Pa)\n2=Volts (v)\n3=Millivolts (mV)\n4=Amperes (A)\n5=Meters (m)\n6=Meters per second (m/s)\n7=Meters per second squared (m/s^2)\n8=Newton (N)\n9=Watt (W)");
    mmap[SegyTraceHeader::transductionConstant] = FieldDetailInfo("Transduction Constant","The miltiplicative constant used to convert the Data Trace samples to the Transduction Units (specified in Trace Header bytes 211-212). The constant is encoded as a four-byte, two's complement integer (bytes 205-208) which is the mantissa and a two-byte, two's complement integer (bytes 209-210) which is the power of ten exponent (i.e. Bytes 205-208 * 10**Bytes 209-210).");
    mmap[SegyTraceHeader::transductionUnit] = FieldDetailInfo("Transduction Units","The unit of measurement of the Data Trace samples after they have been multiplied by the Transduction Constant specified in Trace Header bytes 205-210.\n-1=Other (should be described in Data Sample Measurement Units Stanza)\n0=Unknown\n1=Padcal (Pa)\n2=Volts (v)\n3=Millivolts (mV)\n4=Amperes (A)\n5=Meters (m)\n6=Meters per second (m/s)\n7=Meters per second squared (m/s^2)\n8=Newton (N)\n9=Watt (W)");
    mmap[SegyTraceHeader::devId] = FieldDetailInfo("Device/Trace Identifier","The unit number or id number of the device associated with the Data Trace (i.e. 4368 for vibrator serial number 4368 or 20316 for gun 16 on string 3 on vessel 2). This field allow traces to be associated across trace ensembles independently of the trace number.");
    mmap[SegyTraceHeader::timeScalar] = FieldDetailInfo("Scalar to be applied to times","Scalar to be applied to times specified in Trace Header bytes 95-114 to give the true time value in milliseconds. Scalar=1,+10,+100,+1000, or +10000. If positive, scalar is used as a pultiplier; if negative, scalar is used as divisor. A value of zero is assumed to be a scalar value of 1.");
    mmap[SegyTraceHeader::srcType] = FieldDetailInfo("Source Type/Orientation","Defines the type and the orientation of the energy source. The terms vertical, cross-line an in-line refer to the threee axes of an orthogonal coordinate system. The absolute azimuthal orientation o the coordinate system axes can be defined in the Bin Grid Definition Stanza.\n-1 to -n = Other (should be described in Source Type/Orientation stanza)\n0=Unknown\n1=Vibratory - Vertical orientation\n2=Vibratory - Cross-line orentation\n3=Vibratory - In-line orentation\n4=Impulsive - Veretical orentation\n5=Impulsive - Cross-line orientation\n6=impulsive - In-line orientation\n7=Distributed Impulsive - Vertical orentation\n8=Distributed Impulsive - Cross-line orientation\n9=Distributed Impulsive - In-line orentation");
    mmap[SegyTraceHeader::srcEnergyDirection] = FieldDetailInfo("Source Energy Direction with respect ot the source orientation","The positive orientation direction is defined in Bytes 217-218 of the Trace HEader. The energy direction is encoded in tenths of degrees (i.e. 347.8 is encoded as 3478)");
    mmap[SegyTraceHeader::srcMeasurement] = FieldDetailInfo("Sourse Measurement","Describes the source effort used to generate the trace. The measurement can be simple, qualitative measurements such as the total weight of explosive used or the peak air gun pressure or the number of vibrators times the sweep duration. Although these simple measurements are acceptable, it is preferable to use ture measurement units of energy or work.\nThe constant is encoded as a four-byte, two's complement integer (bytes 225-228) which is the mantissa and a two-byte, two's complement integer (bytes 209-230) which is the power of ten exponent (i.e. Bytes 225-228 * 10 **Bytes 229-230)");
    mmap[SegyTraceHeader::srcMeasurementUnit] = FieldDetailInfo("Source Measurement Unit","The unit used for the Source Measurement, Trace header bytes 225-230.\n-1=Other (should be described in Source Measurement Unit stanza)\n0=Unknown\n1=Joule (J)\n2=Kilowatt (kW)\n3=Pascal (Pa)\n4=Bar (Bar)\n4=Bar-meter (Bar-m)\n5=Newton (N)\n6=Kilograms (kg)");
    return mmap;
}

const std::map < std::string, FieldDetailInfo> SegyTraceHeader::detailInfo = initDetailInfo();

static std::vector<std::string> getFieldNamesFromMap(const std::map < std::string, FieldDetailInfo> fm){
    std::vector<std::string> names;
    for (std::map < std::string, FieldDetailInfo>::const_iterator it = fm.cbegin(); it != fm.cend(); ++it)
        names.push_back(it->first);
    return names;
}

const std::vector<std::string> SegyTraceHeader::fieldNames = getFieldNamesFromMap(SegyTraceHeader::detailInfo);
