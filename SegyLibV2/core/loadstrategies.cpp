#include "loadstrategies.h"
#include <algorithm>

OneTraceStrategy::OneTraceStrategy():_loadedTrace(-1),_unloadTrace(-1){}

bool OneTraceStrategy::canAppendTrace(long long traceNum){
    if(_loadedTrace==-1)return true;
    return false;
}

bool OneTraceStrategy::canLoadTrace(long long traceNum){
    return true;
}

void OneTraceStrategy::loadTrace(long long traceNum){
    if(traceNum==_loadedTrace)_unloadTrace=-1;
    else{
        _unloadTrace=_loadedTrace;
        _loadedTrace=traceNum;
    }
}

long long OneTraceStrategy::getUnloadTrace(){
    long long temp = _unloadTrace;
    _unloadTrace=-1;
    return temp;
}

void OneTraceStrategy::clear(){
    _loadedTrace=-1;
    _unloadTrace=-1;
}

AllTraceStrategy::AllTraceStrategy(){}

bool AllTraceStrategy::canAppendTrace(long long traceNum)const{
    return true;
}

bool AllTraceStrategy::canLoadTrace(long long traceNum) const{
    return true;
}

void AllTraceStrategy::loadTrace(long long traceNum){
    return;
}

long long AllTraceStrategy::getUnloadTrace(){
    return -1;
}

void AllTraceStrategy::clear(){
    return;
}
