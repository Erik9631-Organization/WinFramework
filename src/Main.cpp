#include "catch_amalgamated.hpp"
#include "DemoAppTest.hpp"
#include "OnMountedTest.hpp"

int main( int argc, char* argv[] )
{
    int result = Catch::Session().run(argc, argv);
    return result;
}