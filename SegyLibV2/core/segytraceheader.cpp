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

static std::map < std::string, FieldMappingInfo> initMapperInfo(){
	std::map<std::string, FieldMappingInfo> mmap;
	mmap["traceNumberLine"] = FieldMappingInfo(0, 4);
	mmap["traceNumberReel"] = FieldMappingInfo(4, 4);
	mmap["originalFieldRecordNumber"] = FieldMappingInfo(8, 4);
	mmap["traceSeqNumberFR"] = FieldMappingInfo(12, 4);
	mmap["sourceNumber"] = FieldMappingInfo(16, 4);
	mmap["cdpNumber"] = FieldMappingInfo(20, 4);
	mmap["traceSeqNumberCDP"] = FieldMappingInfo(24, 4);
	mmap["traceIdCode"] = FieldMappingInfo(28, 2);
	mmap["numVerticalSumTraces"] = FieldMappingInfo(30, 2);
	mmap["numHorizontalStackedTraces"] = FieldMappingInfo(32, 2);
	mmap["dataUse"] = FieldMappingInfo(34, 2);
	mmap["distSrcRecv"] = FieldMappingInfo(36, 4);
	mmap["recvElevation"] = FieldMappingInfo(40, 4);
	mmap["surfElevation"] = FieldMappingInfo(44, 4);
	mmap["depthBelowSurf"] = FieldMappingInfo(48, 4);
	mmap["datumElevationRecv"] = FieldMappingInfo(52, 4);
	mmap["datumElevationSrc"] = FieldMappingInfo(56, 4);
	mmap["waterDepthSrc"] = FieldMappingInfo(60, 4);
	mmap["waterDepthGroup"] = FieldMappingInfo(64, 4);
	mmap["elevScalar"] = FieldMappingInfo(68, 2);
	mmap["coordScalar"] = FieldMappingInfo(70, 2);
	mmap["srcCoordX"] = FieldMappingInfo(72, 4);
	mmap["srcCoordY"] = FieldMappingInfo(76, 4);
	mmap["recvGroupCoordX"] = FieldMappingInfo(80, 4);
	mmap["recvGroupCoordY"] = FieldMappingInfo(84, 4);
	mmap["coordUnit"] = FieldMappingInfo(88, 2);
	mmap["weatheringVelocity"] = FieldMappingInfo(90, 2);
	mmap["subWeatheringVelocity"] = FieldMappingInfo(92, 2);
	mmap["upholeTimeSrc"] = FieldMappingInfo(94, 2);
	mmap["upholeTimeRsvGroup"] = FieldMappingInfo(96, 2);
	mmap["srcStatCorrection"] = FieldMappingInfo(98, 2);
	mmap["rcvGroupStatCorrection"] = FieldMappingInfo(100, 2);
	mmap["totalStaticApplied"] = FieldMappingInfo(102, 2);
	mmap["lagTimeA"] = FieldMappingInfo(104, 2);
	mmap["lagTimeB"] = FieldMappingInfo(106, 2);
	mmap["delayRecTime"] = FieldMappingInfo(108, 2);
	mmap["muteTimeStart"] = FieldMappingInfo(110, 2);
	mmap["muteTimeEnd"] = FieldMappingInfo(112, 2);
	mmap["sampleCount"] = FieldMappingInfo(114, 2);
	mmap["sampleInterval"] = FieldMappingInfo(116, 2);
	mmap["gainType"] = FieldMappingInfo(118, 2);
	mmap["instrGainCons"] = FieldMappingInfo(120, 2);
	mmap["instrInitGain"] = FieldMappingInfo(122, 2);
	mmap["correlated"] = FieldMappingInfo(124, 2);
	mmap["sweepFrStart"] = FieldMappingInfo(126, 2);
	mmap["sweepFrEnd"] = FieldMappingInfo(128, 2);
	mmap["sweepLength"] = FieldMappingInfo(130, 2);
	mmap["sweepType"] = FieldMappingInfo(132, 2);
	mmap["sweepTraceTaperLengthStart"] = FieldMappingInfo(134, 2);
	mmap["sweepTraceTaperLengthEnd"] = FieldMappingInfo(136, 2);
	mmap["taperType"] = FieldMappingInfo(138, 2);
	mmap["aliasFilterFr"] = FieldMappingInfo(140, 2);
	mmap["aliasFilterSlope"] = FieldMappingInfo(142, 2);
	mmap["notchFilterFr"] = FieldMappingInfo(144, 2);
	mmap["notchFilterSlope"] = FieldMappingInfo(146, 2);
	mmap["lowCutFr"] = FieldMappingInfo(148, 2);
	mmap["highCutFr"] = FieldMappingInfo(150, 2);
	mmap["lowCutSlope"] = FieldMappingInfo(152, 2);
	mmap["highCutSlope"] = FieldMappingInfo(154, 2);
	mmap["year"] = FieldMappingInfo(156, 2);
	mmap["dayOfYear"] = FieldMappingInfo(158, 2);
	mmap["hour"] = FieldMappingInfo(160, 2);
	mmap["min"] = FieldMappingInfo(162, 2);
	mmap["sec"] = FieldMappingInfo(164, 2);
	mmap["timeCode"] = FieldMappingInfo(166, 2);
	mmap["traceWeightFactor"] = FieldMappingInfo(168, 2);
    mmap["geophoneRoll"] = FieldMappingInfo(170, 2);
    mmap["geophoneFirstTrace"] = FieldMappingInfo(172, 2);
    mmap["geophoneLastTrace"] = FieldMappingInfo(174, 2);
    mmap["gapSize"] = FieldMappingInfo(176, 2);
    mmap["travel"] = FieldMappingInfo(178, 2);
    mmap["cdpX"] = FieldMappingInfo(180, 4);
	mmap["cdpY"] = FieldMappingInfo(184, 4);
	mmap["inlineNumber"] = FieldMappingInfo(188, 4);
	mmap["xlineNumber"] = FieldMappingInfo(192, 4);
    mmap["shotpointNumber"] = FieldMappingInfo(196, 4);
    mmap["shotpointScalar"] = FieldMappingInfo(200, 2);
    mmap["traceMeasurementUnit"] = FieldMappingInfo(202, 2);
    mmap["transductionConstant"] = FieldMappingInfo(204, 6);
    mmap["transductionUnit"] = FieldMappingInfo(210, 2);
    mmap["devId"] = FieldMappingInfo(212, 2);
    mmap["timeScalar"] = FieldMappingInfo(214, 2);
    mmap["srcType"] = FieldMappingInfo(216, 2);
    mmap["srcEnergyDirection"] = FieldMappingInfo(218, 6);
    mmap["srcMeasurement"] = FieldMappingInfo(224, 6);
    mmap["srcMeasurementUnit"] = FieldMappingInfo(230, 2);
	return mmap;
}

const std::map < std::string, FieldMappingInfo> SegyTraceHeader::mapperInfo = initMapperInfo();

static std::map < std::string, FieldDetailInfo> initDetailInfo(){
	std::map<std::string, FieldDetailInfo> mmap;
    mmap["traceNumberLine"] = FieldDetailInfo("Trace sequence within line","Numbers continue to increase if the same line continues across multiple SEGY files (Highly recommended for all types of data)");
    mmap["traceNumberReel"] = FieldDetailInfo("Trace sequence number within SEGY file","Each file starts with trace sequence one");
    mmap["originalFieldRecordNumber"] = FieldDetailInfo("Original field record number");
    mmap["traceSeqNumberFR"] = FieldDetailInfo("Trace number within the origina field record");
    mmap["sourceNumber"] = FieldDetailInfo("Energy source point number","Used when more than one record occurs at the same effective surface location. It is recommended that the new entry defined in Trace Header bytes 197-202 be used for shotpoint number.");
    mmap["cdpNumber"] = FieldDetailInfo("Ensemble number","Ensemble number (i.e. CDP, CMP, CRP, etc)");
    mmap["traceSeqNumberCDP"] = FieldDetailInfo("Trace number within the ensemble","Each ensemble starts with trace number one");
    mmap["traceIdCode"] = FieldDetailInfo("Trace identification code","-1=Other\n0=Unknown\n1=Seismic data\n2=Dead\n3=Dummy\n4=Time break\n5=Uphole\n6=Sweep\n7=Timing\n8=Waterbreak\n9=Near-field hun signature\n10=Far-field gun signature\n11=Seismic pressure sensor\n12=Multicomponent seismic sensor - Vertical component\n13=Multicomponent seismic sensor - Cross-line component\n14=Multicomponent seismic sensor - In-line component\n15=Rotated multicomponent seismic sensor - Vertical component\n16=Rotated multicomponent seismic sensor - Transverse component\n17=Rotated multicomponent seismic sensor - Radial component\n18=Vibrator reaction mass\n19=Vibrator baseplate\n20=Vibrator estimated ground force\n21=Vibrator reference\n22=Time-velocity pairs");
    mmap["numVerticalSumTraces"] = FieldDetailInfo("Number of vertically summed traces","Number of vertically summed traces yielding this trace (1 is one trace, 2 is two summed traces, etc.)");
    mmap["numHorizontalStackedTraces"] = FieldDetailInfo("Number of horizontally stacked traces","Number of horizontally stacked traces yielding this trace (1 is one trace, 2 is two stacked traces, etc.)");
    mmap["dataUse"] = FieldDetailInfo("Data use","1=Production\n2=Test");
    mmap["distSrcRecv"] = FieldDetailInfo("","Distance from center of the source point to the center of the receiver group (negative if opposite to direction in which line is shot)");
    mmap["recvElevation"] = FieldDetailInfo("Receiver group elevation","All elevations above the Vertucal datum are positive and below are negative");
    mmap["surfElevation"] = FieldDetailInfo("Surface elevation at source");
    mmap["depthBelowSurf"] = FieldDetailInfo("Source depth below surface");
    mmap["datumElevationRecv"] = FieldDetailInfo("Datum elevation at receiver group");
    mmap["datumElevationSrc"] = FieldDetailInfo("Datum elevation at source");
    mmap["waterDepthSrc"] = FieldDetailInfo("Water depth at source");
    mmap["waterDepthGroup"] = FieldDetailInfo("Water depth at group");
    mmap["elevScalar"] = FieldDetailInfo("Elevation scalar","Scalar to be applied to all elevations and depths specified in Trace Header bytes 41-68 to give the real value. Scalar=1,+10,+100,+1000, or +10000. If positive, scalar is used as a multiplier; if negative, scalar is used as a divisor.");
    mmap["coordScalar"] = FieldDetailInfo("Coordinate scalar","Scalar to be applied to all coordinates specified in Trace Header bytes 73-88 and to bytes Trace Header 181-188 to give the real value. Scalar=1,+10,+100,+1000, or +10000. If positive, scalar is used as a multiplier; if negative, scalar is used as divisor.");
    mmap["srcCoordX"] = FieldDetailInfo("Source coordinate - X");
    mmap["srcCoordY"] = FieldDetailInfo("Source coordinate - Y");
    mmap["recvGroupCoordX"] = FieldDetailInfo("Group coordinate - X");
    mmap["recvGroupCoordY"] = FieldDetailInfo("Group coordinate - Y");
    mmap["coordUnit"] = FieldDetailInfo("Coordinate units","1=Length (meters or feet)\n2=Seconds of arc\n3=Decimal degrees\n4=Degrees, minutes, seconds (DMS)");
    mmap["weatheringVelocity"] = FieldDetailInfo("Weathering velocity");
    mmap["subWeatheringVelocity"] = FieldDetailInfo("Subweathering velocity");
    mmap["upholeTimeSrc"] = FieldDetailInfo("Uphole time at source in milliseconds");
    mmap["upholeTimeRsvGroup"] = FieldDetailInfo("Uphole time at group in milliseconds");
    mmap["srcStatCorrection"] = FieldDetailInfo("Source static correction in milliseconds");
    mmap["rcvGroupStatCorrection"] = FieldDetailInfo("Group static correction in milliseconds");
    mmap["totalStaticApplied"] = FieldDetailInfo("Total static applied in milliseconds","Zero if no static has been applied");
    mmap["lagTimeA"] = FieldDetailInfo("Lag time A","Time in milliseconds beween end of 240-byte trace identification header and time break. The value is positive if time break occurs after the end of header; negative if time break occurs before the end of header. Time break is defined as the intiation pulse that may be recorded on an auxiliary trace of as otherwise specified by the recording system.");
    mmap["lagTimeB"] = FieldDetailInfo("Lag time B","Time in milliseconds between time break and the initiation time of the energy source. May be positive or negative");
    mmap["delayRecTime"] = FieldDetailInfo("Delay recording time","Time in milliseconds beween initiation time of energy source and the time when recording of data samples begins. In SEGY rev 0 this entry was intended for deep-water work if data recording does not start at zero time. The entry can be negative to accommodate negative start times (i.e. data recorded before time zero, presumably as a result of static application to the data trace). If a non-zero value (negative or positive) is recorded in this entry, a comment to that effect should appear in the Textul File Header.");
    mmap["muteTimeStart"] = FieldDetailInfo("Start mute time","Start mute time in milliseconds");
    mmap["muteTimeEnd"] = FieldDetailInfo("End mute time","End mute time in milliseconds");
    mmap["sampleCount"] = FieldDetailInfo("Number of samples in this trace");
    mmap["sampleInterval"] = FieldDetailInfo("Sample interval","Sample interval in microseconds for this trace. The number of bytes in a trace record must be consistent with the number of samples written in the trace header. This is important for all recording media; but it is particularly crucial for the correct processing of SEGY data in disk files.\nIf the fixed length trace flag in bytes 3503-3504 of the Binary File Header is set, the sample interval and number of samples in every trace in the SEGY file must be the save as the values recorded in the Binary File Header. If the fixed length trace flag is not set, the sample interval and number of samples may vary from trace to trace.");
    mmap["gainType"] = FieldDetailInfo("Gain type of field instrumets","1=fixed\n2=binary\n3=floating point\n4...N=optional use");
    mmap["instrGainCons"] = FieldDetailInfo("Instrument gain constant","Instrument gain constant in dB");
    mmap["instrInitGain"] = FieldDetailInfo("Instrument early or initial gain","Instrument early or initial gain in dB");
    mmap["correlated"] = FieldDetailInfo("Correlated","1=no\n2=yes");
    mmap["sweepFrStart"] = FieldDetailInfo("Seep frequency at start","Seep frequency at start in Hz");
    mmap["sweepFrEnd"] = FieldDetailInfo("Seep frequency at end","Seep frequency at start in Hz");
    mmap["sweepLength"] = FieldDetailInfo("Sweep length","Sweep length in milliseconds");
    mmap["sweepType"] = FieldDetailInfo("Sweep type","1=linear\n2=parabolic\n3=exponential\4=other");
    mmap["sweepTraceTaperLengthStart"] = FieldDetailInfo("Sweep trace taper length at start","Sweep trace taper length at start in milliseconds");
    mmap["sweepTraceTaperLengthEnd"] = FieldDetailInfo("Sweep trace taper length at end","Sweep trace taper length at end in milliseconds");
    mmap["taperType"] = FieldDetailInfo("Taper type","1=linear\n2=cos^2\n3=other");
    mmap["aliasFilterFr"] = FieldDetailInfo("Alias filter frequency","Alias filter frequency (Hz), if used");
    mmap["aliasFilterSlope"] = FieldDetailInfo("Alias filter slope","Alias filter slope (dB/octave)");
    mmap["notchFilterFr"] = FieldDetailInfo("Notch filter frequency","Notch filter frequency (Hz), if used");
    mmap["notchFilterSlope"] = FieldDetailInfo("Notch fileter slope","Notch fileter slope (dB/octave)");
    mmap["lowCutFr"] = FieldDetailInfo("Low-cut frequency","Low-cut frequency (Hz), if used");
    mmap["highCutFr"] = FieldDetailInfo("High-cut frequency","High-cut frequency (Hz), if used");
    mmap["lowCutSlope"] = FieldDetailInfo("Low-cut slope","Low-cut slope (db/octave)");
    mmap["highCutSlope"] = FieldDetailInfo("High-cut slope","High-cut slope (db/octave)");
    mmap["year"] = FieldDetailInfo("Year data recorded","The 1975 standard is unclear as to whether this sould be recorded as a 2-digit or a 4-digit year and both have been used. For SEGY revisions beyond rev 0, the year should be recorded as the complete 4-digit Gregorian calendar year (i.e. the year 2001 should be recorded as 2001_10 (7D1_16))");
    mmap["dayOfYear"] = FieldDetailInfo("Day of year","Julian day for GMT and UTC time basis");
    mmap["hour"] = FieldDetailInfo("Hour of daty","24 hour clock");
    mmap["min"] = FieldDetailInfo("Minute of hour");
    mmap["sec"] = FieldDetailInfo("Second of minute");
    mmap["timeCode"] = FieldDetailInfo("Time basis code","1=Local\n2=GMT (Greenwich Mean Time)\n3=Other, should be explained in a user defined stanza in the Extended Textual File Header\n4=UTC (Coordinated Universal Time)");
    mmap["traceWeightFactor"] = FieldDetailInfo("Trace weighting factor","Defined as 2^(-N) volts for the least significant bit");
    mmap["geophoneRoll"] = FieldDetailInfo("Geophone group number of roll switch position one");
    mmap["geophoneFirstTrace"] = FieldDetailInfo("Geophone group number of trace number one within origianl field record");
    mmap["geophoneLastTrace"] = FieldDetailInfo("Grophone group number of last trace within original field record");
    mmap["gapSize"] = FieldDetailInfo("Gap size","Total number of groups dropped");
    mmap["travel"] = FieldDetailInfo("Over travel associated with tape at beginning or end of line","1=down (or behind)\n2=up (or ahead)");
    mmap["cdpX"] = FieldDetailInfo("X coordinate of ensemble position", "X coordinate of ensemble (CDP) position of this trace (scalar in Trace Header bytes 71-72 applies). The coordinate reference system should be identified through an extended header Location Data stanza");
    mmap["cdpY"] = FieldDetailInfo("Y coordinate of ensemble position", "X coordinate of ensemble (CDP) position of this trace (scalar in Trace Header bytes 71-72 applies). The coordinate reference system should be identified through an extended header Location Data stanza");
    mmap["inlineNumber"] = FieldDetailInfo("Inline number","For 3-D poststack data, this field should be used for the in-line number. If one in-line per SEGY file is being recorded, this value should be the same for all traces in the file and the same value will be recorded in bytes 3205-3208 of the Binary File Header.");
    mmap["xlineNumber"] = FieldDetailInfo("Cross-line number","For 3-D poststack data, this field should be used for the cross-line number. This weill typically be the same value as the ensemble (CDP) number in Trace Header bytes 21-24, but this does not have to be the case.");

    mmap["shotpointNumber"] = FieldDetailInfo("Shotpoint number","This is probably only applicable to 2-D poststack data. Note that it is assumed that the shotpoint number refers to the source location nearest to the ensemble (CDP) location for a particular trace . If this is not the case, there should be a commnet in the Textual File Header explaining what the shotpoint number actually refers to.");
    mmap["shotpointScalar"] = FieldDetailInfo("Shotpoint scalar","Scalar to be applied to the shotpoint number in Trace Header bytes 197-200 to give the real value. If positive, scalar is used as a multiplier; if negative as a divisor; if zero the shotpoint number is not scaled (i.e. it is an integer. A typical value will be -10,allowing shotpoint numbers with one decimal digit to the right of the decimal point)");
    mmap["traceMeasurementUnit"] = FieldDetailInfo("Trace value measurement unit","-1=Other (should be described in Data Sample Measurement Units Stanza)\n0=Unknown\n1=Padcal (Pa)\n2=Volts (v)\n3=Millivolts (mV)\n4=Amperes (A)\n5=Meters (m)\n6=Meters per second (m/s)\n7=Meters per second squared (m/s^2)\n8=Newton (N)\n9=Watt (W)");
    mmap["transductionConstant"] = FieldDetailInfo("Transduction Constant","The miltiplicative constant used to convert the Data Trace samples to the Transduction Units (specified in Trace Header bytes 211-212). The constant is encoded as a four-byte, two's complement integer (bytes 205-208) which is the mantissa and a two-byte, two's complement integer (bytes 209-210) which is the power of ten exponent (i.e. Bytes 205-208 * 10**Bytes 209-210).");
    mmap["transductionUnit"] = FieldDetailInfo("Transduction Units","The unit of measurement of the Data Trace samples after they have been multiplied by the Transduction Constant specified in Trace Header bytes 205-210.\n-1=Other (should be described in Data Sample Measurement Units Stanza)\n0=Unknown\n1=Padcal (Pa)\n2=Volts (v)\n3=Millivolts (mV)\n4=Amperes (A)\n5=Meters (m)\n6=Meters per second (m/s)\n7=Meters per second squared (m/s^2)\n8=Newton (N)\n9=Watt (W)");
    mmap["devId"] = FieldDetailInfo("Device/Trace Identifier","The unit number or id number of the device associated with the Data Trace (i.e. 4368 for vibrator serial number 4368 or 20316 for gun 16 on string 3 on vessel 2). This field allow traces to be associated across trace ensembles independently of the trace number.");
    mmap["timeScalar"] = FieldDetailInfo("Scalar to be applied to times","Scalar to be applied to times specified in Trace Header bytes 95-114 to give the true time value in milliseconds. Scalar=1,+10,+100,+1000, or +10000. If positive, scalar is used as a pultiplier; if negative, scalar is used as divisor. A value of zero is assumed to be a scalar value of 1.");
    mmap["srcType"] = FieldDetailInfo("Source Type/Orientation","Defines the type and the orientation of the energy source. The terms vertical, cross-line an in-line refer to the threee axes of an orthogonal coordinate system. The absolute azimuthal orientation o the coordinate system axes can be defined in the Bin Grid Definition Stanza.\n-1 to -n = Other (should be described in Source Type/Orientation stanza)\n0=Unknown\n1=Vibratory - Vertical orientation\n2=Vibratory - Cross-line orentation\n3=Vibratory - In-line orentation\n4=Impulsive - Veretical orentation\n5=Impulsive - Cross-line orientation\n6=impulsive - In-line orientation\n7=Distributed Impulsive - Vertical orentation\n8=Distributed Impulsive - Cross-line orientation\n9=Distributed Impulsive - In-line orentation");
    mmap["srcEnergyDirection"] = FieldDetailInfo("Source Energy Direction with respect ot the source orientation","The positive orientation direction is defined in Bytes 217-218 of the Trace HEader. The energy direction is encoded in tenths of degrees (i.e. 347.8 is encoded as 3478)");
    mmap["srcMeasurement"] = FieldDetailInfo("Sourse Measurement","Describes the source effort used to generate the trace. The measurement can be simple, qualitative measurements such as the total weight of explosive used or the peak air gun pressure or the number of vibrators times the sweep duration. Although these simple measurements are acceptable, it is preferable to use ture measurement units of energy or work.\nThe constant is encoded as a four-byte, two's complement integer (bytes 225-228) which is the mantissa and a two-byte, two's complement integer (bytes 209-230) which is the power of ten exponent (i.e. Bytes 225-228 * 10 **Bytes 229-230)");
    mmap["srcMeasurementUnit"] = FieldDetailInfo("Source Measurement Unit","The unit used for the Source Measurement, Trace header bytes 225-230.\n-1=Other (should be described in Source Measurement Unit stanza)\n0=Unknown\n1=Joule (J)\n2=Kilowatt (kW)\n3=Pascal (Pa)\n4=Bar (Bar)\n4=Bar-meter (Bar-m)\n5=Newton (N)\n6=Kilograms (kg)");
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
