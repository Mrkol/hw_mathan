#pragma once
#ifndef BLOCKINGFLOWALGORITHM_HPP
#define BLOCKINGFLOWALGORITHM_HPP

#include "MaxFlowAlgorithm.hpp"
#include <queue>
#include <functional>


template<typename T>
class BlockingFlowAlgorithm : public MaxFlowAlgorithm<T>
{
	using Iterator = typename Network<T>::Iterator;

	std::vector<std::size_t> layer_;

	bool calculateLayeredNetwork();

protected:
	virtual bool inLayeredNetwork(Iterator it);

	virtual void pushBlockingFlow() = 0;

public:
	void Initialize(std::shared_ptr<Network<T>> network) override;

	void Calculate() final override;
};

#include "BlockingFlowAlgorithm.tpp"

#endif // BLOCKINGFLOWALGORITHM_HPP
