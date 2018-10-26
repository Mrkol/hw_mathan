#include "EdgeListNetwork.hpp"
#include "NetworkBuilder.hpp"
#include "PreflowPush.hpp"

using Type = long long;
const Type Infinity = 1e10;

template<template<typename> class NetworkType>
std::unique_ptr<Network<Type>> ReadData(std::istream& in)
{
	NetworkBuilder<NetworkType, Type> builder;

	std::size_t bookCount = 0;
	in >> bookCount;

	builder.Initialize(bookCount + 2);
	const std::size_t source = bookCount;
	const std::size_t target = bookCount + 1;
	builder.SetSource(source);
	builder.SetTarget(target);

	for (std::size_t i = 0; i < bookCount; ++i)
	{
		Type usefullness = 0;
		in >> usefullness;
		if (usefullness >= 0)
			builder.AddCapacity(source, i, usefullness);
		else
			builder.AddCapacity(i, target, -usefullness);
	}

	for (std::size_t i = 0; i < bookCount; ++i)
	{
		std::size_t adjacentCount = 0;
		in >> adjacentCount;
		for (std::size_t j = 0; j < adjacentCount; ++j)
		{
			std::size_t adjacent = 0;
			in >> adjacent;
			--adjacent;
			builder.AddCapacity(i, adjacent, Infinity);
		}
	}

	return builder.Finalize();
}

Type Solve(std::shared_ptr<Network<Type>> network, MaxFlowAlgorithm<Type>& algorithm)
{
	algorithm.Initialize(network);
	algorithm.Calculate();
	Type answer = 0;
	for (auto it = network->IterateOutgoingEdgesAt(network->Source()); it; ++it)
	{
		answer += it->Capacity();
	}
	answer -= algorithm.GetFlow();
	return answer;
}

void WriteData(Type t)
{
	std::cout << t << std::endl;
}




int main()
{
	std::shared_ptr<Network<Type>> network(ReadData<EdgeListNetwork>(std::cin));
	PreflowPush<Type> algorithm;
	Type answer = Solve(network, algorithm);
	WriteData(answer);

	return 0;
}

