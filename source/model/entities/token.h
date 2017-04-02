#ifndef TOKEN_H
#define TOKEN_H

#include <QVector>

#include "model/definitions.h"

class Token
{
public:
	virtual ~Token() {}

    virtual Token* duplicate () const = 0;
	virtual int getTokenAccessNumber() const = 0;
	virtual void setTokenAccessNumber (int i) = 0;

	virtual void setEnergy (qreal energy) = 0;
	virtual qreal getEnergy () const = 0;

	virtual QByteArray& getMemoryRef () = 0;

	virtual void serializePrimitives (QDataStream& stream) const = 0;
	virtual void deserializePrimitives (QDataStream& stream) = 0;
};

#endif // TOKEN_H