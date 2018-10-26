#pragma once
#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <cinttypes>
#include <iostream>
#include <vector>
#include <limits>
#include <memory>



const std::size_t InfiniteSize = 
		std::numeric_limits<std::size_t>::max();

template<typename T>
class Network
{
protected:
	virtual void setSource(std::size_t source) = 0;
	virtual void setTarget(std::size_t target) = 0;
	virtual void addBareEdge(
		std::size_t from, std::size_t to, T capacity) = 0;

	class InternalIterator;
public:
	class Iterator;

	virtual std::size_t VerticeCount() = 0;
	virtual std::size_t EdgeCount() = 0;
	virtual std::size_t Source() = 0;
	virtual std::size_t Target() = 0;

	virtual void ClearFlow() = 0;

	virtual Iterator IterateOutgoingEdgesAt(std::size_t from) = 0;
	virtual Iterator IterateIncomingEdgesAt(std::size_t to) = 0;

	virtual ~Network() = default;
};

template<typename T>
class Network<T>::InternalIterator
{
protected:
	virtual void advance() = 0;
	virtual bool ended() = 0;
	virtual std::unique_ptr<InternalIterator> copy() = 0;

	friend class Iterator;

public:
	virtual std::size_t Source() = 0;
	virtual std::size_t Target() = 0;
	virtual T Capacity() = 0;
	virtual T Flow() = 0;

	virtual void AddFlow(T amount) = 0;

	virtual ~InternalIterator() = default;
};

template<typename T>
class Network<T>::Iterator
{
	std::unique_ptr<InternalIterator> internal_;

public:
	Iterator(std::unique_ptr<InternalIterator> internal);
	Iterator(Iterator& other);
	Iterator(Iterator&& other) = default;
	Iterator& operator=(Iterator& other);
	Iterator& operator=(Iterator&& other) = default;

	InternalIterator* operator->();

	Iterator& operator++();
	Iterator operator++(int);

	operator bool();
};

template<typename T>
std::ostream& operator<<(std::ostream& out, Network<T>& network);

#include "Network.tpp"

#endif // NETWORK_HPP
