#pragma once
#ifndef MALHOTRAKUMARMAHESHVARI_HPP
#define MALHOTRAKUMARMAHESHVARI_HPP

#include "MaxFlowAlgorithm.hpp"
#include <queue>
#include <functional>


template<typename T>
class MalhotraKumarMaheshvari : public MaxFlowAlgorithm<T>
{
	using Iterator = typename Network<T>::Iterator;

	std::vector<bool> deleted_;
	std::vector<std::size_t> layer_;
	std::vector<T> potentialIn_;
	std::vector<T> potentialOut_;

	bool inLayeredNetwork(Iterator it);

	void deleteVertice(std::size_t vertice);

	T potential(std::size_t vertice);

	void recalcPotential(std::size_t vertice);

	bool calculateLayeredNetwork();

	void findReachable(std::size_t current, std::vector<bool>& visited, bool reverse);

	void pushFlowThroughVerticeSingleDirection(std::size_t vertice, T initialPush,
		std::vector<Iterator>& iterators, bool reversed);

public:
	void Initialize(std::shared_ptr<Network<T>> network) override;

	void Calculate() override;
};

#include "MalhotraKumarMaheshvari.tpp"

#endif // MALHOTRAKUMARMAHESHVARI_HPP
