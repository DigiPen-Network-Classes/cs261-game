//---------------------------------------------------------
// file:	ClientConfiguration.cpp
// author:	Matthew Picioccio
// email:	matthew.picioccio@digipen.edu
//
// brief:	The app configuration, which comes from the command line and other potential sources.
//
// Copyright © 2021 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "ClientConfiguration.h"


ClientConfiguration ClientConfiguration::BuildConfigurationFromArguments(int argc, char** argv)
{
    ClientConfiguration configuration;
    if (argc != 4) 
    {
        throw std::invalid_argument("usage: program http://localhost:3100 username password");
    }

    // argv[0] is the executable file name and path
    configuration.user_service = std::string(argv[1]);
    configuration.username = std::string(argv[2]);
    configuration.password = std::string(argv[3]);

    return configuration;
}