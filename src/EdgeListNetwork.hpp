#pragma once
#ifndef EDGELISTNETWORK_HPP
#define EDGELISTNETWORK_HPP

#include <cinttypes>
#include <vector>
#include "Network.hpp"


template<typename T>
class EdgeListNetwork : public Network<T>
{
protected:
	std::size_t verticeCount_;
	std::size_t edgeCount_;

	std::size_t source_;
	std::size_t target_;

	//Edge properties
	std::vector<std::size_t> from_;
	std::vector<std::size_t> to_;
	std::vector<T> capacity_;
	std::vector<T> flow_;

	std::vector<std::size_t> firstEdgeFrom_;
	std::vector<std::size_t> nextEdgeFrom_;

	std::vector<std::size_t> firstEdgeTo_;
	std::vector<std::size_t> nextEdgeTo_;

	template<template<typename> class ConcreteNetwork, typename T1>
	friend class NetworkBuilder;

	explicit EdgeListNetwork(std::size_t vertices);

	void setSource(std::size_t source) override;
	void setTarget(std::size_t target) override;
	void addBareEdge(
		std::size_t from, std::size_t to, T capacity) override;

public:
	class InternalIterator;

	std::size_t VerticeCount() override;
	std::size_t EdgeCount() override;
	std::size_t Source() override;
	std::size_t Target() override;

	void ClearFlow() override;

	typename Network<T>::Iterator IterateOutgoingEdgesAt(std::size_t from) override;
	typename Network<T>::Iterator IterateIncomingEdgesAt(std::size_t to) override;
};


template<typename T>
class EdgeListNetwork<T>::InternalIterator : public Network<T>::InternalIterator
{
	std::size_t edgeIndex_;
	EdgeListNetwork<T>* network_;
	bool outgoing_;
	bool ended_;

	InternalIterator(std::size_t index, EdgeListNetwork<T>* network, bool outgoing);

	void advance() override;
	bool ended() override;
	std::unique_ptr<typename Network<T>::InternalIterator> copy() override;

	friend class EdgeListNetwork<T>;

public:
	std::size_t Source() override;
	std::size_t Target() override;
	T Capacity() override;
	T Flow() override;

	void AddFlow(T amount) override;
};

#include "EdgeListNetwork.tpp"

#endif // EDGELISTNETWORK_HPP
