/** Detray library, part of the ACTS project (R&D line)
 * 
 * (c) 2020 CERN for the benefit of the ACTS project
 * 
 * Mozilla Public License Version 2.0
 */

#include "tests/io/read_csv.hpp"

#include <cstdlib>
#include <ios>

#include <gtest/gtest.h>


// This tests the reading of the Track ML detector
TEST(ALGEBRA_PLUGIN, read_tml_detector)
{ 
    using namespace detray;
    using transform3 = __plugin::transform3;
    using surface = surface<transform3>;

    auto env_d_d = std::getenv("DETRAY_TEST_DATA_DIR");
    if (env_d_d == nullptr){
        throw std::ios_base::failure("Test data directory not found. Please set DETRAY_TEST_DATA_DIR.");
    }
    auto data_directory = std::string(env_d_d);
    auto detector = read_csv<transform3>(data_directory+std::string("/tml-detector.csv"));

    ASSERT_EQ(detector.volumes.size(), 9);

    darray<size_t, 9> expected_layers = { 7, 4, 7, 6, 4, 6, 6, 2, 6 };    
    for ( auto [ iv, volume ] : enumerate(detector.volumes)){
        ASSERT_EQ(volume.layers.size(), expected_layers[iv]);
    }
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}