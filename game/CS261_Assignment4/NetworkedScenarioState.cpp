//---------------------------------------------------------
// file:	NetworkedScenarioState.cpp
// author:	Matthew Picioccio
// email:	matthew.picioccio@digipen.edu
//
// brief:	Shared data and functionality for all scenarios that involve networking.
//
// Copyright � 2021 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "pch.h"
#include "NetworkedScenarioState.h"
#include "GameStateManager.h"


NetworkedScenarioState::NetworkedScenarioState(const SOCKET socket, const bool is_host)
	: socket_(socket), is_host_(is_host)
{ }


NetworkedScenarioState::~NetworkedScenarioState() = default;


void NetworkedScenarioState::Update()
{
	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		if (socket_ != INVALID_SOCKET)
		{
			closesocket(socket_);
			socket_ = INVALID_SOCKET;
		}
		GameStateManager::ReturnToBaseState();
		return;
	}
}

int NetworkedScenarioState::GetSocketPort() const 
{
	if (socket_ == INVALID_SOCKET)
	{
		return INVALID_SOCKET;
	}
	sockaddr_in localAddr;
	int addrLen = sizeof(localAddr);
	if (getsockname(socket_, reinterpret_cast<sockaddr*>(&localAddr), &addrLen) == SOCKET_ERROR) 
	{
		return INVALID_SOCKET;
	}
	return ntohs(localAddr.sin_port);
}