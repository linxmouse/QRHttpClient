#ifndef CNC_STATUS_H
#define CNC_STATUS_H

#include "JsonSerializer.h"

class CNCStatus : public JsonSerializable
{
	Q_GADGET
	JSON_SERIALIZABLE
public:
	JSON_PROPERTY(QString, mainProg)
	JSON_PROPERTY(QString, curProg)
	JSON_PROPERTY(int, curSeq)
	JSON_PROPERTY(QString, mode)
	JSON_PROPERTY(QString, status)
	JSON_PROPERTY(QString, alarm)
	JSON_PROPERTY(QString, emg)
};
#endif // !CNC_STATUS_H
