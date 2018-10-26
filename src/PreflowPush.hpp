#pragma once
#ifndef PREFLOWPUSH_HPP
#define PREFLOWPUSH_HPP

#include "MaxFlowAlgorithm.hpp"


template<typename T>
class PreflowPush : public MaxFlowAlgorithm<T>
{
	using Iterator = typename Network<T>::Iterator;

	std::vector<T> overflows_;
	std::vector<std::size_t> heights_;
	std::vector<Iterator> iterators_;
	std::size_t overflownCount_;

	bool fromSourceOrTarget(Iterator edge);
	bool toSourceOrTarget(Iterator edge);
	void discharge(std::size_t vertice);

	void fixupOverflows(Iterator edge, T pushed);

	bool canPush(Iterator edge);

	void push(Iterator edge);
	void relabel(std::size_t vertice);

public:
	void Initialize(std::shared_ptr<Network<T>> network) override;

	void Calculate() override;
};

#include "PreflowPush.tpp"

#endif // PREFLOWPUSH_HPP
