#pragma once

#include "Model/Definitions.h"

class SpaceMetricApi
	: public QObject
{
	Q_OBJECT
public:
	SpaceMetricApi(QObject* parent = nullptr) : QObject(parent) {}
	virtual ~SpaceMetricApi() = default;

	virtual IntVector2D getSize() const = 0;
	virtual IntVector2D correctPositionAndConvertToIntVector(QVector2D const& pos) const = 0;
	virtual void correctPosition(IntVector2D & pos) const = 0;
};
