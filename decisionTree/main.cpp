/*
*	@author := ilgaleanos@gmail.com*
*/
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <math.h>

#include "./include/entropy.hpp"
#include "./include/splitDataSet.hpp"
#include "./include/tree.hpp"


using namespace std;


int main (void) {
        const int SIZE = 5;

        Node dataset[SIZE];
        dataset[0] = {left: true, right: true, label: "yes"};
        dataset[1] = {left: true, right: true, label: "yes"};
        dataset[2] = {left: true, right: false, label: "no"};
        dataset[3] = {left: false, right: true, label: "no"};
        dataset[4] = {left: false, right: true, label: "no"};

        printf("%0.16f\n", Entropy(dataset, SIZE));

        Tree *mDemo  = new Tree(dataset, SIZE);
        delete mDemo;

        bool side = true;
        bool value = true;
        size_t sizeOut = countDataset(dataset, SIZE, side, value );

        Reduced *out = new Reduced[sizeOut];

        splitDataSet(dataset, SIZE, side, value, out);
        for (size_t i = 0; i < sizeOut; i++) {
                printf("%i %s\n", out[i].value, out[i].label.c_str() );
        }
        return 0;
}
