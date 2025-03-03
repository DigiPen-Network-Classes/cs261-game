//---------------------------------------------------------
// file:	ServerConfiguration.cpp
// author:	Matthew Picioccio
// email:	matthew.picioccio@digipen.edu
//
// brief:	The app configuration, which comes from the command line and other potential sources.
//
// Copyright © 2021 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "ServerConfiguration.h"


ServerConfiguration ServerConfiguration::BuildConfigurationFromArguments(int argc, char** argv)
{
    if (argc != 3)
    {
        throw std::invalid_argument("Usage: program game_port shared_secret");
    }
    ServerConfiguration configuration;
    
    configuration.port = atoi(argv[1]);
    configuration.secret = std::string(argv[2]);

    return configuration;
}