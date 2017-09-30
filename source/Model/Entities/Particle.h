#pragma once

#include <QVector2D>

#include "Model/Definitions.h"
#include "Model/ChangeDescriptions.h"
#include "Timestamp.h"

class Particle
	: public Timestamp
{
public:
	Particle(UnitContext* context) : Timestamp(context) {}
	virtual ~Particle() = default;

	virtual ParticleDescription getDescription() const = 0;
	virtual void applyChangeDescription(ParticleChangeDescription const& change) = 0;

    virtual bool processingMovement (Cluster*& cluster) = 0;

	virtual qreal getEnergy() const = 0;
	virtual void setEnergy(qreal value) = 0;

	virtual QVector2D getPosition () const = 0;
	virtual void setPosition(QVector2D value) = 0;

	virtual QVector2D getVelocity() const = 0;
	virtual void setVelocity(QVector2D value) = 0;

	virtual quint64 getId() const = 0;
	virtual void setId(quint64 value) = 0;

	virtual ParticleMetadata getMetadata() const = 0;
	virtual void setMetadata(ParticleMetadata value) = 0;

    virtual void serializePrimitives (QDataStream& stream) const = 0;
	virtual void deserializePrimitives (QDataStream& stream) = 0;
};

