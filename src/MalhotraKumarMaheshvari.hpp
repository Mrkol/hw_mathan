#pragma once
#ifndef MALHOTRAKUMARMAHESHVARI_HPP
#define MALHOTRAKUMARMAHESHVARI_HPP

#include "BlockingFlowAlgorithm.hpp"


template<typename T>
class MalhotraKumarMaheshvari : public BlockingFlowAlgorithm<T>
{
	using Iterator = typename Network<T>::Iterator;

	std::vector<bool> deleted_;
	std::vector<T> potentialIn_;
	std::vector<T> potentialOut_;


	void deleteVertice(std::size_t vertice);

	T potential(std::size_t vertice);

	void recalcPotential(std::size_t vertice);

	void findReachable(std::size_t current, std::vector<bool>& visited, bool reverse);

	void pushFlowThroughVerticeSingleDirection(std::size_t vertice, T initialPush,
		std::vector<Iterator>& iterators, bool reversed);

protected:
	bool inLayeredNetwork(Iterator it) override;

	void pushBlockingFlow() override;

public:
	void Initialize(std::shared_ptr<Network<T>> network) override;
};

#include "MalhotraKumarMaheshvari.tpp"

#endif // MALHOTRAKUMARMAHESHVARI_HPP
