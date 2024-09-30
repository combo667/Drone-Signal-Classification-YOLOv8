#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION  // Disable deprecated API

#include <Python.h>
#include <patchlevel.h>
#include <pyconfig.h>
#include <pymacconfig.h>
#include <arrayobject.h>

#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <libgen.h>
#include <limits.h>
#include <cstdlib>
#include <complex>
#include <limits>
using namespace std;

/* Helper function to extract data from txt file and make a vector<complex<double >> storing the IQ values */
vector< complex <double>> load_input_data(const char* file_path){
    ifstream file(file_path);
    vector< complex <double>> data;
    string line;
    vector<double>i;
    vector<double>q;

    while (getline(file>>ws,line)) {
        string row;
        row = line;
        unsigned int value =  stoll(row);
        

        int16_t q_value = (value >> 16) & 0xFFFF;
        int16_t i_value = value & 0xFFFF;
        complex<double> iq (i_value,q_value);
        data.push_back(iq);
    }
    return data;
}

/* Helper function to convert complex vector to numpy array */
PyObject* vectorToNumpyArray(vector< complex <double>>& vec) {

    Py_Initialize();
    import_array();
    size_t vector_size = vec.size();

    npy_intp dims[] = {static_cast<npy_intp>(vector_size)};
    PyObject* npArray = PyArray_SimpleNewFromData(1, dims, NPY_CDOUBLE,(void*)vec.data());

    return npArray;
}

/* Helper Function to get current timestamp*/
void gettime()
{
    auto currtime = chrono::system_clock::now();

    time_t currtime_t = chrono::system_clock::to_time_t(currtime);

    cout<< ctime(&currtime_t)<<endl;
}


int main() {
    // Initialize the Python interpreter
    cout<<"Program started"<<endl;
    gettime();

    Py_Initialize();

    // Initialize the NumPy C API
    if (_import_array() < 0) {
        PyErr_Print();
        return 1;
    }

    PyObject* pName = PyUnicode_DecodeFSDefault("Wrapper-helper");
    PyObject* pModule = PyImport_Import(pName);
	Py_DECREF(pName);
    if (!pModule) {
        PyErr_Print();
        return 1;
    }
    cout<<"Module loaded successfully"<<endl;

    // Get references to the functions in the module
    PyObject* psave_spec = PyObject_GetAttrString(pModule, "make_spec");
    PyObject* pload_model = PyObject_GetAttrString(pModule, "load_model");

    // Put location where Model weight files are stored
    const char* location = "C:\\Users\\DELL\\Desktop\\test_cpp\\final_testing\\best.pt";
    PyObject* str_loc = PyUnicode_FromString(location);

    // Call the function to load the model, pass the weight location here
    PyObject* load_model = PyObject_CallFunctionObjArgs(pload_model,str_loc,NULL);


    cout<<"Loading the .txt file"<<endl;
    // Generate example signal in C++
    vector< complex <double>> signal = load_input_data("C:/Users/DELL/Desktop/to_swapnil/iq_data_2.txt");

    // Converting that signal from complex vector to numpy 
    PyObject* IQ =  vectorToNumpyArray(signal);
    cout<<"IQ numpy made"<<endl;

    // make and save spectrograms using the save_spec function from python module
    PyObject* pcall_save_spec = PyObject_CallFunctionObjArgs(psave_spec, IQ,load_model,NULL);
    if (!pcall_save_spec) {
        PyErr_Print();
        return 1;
    }

    if(PyUnicode_Check(pcall_save_spec))
    {
        const char* final_result = PyUnicode_AsUTF8(pcall_save_spec);
        cout<<"Printing result from CPP"<<endl;
        cout<<final_result<<endl;
    }
    cout<<"Execution completed"<<endl;
    gettime();
    

    // Cleanup
    Py_DECREF(pModule);
    Py_DECREF(IQ);
    Py_DECREF(pload_model);
    Py_DECREF(load_model);
    Py_DECREF(psave_spec);
    Py_DECREF(str_loc);
    Py_DECREF(pcall_save_spec);

    // Finalize the Python interpreter
    Py_Finalize();

    return 0;
}

