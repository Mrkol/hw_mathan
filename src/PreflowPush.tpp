#include "PreflowPush.hpp"
#include <cmath>


template<typename T>
void PreflowPush<T>::Initialize(std::shared_ptr<Network<T>> network)
{
	overflows_.assign(network->VerticeCount(), 0);
	heights_.assign(network->VerticeCount(), 0);
	overflownCount_ = 0;

	MaxFlowAlgorithm<T>::Initialize(network);

	iterators_.reserve(network->VerticeCount());
	for (std::size_t i = 0; i < network->VerticeCount(); ++i)
	{
		iterators_.push_back(network->IterateOutgoingEdgesAt(i));
	}
}

template<typename T>
bool PreflowPush<T>::fromSourceOrTarget(Iterator edge)
{
	return edge->Source() == this->network_->Source()
		|| edge->Source() == this->network_->Target();
}

template<typename T>
bool PreflowPush<T>::toSourceOrTarget(Iterator edge)
{
	return edge->Target() == this->network_->Source()
		|| edge->Target() == this->network_->Target();
}

template<typename T>
void PreflowPush<T>::discharge(std::size_t vertice)
{
	while (overflows_[vertice] > 0)
	{
		if (iterators_[vertice])
		{
			push(iterators_[vertice]);
			++iterators_[vertice];
		}
		else
		{
			relabel(vertice);
			iterators_[vertice] = this->network_->IterateOutgoingEdgesAt(vertice);	
		}
	}
}

template<typename T>
bool PreflowPush<T>::canPush(Iterator edge)
{
	return heights_[edge->Source()] == heights_[edge->Target()] + 1
		&& edge->Flow() < edge->Capacity()
		&& (overflows_[edge->Source()] > 0
			|| edge->Source() == this->network_->Source());
}

template<typename T>
void PreflowPush<T>::fixupOverflows(Iterator edge, T pushed)
{
	if (!fromSourceOrTarget(edge))
	{
		if (overflows_[edge->Source()] == pushed)
			--overflownCount_;
		overflows_[edge->Source()] -= pushed;
	}

	if (!toSourceOrTarget(edge))
	{
		if (overflows_[edge->Target()] == 0)
			++overflownCount_;
		overflows_[edge->Target()] += pushed;
	}
}

template<typename T>
void PreflowPush<T>::push(Iterator edge)
{
	if (!canPush(edge))
		return;

	T pushable = std::min(edge->Capacity() - edge->Flow(), overflows_[edge->Source()]);

	if (edge->Source() == this->network_->Source())
			pushable = edge->Capacity() - edge->Flow();

	
	edge->AddFlow(pushable);
	fixupOverflows(edge, pushable);
}

template<typename T>
void PreflowPush<T>::relabel(std::size_t vertice)
{
	std::size_t m = 2*this->network_->VerticeCount();
	for (auto it = this->network_->IterateOutgoingEdgesAt(vertice); it; ++it)
	{
		if (it->Flow() >= it->Capacity())
			continue;

		if (canPush(it))
			return;

		m = std::min(m, heights_[it->Target()]);
	}

	heights_[vertice] = m + 1;
}


template<typename T>
void PreflowPush<T>::Calculate()
{
	Network<T>& network = *this->network_;

	heights_[network.Source()] = 1;
	for (auto it = network.IterateOutgoingEdgesAt(network.Source()); it; ++it)
	{
		push(it);
	}
	heights_[network.Source()] = network.VerticeCount();

	while (overflownCount_ > 0)
	{
		for (std::size_t i = 0; i < network.VerticeCount(); ++i)
		{
			discharge(i);	
		}
	}
}
