/*
 * Copyright (c) <2016>, <Robert Reinecke>
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or other
 * materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef GLOBAL_FLOW__MAIN_HPP
#define GLOBAL_FLOW__MAIN_HPP

#include "../global-gradient-based-groundwater-model/src/GW_Interface.hpp"
#include "../global-gradient-based-groundwater-model/src/Simulation/Stepper.hpp"
#include "../global-gradient-based-groundwater-model/src/Simulation/Simulation.hpp"
#include "../global-gradient-based-groundwater-model/src/Simulation/Options.hpp"
#include "../global-gradient-based-groundwater-model/src/DataProcessing/DataOutput/OutputManager.hpp"
#include "set"
#include <fstream>
#include "../global-gradient-based-groundwater-model/src/Misc/colors.hpp"
#include "SteadyDataReader.hpp"

namespace GlobalFlow {

    class NotCoupled;

    /**
     * @class Runner
     * @implements GW_Interface
     * @brief A standalone global steady-state groundwater model
     */
    class Runner : GW_Interface<NotCoupled> {
    public:

        /**
         * @brief Default constructor
         */
        Runner();

        void
        loadSettings();

        void
        setupSimulation();

        void
        simulate();

        void
        getResults();

        void
        writeNodeInfosToCSV();

        void
        writeData();

    private:
        /** @var _eq @brief The groundwater equation */
        Solver::Equation *_eq{};
        /** @var op @brief The options object holding all user input */
        Simulation::Options op;
        /** @var sim @brief The simulation object holding the data */
        Simulation::Simulation sim;
        /** @var reader @brief The data reader object responsible for reading in data */
        DataProcessing::SteadyDataReader *reader{};

        std::string pathToConfig{};

        /**
         * @brief Helper function for arcID mappings
         * @return a set of arcIDs
         */
        std::set<int> getMapping();
    };

}//ns
#endif //GROUNDWATER_SOLVER_MAIN_HPP
