#include <iostream>

#include <vsmc/core/sampler.hpp>
#include <vsmc/core/state_tuple.hpp>

#include "hdf5.h"

#include "H5Cpp.h"

using namespace std;
using namespace H5;
using namespace vsmc;


const int NUM_PARTICLES = 1000;

const H5std_string DATA_FILE( "data/data.h5" );

const H5std_string TIME("time");
const H5std_string STATE("state");
const H5std_string OBSERVATION("observation");

struct BasicDatum {
    int time;
    int state;
    double observation;
};

class HmmCollection : public StateTuple<RowMajor, int, double> {
public:
    HmmCollection(size_type size) :
            StateTuple<RowMajor, int, double>(size),
            observations_(size)
    {}

    double log_likelihood() {return 0;}

    void read_data() {
        H5File* file = new H5File(DATA_FILE, H5F_ACC_RDONLY);
        //Group* group = new Group(file->openGroup("/basic"));
        DataSet* dataset = new DataSet(file->openDataSet("/basic/data"));
        DataSpace space = dataset->getSpace();
        int rank = space.getSimpleExtentNdims(); //should be 1 for now!
        hsize_t dims[rank];
        space.getSimpleExtentDims(dims);
        int N = dims[0];
        cout << "will read in " << N << " lines of data." << endl;
        CompType datumType(sizeof(BasicDatum));
        datumType.insertMember(TIME, HOFFSET(BasicDatum, time), PredType::NATIVE_INT);
        datumType.insertMember(STATE, HOFFSET(BasicDatum, state), PredType::NATIVE_INT);
        datumType.insertMember(OBSERVATION, HOFFSET(BasicDatum, observation), PredType::NATIVE_DOUBLE);
        BasicDatum basicData[N];
        dataset->read(basicData, datumType);
        delete dataset;
        delete file;
    }

private:
    vector<double> observations_;

};


int main() {



    Sampler<HmmCollection> sampler(NUM_PARTICLES, vsmc::Stratified, 0.5);


    return 0;
}