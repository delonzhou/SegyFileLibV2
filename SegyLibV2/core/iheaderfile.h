#ifndef IHEADERFILE_H
#define IHEADERFILE_H

#include "iheader.h"
#include <memory>


class IHeaderFile
{
public:
	//Возвращает заголовок файла
    virtual const IHeader& getHeader()const=0;

	//Задаёт заголовок файла
    virtual bool setHeader(const IHeader& header)=0;
};

#endif // IHEADERFILE_H
