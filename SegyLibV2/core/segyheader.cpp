#include "segyheader.h"

SegyHeader::SegyHeader(){
	for (std::map < std::string, FieldDetailInfo>::const_iterator it = detailInfo.begin(); it != detailInfo.end(); ++it)
		fieldValue[it->first] = 0;
}

boost::any SegyHeader::get(const std::string &fieldName) const{
    if (fieldValue.count(fieldName) < 1)
        throw;
    return fieldValue.find(fieldName)->second;
}

void SegyHeader::set(const std::string &fieldName, boost::any value){
    fieldValue[fieldName]=boost::any_cast<int>(value);
}

const std::vector<std::string>& SegyHeader::getFieldNames()const{
	return fieldNames;
}

static std::map < std::string, FieldMappingInfo> initMapperInfo(){
	std::map<std::string, FieldMappingInfo> mmap;
	mmap["jobId"] = FieldMappingInfo(0, 4);
	mmap["lineNumber"] = FieldMappingInfo(4, 4);
	mmap["reelNumber"] = FieldMappingInfo(8, 4);
	mmap["numTracesPerRecord"] = FieldMappingInfo(12, 2);
	mmap["numOfAxualiryTracesPerRecord"] = FieldMappingInfo(14, 2);
	mmap["sampleInterval"] = FieldMappingInfo(16, 2);
	mmap["sampleIntervalOrigin"] = FieldMappingInfo(18, 2);
	mmap["sampleCount"] = FieldMappingInfo(20, 2);
	mmap["sampleCountOrigin"] = FieldMappingInfo(22, 2);
	mmap["type"] = FieldMappingInfo(24, 2);
	mmap["cdpFold"] = FieldMappingInfo(26, 2);
	mmap["traceSorting"] = FieldMappingInfo(28, 2);
	mmap["verticalSum"] = FieldMappingInfo(30, 2);
	mmap["sweepFrStart"] = FieldMappingInfo(32, 2);
	mmap["sweepFrEnd"] = FieldMappingInfo(34, 2);
	mmap["sweepLength"] = FieldMappingInfo(36, 2);
	mmap["sweepType"] = FieldMappingInfo(38, 2);
	mmap["traceNumOfSweepChannel"] = FieldMappingInfo(40, 2);
	mmap["sweepTaperLengthStart"] = FieldMappingInfo(42, 2);
	mmap["sweepTaperLengthEnd"] = FieldMappingInfo(44, 2);
	mmap["taperType"] = FieldMappingInfo(46, 2);
	mmap["corrDataTraces"] = FieldMappingInfo(48, 2);
	mmap["binGainRecovery"] = FieldMappingInfo(50, 2);
	mmap["ampRecoveryMethod"] = FieldMappingInfo(52, 2);
	mmap["measurementSys"] = FieldMappingInfo(54, 2);
	mmap["impSignal"] = FieldMappingInfo(56, 2);
	mmap["polarityCode"] = FieldMappingInfo(58, 2);
    mmap["segyFormat"]=FieldMappingInfo(300,2);
    mmap["fixedLength"]=FieldMappingInfo(302,2);
	return mmap;
}

const std::map < std::string, FieldMappingInfo> SegyHeader::mapperInfo = initMapperInfo();

static std::map < std::string, FieldDetailInfo> initDetailInfo(){
	std::map<std::string, FieldDetailInfo> mmap;
    mmap["jobId"] = FieldDetailInfo("Job identification number","Job identification number");
    mmap["lineNumber"] = FieldDetailInfo("Line number","For 3-D poststack data, this will typically contain the in-line number");
    mmap["reelNumber"] = FieldDetailInfo("Reel number","Reel number");
    mmap["numTracesPerRecord"] = FieldDetailInfo("Number of data traces per ensemble","Number of data traces per ensemble (Mandatory for prestack data)");
    mmap["numOfAxualiryTracesPerRecord"] = FieldDetailInfo("Number of auxiliary traces per ensemble","Number of auxiliary traces per ensemble (Mandatory for prestack data)");
    mmap["sampleInterval"] = FieldDetailInfo("Sample interval in microseconds","Sample interval in microseconds (Mandatory for prestack data)");
    mmap["sampleIntervalOrigin"] = FieldDetailInfo("Sample interval in microseconds of original field recording","Sample interval in microseconds of original field recording");
    mmap["sampleCount"] = FieldDetailInfo("Number of samples per data trace","Number of samples per data trace (Mandatory for all types of data)\nThe sample interval and number of samples in the Binary File Header should be for the primary set of seismic data traces in the file.");
    mmap["sampleCountOrigin"] = FieldDetailInfo("Number of samples per data trace for original field recording","Number of samples per data trace for original field recording");
    mmap["type"] = FieldDetailInfo("Data sample format code","Data sample format code (Mandatory for all data)\n1=4-byte IBM floating-point\n2=4-byte, two's complement integer\n3=2-byte, two's complement integer\n4=4-byte fixed-pointwith gain (obsolete)\n5=4-byte IEEE floating-point\n6=Not currently used\n7=Not currently used\n8=1-byte, two's complement integer");
    mmap["cdpFold"] = FieldDetailInfo("Ensemble fold","The expected number of data taces per trace ensemble (e.g. the CMP fold). Highly recommended for all types of data.");
    mmap["traceSorting"] = FieldDetailInfo("Trace sorting code","Trace sorting code (i.e. type of ensemble):\n-1=Other (should be explained in user Extended Textual File Header stanza\n0=Unknown\n1=As recorded (no sorting)\n2=CDP ensemble\n3=Single fold continuous profile\n4=Horizontally stacked\n5=Common source point\n6=Common receiver point\n7=Common offset point\n8=Common mid-point\n9=Common conversion point");
    mmap["verticalSum"] = FieldDetailInfo("Vertical sum code");
    mmap["sweepFrStart"] = FieldDetailInfo("Sweep frequency at start","Sweep frequency at start (Hz)");
    mmap["sweepFrEnd"] = FieldDetailInfo("Sweep frequency at end","Sweep frequency at end (Hz)");
    mmap["sweepLength"] = FieldDetailInfo("Sweep length","Sweep length (miliseconds)");
    mmap["sweepType"] = FieldDetailInfo("Sweep type code","Sweep type code:\n1=linear\n2=parabolic\n3=exponential\n4=other");
    mmap["traceNumOfSweepChannel"] = FieldDetailInfo("Trace number of sweep channel");
    mmap["sweepTaperLengthStart"] = FieldDetailInfo("Sweep trace taper length at start","Sweep trace taper length in milliseconds at start if tapered (the taper starts at zero time and is effective fo tis length)");
    mmap["sweepTaperLengthEnd"] = FieldDetailInfo("Sweep trace taper length at end","Sweep trace taper length in milliseconds at end (the ending taper start at seep length minus the taper length at end)");
    mmap["taperType"] = FieldDetailInfo("Taper type","Taper type:\n1=linear\n2=cos^2\n3=other");
    mmap["corrDataTraces"] = FieldDetailInfo("Correlated data traces","Correlated data traces:\n1=no\n2=yes");
    mmap["binGainRecovery"] = FieldDetailInfo("Binary gain recovered","Binary gain recovered:\n1=yes\n2=no");
    mmap["ampRecoveryMethod"] = FieldDetailInfo("Amplitude recovery metod","Amplitued recovery method:\n1=none\n2=spherical divergence\n3=AGC\n4=other");
    mmap["measurementSys"] = FieldDetailInfo("Measurement system","Measurement system (Highly recommended for all types of data). If Location Data stanzas are included in the file, this entry must agree with the Location Data stanza. If there is a disagreement, the last Location Data stanza i the controlling autority.\n1=Meters\n2=Feet");
    mmap["impSignal"] = FieldDetailInfo("Impulse signal polarity","1=Increase in pressure or upward geophone case movement gives negative number on tape\n2=Increase in pressure or upward geophone case movement gives positive number on tape.");
    mmap["polarityCode"] = FieldDetailInfo("Vibratory polarity code","Seismic signal lags pilot signal by:\n1=337.5 to 22.5\n2=22.5 to 67.5\n3=67.5 to 112.5\n4=112.5 to 157.5\n5=157.5 to 202.5\n6=202.5 to 247.5\n7=247.5 to 292.5\n8=292.5 to 337.5");
    mmap["segyFormat"]=FieldDetailInfo("SEGY Format Revision Number","This is a 16-bit unsigned value with a Q-point between the first and second bytes. Thus for SEGY Revision 1.0, as difined in this document, this will be recorded as 0100_16. This field is mandatory for all version of SEGY, although a value of zero indicates \"traditional\" SEGY conforming to the 1975 standard.");
    mmap["fixedLength"]=FieldDetailInfo("Fixed length trace flag","A value of one indicates that all trace3s in this SEGY file are guaranteed to have the same sample interval and number of samples, as specified in Textual File Header bytes 3217-3218 and 3221-3222. A value of zero indicates that the length of the tracs in the file may vary and the number of sample in bytes 115-116 of the Trace Header must be examined to determine the actual lnegth of each trace. This field is mandatory for all version of SEGY, although a value of zero indicates \"traditional\" SEGY conforming to the 1975 standard.");
	return mmap;
}

const std::map < std::string, FieldDetailInfo> SegyHeader::detailInfo=initDetailInfo();


static std::vector<std::string> getFieldNamesFromMap(const std::map < std::string, FieldDetailInfo> fm){
	std::vector<std::string> names;
	for (std::map < std::string, FieldDetailInfo>::const_iterator it = fm.cbegin(); it != fm.cend(); ++it)
		names.push_back(it->first);
	return names;
}

const std::vector<std::string> SegyHeader::fieldNames = getFieldNamesFromMap(SegyHeader::detailInfo);
