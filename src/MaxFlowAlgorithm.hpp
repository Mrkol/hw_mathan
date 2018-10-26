#pragma once
#ifndef MAXFLOWALGORITHM_HPP
#define MAXFLOWALGORITHM_HPP

#include "Network.hpp"


template<typename T>
class MaxFlowAlgorithm
{
protected:
	std::shared_ptr<Network<T>> network_;

public:
	virtual void Initialize(std::shared_ptr<Network<T>> network);

	std::shared_ptr<Network<T>> GetNetwork();

	T GetFlow();

	virtual void Calculate() = 0;
};

#include "MaxFlowAlgorithm.tpp"

#endif // MAXFLOWALGORITHM_HPP
