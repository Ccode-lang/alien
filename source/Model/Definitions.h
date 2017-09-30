#pragma once

#include "Base/Definitions.h"
#include "Model/Metadata/CellMetadata.h"
#include "Model/Metadata/ClusterMetadata.h"
#include "Model/Metadata/ParticleMetadata.h"

#include "DllExport.h"

class Cell;
class Cluster;
class UnitGrid;
class Particle;
class Token;
class CellFeature;
class Unit;
class CellMap;
class ParticleMap;
class SpaceMetric;
class SpaceMetricLocal;
class MapCompartment;
class UnitGrid;
class UnitThreadController;
class UnitContext;
class SimulationContextLocal;
class SimulationContext;
class SimulationParameters;
class SimulationController;
class SymbolTable;
class UnitObserver;
class EntityFactory;
class ContextFactory;
struct DataChangeDescription;
struct ClusterChangeDescription;
struct CellChangeDescription;
struct ParticleChangeDescription;
struct DataDescription;
struct ClusterDescription;
struct CellDescription;
struct ParticleDescription;
class SimulationAccess;
class QTimer;
class ModelBuilderFacade;
class SerializationFacade;
class CellConnector;

struct CellClusterHash
{
	std::size_t operator()(Cluster* const& s) const;
};
typedef std::unordered_set<Cluster*, CellClusterHash> CellClusterSet;

struct CellHash
{
    std::size_t operator()(Cell* const& s) const;
};
typedef std::unordered_set<Cell*, CellHash> CellSet;

