#pragma once

#include "Base.cuh"
#include "Cell.cuh"

class GenomeDecoder
{
public:
    __inline__ __device__ static bool isFinished(ConstructorFunction const& constructor);
    __inline__ __device__ static bool readBool(ConstructorFunction& constructor);
    __inline__ __device__ static uint8_t readByte(ConstructorFunction& constructor);
    __inline__ __device__ static int readWord(ConstructorFunction& constructor);
    __inline__ __device__ static float readFloat(ConstructorFunction& constructor);  //return values from -1 to 1
    __inline__ __device__ static float readAngle(ConstructorFunction& constructor);
    template <typename GenomeHolderSource, typename GenomeHolderTarget>
    __inline__ __device__ static void copyGenome(SimulationData& data, GenomeHolderSource& source, GenomeHolderTarget& target);

    __inline__ __device__ static bool convertByteToBool(uint8_t b);
    __inline__ __device__ static int convertBytesToWord(uint8_t b1, uint8_t b2);
};

/************************************************************************/
/* Implementation                                                       */
/************************************************************************/
__inline__ __device__ bool GenomeDecoder::isFinished(ConstructorFunction const& constructor)
{
    return constructor.currentGenomePos >= constructor.genomeSize;
}

__inline__ __device__ bool GenomeDecoder::readBool(ConstructorFunction& constructor)
{
    return convertByteToBool(readByte(constructor));
}

__inline__ __device__ uint8_t GenomeDecoder::readByte(ConstructorFunction& constructor)
{
    if (isFinished(constructor)) {
        return 0;
    }
    uint8_t result = constructor.genome[constructor.currentGenomePos++];
    return result;
}

__inline__ __device__ int GenomeDecoder::readWord(ConstructorFunction& constructor)
{
    auto b1 = readByte(constructor);
    auto b2 = readByte(constructor);
    return convertBytesToWord(b1, b2);
}

__inline__ __device__ float GenomeDecoder::readFloat(ConstructorFunction& constructor)
{
    return static_cast<float>(static_cast<int8_t>(readByte(constructor))) / 128.0f;
}

__inline__ __device__ float GenomeDecoder::readAngle(ConstructorFunction& constructor)
{
    return static_cast<float>(static_cast<int8_t>(readByte(constructor))) / 120 * 180;
}

__inline__ __device__ bool GenomeDecoder::convertByteToBool(uint8_t b)
{
    return static_cast<int8_t>(b) > 0;
}

__inline__ __device__ int GenomeDecoder::convertBytesToWord(uint8_t b1, uint8_t b2)
{
    return static_cast<int>(b1) | (static_cast<int>(b2 << 8));
}

template <typename GenomeHolderSource, typename GenomeHolderTarget>
__inline__ __device__ void GenomeDecoder::copyGenome(SimulationData& data, GenomeHolderSource& source, GenomeHolderTarget& target)
{
    bool makeGenomeCopy = readBool(source);
    if (!makeGenomeCopy) {
        auto size = min(readWord(source), toInt(source.genomeSize));
        target.genomeSize = size;
        target.genome = data.objects.auxiliaryData.getAlignedSubArray(size);
        //#TODO can be optimized
        for (int i = 0; i < size; ++i) {
            target.genome[i] = readByte(source);
        }
    } else {
        auto size = source.genomeSize;
        target.genomeSize = size;
        target.genome = data.objects.auxiliaryData.getAlignedSubArray(size);
        //#TODO can be optimized
        for (int i = 0; i < size; ++i) {
            target.genome[i] = source.genome[i];
        }
    }
}