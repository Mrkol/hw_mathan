#pragma once
#ifndef DINIC_HPP
#define DINIC_HPP

#include "BlockingFlowAlgorithm.hpp"

template<typename T>
class Dinic : public BlockingFlowAlgorithm<T>
{
	using Iterator = typename Network<T>::Iterator;

	T pushSinglePath(std::size_t start, T currentMin,
		std::vector<Iterator>& iterators);

protected:
	void pushBlockingFlow() override;
};

#include "Dinic.tpp"

#endif // DINIC_HPP
