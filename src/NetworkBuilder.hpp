#pragma once
#ifndef NETWORKBUILDER_HPP
#define NETWORKBUILDER_HPP

#include "Network.hpp"
#include <memory>


template<template<typename> class ConcreteNetwork, typename T>
class NetworkBuilder
{
	std::size_t source_;
	std::size_t target_;
	std::vector<std::vector<T>> adjacencyMatrix_;
	using OwnType = NetworkBuilder<ConcreteNetwork, T>;

public:
	NetworkBuilder& Initialize(std::size_t vertices);
	NetworkBuilder& SetSource(std::size_t source);
	NetworkBuilder& SetTarget(std::size_t target);
	NetworkBuilder& AddCapacity(
		std::size_t from, std::size_t to, T capacity);

	std::unique_ptr<ConcreteNetwork<T>> Finalize();
};

#include "NetworkBuilder.tpp"

#endif // NETWORKBUILDER_HPP
