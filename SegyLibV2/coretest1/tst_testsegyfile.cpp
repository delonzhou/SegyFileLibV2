#include <QString>
#include <QtTest>

#include "segyfile.h"
#include "segyheader.h"
#include "sufile.h"
#include <memory>
#include <random>
#include <cmath>

#define VERYSMALL  (1.0E-150)
#define EPSILON    (1.0E-6)
bool isEqual(double a, double b)
{
    double absDiff = fabs(a - b);
    if (absDiff < VERYSMALL)
    {
        return true;
    }

    double maxAbs  = std::max(fabs(a),fabs(b));
    return (absDiff/maxAbs) < EPSILON;
}

class TestSegyFile : public QObject
{
    Q_OBJECT

public:
    TestSegyFile();

private Q_SLOTS:
    void testCase1();
    void testCase2();
};

TestSegyFile::TestSegyFile()
{
}

void TestSegyFile::testCase1()
{
    size_t sampleCount=100;
    size_t traceCount=1000;
    SegyHeader sh;
    sh.set("sampleInterval",2000);
    sh.set("sampleCount",static_cast<int>(sampleCount));
    sh.set("type",static_cast<int>(FORMAT_IBM));
    std::shared_ptr<SegyFile<double> > sf(SegyFile<double>::createSegy("test.sgy",0,sh,ENDIAN_BIG));

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-1000.0, 1000.0);

    std::vector<std::vector<double> > traces;

    for(size_t i=0;i<traceCount;++i){
        std::vector<double> trace;
        for(size_t j=0;j<sampleCount;++j){
            trace.push_back(dist(mt));
        }
        sf->setTrace(i,trace);
        traces.push_back(trace);
    }

    sf->closeFile();
    sf.reset();

    SegyFile<double> sf2("test.sgy","r",FieldMapper(),FieldMapper(),ENDIAN_BIG);

    for(size_t i=0;i<traceCount;++i){
        bool res=true;
        auto sftrace=sf2.getTrace(i);
        auto trace=traces[i];
        for(size_t j=0;j<trace.size();++j){
            double a=trace[j];
            double b=sftrace->at(j);
            res=res&isEqual(trace[j],sftrace->at(j));
        }
        QCOMPARE(res, true);
    }

}

void TestSegyFile::testCase2()
{
    size_t sampleCount=100;
    size_t traceCount=1000;
    std::shared_ptr<SuFile<double> > sf(SuFile<double>::createSu("test.su",sampleCount,FORMAT_IBM,ENDIAN_BIG));

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-1000.0, 1000.0);

    SuTraceHeader sth;
    sth.set("sampleCount",static_cast<int>(sampleCount));
    sth.set("sampleInterval",1000);

    std::vector<std::vector<double> > traces;

    for(size_t i=0;i<traceCount;++i){
        std::vector<double> trace;
        for(size_t j=0;j<sampleCount;++j){
            trace.push_back(dist(mt));
        }
        sf->setTrace(i,trace);
        sf->setTraceHeader(i,sth);
        traces.push_back(trace);
    }

    sf->closeFile();
    sf.reset();

    SuFile<double> sf2("test.su",sampleCount,"r",FieldMapper(),FORMAT_IBM,ENDIAN_BIG);

    for(size_t i=0;i<traceCount;++i){
        bool res=true;
        auto sftrace=sf2.getTrace(i);
        auto trace=traces[i];
        for(size_t j=0;j<trace.size();++j){
            double a=trace[j];
            double b=sftrace->at(j);
            res=res&isEqual(trace[j],sftrace->at(j));
        }
        QCOMPARE(res, true);
    }

}

QTEST_APPLESS_MAIN(TestSegyFile)

#include "tst_testsegyfile.moc"
