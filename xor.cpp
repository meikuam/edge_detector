#include <iostream>
#include <unistd.h>
#include <fstream>

#include "danknet.h"

using namespace std;
using namespace danknet;

bool fexists(const char *filename) {
  std::ifstream ifile(filename);
  return (bool)ifile;
}


int main(int argc, char *argv[])
{
    cout<<"start"<<endl;


        Net<double> xorNet;


        Blob<double> data("data", Shape(1, 1, 2));
        Blob<double> label("label", Shape(1, 1, 2));

        vector<Blob<double>*>    ip0_bottom,
                                 ip0_top,
                                 ip1_top,
                ip2_top,
                ip3_top,
                ip4_top,
                                 softmax_top;
        ip0_bottom.push_back(&data);
        cout<<"AddLayer"<<endl;
         double lr_rate = 0.04;

        xorNet.AddLayer(new FullyConnectedLayer<double>(200, ReLU, "ip0", ip0_bottom, ip0_top));;
        xorNet.AddLayer(new FullyConnectedLayer<double>(2, ReLU, "ip4", ip0_top, ip4_top));
        ip4_top.push_back(&label);
        xorNet.AddLayer(new LossLayer<double>("loss", ip4_top, softmax_top));

        xorNet.lr_rate(lr_rate);
        xorNet.weight_decay(0);
        xorNet.momentum(0.0);
        xorNet.gamma(0.1);
        xorNet.step_size(9900);

        xorNet.WeightsToHDF5("xorNet1000.hdf5");
        xorNet.WeightsFromHDF5("xorNet1000.hdf5");
        cout<<"---------------------Forward----------------------"<<endl;
        for(int i = 0, k = 0; i <= 1000; i++, k++) {
            if(i%2 == 0 ){
                *label.Data(0)->data(0, 0, 0) = 0;
                *label.Data(0)->data(0, 0, 1) = 1;
                if(k%2 == 0) {
                    *data.Data(0)->data(0, 0, 0) = 0;
                    *data.Data(0)->data(0, 0, 1) = 1;
                } else {
                    *data.Data(0)->data(0, 0, 0) = 1;
                    *data.Data(0)->data(0, 0, 1) = 0;
                }

            } else {
                *label.Data(0)->data(0, 0, 0) = 1;
                *label.Data(0)->data(0, 0, 1) = 0;

                if(k%2 == 0) {
                    *data.Data(0)->data(0, 0, 0) = 0;
                    *data.Data(0)->data(0, 0, 1) = 0;
                } else {
                    *data.Data(0)->data(0, 0, 0) = 1;
                    *data.Data(0)->data(0, 0, 1) = 1;
                }
            }

        xorNet.Forward();
        cout<<i<<" "<<softmax_top[0]->name()<<" "<<*softmax_top[0]->data(0, 0, 0, 0)<<endl;
        xorNet.Backward();

        if(i%1000 == 0) {
            cout<<"WeightsToHDF5"<<endl;
          xorNet.WeightsToHDF5("xorNet" + to_string(i) + ".hdf5");
        }
    }
        //test
        double loss = 0;
        for(int i = 0, k = 0; i < 100; i++, k++) {
            if(i%2 == 0 ){
                *label.Data(0)->data(0, 0, 0) = 0;
                *label.Data(0)->data(0, 0, 1) = 1;
                if(k%2 == 0) {
                    *data.Data(0)->data(0, 0, 0) = 0;
                    *data.Data(0)->data(0, 0, 1) = 1;
                } else {
                    *data.Data(0)->data(0, 0, 0) = 1;
                    *data.Data(0)->data(0, 0, 1) = 0;
                }

            } else {
                *label.Data(0)->data(0, 0, 0) = 1;
                *label.Data(0)->data(0, 0, 1) = 0;

                if(k%2 == 0) {
                    *data.Data(0)->data(0, 0, 0) = 0;
                    *data.Data(0)->data(0, 0, 1) = 0;
                } else {
                    *data.Data(0)->data(0, 0, 0) = 1;
                    *data.Data(0)->data(0, 0, 1) = 1;
                }
            }
            xorNet.Forward();
            loss += *softmax_top[0]->data(0, 0, 0, 0);
            cout<<"label: "<< *label.data(0, 0, 0, 0) <<" "<< *label.data(0, 0, 0, 1) <<endl;
            cout<<"ip4_top: "<< *ip4_top[0]->data(0, 0, 0, 0) <<" "<< *ip4_top[0]->data(0, 0, 0, 1) <<endl;
        }
        loss /= 100.0;
        cout<<"test: "<< loss <<endl;

        return 0;
}
