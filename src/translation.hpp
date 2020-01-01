// Copyright (c) 2018-2020 Emil Engler et al.
// Distributed under the GNU GENERAL PUBLIC LICENSE Version 3, see the accompanying
// file LICENSE.txt or <https://www.gnu.org/licenses/gpl-3.0.html>.
#include <string>
#include <vector>
#include <iostream>
#include "libs/json.hpp"

namespace sysget
{
    std::string JsonSTR(nlohmann::json j);
    nlohmann::json language(std::string lang);
}