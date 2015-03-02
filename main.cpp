#include <iostream>

#include <vsmc/core/sampler.hpp>

#include "hdf5.h"

#include "H5Cpp.h"

using namespace std;
using namespace H5;


const string DATA_DIR = getenv("VSMC_TEST_DATA_DIR");
const H5std_string DATA_FILE( DATA_DIR + "/" + "data.h5" );




int main() {

    H5File* file = new H5File(DATA_FILE, H5F_ACC_RDONLY);
    //Group* group = new Group(file->openGroup("/basic"));
    DataSet* dataset = new DataSet(file->openDataSet("/basic/data"));
    return 0;
}