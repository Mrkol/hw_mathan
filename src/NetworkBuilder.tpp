#include "NetworkBuilder.hpp"


template<template<typename> class ConcreteNetwork, typename T>
auto NetworkBuilder<ConcreteNetwork, T>::Initialize(std::size_t vertices)
	-> OwnType&
{
	adjacencyMatrix_.assign(vertices, std::vector<T>(vertices, T(0)));
	return *this;
}

template<template<typename> class ConcreteNetwork, typename T>
auto NetworkBuilder<ConcreteNetwork, T>::SetSource(std::size_t source)
	-> OwnType&
{
	source_ = source;
	return *this;
}

template<template<typename> class ConcreteNetwork, typename T>
auto NetworkBuilder<ConcreteNetwork, T>::SetTarget(std::size_t target)
	-> OwnType&
{
	target_ = target;
	return *this;
}

template<template<typename> class ConcreteNetwork, typename T>
auto NetworkBuilder<ConcreteNetwork, T>::AddCapacity(
	std::size_t from, std::size_t to, T capacity)
	-> OwnType&
{
	adjacencyMatrix_[from][to] += capacity;
	return *this;
}

template<template<typename> class ConcreteNetwork, typename T>
auto NetworkBuilder<ConcreteNetwork, T>::Finalize()
	-> std::unique_ptr<ConcreteNetwork<T>>
{
	std::unique_ptr<ConcreteNetwork<T>>
		network(new ConcreteNetwork<T>(adjacencyMatrix_.size()));
	network->setSource(source_);
	network->setTarget(target_);
	for (std::size_t i = 0; i < adjacencyMatrix_.size(); ++i)
	{
		for (std::size_t j = i + 1; j < adjacencyMatrix_[i].size(); ++j)
		{
			if (adjacencyMatrix_[i][j] <= 0 && adjacencyMatrix_[j][i] <= 0)
				continue;

			network->addBareEdge(i, j, adjacencyMatrix_[i][j]);
			network->addBareEdge(j, i, adjacencyMatrix_[j][i]);
		}
	}
	return network;
}
