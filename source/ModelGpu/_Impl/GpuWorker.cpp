#include <functional>

#include "Model/SpaceMetricApi.h"

#include "GpuWorker.h"
#include "CudaFunctions.cuh"

GpuWorker::~GpuWorker()
{
	end_Cuda();
}

void GpuWorker::init(SpaceMetricApi* metric)
{
	auto size = metric->getSize();
	init_Cuda({ size.x, size.y });
}

void GpuWorker::getData(IntRect const & rect, ResolveDescription const & resolveDesc, DataDescription & result) const
{
	int numCLusters;
	ClusterCuda* clusters;
	result.clear();
	getDataRef_Cuda(numCLusters, clusters);
	for (int i = 0; i < numCLusters; ++i) {
		CellClusterDescription clusterDesc;
		if (rect.isContained({ (int)clusters[i].pos.x, (int)clusters[i].pos.y }))
		for (int j = 0; j < clusters[i].numCells; ++j) {
			auto pos = clusters[i].cells[j].absPos;
			clusterDesc.addCell(CellDescription().setPos({ (float)pos.x, (float)pos.y }).setMetadata(CellMetadata()).setEnergy(100.0f));
		}
		result.addCellCluster(clusterDesc);
	}
}

void GpuWorker::calculateTimestep()
{
	calcNextTimestep_Cuda();
	Q_EMIT timestepCalculated();
}
