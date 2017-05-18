#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QtCore/qmath.h>
#include <QMatrix4x4>

#include "Base/ServiceLocator.h"
#include "gui/Settings.h"
#include "gui/visualeditor/ViewportInfo.h"
#include "model/AccessPorts/SimulationAccess.h"
#include "model/BuilderFacade.h"
#include "model/SimulationController.h"
#include "model/Context/SimulationContext.h"
#include "model/Context/EnergyParticleMap.h"
#include "model/Context/CellMap.h"
#include "model/Context/SpaceMetric.h"
#include "model/Entities/Cell.h"
#include "model/Entities/CellCluster.h"
#include "model/Entities/EnergyParticle.h"

#include "pixeluniverse.h"

PixelUniverse::PixelUniverse(QObject* parent)
{
	setBackgroundBrush(QBrush(BACKGROUND_COLOR));
    _pixmap = addPixmap(QPixmap());
    update();
}

PixelUniverse::~PixelUniverse()
{
	delete _image;
}

void PixelUniverse::init(SimulationController* controller, ViewportInfo* viewport)
{
	BuilderFacade* facade = ServiceLocator::getInstance().getService<BuilderFacade>();
	_context = controller->getContext();
	_viewport = viewport;
	auto simAccess = facade->buildSimulationAccess(_context);
	SET_CHILD(_simAccess, simAccess);

	delete _image;
	IntVector2D size = _context->getSpaceMetric()->getSize();
	_image = new QImage(size.x, size.y, QImage::Format_RGB32);
	QGraphicsScene::setSceneRect(0, 0, _image->width(), _image->height());

	connect(controller, &SimulationController::timestepCalculated, this, &PixelUniverse::requestData);
	connect(_simAccess, &SimulationAccess::dataReadyToRetrieve, this, &PixelUniverse::retrieveAndDisplayData);

	requestAllData();
}

void PixelUniverse::requestAllData()
{
	IntVector2D size = _context->getSpaceMetric()->getSize();
	ResolveDescription resolveDesc;
	_simAccess->requireData({ {0, 0}, size }, resolveDesc);
}

Q_SLOT void PixelUniverse::requestData()
{
	ResolveDescription resolveDesc;
	IntRect rect = _viewport->getRect();
	_simAccess->requireData(rect, resolveDesc);
}

Q_SLOT void PixelUniverse::retrieveAndDisplayData()
{
	auto const& dataDesc = _simAccess->retrieveData();

	_image->fill(UNIVERSE_COLOR);

	displayClusters(dataDesc);
	displayParticles(dataDesc);
	_pixmap->setPixmap(QPixmap::fromImage(*_image));
}

namespace
{
	uint32_t calcCellColor(CellMetadata const& meta, double energy)
	{
		uint8_t r = 0;
		uint8_t g = 0;
		uint8_t b = 0;
		auto const& color = meta.color;
		if (color == 0) {
			r = INDIVIDUAL_CELL_COLOR1.red();
			g = INDIVIDUAL_CELL_COLOR1.green();
			b = INDIVIDUAL_CELL_COLOR1.blue();
		}
		if (color == 1) {
			r = INDIVIDUAL_CELL_COLOR2.red();
			g = INDIVIDUAL_CELL_COLOR2.green();
			b = INDIVIDUAL_CELL_COLOR2.blue();
		}
		if (color == 2) {
			r = INDIVIDUAL_CELL_COLOR3.red();
			g = INDIVIDUAL_CELL_COLOR3.green();
			b = INDIVIDUAL_CELL_COLOR3.blue();
		}
		if (color == 3) {
			r = INDIVIDUAL_CELL_COLOR4.red();
			g = INDIVIDUAL_CELL_COLOR4.green();
			b = INDIVIDUAL_CELL_COLOR4.blue();
		}
		if (color == 4) {
			r = INDIVIDUAL_CELL_COLOR5.red();
			g = INDIVIDUAL_CELL_COLOR5.green();
			b = INDIVIDUAL_CELL_COLOR5.blue();
		}
		if (color == 5) {
			r = INDIVIDUAL_CELL_COLOR6.red();
			g = INDIVIDUAL_CELL_COLOR6.green();
			b = INDIVIDUAL_CELL_COLOR6.blue();
		}
		if (color == 6) {
			r = INDIVIDUAL_CELL_COLOR7.red();
			g = INDIVIDUAL_CELL_COLOR7.green();
			b = INDIVIDUAL_CELL_COLOR7.blue();
		}
		quint32 e = energy / 2.0 + 20.0;
		if (e > 150) {
			e = 150;
		}
		r = r*e / 150;
		g = g*e / 150;
		b = b*e / 150;
		return (r << 16) | (g << 8) | b;
	}

	uint32_t calcParticleColor(double energy)
	{
		quint32 e = (energy + 10)*5;
		if (e > 150) {
			e = 150;
		}
		return (e << 16) | 0x30;
	}
}

void PixelUniverse::displayClusters(DataDescription const& data) const
{
	auto space = _context->getSpaceMetric();
	for (auto const& clusterTracker : data.clusters) {
		auto const& clusterDesc = clusterTracker.getValue();
		for (auto const& cellTracker : clusterDesc.cells) {
			auto const& cellDesc = cellTracker.getValue();
			auto const& pos = cellDesc.pos.getValue();
			auto const& meta = cellDesc.metadata.getValue();
			auto const& energy = cellDesc.energy.getValue();
			auto intPos = space->correctPositionWithIntPrecision(pos);
			_image->setPixel(intPos.x, intPos.y, calcCellColor(meta, energy));
		}
	}
}

void PixelUniverse::displayParticles(DataDescription const & data) const
{
	auto space = _context->getSpaceMetric();
	for (auto const& particleTracker : data.particles) {
		auto const& particleDesc = particleTracker.getValue();
		auto const& pos = particleDesc.pos.getValue();
		auto const& energy = particleDesc.energy.getValue();
		auto intPos = space->correctPositionWithIntPrecision(pos);
		_image->setPixel(intPos.x, intPos.y, calcParticleColor(energy));
	}
}
